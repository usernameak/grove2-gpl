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

#include "SceneEditor.h"

#include <grScene/Scene.h>

#include <ged/Editor/Scene/SceneEditorPane.h>
#include <ged/Action/Action.h>
#include <grUi/Widget/Window/RootWindowManager.h>

#include <grRenderCore/Mesh/Mesh.h>
#include <grScene/SceneGeom.h>
#include <grScene/Camera.h>
#include <nxfResource/MutableResourceManager.h>

using namespace ged::SceneEditor;

SceneEditor::SceneEditor(document::Document *document)
    : Editor(document) {

    m_editedScene = document->get_asset().rttiCast2<grScene::Scene>();
    assert(m_editedScene);
}

void SceneEditor::doInitializeEditor() {
    Editor::doInitializeEditor();

    m_visualScene = gnaNew<grScene::Scene>();

    initializeRender();
    m_sceneEditorPane = gnaNew<SceneEditorPane>(this);
}

void SceneEditor::initializeRender() {
    m_sceneContainer = gnaNew<grScene::SceneContainer>();

    m_camera       = m_visualScene->createObject<grScene::Camera>();
    m_camera->name = GTXT("EditorCamera");

    setupGridMesh();
    m_sceneContainer->addScene(m_editedScene);
    m_sceneContainer->addScene(m_visualScene);
}

SceneEditor::~SceneEditor() {
    m_sceneEditorPane = nullptr;
}

gnaPointer<grUiWidget> SceneEditor::get_tabContentWidget() {
    return m_sceneEditorPane;
}

void SceneEditor::selectObject(gnaWeakPointer<gtlObject> obj) {
    Editor::selectObject(obj);

    auto sceneObj = obj.rttiCast2<grScene::SceneObject>();

    m_selectedObject = sceneObj;
    m_sceneEditorPane->onObjectSelected(sceneObj);

    m_sceneEditorPane->m_outliner->selectObject(sceneObj);
}

namespace ged::SceneEditor {
    class DeleteNodeAction : public action::Action {
        SceneEditor *m_editor;
        gnaPointer<grScene::Node> m_parent;
        gnaPointer<grScene::SceneObject> m_node;

    public:
        GTL_RTTI_DECLARE();

        DeleteNodeAction(SceneEditor *editor, gnaPointer<grScene::Node> parent, gnaPointer<grScene::SceneObject> node)
            : m_editor(editor),
              m_parent(std::move(parent)),
              m_node(std::move(node)) {}

        void execute() override {
            if (m_editor->m_selectedObject == m_node) {
                m_editor->selectObject(nullptr);
            }
            assert(false);
            // m_parent->removeSubnode(m_node);
            m_editor->refreshNodeList(); // TODO: somehow automatically handle this
        }

        void undo() override {
            assert(false);
            // m_parent->addSubnode(m_node);
        }

        gtl::String describe() const override {
            return gtl::String::format(GTXT("Delete node `%ls`"), m_node->name.toCString());
        }
    };

    class DuplicateNodeAction : public ged::action::Action {
        SceneEditor *m_editor;
        gnaPointer<grScene::SceneObject> m_node;
        gnaPointer<grScene::SceneObject> m_newNode;

    public:
        GTL_RTTI_DECLARE();

        DuplicateNodeAction(SceneEditor *editor, gnaPointer<grScene::SceneObject> node, gnaPointer<grScene::SceneObject> newNode)
            : m_editor(editor),
              m_node(std::move(node)),
              m_newNode(std::move(newNode)) {}

        void execute() override {
            if (auto parent = m_node->m_parent.rttiCast2<grScene::Node>()) {
                assert(false);
                // parent->addSubnode(m_newNode);
                m_editor->refreshNodeList(); // TODO: somehow automatically handle this
            }
        }

        void undo() override {
            if (m_newNode) {
                if (auto parent = m_newNode->m_parent.rttiCast2<grScene::Node>()) {
                    if (m_editor->m_selectedObject == m_newNode) {
                        m_editor->selectObject(nullptr);
                    }
                    assert(false);
                    // parent->removeSubnode(m_newNode);
                }
            }
        }

        gtl::String describe() const override {
            return gtl::String::format(GTXT("Duplicate node `%ls`"), m_node->name.toCString());
        }
    };
}

GTL_RTTI_DEFINE(ged::SceneEditor::DeleteNodeAction, GTL_RTTI_INHERITS(ged::action::Action));
GTL_RTTI_DEFINE(ged::SceneEditor::DuplicateNodeAction, GTL_RTTI_INHERITS(ged::action::Action));

void SceneEditor::duplicateSelectedObject() {
    if (!m_selectedObject) return;
    if (!m_selectedObject->m_parent) return;

    auto parent = m_selectedObject->m_parent.rttiCast2<grScene::Node>();
    if (parent) {
        gnaPointer<grScene::SceneObject> newObject = m_selectedObject->clone().cast<grScene::SceneObject>();
        if (newObject) {
            gtl::String newName = static_cast<gtl::String>(newObject->name);
            newName += GTXT(" copy");
            newObject->name = newName;

            executeAction(gnaNew<DuplicateNodeAction>(this, m_selectedObject, newObject));
        }
    }
}

bool SceneEditor::canDeleteNode(gnaWeakPointer<grScene::SceneObject> node) {
    return node->m_parent != nullptr;
}

void SceneEditor::deleteNode(gnaPointer<grScene::SceneObject> node) {
    auto parent = m_selectedObject->m_parent.rttiCast2<grScene::Node>();
    if (parent && canDeleteNode(node)) {
        executeAction(gnaNew<DeleteNodeAction>(this, parent, node));
    }
}

void SceneEditor::refreshNodeList() {
    m_sceneEditorPane->updateNodeList();
}

void SceneEditor::setupGridMesh() {
    const auto gridMesh = gnaNew<grRenderCore::Mesh>();
    gridMesh->m_flags |= grRenderCore::Mesh::FLAG_IMMUTABLE;
    gridMesh->m_primitiveType = grRenderCore::Mesh::TYPE_LINES;

    gridMesh->set_vertexFormat(grRenderCore::VFF_POSITION | grRenderCore::VFF_COLOR);

    gridMesh->set_vertexCount((16 * 2 + 1) * 2 * 2);

    int i = 0;

    for (int x = -16; x <= 16; x++) {
        auto v1       = gridMesh->getVertex(i);
        v1.position() = { (float)x, -16, 0 };
        v1.color()    = 0xFF808080;
        i++;

        auto v2       = gridMesh->getVertex(i);
        v2.position() = { (float)x, 16, 0 };
        v2.color()    = 0xFF808080;
        i++;
    }

    for (int y = -16; y <= 16; y++) {
        auto v1       = gridMesh->getVertex(i);
        v1.position() = { -16, (float)y, 0 };
        v1.color()    = 0xFF808080;
        i++;

        auto v2       = gridMesh->getVertex(i);
        v2.position() = { 16, (float)y, 0 };
        v2.color()    = 0xFF808080;
        i++;
    }

    gridMesh->markDirty();

    const auto gridGeom = m_visualScene->createObject<grScene::Geometry>();
    gridGeom->set_mesh(gridMesh);
    gridGeom->material                          = gnaNew<grScene::MaterialInstance>();
    gridGeom->material->m_pipelineName          = "FlatShaded_Default";
    gridGeom->material->m_shadowMapPipelineName = gtl::Name();
    gridGeom->name                              = GTXT("EditorGrid");

    m_gridSceneNode = gridGeom;
}
