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

#include <grRenderCore/ConstantBuffer/ConstantBuffer.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace grDX11 {
    class DX11RenderInterface;

    class ConstBufferPool {
        std::unordered_map<size_t, std::list<Microsoft::WRL::ComPtr<ID3D11Buffer>>> m_poolStorage;

        DX11RenderInterface *m_renderInterface;

    public:
        ConstBufferPool(DX11RenderInterface *renderInterface)
            : m_renderInterface(renderInterface) {}

        Microsoft::WRL::ComPtr<ID3D11Buffer> allocateBuffer(size_t size);
        void releaseBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer> &&buffer);
    };

    class ConstBufferRenderData : public grRenderCore::ConstantBufferRenderData {
        DX11RenderInterface *m_renderInterface;
        gnaWeakPointer<grRenderCore::ConstantBuffer> m_constantBuffer;

    public:
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

        ConstBufferRenderData(DX11RenderInterface *renderInterface, gnaWeakPointer<grRenderCore::ConstantBuffer> constantBuffer);
        ~ConstBufferRenderData();

        void loadToGPU();
    };
}