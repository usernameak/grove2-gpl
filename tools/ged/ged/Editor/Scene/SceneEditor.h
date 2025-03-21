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
#include <grScene/Scene.h>
#include <ged/Document/Document.h>

namespace ged {
    namespace SceneEditor {
        class SceneEditorPane;

        class SceneEditor : public Editor {
        public:
            explicit SceneEditor(document::Document *document);

            void initializeRender();
            void setupGridMesh();

            virtual ~SceneEditor() override;

            gnaPointer<grUiWidget> get_tabContentWidget() override;

            void duplicateSelectedObject();
            bool canDeleteNode(gnaWeakPointer<grScene::SceneObject> node);
            void deleteNode(gnaPointer<grScene::SceneObject> node);
            void refreshNodeList();

            void selectObject(gnaWeakPointer<gtlObject> obj) override;

            gnaPointer<grScene::SceneContainer> m_sceneContainer;
            gnaPointer<grScene::Scene> m_editedScene;
            gnaPointer<grScene::Scene> m_visualScene;
            gnaPointer<grScene::SceneObject> m_gridSceneNode;
            gnaPointer<grScene::SceneObject> m_selectedObject;
            gnaPointer<grScene::Camera> m_camera;

        protected:
            void doInitializeEditor() override;

        private:
            gnaPointer<SceneEditorPane> m_sceneEditorPane;
        };
    }
}
