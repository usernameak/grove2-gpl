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

#pragma once

#include <cstdint>
#include <gr2DCoords.h>
#include <gtlUtil/Logging.h>
#include <gtlString/String.h>
#include <gtlObject/Object.h>

#include "ImgDLL.h"

namespace grImg {
    enum ImageFormat : uint16_t {
        IMGFMT_NONE = 0,

        IMGFMT_ARGB8 = 1,
        IMGFMT_D24S8 = 2,
        IMGFMT_D32   = 3,
        IMGFMT_DXT1  = 4,
        IMGFMT_DXT3  = 5,
        IMGFMT_DXT5  = 6,
        IMGFMT_R32F  = 7,
        IMGFMT_XRGB8 = 8,

        IMGFMT_ARGB8_SRGB = 9,
        IMGFMT_DXT1_SRGB  = 10,
        IMGFMT_DXT3_SRGB  = 11,
        IMGFMT_DXT5_SRGB  = 12,

        IMGFMT_MAX_VALID_RAM_TYPE = 256,

        // special VRAM-only image formats; cannot be decoded
        IMGFMT_BACKBUFFER = 4096,
        IMGFMT_EXTERNAL   = 4097
    };

    class GR_IMG_DLLIMPEXP Image : public gtlObject {
    public:
        enum ImageType : uint8_t {
            TYPE_BITMAP,
            TYPE_RENDERTARGET,
            TYPE_SURFACE,
            TYPE_SPECIAL_VRAM
        };

        enum SamplingMode : uint8_t {
            SAMP_POINT,
            SAMP_LINEAR,
        };

        enum ColorSpace : uint8_t {
            COLORSPACE_LINEAR,
            COLORSPACE_SRGB
        };

    private:
        gtl::String m_name;

        ImageFormat m_format;
        ImageType m_type;

    public:
        SamplingMode m_samplingMode;

    private:
        uint32_t m_width, m_height;
        uint32_t m_numMipMaps;
        unsigned char *m_bitmapData;
        size_t m_bitmapDataSize;

        void *m_implementationData;

    public:
        GTL_DECLARE_OBJECT_CLONE;
        GTL_RTTI_DECLARE();
        NXF_SERIALIZABLE_DECLARE();

        class GR_IMG_DLLIMPEXP RendererData {
        public:
            GTL_RTTI_DECLARE();

            virtual ~RendererData() = default;

            // called *after* the Image object gets new size.
            virtual void resize(uint32_t width, uint32_t height) = 0;
        };

        Image();
        explicit Image(const gtl::String &name);
        virtual ~Image() override;

        void set_name(const gtl::String &name) {
            m_name = name;
        }

        const gtl::String &get_name() const {
            return m_name;
        }

        uint32_t get_width() const {
            return m_width;
        }

        uint32_t get_height() const {
            return m_height;
        }

        grDimension get_size() const {
            return { (int)get_width(), (int)get_height() };
        }

        ImageType get_type() const {
            return m_type;
        }

        const unsigned char *get_bitmapData(int mipmap = 0) const {
            if (mipmap >= m_numMipMaps) {
                return nullptr;
            }
            return m_bitmapData + calculateMipOffset(mipmap);
        }

        ImageFormat get_format() const {
            return m_format;
        }

        int get_numMipMaps() const {
            return m_numMipMaps;
        }

        void *get_implementationData() const {
            return m_implementationData;
        }

        /**
         * Loads (possibly MIP-mapped) bitmap data into the image.
         * Mipmaps must be stored sequentially in the bitmapData.
         * @param width - width of the bitmap
         * @param height - height of the bitmap
         * @param fmt - format of the bitmap data
         * @param bitmapData - bitmap data, must be created with gtlNew[].
         * Note that this function takes ownership of the data.
         * @param numMipMaps - number of mipmaps in bitmap;
         */
        void loadBitmapData(uint32_t width, uint32_t height, ImageFormat fmt, unsigned char *bitmapData, int numMipMaps = 1);

        /**
         * what is this doing here? bindings brought it here.
         * TODO: remove when proper bindings are implemented
         */
        void loadBitmapDataSlow(uint32_t width, uint32_t height, ImageFormat fmt, const void *bitmapData, size_t bitmapDataSize, int numMipMaps = 1);

