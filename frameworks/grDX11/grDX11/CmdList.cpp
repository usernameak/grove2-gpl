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

#include "CmdList.h"

#include <grRenderCore/Mesh/Mesh.h>
#include <grRenderCore/ConstantBuffer/ConstantBuffer.h>
#include "DX11RenderInterface.h"
#include "PipelineObject.h"
#include "PipelineRenderObject.h"
#include "ImageRenderData.h"
#include "DX11MeshRenderer.h"
#include "RenderTargetSet.h"
#include "ConstBuffer.h"
#include "Sampler.h"

grDX11::CmdListEmitter::CmdListEmitter(grDX11::DX11RenderInterface *renderInterface)
    : m_renderInterface(renderInterface) {}

void grDX11::CmdListEmitter::begin() {
    HRESULT hres = m_renderInterface->m_device->CreateDeferredContext(0, &m_context);
    if (FAILED(hres)) {
        GR_FATAL(GTXT("Could not create D3D11 deferred context: error 0x%08x"), hres);
    }
}

gnaPointer<grRenderCore::CmdList> grDX11::CmdListEmitter::end() {
    Microsoft::WRL::ComPtr<ID3D11CommandList> commandList;
    HRESULT hres = m_context->FinishCommandList(FALSE, &commandList);
    if (FAILED(hres)) {
        GR_FATAL(GTXT("Could not finish D3D11 command list: error 0x%08x"), hres);
    }
    m_context         = nullptr;
    m_currentPipeline = nullptr;
    m_currentRTS      = nullptr;

    return gnaNew<CmdList>(m_renderInterface, commandList, std::move(m_heldReferences));
}

void grDX11::CmdListEmitter::cmdClear(
    std::underlying_type_t<grRenderCore::ClearFlags> flags,
    grRenderCore::RGBAColor clearColor,
    float clearDepth,
    uint32_t clearStencil) {

    if (flags & grRenderCore::CLEAR_FLAG_COLOR) {
        m_currentRTS.cast<RenderTargetSet>()->clearColor(m_context.Get(), 0, clearColor);
    }
    if (flags & (grRenderCore::CLEAR_FLAG_DEPTH | grRenderCore::CLEAR_FLAG_STENCIL)) {
        m_currentRTS.cast<RenderTargetSet>()->clearDepthStencil(m_context.Get(), flags, clearDepth, clearStencil);
    }
}

void grDX11::CmdListEmitter::cmdBindRenderTargetSet(gnaWeakPointer<grRenderCore::RenderTargetSet> rts) {
    rts.cast<RenderTargetSet>()->bind(m_context.Get());
    m_currentRTS = rts;
}

void grDX11::CmdListEmitter::cmdViewport(int x, int y, int width, int height) {
    D3D11_VIEWPORT viewport{ (float)x, (float)y, (float)width, (float)height, 0.0f, 1.0f };
    m_context->RSSetViewports(1, &viewport);
}

void grDX11::CmdListEmitter::cmdSetClipRect(int x, int y, int width, int height) {
    D3D11_RECT rect{ x, y, x + width, y + height };
    m_context->RSSetScissorRects(1, &rect);
}

void grDX11::CmdListEmitter::cmdSetDepthBias(int32_t depthBias, float depthBiasClamp, float depthBiasSlopeScale) {
    m_currentRasterizerStateInfo.depthBias = depthBias;
    m_currentRasterizerStateInfo.depthBiasClamp = depthBiasClamp;
    m_currentRasterizerStateInfo.depthBiasSlopeScale = depthBiasSlopeScale;

    m_currentRasterizerState = nullptr;
}

void grDX11::CmdListEmitter::cmdBindPipeline(gnaWeakPointer<grRenderCore::PipelineObject> pipeline) {
    auto *pipelineRenderObject = pipeline.cast<PipelineObject>()->get_renderObject();

    m_currentRasterizerStateInfo = pipelineRenderObject->getDefaultRasterizerStateInfo();
    m_currentRasterizerState     = nullptr;

    pipelineRenderObject->bind(m_context.Get());
    m_currentPipeline = pipeline;
}

