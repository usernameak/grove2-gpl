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

#include <ged/Editor/Editor.h>
#include <grScene/Material/MaterialInstance.h>

#include <grScene/SceneNode.h>
#include <grRenderView/Render/RenderPassView.h>

#include "MaterialEditorView.h"

namespace ged {
    namespace MaterialEditor {
        class MaterialEditorPane;

        class MaterialEditor : public ged::Editor {
        public:
            MaterialEditor(ged::document::Document *document, gnaPointer<grScene::MaterialInstance> material);
            virtual ~MaterialEditor() override;

            void initializeRender();
            void setupPreviewMesh();

            gtl::String get_tabTitle() override;
            gnaPointer<grUiWidget> get_tabContentWidget() override;

            grRenderView::Render::RenderPassView *m_renderPass = nullptr;
            gnaPointer<grScene::Node> m_rootSceneNode;
            gnaPointer<grScene::Camera> m_camera;
            gnaPointer<grScene::SceneObject> m_materialPreviewNode;

            gnaPointer<grScene::MaterialInstance> m_material;
            gnaPointer<MaterialEditorPane> m_materialEditorPane;
        };
    }
}
