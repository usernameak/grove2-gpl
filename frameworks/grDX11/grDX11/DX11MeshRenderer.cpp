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

#include "DX11MeshRenderer.h"

#include "DX11RenderInterface.h"
#include "PipelineObject.h"

grDX11::MeshRenderer::MeshRenderer(DX11RenderInterface *renderInterface, gnaWeakPointer<grRenderCore::Mesh> mesh)
    : m_renderInterface(renderInterface),
      m_mesh(mesh),
      m_allocatedVertexBufferSize(0),
      m_allocatedIndexBufferSize(0) {}

void grDX11::MeshRenderer::loadToGPU(uint32_t flags) {
    assert(m_mesh);

    if (!(m_mesh->m_flags & grRenderCore::Mesh::FLAG_DIRTY))
        return;

    bool allocateOnly = flags & grRenderCore::RenderInterface::MESH_REGISTER_FLAG_ONLY_ALLOCATE;

    if (!allocateOnly) {
        m_mesh->m_flags &= ~grRenderCore::Mesh::FLAG_DIRTY;
    }

    m_drawVertexCount = m_mesh->m_indexCount != grRenderCore::Mesh::INVALID_INDEX_COUNT
                          ? m_mesh->m_indexCount
                          : m_mesh->m_vertexCount;

    // if (m_drawVertexCount <= 0) {
    //    return;
    // }

    uploadSingleBuffer(
        m_vertexBuffer,
        false,
        allocateOnly ? nullptr : m_mesh->m_geometryDataBuffer,
        m_mesh->m_vertexFormatInfo.m_stride);

    if (m_mesh->m_indexCount != grRenderCore::Mesh::INVALID_INDEX_COUNT) {
        uploadSingleBuffer(
            m_indexBuffer,
            true,
            allocateOnly ? nullptr : m_mesh->m_indices,
            sizeof(*m_mesh->m_indices));
    }

    if (m_mesh->m_primitiveType == grRenderCore::Mesh::TYPE_TRIANGLES) {
        m_primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    } else if (m_mesh->m_primitiveType == grRenderCore::Mesh::TYPE_LINES) {
        m_primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
    } else {
        assert(false);
    }

    if (!allocateOnly && (m_mesh->m_flags & grRenderCore::Mesh::FLAG_CLEAR_ON_UPLOAD)) {
        if (m_mesh->m_flags & grRenderCore::Mesh::FLAG_IMMUTABLE) {
            m_mesh->deallocateMeshData();
        } else {
            m_mesh->clearMeshData();
        }
    }
}

void grDX11::MeshRenderer::uploadSingleBuffer(
    Microsoft::WRL::ComPtr<ID3D11Buffer> &vbo,
    bool isIndex,
    void *arr,
    size_t elementSize) {

    bool immutable     = m_mesh->m_flags & grRenderCore::Mesh::FLAG_IMMUTABLE;
    size_t oldCapacity = isIndex ? m_allocatedIndexBufferSize : m_allocatedVertexBufferSize;
    size_t capacity    = isIndex ? m_mesh->m_indexCapacity : m_mesh->m_vertexCapacity;
    size_t count       = isIndex ? m_mesh->m_indexCount : m_mesh->m_vertexCount;

    size_t totalCapacity = capacity * elementSize;

    if (totalCapacity == 0) {
        if (isIndex) {
            m_allocatedIndexBufferSize = 0;
        } else {
            m_allocatedVertexBufferSize = 0;
        }
        vbo = nullptr;
        return;
    }

    if (!vbo || (capacity != oldCapacity)) {
        D3D11_BUFFER_DESC bufferDesc{};
        // TODO: should we use count if it's immutable? that would make sense;
        //  also see below for m_allocatedIndexBufferSize/m_allocatedVertexBufferSize
        bufferDesc.ByteWidth           = totalCapacity;
        bufferDesc.Usage               = immutable ? D3D11_USAGE_IMMUTABLE : D3D11_USAGE_DYNAMIC;
        bufferDesc.BindFlags           = isIndex ? D3D11_BIND_INDEX_BUFFER : D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags      = immutable ? 0 : D3D11_CPU_ACCESS_WRITE;
        bufferDesc.MiscFlags           = 0;
        bufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA immutableData{};
        if (immutable) {
            assert(arr);
            immutableData.pSysMem          = arr;
            immutableData.SysMemPitch      = 0;
            immutableData.SysMemSlicePitch = 0;
        }

        HRESULT hres = m_renderInterface->m_device->CreateBuffer(
            &bufferDesc,
            immutable ? &immutableData : nullptr,
            &vbo);
        if (FAILED(hres)) {
            GR_FATAL(GTXT("D3D11 CreateBuffer failed; error 0x%08x"), hres);
        }

        if (isIndex) {
            m_allocatedIndexBufferSize = capacity;
        } else {
            m_allocatedVertexBufferSize = capacity;
        }
    }

    if (arr && !immutable) {
        // TODO: if we want async, we might need to add deferred upload context later
        D3D11_MAPPED_SUBRESOURCE mappedSubres{};
        HRESULT hres = m_renderInterface->m_immediateContext->Map(
            vbo.Get(), 0,
            D3D11_MAP_WRITE_DISCARD,
            0,
            &mappedSubres);
        if (FAILED(hres)) {
            GR_FATAL(GTXT("D3D11 buffer Map failed; error 0x%08x"), hres);
        }

        memcpy(mappedSubres.pData, arr, totalCapacity);

        m_renderInterface->m_immediateContext->Unmap(vbo.Get(), 0);
    }
}

