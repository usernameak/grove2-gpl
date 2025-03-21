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

#include "UiRendererImpl.h"

#include <grRenderCore/RenderInterface.h>
#include <grRenderCore/Pipeline/PipelineLibrary.h>
#include <grRenderCore/Sampler/Sampler.h>

#include <grUi/Widget/WidgetLayout.h>
#include <grUi/Utils/UiTime.h>

static constexpr auto UI_VERTEX_FORMAT = grRenderCore::VFF_POSITION | grRenderCore::VFF_TEXCOORD | grRenderCore::VFF_COLOR;

grUiRendererImpl::grUiRendererImpl()
    : RenderPass(grRenderCore::g_renderInterface),
      m_uiGlobalUniforms(gnaNew<grRenderCore::ConstantBufferT<grUiGlobalUniforms>>()),
      m_defaultEffectCbuffer(gnaNew<grRenderCore::ConstantBufferT<grUiEffectUniforms>>()),
      m_currentEffectCbuffer(m_defaultEffectCbuffer),
      m_currentMeshIndex(0) {
    m_defaultEffectCbuffer->data.uEffectId = 0;
    m_defaultEffectCbuffer->markDirty();

    m_commandListEmitter = grRenderCore::g_renderInterface->createCmdListEmitter();

    grRenderCore::PipelineKey key{
        .name         = "UI",
        .vertexFormat = UI_VERTEX_FORMAT,
        .blendMode    = grRenderCore::BLEND_MODE_TRANSLUCENT
    };

    m_pipeline = grRenderCore::g_renderInterface->get_pipelineLibrary()->findPipeline(key);

    grRenderCore::SamplerProperties samplerProperties{};
    m_sampler = grRenderCore::g_renderInterface->findSampler(samplerProperties);

    grRenderCore::g_renderInterface->registerOrUpdateConstantBuffer(m_defaultEffectCbuffer);

    m_uiMeshes.emplace_back();
    setupMesh(0);
}

grUiRendererImpl::~grUiRendererImpl() = default;

void grUiRendererImpl::setupMesh(uint32_t index) {
    constexpr uint32_t VERTEX_CAPACITY = 1024 * 4;
    constexpr uint32_t INDEX_CAPACITY  = 1024 * 6;

    auto mesh = gnaNew<grRenderCore::Mesh>();
    mesh->set_vertexFormat(UI_VERTEX_FORMAT);
    mesh->set_indexCount(0);
    mesh->set_vertexCapacity(VERTEX_CAPACITY);
    mesh->set_indexCapacity(INDEX_CAPACITY);
    mesh->m_flags |= grRenderCore::Mesh::FLAG_DONT_GROW_CAPACITY;
    mesh->markDirty();

    grRenderCore::g_renderInterface->registerOrUpdateMesh(mesh, grRenderCore::RenderInterface::MESH_REGISTER_FLAG_ONLY_ALLOCATE);

    m_uiMeshes[index] = mesh;
}

void grUiRendererImpl::allocateNewMesh() {
    m_startIndex = 0;
    if (++m_currentMeshIndex >= m_uiMeshes.size()) {
        m_uiMeshes.emplace_back();
        setupMesh(m_currentMeshIndex);
    }
}

gnaWeakPointer<grRenderCore::Mesh> grUiRendererImpl::currentMesh() const {
    return m_uiMeshes[m_currentMeshIndex];
}

void grUiRendererImpl::finalizeCurrentMesh() {
    currentMesh()->markDirty();
    grRenderCore::g_renderInterface->registerOrUpdateMesh(currentMesh());
}

