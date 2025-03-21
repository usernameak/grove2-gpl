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

#include "ImageRenderData.h"

#include "DX11RenderInterface.h"

grDX11::ImageRenderData::ImageRenderData(DX11RenderInterface *renderInterface, gnaWeakPointer<grImg::Image> image)
    : m_flags(0),
      m_image(std::move(image)),
      m_renderInterface(renderInterface) {
}

void grDX11::ImageRenderData::loadToGPU() {
    if (m_image->get_width() == 0 || m_image->get_height() == 0) {
        // delayed load
        m_flags |= FLAG_DELAYED_LOAD;
        return;
    }

    if (m_image->get_type() == grImg::Image::TYPE_SURFACE) {
        m_texture = (ID3D11Texture2D *)m_image->get_implementationData();
    } else {
        createTextureObject();
    }
}

void grDX11::ImageRenderData::resize(uint32_t width, uint32_t height) {
    if (m_image->get_type() == grImg::Image::TYPE_SURFACE) {
        m_texture = (ID3D11Texture2D *)m_image->get_implementationData();
    } else {
        createTextureObject();
    }
}

void grDX11::ImageRenderData::createTextureObject() {
    m_texture = nullptr;

    D3D11_TEXTURE2D_DESC desc;
    desc.Width              = m_image->get_width();
    desc.Height             = m_image->get_height();
    desc.MipLevels          = m_image->get_numMipMaps();
    desc.ArraySize          = 1;
    desc.Format             = convertFormatToDXGITypeless(m_image->get_format());
    desc.SampleDesc.Count   = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage              = m_image->get_type() == grImg::Image::TYPE_RENDERTARGET
                                ? D3D11_USAGE_DEFAULT
                                : D3D11_USAGE_IMMUTABLE;
    desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
    if (m_image->get_type() == grImg::Image::TYPE_RENDERTARGET) {
        if (isDepthStencilFormat(m_image->get_format())) {
            desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
        } else {
            desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
        }
    }
    desc.CPUAccessFlags = 0;
    desc.MiscFlags      = 0;

    int firstMipLevel = -1;
    std::vector<D3D11_SUBRESOURCE_DATA> subresourceDatas;
    if (m_image->get_type() == grImg::Image::TYPE_BITMAP) {
        subresourceDatas.resize(m_image->get_numMipMaps());

        for (int mipLevel = 0; mipLevel < m_image->get_numMipMaps(); mipLevel++) {
            subresourceDatas[mipLevel].pSysMem          = m_image->get_bitmapData(mipLevel);
            subresourceDatas[mipLevel].SysMemPitch      = m_image->get_bitmapRowStride(mipLevel);
            subresourceDatas[mipLevel].SysMemSlicePitch = 0;

            if (subresourceDatas[mipLevel].pSysMem && firstMipLevel == -1) {
                firstMipLevel = mipLevel;
            }
        }
    }
    if (firstMipLevel == -1) {
        firstMipLevel = 0;
    }

    HRESULT hres = m_renderInterface->m_device->CreateTexture2D(
        &desc,
        m_image->get_type() == grImg::Image::TYPE_RENDERTARGET
            ? nullptr
            : subresourceDatas.data(),
        &m_texture);
    if (FAILED(hres)) {
        GR_FATAL(GTXT("Could not load texture to GPU: error 0x%08x"), hres);
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
    srvDesc.Format                    = convertFormatToDXGISRV(m_image->get_format());
    srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels       = m_image->get_numMipMaps();
    srvDesc.Texture2D.MostDetailedMip = firstMipLevel;

    hres = m_renderInterface->m_device->CreateShaderResourceView(
        m_texture.Get(),
        &srvDesc,
        &m_srv);
    if (FAILED(hres)) {
        GR_FATAL(GTXT("Could not create texture SRV: error 0x%08x"), hres);
    }
}

DXGI_FORMAT grDX11::ImageRenderData::convertFormatToDXGI(uint16_t inFmt) {
    using namespace grImg;
    switch (inFmt) {
    case IMGFMT_ARGB8: return DXGI_FORMAT_B8G8R8A8_UNORM;
    case IMGFMT_D24S8: return DXGI_FORMAT_D24_UNORM_S8_UINT;
    case IMGFMT_D32: return DXGI_FORMAT_D32_FLOAT;
    case IMGFMT_DXT1: return DXGI_FORMAT_BC1_UNORM;
    case IMGFMT_DXT3: return DXGI_FORMAT_BC2_UNORM;
    case IMGFMT_DXT5: return DXGI_FORMAT_BC3_UNORM;
    case IMGFMT_ARGB8_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
    case IMGFMT_DXT1_SRGB: return DXGI_FORMAT_BC1_UNORM_SRGB;
    case IMGFMT_DXT3_SRGB: return DXGI_FORMAT_BC2_UNORM_SRGB;
    case IMGFMT_DXT5_SRGB: return DXGI_FORMAT_BC3_UNORM_SRGB;
    default:
        GR_FATAL(GTXT("Unsupported image format: 0x%04x"), inFmt);
    }
}

DXGI_FORMAT grDX11::ImageRenderData::convertFormatToDXGITypeless(uint16_t inFmt) {
    using namespace grImg;
    switch (inFmt) {
    case IMGFMT_ARGB8:
    case IMGFMT_ARGB8_SRGB: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
    case IMGFMT_D24S8: return DXGI_FORMAT_R24G8_TYPELESS;
    case IMGFMT_D32: return DXGI_FORMAT_R32_TYPELESS;
    case IMGFMT_DXT1:
    case IMGFMT_DXT1_SRGB: return DXGI_FORMAT_BC1_TYPELESS;
    case IMGFMT_DXT3:
    case IMGFMT_DXT3_SRGB: return DXGI_FORMAT_BC2_TYPELESS;
    case IMGFMT_DXT5:
    case IMGFMT_DXT5_SRGB: return DXGI_FORMAT_BC3_TYPELESS;
    default:
        GR_FATAL(GTXT("Unsupported image format: 0x%04x"), inFmt);
    }
}

DXGI_FORMAT grDX11::ImageRenderData::convertFormatToDXGISRV(uint16_t inFmt) {
    using namespace grImg;
    switch (inFmt) {
    case IMGFMT_ARGB8: return DXGI_FORMAT_B8G8R8A8_UNORM;
    case IMGFMT_ARGB8_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
    case IMGFMT_D24S8: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    case IMGFMT_D32: return DXGI_FORMAT_R32_FLOAT;
    case IMGFMT_DXT1: return DXGI_FORMAT_BC1_UNORM;
    case IMGFMT_DXT3: return DXGI_FORMAT_BC2_UNORM;
    case IMGFMT_DXT5: return DXGI_FORMAT_BC3_UNORM;
    case IMGFMT_DXT1_SRGB: return DXGI_FORMAT_BC1_UNORM_SRGB;
    case IMGFMT_DXT3_SRGB: return DXGI_FORMAT_BC2_UNORM_SRGB;
    case IMGFMT_DXT5_SRGB: return DXGI_FORMAT_BC3_UNORM_SRGB;
    default:
        GR_FATAL(GTXT("Unsupported image format: 0x%04x"), inFmt);
    }
}

bool grDX11::ImageRenderData::isDepthStencilFormat(uint16_t inFmt) {
    return inFmt == grImg::IMGFMT_D24S8 || inFmt == grImg::IMGFMT_D32;
}
