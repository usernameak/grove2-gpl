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

#include "RenderPassView.h"

#include <grRenderCore/RenderInterface.h>
#include <grRenderCore/Pipeline/PipelineLibrary.h>
#include <grRenderCore/Pipeline/PipelineObject.h>
#include <grRenderCore/Mesh/InstancedMesh.h>
#include <grScene/SceneGeom.h>
#include "RenderPassShadowView.h"

using namespace grScene;
using namespace grRenderView;
using namespace grRenderView::Render;

RenderPassView::RenderPassView(gnaWeakPointer<grScene::SceneContainer> sceneContainer)
    : RenderPass(grRenderCore::g_renderInterface),
      m_sceneUniforms(gnaNew<grRenderCore::ConstantBufferT<SceneUniforms>>()),
      m_lightsUniforms(gnaNew<grRenderCore::ConstantBufferT<LightsUniforms>>()),
      m_instancedMesh(gnaNew<grRenderCore::InstancedMesh>()),
      m_sceneContainer(sceneContainer),
      m_enableShadowmapping(false) {

    m_instancedMesh->set_vertexFormat(grRenderCore::VFF_INSTANCE_TRANSFORM);

    auto rtsb = grRenderCore::g_renderInterface->createRTSBuilder();

    auto outImage = gnaNew<grImg::Image>(GTXT("/textures/__special.nxf:RenderPassView_Color"));
    outImage->loadRenderTarget(0, 0, grImg::IMGFMT_ARGB8_SRGB, 1);

    rtsb->setColorImage(0, outImage);

    auto depthTexture = gnaNew<grImg::Image>(GTXT("/textures/__special.nxf:RenderPassView_Depth"));
    depthTexture->loadRenderTarget(0, 0, grImg::IMGFMT_D24S8, 1);

    rtsb->setDepthImage(depthTexture);

    m_rts = rtsb->build();

    grRenderCore::SamplerProperties textureSamplerProps{};
    m_textureSampler = grRenderCore::g_renderInterface->findSampler(textureSamplerProps);

    grRenderCore::SamplerProperties shadowSamplerProps{
        .filteringMode = grRenderCore::SAMP_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
        .addrModeU     = grRenderCore::SAMP_ADDRESS_BORDER,
        .addrModeV     = grRenderCore::SAMP_ADDRESS_BORDER,
        .addrModeW     = grRenderCore::SAMP_ADDRESS_BORDER,
        .cmpFunc       = grRenderCore::SAMP_COMPARISON_LESS,
        .borderColor   = { 1, 1, 1, 1 },
    };
    m_shadowSampler = grRenderCore::g_renderInterface->findSampler(shadowSamplerProps);
}

RenderPassView::~RenderPassView() = default;

void RenderPassView::update(float deltaTime) {
    RenderPass::update(deltaTime);

    if (!m_sceneContainer) return;
    if (!m_cameraNode) return;

    if (m_enableShadowmapping) {
        for (gnaWeakPointer<Scene> scene : m_sceneContainer->m_scenes) {
            for (gnaWeakPointer<grScene::Light> light : scene->m_lightObjects) {
                auto [it, addedView] = m_shadowMapViews.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(light),
                    std::forward_as_tuple(this, light));
                if (addedView) {
                    dependencies.push_back(&it->second);
                }
            }
        }
    }
}

