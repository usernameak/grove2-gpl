// GroveEngine 2
// Copyright (C) 2020-2025 usernameak
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 3, as
// published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "Image.h"

GTL_RTTI_DEFINE(grImg::Image::RendererData);
GTL_RTTI_DEFINE(grImg::Image, GTL_RTTI_INHERITS(gtlObject));
GTL_DEFINE_OBJECT_CLONE(grImg::Image);

grImg::Image::Image()
    : m_format(IMGFMT_NONE),
      m_type(TYPE_BITMAP),
      m_samplingMode(SAMP_POINT), // TODO: temporary, should become LINEAR later
      m_width(0),
      m_height(0),
      m_numMipMaps(1),
      m_bitmapData(nullptr),
      m_bitmapDataSize(0),
      m_implementationData(nullptr),
      m_rendererData(nullptr) {}

grImg::Image::Image(const gtl::String &name)
    : Image() {
    set_name(name);
}

grImg::Image::~Image() {
    gtlDelete m_rendererData;
    gtlDeleteArray m_bitmapData;
}

void grImg::Image::loadBitmapData(uint32_t width, uint32_t height, ImageFormat fmt, unsigned char *bitmapData, int numMipMaps) {
    m_type   = TYPE_BITMAP;
    m_width  = width;
    m_height = height;
    m_format = fmt;
    gtlDeleteArray m_bitmapData;
    m_bitmapData         = bitmapData;
    m_bitmapDataSize     = calculateTotalByteSize();
    m_numMipMaps         = numMipMaps;
    m_implementationData = nullptr;
}

void grImg::Image::loadBitmapDataSlow(uint32_t width, uint32_t height, ImageFormat fmt, const void *bitmapData, size_t bitmapDataSize, int numMipMaps) {
    auto *ptr = gtlNew unsigned char[bitmapDataSize];
    memcpy(ptr, bitmapData, bitmapDataSize);
    loadBitmapData(width, height, fmt, ptr, numMipMaps);
}

void grImg::Image::loadImplementationData(uint32_t width, uint32_t height, ImageFormat fmt, void *implementationData, int numMipMaps) {
    m_type   = TYPE_SPECIAL_VRAM;
    m_width  = width;
    m_height = height;
    m_format = fmt;
    gtlDeleteArray m_bitmapData;
    m_bitmapData         = nullptr;
    m_bitmapDataSize     = 0;
    m_numMipMaps         = numMipMaps;
    m_implementationData = implementationData;
}

void grImg::Image::loadRenderTarget(uint32_t width, uint32_t height, ImageFormat fmt, int numMipMaps) {
    m_type   = TYPE_RENDERTARGET;
    m_width  = width;
    m_height = height;
    m_format = fmt;
    gtlDeleteArray m_bitmapData;
    m_bitmapData         = nullptr;
    m_bitmapDataSize     = 0;
    m_numMipMaps         = numMipMaps;
    m_implementationData = nullptr;
}

void grImg::Image::loadSurface(uint32_t width, uint32_t height, ImageFormat fmt, void *externalSurface) {
    m_type   = TYPE_SURFACE;
    m_width  = width;
    m_height = height;
    m_format = fmt;
    gtlDeleteArray m_bitmapData;
    m_bitmapData         = nullptr;
    m_numMipMaps         = 1;
    m_implementationData = externalSurface;
}

void grImg::Image::resize(uint32_t width, uint32_t height) {
    if (width == m_width && height == m_height) return; // don't resize

    m_width  = width;
    m_height = height;
    if (m_rendererData) {
        m_rendererData->resize(width, height);
    }
}

void grImg::Image::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    gtlObject::cloneMembers(dest, cctx);

    gnaWeakPointer<Image> cDest = dest.cast<Image>();
    cDest->m_format             = m_format;
    cDest->m_type               = m_type;
    cDest->m_samplingMode       = m_samplingMode;
    cDest->m_width              = m_width;
    cDest->m_height             = m_height;
    cDest->m_numMipMaps         = m_numMipMaps;

    gtlDeleteArray cDest->m_bitmapData;
    if (m_bitmapData) {
        size_t size         = calculateTotalByteSize();
        cDest->m_bitmapData = gtlNew unsigned char[size];
        memcpy(cDest->m_bitmapData, m_bitmapData, size);
    } else {
        cDest->m_bitmapData = nullptr;
    }

    cDest->m_implementationData = m_implementationData;
    cDest->m_name               = m_name;
}

