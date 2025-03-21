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

#include <grImg/Image.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace grDX11 {
    class DX11RenderInterface;

    class ImageRenderData : public grImg::Image::RendererData {
        enum : uint8_t {
            FLAG_DELAYED_LOAD = GTL_BIT(0),
        };

        uint8_t m_flags;
        DX11RenderInterface *m_renderInterface;

    public:
        const gnaWeakPointer<grImg::Image> m_image;

        explicit ImageRenderData(DX11RenderInterface *renderInterface, gnaWeakPointer<grImg::Image> image);

        void loadToGPU();
        void resize(uint32_t width, uint32_t height) override;

        static DXGI_FORMAT convertFormatToDXGI(uint16_t inFmt);
        static DXGI_FORMAT convertFormatToDXGITypeless(uint16_t inFmt);
        static DXGI_FORMAT convertFormatToDXGISRV(uint16_t inFmt);
        static bool isDepthStencilFormat(uint16_t inFmt);

        Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv;

    private:
        void createTextureObject();
    };
}