gnaPointer<grRenderCore::CmdList> grUiRendererImpl::prepareCommandList(float deltaTime) {
    m_currentMeshIndex = 0;
    for (auto mesh : m_uiMeshes) {
        mesh->set_indexCount(0);
        mesh->set_vertexCount(0);
    }

    auto dim   = m_rts->getColorImage(0)->get_size();
    int width  = dim.width;
    int height = dim.height;

    m_uiGlobalUniforms->data.projectionMatrix = grRenderCore::g_renderInterface->convertProjectionMatrix(
        gtlMath2::Matrix4x4f::ortho(0.0f, (float)width, (float)height, 0.0f, -1.f, 1.f));
    m_uiGlobalUniforms->markDirty();

    grRenderCore::g_renderInterface->registerOrUpdateConstantBuffer(m_uiGlobalUniforms);


    m_commandListEmitter->begin();

    m_commandListEmitter->cmdBindRenderTargetSet(m_rts);

    m_commandListEmitter->cmdBindPipeline(m_pipeline);
    m_commandListEmitter->cmdBindSampler(0, m_sampler);
    m_commandListEmitter->cmdBindConstantBuffer(0, m_uiGlobalUniforms);

    m_commandListEmitter->cmdViewport(0, 0, dim.width, dim.height);
    m_commandListEmitter->cmdClear(grRenderCore::CLEAR_FLAG_COLOR);

    clipStack.push_back(grRectangle{ 0, 0, width, height });
    updateClip();

    get_transform().makeIdentity();

    m_startIndex = 0;

    grUi_gTimeMs += (unsigned long long)((double)deltaTime * 1000.0f);

    if (get_renderWidget()) {
        get_renderWidget()->draw(this);
    }

    flushVertexStream();

    finalizeCurrentMesh();

    clipStack.pop_back();

    auto cmdList = m_commandListEmitter->end();

    m_currentTexture = nullptr;

    return cmdList;
}

void grUiRendererImpl::flushVertexStream() {
    if (!m_currentTexture) {
        return;
    }

    int endIndex = currentMesh()->get_currentIndex();
    if (endIndex == m_startIndex)
        return;

    grRenderCore::MeshRegion meshRegion(currentMesh(), m_startIndex, endIndex - m_startIndex);
    createDrawcallFromMeshRegion(m_currentTexture, meshRegion);
    m_startIndex = endIndex;
}

void grUiRendererImpl::drawSprite(float ox, float oy, const grUiSprite &sprite, uint32_t tint) {
    {
        if (sprite.m_texture != m_currentTexture) {
            flushVertexStream();
            m_currentTexture = sprite.m_texture;
        }

        float dx = sprite.dstWidth;
        float dy = sprite.dstHeight;

        auto v1 = currentMesh()->addVertex();
        if (!v1) goto fail;
        v1.position() = transformVertex({ ox, oy, 0.0f });
        v1.texCoord() = { sprite.minU, sprite.minV };
        v1.color()    = tint;

        auto v2 = currentMesh()->addVertex();
        if (!v2) goto fail;
        v2.position() = transformVertex({ ox, oy + dy, 0.0f });
        v2.texCoord() = { sprite.minU, sprite.maxV };
        v2.color()    = tint;

        auto v3 = currentMesh()->addVertex();
        if (!v3) goto fail;
        v3.position() = transformVertex({ ox + dx, oy + dy, 0.0f });
        v3.texCoord() = { sprite.maxU, sprite.maxV };
        v3.color()    = tint;

        auto v4 = currentMesh()->addVertex();
        if (!v4) goto fail;
        v4.position() = transformVertex({ ox + dx, oy, 0.0f });
        v4.texCoord() = { sprite.maxU, sprite.minV };
        v4.color()    = tint;

        if (!currentMesh()->addQuadIndexes(v1, v2, v3, v4)) goto fail;
    }
    return;

fail:
    flushVertexStream();
    finalizeCurrentMesh();
    allocateNewMesh();
    drawSprite(ox, oy, sprite, tint);
}

void grUiRendererImpl::set_uiDrawEffect(const grUiDrawEffectData &effectData, gtl::PooledAString shaderName) {
    flushVertexStream();

    grRenderCore::PipelineKey key{
        .name         = shaderName,
        .vertexFormat = UI_VERTEX_FORMAT,
        .blendMode    = grRenderCore::BLEND_MODE_TRANSLUCENT
    };
    m_commandListEmitter->cmdBindPipeline(grRenderCore::g_renderInterface->get_pipelineLibrary()->findPipeline(key));
    if (effectData.effectId == 0) {
        m_currentEffectCbuffer = m_defaultEffectCbuffer;
    } else {
        m_currentEffectCbuffer                     = gnaNew<grRenderCore::ConstantBufferT<grUiEffectUniforms>>();
        m_currentEffectCbuffer->data.uEffectId     = effectData.effectId;
        m_currentEffectCbuffer->data.uEffectParam1 = effectData.effectParam1;
        m_currentEffectCbuffer->markDirty();

        grRenderCore::g_renderInterface->registerOrUpdateConstantBuffer(m_currentEffectCbuffer);
    }
}