gnaPointer<grRenderCore::CmdList> RenderPassView::prepareCommandList(float deltaTime) {
    if (!m_sceneContainer) return nullptr;
    if (!m_cameraNode) return nullptr;

    auto cmdListEmitter = grRenderCore::g_renderInterface->createCmdListEmitter();

    cmdListEmitter->begin();

    cmdListEmitter->cmdBindRenderTargetSet(m_rts);

    setupCameraPerspective();

    m_sceneUniforms->data.viewProjectionMatrix =
        grRenderCore::g_renderInterface->convertProjectionMatrix(m_cameraNode->projectionMatrix, true) *
        m_cameraNode->viewMatrix;

    uint32_t lightIndex = 0;
    for (auto &lightUniforms : m_lightsUniforms->data.lights) {
        lightUniforms.type = LIGHT_TYPE_NONE;
    }

    RenderPassShadowView *currentSMView = nullptr;

    auto *instancedGeometryMaps = gtlNew InstancedGeometryMap[m_sceneContainer->m_scenes.size()];
    for (size_t i = 0; i < m_sceneContainer->m_scenes.size(); i++) {
        gnaWeakPointer<Scene> scene = m_sceneContainer->m_scenes[i];

        for (gnaWeakPointer<grScene::Geometry> geom : scene->m_geometryObjects) {
            addGeometryToInstanceList(instancedGeometryMaps[i], geom);
        }
        for (gnaWeakPointer<grScene::Light> light : scene->m_lightObjects) {
            if (lightIndex >= MAX_LIGHTS) break;

            auto &lightUniforms = m_lightsUniforms->data.lights[lightIndex++];
            if (auto dirLight = light.rttiCast2<grScene::DirectionalLight>()) {
                lightUniforms.type       = LIGHT_TYPE_DIRECTIONAL;
                lightUniforms.lightColor = { dirLight->m_color.r, dirLight->m_color.g, dirLight->m_color.b, 1.0f };
                lightUniforms.lightDir   = gtlMath2::Vector4f{
                    -(gtlMath2::Vector3f{ 0.0f, 0.0f, -1.0f } * dirLight->m_globalTransform.rotation), 1.0f
                };
                if (m_enableShadowmapping) {
                    auto it = m_shadowMapViews.find(light);
                    if (it != m_shadowMapViews.end()) {
                        // FIXME: multiple shadowmaps won't work
                        currentSMView = &it->second;
                        m_sceneUniforms->data.shadowmapMatrix =
                            grRenderCore::g_renderInterface->convertProjectionMatrix(
                                it->second.m_cameraNode->projectionMatrix, true) *
                            it->second.m_cameraNode->viewMatrix;
                    }
                }
            }
        }
    }

    m_sceneUniforms->markDirty();
    m_lightsUniforms->markDirty();
    grRenderCore::g_renderInterface->registerOrUpdateConstantBuffer(m_sceneUniforms);
    grRenderCore::g_renderInterface->registerOrUpdateConstantBuffer(m_lightsUniforms);

    m_instancedMesh->clearInstanceData();
    for (size_t i = 0; i < m_sceneContainer->m_scenes.size(); i++) {
        prepareInstanceData(instancedGeometryMaps[i]);
    }
    m_instancedMesh->markDirty();
    grRenderCore::g_renderInterface->registerOrUpdateInstancedMesh(m_instancedMesh);

    auto dim = m_rts->get_size();
    cmdListEmitter->cmdViewport(0, 0, dim.width, dim.height);
    cmdListEmitter->cmdClear(grRenderCore::CLEAR_FLAG_COLOR | grRenderCore::CLEAR_FLAG_DEPTH);
    cmdListEmitter->cmdBindConstantBuffer(0, m_sceneUniforms);
    cmdListEmitter->cmdBindConstantBuffer(2, m_lightsUniforms);
    if (currentSMView) {
        cmdListEmitter->cmdBindTexture(3, currentSMView->m_rts->getDepthImage());
    }
    for (int i = 0; i < 3; i++) {
        cmdListEmitter->cmdBindSampler(i, m_textureSampler);
    }
    cmdListEmitter->cmdBindSampler(3, m_shadowSampler);

    for (size_t i = 0; i < m_sceneContainer->m_scenes.size(); i++) {
        for (auto &[key, instanceInfo] : instancedGeometryMaps[i]) {
            drawGeometry(cmdListEmitter, key, instanceInfo);
        }
    }

    gtlDeleteArray instancedGeometryMaps;

    return cmdListEmitter->end();
}

void RenderPassView::addGeometryToInstanceList(InstancedGeometryMap &map, gnaWeakPointer<grScene::Geometry> geom) {
    if (!geom->get_mesh()) return;

    InstancingKey key{
        .mesh = geom->get_mesh()
    };

    key.mtl = geom->material;
    if (!key.mtl) {
        key.mtl = grScene::MaterialInstance::defaultMaterial;
    }

    map[key].geometries.push_back(geom);
}

