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

#include "RenderTargetSet.h"

#include "DX11RenderInterface.h"
#include "ImageRenderData.h"

grDX11::RenderTargetSetBuilder::RenderTargetSetBuilder(grDX11::DX11RenderInterface *renderInterface)
    : m_renderInterface(renderInterface) {}

void grDX11::RenderTargetSetBuilder::setColorImage(size_t imageIndex, gnaPointer<grImg::Image> image) {
    m_colorImages[imageIndex] = image;
}

void grDX11::RenderTargetSetBuilder::setDepthImage(gnaPointer<grImg::Image> image) {
    m_depthImage = image;
}

gnaPointer<grRenderCore::RenderTargetSet> grDX11::RenderTargetSetBuilder::build() {
    return gnaNew<RenderTargetSet>(m_renderInterface, m_colorImages, m_depthImage);
}

grDX11::RenderTargetSet::RenderTargetSet(
    grDX11::DX11RenderInterface *renderInterface,
    gnaPointer<grImg::Image> *colorImages,
    gnaPointer<grImg::Image> depthImage)
    : m_renderInterface(renderInterface),
      m_isValid(false),
      m_depthImage(depthImage) {
    std::copy(colorImages, colorImages + grRenderCore::RenderTargetSet::MAX_COLOR_IMAGES, m_colorImages);
    invalidate();
}

gnaWeakPointer<grImg::Image> grDX11::RenderTargetSet::getColorImage(size_t imageIndex) const {
    return m_colorImages[imageIndex];
}

gnaWeakPointer<grImg::Image> grDX11::RenderTargetSet::getDepthImage() const {
    return m_depthImage;
}

void grDX11::RenderTargetSet::invalidate() {
    m_isValid = false;

    // TODO: don't recreate *all* the RTVs
    for (auto &rtv : m_renderTargetViews) {
        rtv = nullptr;
    }
    m_depthStencilView = nullptr;

    for (size_t i = 0; i < grRenderCore::RenderTargetSet::MAX_COLOR_IMAGES; i++) {
        gnaWeakPointer<grImg::Image> image = m_colorImages[i];
        if (!image) continue;

        if (image->get_width() == 0 || image->get_height() == 0) return;
    }

    if (m_depthImage) {
        if (m_depthImage->get_width() == 0 || m_depthImage->get_height() == 0) return;
    }

    for (size_t i = 0; i < grRenderCore::RenderTargetSet::MAX_COLOR_IMAGES; i++) {
        gnaWeakPointer<grImg::Image> image = m_colorImages[i];
        if (!image) continue;
        m_renderInterface->registerTexture(image);
        auto *renderData = static_cast<ImageRenderData *>(image->m_rendererData);

        D3D11_RENDER_TARGET_VIEW_DESC desc{};
        desc.Format             = ImageRenderData::convertFormatToDXGI(image->get_format());
        desc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
        desc.Texture2D.MipSlice = 0; // TODO: attachment MIP levels

        HRESULT hr = m_renderInterface->m_device->CreateRenderTargetView(
            renderData->m_texture.Get(),
            &desc,
            &m_renderTargetViews[i]);
        if (FAILED(hr)) {
            GR_FATAL(GTXT("Failed to create RTV: error 0x%08x"), hr);
        }
    }

    if (m_depthImage) {
        m_renderInterface->registerTexture(m_depthImage);
        auto *renderData = static_cast<ImageRenderData *>(m_depthImage->m_rendererData);

        D3D11_DEPTH_STENCIL_VIEW_DESC desc{};
        desc.Format             = ImageRenderData::convertFormatToDXGI(m_depthImage->get_format());
        desc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
        desc.Flags              = 0;
        desc.Texture2D.MipSlice = 0; // TODO: attachment MIP levels

        HRESULT hr = m_renderInterface->m_device->CreateDepthStencilView(
            renderData->m_texture.Get(),
            &desc,
            &m_depthStencilView);
        if (FAILED(hr)) {
            GR_FATAL(GTXT("Failed to create DSV: error 0x%08x"), hr);
        }
    }

    m_isValid = true;
}

bool grDX11::RenderTargetSet::isValid() const {
    return m_isValid;
}

void grDX11::RenderTargetSet::bind(ID3D11DeviceContext *cx) {
    cx->OMSetRenderTargets(
        grRenderCore::RenderTargetSet::MAX_COLOR_IMAGES,
        m_renderTargetViews[0].GetAddressOf(),
        m_depthStencilView.Get());
}

void grDX11::RenderTargetSet::clearColor(ID3D11DeviceContext *cx, unsigned int index, grRenderCore::RGBAColor color) {
    if (m_renderTargetViews[index]) {
        FLOAT colorRGBA[] = { color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f };
        cx->ClearRenderTargetView(m_renderTargetViews[index].Get(), colorRGBA);
    }
}

void grDX11::RenderTargetSet::clearDepthStencil(
    ID3D11DeviceContext *cx,
    std::underlying_type_t<grRenderCore::ClearFlags> flags,
    float clearDepth,
    uint32_t clearStencil) {
    if (m_depthStencilView) {
        UINT d3dClearFlags = 0;
        if (flags & grRenderCore::CLEAR_FLAG_DEPTH) {
            d3dClearFlags = D3D11_CLEAR_DEPTH;
        }
        if (flags & grRenderCore::CLEAR_FLAG_STENCIL) {
            d3dClearFlags = D3D11_CLEAR_STENCIL;
        }
        cx->ClearDepthStencilView(m_depthStencilView.Get(), d3dClearFlags, clearDepth, (UINT8) clearStencil);
    }
}