static grImg::ImageFormat convertFormatToColorSpace(grImg::ImageFormat fmt, grImg::Image::ColorSpace colorSpace) {
    switch (fmt) {
    case grImg::IMGFMT_ARGB8:
    case grImg::IMGFMT_ARGB8_SRGB:
        switch (colorSpace) {
        case grImg::Image::COLORSPACE_LINEAR: return grImg::IMGFMT_ARGB8;
        case grImg::Image::COLORSPACE_SRGB: return grImg::IMGFMT_ARGB8_SRGB;
        }
        break;
    case grImg::IMGFMT_DXT1:
    case grImg::IMGFMT_DXT1_SRGB:
        switch (colorSpace) {
        case grImg::Image::COLORSPACE_LINEAR: return grImg::IMGFMT_DXT1;
        case grImg::Image::COLORSPACE_SRGB: return grImg::IMGFMT_DXT1_SRGB;
        }
        break;
    case grImg::IMGFMT_DXT3:
    case grImg::IMGFMT_DXT3_SRGB:
        switch (colorSpace) {
        case grImg::Image::COLORSPACE_LINEAR: return grImg::IMGFMT_DXT3;
        case grImg::Image::COLORSPACE_SRGB: return grImg::IMGFMT_DXT3_SRGB;
        }
        break;
    case grImg::IMGFMT_DXT5:
    case grImg::IMGFMT_DXT5_SRGB:
        switch (colorSpace) {
        case grImg::Image::COLORSPACE_LINEAR: return grImg::IMGFMT_DXT5;
        case grImg::Image::COLORSPACE_SRGB: return grImg::IMGFMT_DXT5_SRGB;
        }
        break;
    default:
        return grImg::IMGFMT_NONE;
    }
    return grImg::IMGFMT_NONE;
}

bool grImg::Image::setFormatToColorSpace(ColorSpace colorSpace) {
    // reset the renderer data in case the image has already been created
    gtlDelete m_rendererData;
    m_rendererData = nullptr;

    ImageFormat fmt = convertFormatToColorSpace(m_format, colorSpace);
    if (fmt == IMGFMT_NONE) {
        return false;
    }
    m_format = fmt;
    return true;
}

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grImg::Image::serializationImpl(TSerializationInterface &proxy) {
    GNA_CHECK_STATUS(gtlObject::serializationImpl(proxy));

    GNA_CHECK_STATUS(proxy.serialize("name", m_name));
    GNA_CHECK_STATUS(proxy.serialize("type", m_type));
    GNA_CHECK_STATUS(proxy.serialize("format", m_format));
    GNA_CHECK_STATUS(proxy.serialize("samplingMode", m_samplingMode));
    GNA_CHECK_STATUS(proxy.serialize("width", m_width));
    GNA_CHECK_STATUS(proxy.serialize("height", m_height));
    GNA_CHECK_STATUS(proxy.serialize("numMipMaps", m_numMipMaps));

    if (proxy.get_direction() == nxfSerialization::SerializationDirection::WRITE) {
        if (m_bitmapData) {
            GNA_CHECK_STATUS(proxy.serializeRawData("bitmapData", m_bitmapData, m_bitmapData ? m_bitmapDataSize : 0));
        }
    } else if (proxy.get_direction() == nxfSerialization::SerializationDirection::READ) {
        gtlDeleteArray m_bitmapData;

        GNA_CHECK_STATUS(proxy.deserializeRawDataSize(m_bitmapDataSize));
        if (m_bitmapDataSize != 0) {
            m_bitmapData = gtlNew unsigned char[m_bitmapDataSize];
            GNA_CHECK_STATUS(proxy.deserializeRawData(m_bitmapData, m_bitmapDataSize));
        } else {
            m_bitmapData = nullptr;
        }
    }

    return GNA_E_OK;
}
