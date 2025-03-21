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

#include "ConstBuffer.h"

#include "DX11RenderInterface.h"

Microsoft::WRL::ComPtr<ID3D11Buffer> grDX11::ConstBufferPool::allocateBuffer(size_t size) {
    auto &storage = m_poolStorage[size];
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    if (storage.empty()) {
        D3D11_BUFFER_DESC bufferDesc{};
        bufferDesc.ByteWidth           = size;
        bufferDesc.Usage               = D3D11_USAGE_DYNAMIC;
        bufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
        bufferDesc.MiscFlags           = 0;
        bufferDesc.StructureByteStride = 0;

        HRESULT hres = m_renderInterface->m_device->CreateBuffer(
            &bufferDesc,
            nullptr,
            &buffer);
        if (FAILED(hres)) {
            GR_FATAL(GTXT("Could not create D3D11 const buffer; error 0x%08x"), hres);
        }
    } else {
        buffer = storage.front();
        storage.pop_front();
    }
    return buffer;
}

void grDX11::ConstBufferPool::releaseBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer> &&buffer) {
    if (!buffer) return;

    D3D11_BUFFER_DESC desc;
    buffer->GetDesc(&desc);
    m_poolStorage[desc.ByteWidth].push_back(std::move(buffer));
}

grDX11::ConstBufferRenderData::ConstBufferRenderData(
    grDX11::DX11RenderInterface *renderInterface,
    gnaWeakPointer<grRenderCore::ConstantBuffer> constantBuffer)
    : m_renderInterface(renderInterface),
      m_constantBuffer(constantBuffer) {}

grDX11::ConstBufferRenderData::~ConstBufferRenderData() {
    m_renderInterface->m_constBufferPool.releaseBuffer(std::move(m_buffer));
}

void grDX11::ConstBufferRenderData::loadToGPU() {
    if (!(m_constantBuffer->dirty))
        return;

    m_constantBuffer->dirty = false;

    void *data;
    size_t size = m_constantBuffer->get_data(&data);

    if (!m_buffer) {
        size_t alignedSize = (size + 15) / 16 * 16;
        m_buffer = m_renderInterface->m_constBufferPool.allocateBuffer(alignedSize);
    }

    D3D11_MAPPED_SUBRESOURCE mappedSubres;
    HRESULT hres = m_renderInterface->m_immediateContext->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubres);
    if (FAILED(hres)) {
        GR_FATAL(GTXT("Could not map D3D11 const buffer; error 0x%08x"), hres);
    }

    memcpy(mappedSubres.pData, data, size);

    m_renderInterface->m_immediateContext->Unmap(m_buffer.Get(), 0);
}