void grUiRendererImpl::pushClip(const grRectangle &rc) {
    gtlMath2::Vector2f pos1{ (float)rc.x, (float)rc.y };
    gtlMath2::Vector2f pos2{ (float)rc.width, (float)rc.height };
    pos2 += pos1;

    pos1 = get_transform() * gtlMath2::Vector3f{ pos1, 1.0f };
    pos2 = get_transform() * gtlMath2::Vector3f{ pos2, 1.0f };

    clipStack.push_back(grRectangle{
        (int)pos1.x,
        (int)pos1.y,
        (int)(pos2.x - pos1.x),
        (int)(pos2.y - pos1.y) });

    updateClip();
}

void grUiRendererImpl::popClip() {
    clipStack.pop_back();

    updateClip();
}

void grUiRendererImpl::updateClip() {
    flushVertexStream();

    grRectangle rc = clipStack.back();
    m_commandListEmitter->cmdSetClipRect(
        rc.x, rc.y,
        rc.width, rc.height);
}

void grUiRendererImpl::createDrawcallFromMeshRegion(
    gnaWeakPointer<grImg::Image> texture,
    const grRenderCore::MeshRegion &meshRegion) {

    grRenderCore::g_renderInterface->registerTexture(texture);

    m_commandListEmitter->cmdBindConstantBuffer(1, m_currentEffectCbuffer);
    m_commandListEmitter->cmdBindTexture(0, texture);

    m_commandListEmitter->cmdDrawMesh(meshRegion);
}

gtlMath2::Vector3f grUiRendererImpl::transformVertex(gtlMath2::Vector3f vertex_in) const {
    gtlMath2::Vector3f invec  = { vertex_in.x, vertex_in.y, 1.0f };
    gtlMath2::Vector2f outvec = get_transform() * invec;
    return {
        outvec.x, outvec.y, vertex_in.z
    };
}

void grUiRendererImpl::drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2, uint32_t color) {
    uint32_t initialIndexCount = currentMesh()->m_indexCount;

    {
        if (m_whiteTexture != m_currentTexture) {
            flushVertexStream();
            m_currentTexture = m_whiteTexture;
        }

        auto v1 = currentMesh()->addVertex();
        if (!v1) goto fail;
        v1.position() = transformVertex({ x0, y0, 0.0f });
        v1.texCoord() = { 0.0f, 0.0f };
        v1.color()    = color;

        auto v2 = currentMesh()->addVertex();
        if (!v2) goto fail;
        v2.position() = transformVertex({ x1, y1, 0.0f });
        v2.texCoord() = { 0.0f, 0.0f };
        v2.color()    = color;

        auto v3 = currentMesh()->addVertex();
        if (!v3) goto fail;
        v3.position() = transformVertex({ x2, y2, 0.0f });
        v3.texCoord() = { 0.0f, 0.0f };
        v3.color()    = color;

        if (!currentMesh()->addIndex(v1)) goto fail;
        if (!currentMesh()->addIndex(v2)) goto fail;
        if (!currentMesh()->addIndex(v3)) goto fail;
    }
    return;
fail:
    currentMesh()->set_indexCount(initialIndexCount);
    flushVertexStream();
    finalizeCurrentMesh();
    allocateNewMesh();
    drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

void grUiRendererImpl::swapCompositionLayers() {
    // unsupported
}

grUiSprite grUiRendererImpl::get_compositionLayerSprite(int x, int y, int width, int height) {
    // unsupported
    return grUiSprite();
}

void grUiRendererImpl::resize(int width, int height) {
    RenderPass::resize(width, height);

    m_rts->getColorImage(0)->resize(width, height);
    invalidateFB();
}
