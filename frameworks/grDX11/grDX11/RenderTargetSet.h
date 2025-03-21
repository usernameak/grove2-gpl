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

#include <grRenderCore/RenderTarget/RenderTargetSet.h>
#include <grRenderCore/RenderTypes.h>
#include <grRenderCore/CmdList/CmdConstants.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace grDX11 {
    class DX11RenderInterface;

    class RenderTargetSetBuilder : public grRenderCore::RenderTargetSetBuilder {
        DX11RenderInterface *m_renderInterface;

        gnaPointer<grImg::Image> m_colorImages[grRenderCore::RenderTargetSet::MAX_COLOR_IMAGES];
        gnaPointer<grImg::Image> m_depthImage;

    public:
        explicit RenderTargetSetBuilder(DX11RenderInterface *renderInterface);

        void setColorImage(size_t imageIndex, gnaPointer<grImg::Image> image) override;
        void setDepthImage(gnaPointer<grImg::Image> image) override;

        gnaPointer<grRenderCore::RenderTargetSet> build() override;
    };

    class RenderTargetSet final : public grRenderCore::RenderTargetSet {
        DX11RenderInterface *m_renderInterface;

        bool m_isValid;

        gnaPointer<grImg::Image> m_colorImages[grRenderCore::RenderTargetSet::MAX_COLOR_IMAGES];
        gnaPointer<grImg::Image> m_depthImage;

        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetViews[grRenderCore::RenderTargetSet::MAX_COLOR_IMAGES];
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

    public:
        explicit RenderTargetSet(
            DX11RenderInterface *renderInterface,
            gnaPointer<grImg::Image> *colorImages,
            gnaPointer<grImg::Image> depthImage);

        gnaWeakPointer<grImg::Image> getColorImage(size_t imageIndex) const override;
        gnaWeakPointer<grImg::Image> getDepthImage() const override;

        void invalidate() override;
        bool isValid() const override;
        void bind(ID3D11DeviceContext *cx);
        void clearColor(ID3D11DeviceContext *cx, unsigned int index, grRenderCore::RGBAColor color);
        void clearDepthStencil(
            ID3D11DeviceContext *cx,
            std::underlying_type_t<grRenderCore::ClearFlags> flags,
            float clearDepth,
            uint32_t clearStencil);
    };
}