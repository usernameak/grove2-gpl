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

#include "MaterialEditor.h"

#include <ged/Editor/Material/MaterialEditorPane.h>

#include <grUi/Widget/WidgetEmpty.h>

#include <grScene/Camera.h>
#include <grRenderCore/Mesh/Mesh.h>
#include <grScene/SceneGeom.h>

using namespace ged::MaterialEditor;

MaterialEditor::MaterialEditor(
    ged::document::Document *document,
    gnaPointer<grScene::MaterialInstance> material)
    : Editor(document),
      m_material(std::move(material)) {

    initializeRender();
    m_materialEditorPane = gnaNew<MaterialEditorPane>(this);
}

MaterialEditor::~MaterialEditor() {
    m_materialEditorPane = nullptr;
    gtlDelete m_renderPass;
}

void MaterialEditor::initializeRender() {
    m_renderPass = gtlNew grRenderView::Render::RenderPassView();

    m_rootSceneNode       = gnaNew<grScene::Node>();
    m_rootSceneNode->name = GTXT("EditorRoot");
    // renderViewContainer->addRenderView(gnaNew<grRenderView::SceneRenderView>(m_rootSceneNode));
    // TODO:

    m_camera                               = gnaNew<grScene::Camera>();
    m_camera->name                         = GTXT("EditorCamera");
    m_camera->m_localTransform.translation = { 1.5f };

    m_camera->m_localTransform.rotation = { 0, 0.78539f, -2.35619f };

    m_renderPass->m_cameraNode = m_camera;

    setupPreviewMesh();

    // m_renderPass->m_renderViewContainer = renderViewContainer;

    // m_rootSceneNode->addSubnode(m_materialPreviewNode);
    // m_rootSceneNode->addSubnode(m_camera);
}

void MaterialEditor::setupPreviewMesh() {
    int nSlices = 32;
    int nStacks = 32;

    auto sphereMesh = gnaNew<grRenderCore::Mesh>();
    sphereMesh->m_flags |= grRenderCore::Mesh::FLAG_IMMUTABLE;

    sphereMesh->set_vertexFormat(grRenderCore::VFF_POSITION | grRenderCore::VFF_TEXCOORD);

    sphereMesh->set_vertexCount((nStacks - 1) * nSlices + 2);
    sphereMesh->set_indexCount((nStacks - 1) * nSlices * 6);

    uint32_t vidx = 0;

    auto v0       = sphereMesh->getVertex(vidx++);
    v0.texCoord() = { 0, 0 };
    v0.position() = { 0, 1, 0 };

    for (int i = 0; i < nStacks - 1; i++) {
        auto u   = static_cast<float>(i) / static_cast<float>(nStacks);
        auto phi = gtlMath2::pi<float> * u;

        for (int j = 0; j < nSlices; j++) {
            auto v     = static_cast<float>(j) / static_cast<float>(nSlices);
            auto theta = 2.0f * gtlMath2::pi<float> * v;
            auto x     = std::sin(phi) * std::cos(theta);
            auto y     = std::cos(phi);
            auto z     = std::sin(phi) * std::sin(theta);

            auto vij       = sphereMesh->getVertex(vidx++);
            vij.texCoord() = { u, v };
            vij.position() = { x, y, z };
        }
    }

    auto v1       = sphereMesh->getVertex(vidx++);
    v1.texCoord() = { 0, 1 };
    v1.position() = { 0, -1, 0 };

    uint32_t iidx = 0;

    for (int i = 0; i < nSlices; i++) {
        auto i0                       = i + 1;
        auto i1                       = (i + 1) % nSlices + 1;
        sphereMesh->m_indices[iidx++] = v0;
        sphereMesh->m_indices[iidx++] = i1;
        sphereMesh->m_indices[iidx++] = i0;

        i0 = i + nSlices * (nStacks - 2) + 1;
        i1 = (i + 1) % nSlices + nSlices * (nStacks - 2) + 1;

        sphereMesh->m_indices[iidx++] = v1;
        sphereMesh->m_indices[iidx++] = i0;
        sphereMesh->m_indices[iidx++] = i1;
    }

    for (int j = 0; j < nStacks - 2; j++) {
        auto j0 = j * nSlices + 1;
        auto j1 = (j + 1) * nSlices + 1;
        for (int i = 0; i < nSlices; i++) {
            auto i0 = j0 + i;
            auto i1 = j0 + (i + 1) % nSlices;
            auto i2 = j1 + (i + 1) % nSlices;
            auto i3 = j1 + i;

            sphereMesh->m_indices[iidx++] = i0;
            sphereMesh->m_indices[iidx++] = i1;
            sphereMesh->m_indices[iidx++] = i2;

            sphereMesh->m_indices[iidx++] = i2;
            sphereMesh->m_indices[iidx++] = i3;
            sphereMesh->m_indices[iidx++] = i0;
        }
    }

    sphereMesh->markDirty();

    auto sphereGeom = gnaNew<grScene::Geometry>();
    sphereGeom->set_mesh(sphereMesh);
    sphereGeom->material  = m_material;
    m_materialPreviewNode = sphereGeom;
}

gtl::String MaterialEditor::get_tabTitle() {
    return "Material";
}

gnaPointer<grUiWidget> MaterialEditor::get_tabContentWidget() {
    return m_materialEditorPane;
}