void RenderPassView::prepareInstanceData(InstancedGeometryMap &map) {
    for (auto &[key, instanceInfo] : map) {
        instanceInfo.startInstance = m_instancedMesh->m_instanceCount;
        for (gnaWeakPointer<grScene::Geometry> geometry : instanceInfo.geometries) {
            auto instance        = m_instancedMesh->addInstance();
            instance.transform() = geometry->m_globalTransform.toMatrix4x3();
        }
        instanceInfo.numInstances = m_instancedMesh->m_instanceCount - instanceInfo.startInstance;
    }
}

void RenderPassView::drawGeometry(
    gnaWeakPointer<grRenderCore::CmdListEmitter> cmdList,
    const InstancingKey &instancingKey,
    const InstanceInfo &instanceInfo) {

    gnaWeakPointer<grScene::MaterialInstance> mtl = instancingKey.mtl;

    auto objectUniforms = gnaNew<grRenderCore::ConstantBufferT<ObjectUniforms>>();
    // objectUniforms->data.modelMatrix = geom->m_globalTransform.toMatrix();
    objectUniforms->data.materialColor.x = mtl->baseColor.get_red() / 255.0f;
    objectUniforms->data.materialColor.y = mtl->baseColor.get_green() / 255.0f;
    objectUniforms->data.materialColor.z = mtl->baseColor.get_blue() / 255.0f;
    objectUniforms->data.materialColor.w = mtl->baseColor.getAlpha() / 255.0f;
    objectUniforms->markDirty();

    gnaWeakPointer<grRenderCore::Mesh> mesh = instancingKey.mesh;
    if (mesh) {
        mesh->m_flags &= ~grRenderCore::Mesh::FLAG_CLEAR_ON_UPLOAD; // FIXME:

        grRenderCore::g_renderInterface->registerOrUpdateMesh(mesh);

        for (uint32_t textureSlot = 0; textureSlot < 3; textureSlot++) {
            gnaPointer<grImg::Image> texture;
            if (mtl) {
                texture = mtl->get_textureImage((grScene::MaterialInstance::TextureSlot)textureSlot);
            }
            if (texture) {
                grRenderCore::g_renderInterface->registerTexture(texture);
                cmdList->cmdBindTexture(textureSlot, texture);
            }
        }
        grRenderCore::g_renderInterface->registerOrUpdateConstantBuffer(objectUniforms);
        cmdList->cmdBindConstantBuffer(1, objectUniforms);

        if (bindPipelineFromInstKey(cmdList, instancingKey)) {
            cmdList->cmdDrawInstancedMesh(mesh, m_instancedMesh, instanceInfo.startInstance, instanceInfo.numInstances);
        }
    }
}

void RenderPassView::resize(int width, int height) {
    if (m_rts) {
        m_rts->getColorImage(0)->resize(width, height);
        m_rts->getDepthImage()->resize(width, height);
        invalidateFB();
    }
}

bool RenderPassView::bindPipelineFromInstKey(
    gnaWeakPointer<grRenderCore::CmdListEmitter> cmdList,
    const InstancingKey &key) {

    grRenderCore::PipelineKey pkey{
        .name         = key.mtl->m_pipelineName,
        .vertexFormat = (m_instancedMesh->m_vertexFormat | key.mesh->m_vertexFormat)
    };
    auto pipeline = grRenderCore::g_renderInterface->get_pipelineLibrary()->findPipeline(pkey);
    assert(pipeline);

    if (!pipeline) return false;

    cmdList->cmdBindPipeline(pipeline);
    return true;
}

void RenderPassView::set_enableShadowmapping(bool enable) {
    if (enable && !m_enableShadowmapping) {
        m_enableShadowmapping = true;
    } else if (!enable && m_enableShadowmapping) {
        m_enableShadowmapping = false;
        for (auto &[_, view] : m_shadowMapViews) {
            // not very fast but well-well.
            std::erase(dependencies, &view);
        }
        m_shadowMapViews.clear();
    }
}

void RenderPassView::setupCameraPerspective() {
    auto dim = m_rts->get_size();
    m_cameraNode->setupPerspective(dim.width, dim.height);
}
