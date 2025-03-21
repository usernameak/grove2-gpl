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

#include "RenderPassShadowView.h"

#include <grRenderCore/Pipeline/PipelineLibrary.h>
#include <grRenderCore/RenderInterface.h>
#include <grScene/Material/MaterialInstance.h>

grRenderView::Render::RenderPassShadowView::RenderPassShadowView(
    RenderPassView *parent,
    gnaPointer<grScene::Light> light)
    : m_light(std::move(light)) {

    m_cameraNode = gnaNew<grScene::Camera>();

    m_sceneContainer = parent->m_sceneContainer;

    auto rtsb = m_renderInterface->createRTSBuilder();

    auto depthTexture = gnaNew<grImg::Image>(GTXT("/textures/__special.nxf:RenderPassShadowView_Depth"));
    depthTexture->loadRenderTarget(1024, 1024, grImg::IMGFMT_D32, 1);
    rtsb->setDepthImage(depthTexture);

    m_rts = rtsb->build();
}

void grRenderView::Render::RenderPassShadowView::update(float deltaTime) {
    RenderPassView::update(deltaTime);

    m_bbox = { 0, 0 };
    for (gnaWeakPointer<grScene::Scene> scene : m_sceneContainer->m_scenes) {
        m_bbox.merge(scene->m_rootNode->m_globalBounds);
    }

    m_cameraNode->m_sourceTransform.translation = (m_bbox.min + m_bbox.max) * .5f;
    m_cameraNode->m_sourceTransform.scale       = 1.0f;
    m_cameraNode->m_sourceTransform.rotation    = m_light->m_globalTransform.rotation *
                                               gtlMath2::Quaternionf::rotationY(gtlMath2::pi<float> * .5f);

    m_cameraNode->update(deltaTime);
    m_cameraNode->postUpdate(deltaTime);
}

bool grRenderView::Render::RenderPassShadowView::bindPipelineFromInstKey(
    gnaWeakPointer<grRenderCore::CmdListEmitter> cmdList,
    const InstancingKey &key) {

    if (key.mtl->m_shadowMapPipelineName.empty()) return false;

    grRenderCore::PipelineKey pkey{
        .name         = key.mtl->m_shadowMapPipelineName,
        .vertexFormat = (m_instancedMesh->m_vertexFormat | key.mesh->m_vertexFormat)
    };
    auto pipeline = grRenderCore::g_renderInterface->get_pipelineLibrary()->findPipeline(pkey);
    if (!pipeline) return false;

    cmdList->cmdBindPipeline(pipeline);
    cmdList->cmdSetDepthBias(10000, 0.0f, 1.5f);

    return true;
}

void grRenderView::Render::RenderPassShadowView::setupCameraPerspective() {
    gtlMath2::Vector3f bboxCenter = (m_bbox.min + m_bbox.max) * .5f;

    gtlMath2::Quaternionf invCameraRot = m_cameraNode->m_sourceTransform.rotation;
    invCameraRot.inverse();

    gtlMath2::AABB centeredBbox{
        m_bbox.min - bboxCenter,
        m_bbox.max - bboxCenter
    };

    gtlMath2::Vector3f corners[] = {
        { centeredBbox.min.x, centeredBbox.min.y, centeredBbox.min.z },
        { centeredBbox.max.x, centeredBbox.min.y, centeredBbox.min.z },
        { centeredBbox.min.x, centeredBbox.max.y, centeredBbox.min.z },
        { centeredBbox.max.x, centeredBbox.max.y, centeredBbox.min.z },
        { centeredBbox.min.x, centeredBbox.min.y, centeredBbox.max.z },
        { centeredBbox.max.x, centeredBbox.min.y, centeredBbox.max.z },
        { centeredBbox.min.x, centeredBbox.max.y, centeredBbox.max.z },
        { centeredBbox.max.x, centeredBbox.max.y, centeredBbox.max.z },
    };
    gtlMath2::Matrix4x3f matrix(invCameraRot);

    gtlMath2::AABB rotatedBbox = { INFINITY, -INFINITY }; // FIXME: this stuff will not work with -ffast-math
    for (const auto &corner : corners) {
        auto newCorner = matrix * corner;

        if (newCorner.x < rotatedBbox.min.x) rotatedBbox.min.x = newCorner.x;
        if (newCorner.y < rotatedBbox.min.y) rotatedBbox.min.y = newCorner.y;
        if (newCorner.z < rotatedBbox.min.z) rotatedBbox.min.z = newCorner.z;

        if (newCorner.x > rotatedBbox.max.x) rotatedBbox.max.x = newCorner.x;
        if (newCorner.y > rotatedBbox.max.y) rotatedBbox.max.y = newCorner.y;
        if (newCorner.z > rotatedBbox.max.z) rotatedBbox.max.z = newCorner.z;
    }

    m_cameraNode->projectionMatrix =
        gtlMath2::Matrix4x4f::ortho(
            rotatedBbox.min.y, rotatedBbox.max.y,
            rotatedBbox.min.z, rotatedBbox.max.z,
            rotatedBbox.min.x, rotatedBbox.max.x);
}
