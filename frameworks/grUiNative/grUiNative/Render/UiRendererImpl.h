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

#include <grUi/Render/UiRenderer.h>

#include <gtlMath2/Matrix/Matrix4x4.h>

#include <grRenderCore/RenderPass/RenderPass.h>
#include <grRenderCore/ConstantBuffer/ConstantBuffer.h>
#include <grRenderCore/Pipeline/PipelineObject.h>
#include <grRenderCore/Mesh/Mesh.h>

#include <gr2DCoords.h>

#include <deque>
#include <grRenderCore/CmdList/CmdListEmitter.h>

#pragma pack(push, 4)
struct grUiGlobalUniforms {
    gtlMath2::Matrix4x4f projectionMatrix;
};
struct grUiEffectUniforms {
    uint32_t uEffectId;
    float uEffectParam1;
    uint32_t _pad1;
    uint32_t _pad2;
};
#pragma pack(pop)

class grUiWidget;

class grUiRendererImpl : public grRenderCore::RenderPass, public grUiRenderer {
    std::deque<grRectangle> clipStack;

    std::vector<gnaPointer<grRenderCore::Mesh>> m_uiMeshes;
    uint32_t m_currentMeshIndex;

    gnaPointer<grRenderCore::Sampler> m_sampler;
    gnaPointer<grRenderCore::ConstantBufferT<grUiGlobalUniforms>> m_uiGlobalUniforms;
    gnaPointer<grRenderCore::ConstantBufferT<grUiEffectUniforms>> m_defaultEffectCbuffer;
    gnaPointer<grRenderCore::ConstantBufferT<grUiEffectUniforms>> m_currentEffectCbuffer;

    gnaPointer<grRenderCore::CmdListEmitter> m_commandListEmitter;

    gnaPointer<grRenderCore::PipelineObject> m_pipeline;

    unsigned int m_startIndex;
    gnaPointer<grImg::Image> m_currentTexture;

public:
    grUiRendererImpl();
    virtual ~grUiRendererImpl() override;

    gnaPointer<grRenderCore::CmdList> prepareCommandList(float deltaTime) override;

    void drawSprite(float ox, float oy, const grUiSprite &sprite, uint32_t tint) override;

    void set_uiDrawEffect(const grUiDrawEffectData &effectData, gtl::PooledAString shaderName) override;

    void pushClip(const grRectangle &rc) override;

    void popClip() override;
    void drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2, uint32_t color) override;

    void swapCompositionLayers() override;
    grUiSprite get_compositionLayerSprite(int x, int y, int width, int height) override;
    void resize(int width, int height) override;

private:
    void setupMesh(uint32_t index);
    void allocateNewMesh();
    gnaWeakPointer<grRenderCore::Mesh> currentMesh() const;
    void finalizeCurrentMesh();

    void flushVertexStream();

    void updateClip();

    void createDrawcallFromMeshRegion(gnaWeakPointer<grImg::Image> texture, const grRenderCore::MeshRegion &meshRegion);

    gtlMath2::Vector3f transformVertex(gtlMath2::Vector3f vertex_in) const;
};