        void loadImplementationData(uint32_t width, uint32_t height, ImageFormat fmt, void *implementationData, int numMipMaps = 1);

        void loadRenderTarget(uint32_t width, uint32_t height, ImageFormat fmt, int numMipMaps = 1);

        void loadSurface(uint32_t width, uint32_t height, ImageFormat fmt, void *externalSurface = nullptr);

        void resize(uint32_t width, uint32_t height);

        uint32_t calculateMipWidth(int mipLevel) const {
            uint32_t mipWidth = m_width >> mipLevel;
            if (mipWidth == 0) mipWidth = 1;
            return mipWidth;
        }

        uint32_t calculateMipHeight(int mipLevel) const {
            uint32_t mipHeight = m_height >> mipLevel;
            if (mipHeight == 0) mipHeight = 1;
            return mipHeight;
        }

        static size_t calculateByteSize(ImageFormat format, uint32_t width, uint32_t height, int mipLevel = 0) {
            width >>= mipLevel;
            height >>= mipLevel;
            if (width == 0) width = 1;
            if (height == 0) height = 1;

            if (format == IMGFMT_ARGB8 ||
                format == IMGFMT_XRGB8 ||
                format == IMGFMT_R32F ||
                format == IMGFMT_D24S8 ||
                format == IMGFMT_ARGB8_SRGB) {

                return width * height * 4;
            } else if (
                format == IMGFMT_DXT1 ||
                format == IMGFMT_DXT3 ||
                format == IMGFMT_DXT5 ||
                format == IMGFMT_DXT1_SRGB ||
                format == IMGFMT_DXT3_SRGB ||
                format == IMGFMT_DXT5_SRGB) {

                uint32_t blocksWidth  = (width + 3) / 4;
                uint32_t blocksHeight = (height + 3) / 4;

                return blocksWidth * blocksHeight * ((format == IMGFMT_DXT1 || format == IMGFMT_DXT1_SRGB) ? 8 : 16);
            } else {
                GR_FATAL(GTXT("Unsupported image format: 0x%04x"), format);
            }
        }

        size_t calculateMipByteSize(int mipLevel) const {
            return calculateByteSize(m_format, m_width, m_height, mipLevel);
        }

        size_t calculateTotalBitmapSize() const {
            size_t value = 0;
            for (int i = 0; i < m_numMipMaps; i++) {
                value += calculateMipByteSize(i);
            }
            return value;
        }

        size_t calculateMipOffset(int mipLevel) const {
            size_t offset = 0;
            for (int i = 0; i < mipLevel; i++) {
                offset += calculateMipByteSize(i);
            }
            return offset;
        }

        size_t get_bitmapRowStride(int mipLevel) const {
            uint32_t width = calculateMipWidth(mipLevel);
            if (m_format == IMGFMT_ARGB8 ||
                m_format == IMGFMT_ARGB8_SRGB ||
                m_format == IMGFMT_XRGB8 ||
                m_format == IMGFMT_R32F ||
                m_format == IMGFMT_D24S8) {

                return width * 4;
            } else if (
                m_format == IMGFMT_DXT1 ||
                m_format == IMGFMT_DXT3 ||
                m_format == IMGFMT_DXT5 ||
                m_format == IMGFMT_DXT1_SRGB ||
                m_format == IMGFMT_DXT3_SRGB ||
                m_format == IMGFMT_DXT5_SRGB) {

                uint32_t blocksWidth = (width + 3) / 4;
                return blocksWidth * ((m_format == IMGFMT_DXT1 || m_format == IMGFMT_DXT1_SRGB) ? 8 : 16);
            } else {
                GR_FATAL(GTXT("Unsupported image format: 0x%04x"), m_format);
            }
        }

        /**
         * Sets the image format corresponding to the given color space
         * @param colorSpace the colorspace
         * @return whether this format supports color management
         */
        bool setFormatToColorSpace(ColorSpace colorSpace);

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy);

        RendererData *m_rendererData;

    private:
        size_t calculateTotalByteSize() const {
            return calculateMipOffset(get_numMipMaps());
        }
    };
}