void grDX11::MeshRenderer::drawRegion(
    ID3D11DeviceContext *cx,
    uint32_t start,
    uint32_t count) {

    UINT stride = m_mesh->m_vertexFormatInfo.m_stride;
    UINT offset = 0;
    cx->IASetPrimitiveTopology(m_primitiveTopology);
    cx->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
    cx->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

    if (m_mesh->m_indexCount == grRenderCore::Mesh::INVALID_INDEX_COUNT) {
        cx->Draw(count, start);
    } else {
        cx->DrawIndexed(count, start, 0);
    }
}

grDX11::InstancedMeshRenderer::InstancedMeshRenderer(
    grDX11::DX11RenderInterface *renderInterface,
    gnaWeakPointer<grRenderCore::InstancedMesh> mesh)
    : m_renderInterface(renderInterface),
      m_instancedMesh(mesh),
      m_allocatedInstanceBufferSize(0) {
}

void grDX11::InstancedMeshRenderer::loadToGPU(uint32_t flags) {
    assert(m_instancedMesh);

    if (!(m_instancedMesh->m_flags & grRenderCore::Mesh::FLAG_DIRTY))
        return;

    bool allocateOnly = flags & grRenderCore::RenderInterface::MESH_REGISTER_FLAG_ONLY_ALLOCATE;

    if (!allocateOnly) {
        m_instancedMesh->m_flags &= ~grRenderCore::Mesh::FLAG_DIRTY;
    }

    m_drawInstanceCount = m_instancedMesh->m_instanceCount;

    uploadSingleBuffer(
        m_instanceBuffer,
        allocateOnly ? nullptr : m_instancedMesh->m_instanceDataBuffer,
        m_instancedMesh->m_instanceVertexFormatInfo.m_stride);

    if (!allocateOnly && (m_instancedMesh->m_flags & grRenderCore::Mesh::FLAG_CLEAR_ON_UPLOAD)) {
        if (m_instancedMesh->m_flags & grRenderCore::Mesh::FLAG_IMMUTABLE) {
            m_instancedMesh->deallocateInstanceData();
        } else {
            m_instancedMesh->clearInstanceData();
        }
    }
}

void grDX11::InstancedMeshRenderer::draw(
    ID3D11DeviceContext *cx,
    gnaWeakPointer<grRenderCore::Mesh> mesh,
    uint32_t startInstance,
    uint32_t numInstances) {

    auto meshRenderer = mesh->renderer.cast<MeshRenderer>();

    UINT stride         = mesh->m_vertexFormatInfo.m_stride;
    UINT instanceStride = m_instancedMesh->m_instanceVertexFormatInfo.m_stride;
    UINT offset         = 0;
    cx->IASetPrimitiveTopology(meshRenderer->m_primitiveTopology);
    cx->IASetVertexBuffers(0, 1, meshRenderer->m_vertexBuffer.GetAddressOf(), &stride, &offset);
    cx->IASetVertexBuffers(1, 1, m_instanceBuffer.GetAddressOf(), &instanceStride, &offset);
    cx->IASetIndexBuffer(meshRenderer->m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

    if (mesh->m_indexCount == grRenderCore::Mesh::INVALID_INDEX_COUNT) {
        cx->DrawInstanced(meshRenderer->m_drawVertexCount, numInstances, 0, startInstance);
    } else {
        cx->DrawIndexedInstanced(meshRenderer->m_drawVertexCount, numInstances, 0, 0, startInstance);
    }
}

void grDX11::InstancedMeshRenderer::uploadSingleBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer> &vbo, void *arr, size_t elementSize) {
    bool immutable     = m_instancedMesh->m_flags & grRenderCore::Mesh::FLAG_IMMUTABLE;
    size_t oldCapacity = m_allocatedInstanceBufferSize;
    size_t capacity    = m_instancedMesh->m_instanceCapacity;
    size_t count       = m_instancedMesh->m_instanceCount;

    size_t totalCapacity = capacity * elementSize;

    if (totalCapacity == 0) {
        m_allocatedInstanceBufferSize = 0;
        vbo                           = nullptr;
        return;
    }

    if (!vbo || (capacity != oldCapacity)) {
        D3D11_BUFFER_DESC bufferDesc{};
        // TODO: should we use count if it's immutable? that would make sense;
        //  also see below for m_allocatedIndexBufferSize/m_allocatedVertexBufferSize
        bufferDesc.ByteWidth           = totalCapacity;
        bufferDesc.Usage               = immutable ? D3D11_USAGE_IMMUTABLE : D3D11_USAGE_DYNAMIC;
        bufferDesc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags      = immutable ? 0 : D3D11_CPU_ACCESS_WRITE;
        bufferDesc.MiscFlags           = 0;
        bufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA immutableData{};
        if (immutable) {
            assert(arr);
            immutableData.pSysMem          = arr;
            immutableData.SysMemPitch      = 0;
            immutableData.SysMemSlicePitch = 0;
        }

        HRESULT hres = m_renderInterface->m_device->CreateBuffer(
            &bufferDesc,
            immutable ? &immutableData : nullptr,
            &vbo);
        if (FAILED(hres)) {
            GR_FATAL(GTXT("D3D11 CreateBuffer failed; error 0x%08x"), hres);
        }

        m_allocatedInstanceBufferSize = capacity;
    }

    if (arr && !immutable) {
        // TODO: if we want async, we might need to add deferred upload context later
        D3D11_MAPPED_SUBRESOURCE mappedSubres{};
        HRESULT hres = m_renderInterface->m_immediateContext->Map(
            vbo.Get(), 0,
            D3D11_MAP_WRITE_DISCARD,
            0,
            &mappedSubres);
        if (FAILED(hres)) {
            GR_FATAL(GTXT("D3D11 buffer Map failed; error 0x%08x"), hres);
        }

        memcpy(mappedSubres.pData, arr, totalCapacity);

        m_renderInterface->m_immediateContext->Unmap(vbo.Get(), 0);
    }
}