void grDX11::CmdListEmitter::cmdBindSampler(uint8_t slot, gnaWeakPointer<grRenderCore::Sampler> sampler) {
    m_context->PSSetSamplers(slot, 1, sampler.cast<Sampler>()->m_samplerState.GetAddressOf());
}

void grDX11::CmdListEmitter::cmdBindTexture(uint8_t slot, gnaWeakPointer<grImg::Image> image) {
    m_context->PSSetShaderResources(slot, 1, static_cast<ImageRenderData *>(image->m_rendererData)->m_srv.GetAddressOf());
}

void grDX11::CmdListEmitter::cmdBindConstantBuffer(uint8_t slot, gnaWeakPointer<grRenderCore::ConstantBuffer> cb) {
    auto rd = cb->m_rendererData.cast<ConstBufferRenderData>();
    m_context->VSSetConstantBuffers(slot, 1, rd->m_buffer.GetAddressOf());
    m_context->PSSetConstantBuffers(slot, 1, rd->m_buffer.GetAddressOf());
    m_heldReferences.push_back(cb);
}

void grDX11::CmdListEmitter::cmdDrawMesh(grRenderCore::MeshRegion meshRegion) {
    assert(m_currentPipeline);
    assert(m_currentPipeline.cast<PipelineObject>()->get_vertexFormat() == meshRegion.mesh->m_vertexFormat);
    if (m_currentPipeline.cast<PipelineObject>()->get_vertexFormat() != meshRegion.mesh->m_vertexFormat) return;

    auto meshRenderer = meshRegion.mesh->renderer.cast<MeshRenderer>();
    assert(meshRenderer);

    uint32_t vertexCount = meshRegion.regionVertexCount;
    if (vertexCount == grRenderCore::MeshRegion::INVALID_OFFSET) {
        vertexCount = meshRenderer->m_drawVertexCount;
    }

    preDraw();

    meshRenderer->drawRegion(m_context.Get(), meshRegion.regionStartOffset, vertexCount);
}

void grDX11::CmdListEmitter::cmdDrawInstancedMesh(
    gnaWeakPointer<grRenderCore::Mesh> mesh,
    gnaWeakPointer<grRenderCore::InstancedMesh> instancedMesh,
    uint32_t startInstance,
    uint32_t numInstances) {

    assert(m_currentPipeline);
    assert(m_currentPipeline.cast<PipelineObject>()->get_vertexFormat() == (instancedMesh->m_vertexFormat | mesh->m_vertexFormat));
    if (m_currentPipeline.cast<PipelineObject>()->get_vertexFormat() != (instancedMesh->m_vertexFormat | mesh->m_vertexFormat)) return;

    auto meshRenderer = instancedMesh->renderer.cast<InstancedMeshRenderer>();
    assert(meshRenderer);

    preDraw();

    meshRenderer->draw(m_context.Get(), mesh, startInstance, numInstances);

    m_heldReferences.push_back(instancedMesh);
}

void grDX11::CmdListEmitter::preDraw() {
    if (!m_currentRasterizerState) {
        gnaStatus status = m_renderInterface->m_rasterizerStateCache.findRasterizerState(
            m_currentRasterizerStateInfo,
            m_currentRasterizerState);

        m_context->RSSetState(m_currentRasterizerState.Get());

        if (!status) {
            GR_WARNING(GTXT("Rasterizer state lookup failed: %ls"), status.get_errorMessage());
        }
    }
}

grDX11::CmdList::CmdList(
    grDX11::DX11RenderInterface *renderInterface,
    Microsoft::WRL::ComPtr<ID3D11CommandList> cmdList,
    std::vector<gnaPointer<gtlRcObject>> &&heldReferences)
    : m_renderInterface(renderInterface),
      m_cmdList(cmdList),
      m_heldReferences(std::move(heldReferences)) {
}

void grDX11::CmdList::execute() {
    m_renderInterface->m_immediateContext->ExecuteCommandList(m_cmdList.Get(), FALSE);
}
