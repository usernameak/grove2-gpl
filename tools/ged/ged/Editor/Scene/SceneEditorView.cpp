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

#include "SceneEditorView.h"

#include <grRenderView/Render/RenderPassView.h>

#include <ged/Editor/Scene/SceneEditor.h>
#include <ged/Action/ActionModifyProperty.h>

using namespace ged::SceneEditor;

SceneEditorView::SceneEditorView(SceneEditor *pEditor)
    : Base3DEditorView(pEditor->m_camera),
      m_pEditor(pEditor),
      m_axisKeyBits(0),
      m_snapToGrid(false) {

    onObjectSelected(pEditor->m_selectedObject);

    m_renderPass->m_sceneContainer = pEditor->m_sceneContainer;
    m_renderPass->set_enableShadowmapping(true);

    eventSink_keyEvent.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onKeyEvent));
}

SceneEditorView::~SceneEditorView() = default;

void SceneEditorView::onObjectSelected(gnaWeakPointer<grScene::SceneObject> obj) {
    // m_selRenderView->m_scene = obj;
    // TODO: object selection preview
}

void SceneEditorView::tick(float deltaTime) {
    Base3DEditorView::tick(deltaTime);

    m_pEditor->m_sceneContainer->update(deltaTime);
    m_pEditor->m_sceneContainer->postUpdate(deltaTime);
}

void SceneEditorView::on3DAction(gtlMath2::Vector2f position) {
    Base3DEditorView::on3DAction(position);

    grScene::RayCastResult rcr;

    if (m_camera->rayCastAgainst(m_pEditor->m_editedScene->m_rootNode, rcr, position)) {
        m_pEditor->selectObject(rcr.object);

        auto dndctx = gnaNew<SceneEditorDragContext>(
            0, this,
            rcr.object->m_localTransform, rcr.object->m_globalTransform,
            position
        );
        grUi_gRootWindowManager->startDragAndDrop(dndctx);
    } else {
        m_pEditor->selectObject(nullptr);
    }
}

bool SceneEditorView::onKeyEvent(grUiEventKeyPress &ev) {
    if (ev.action == GR_ACTION_KEY_PRESSED) {
        if (ev.keycode == grKeycode::GR_KEY_DELETE) {
            m_pEditor->deleteNode(m_pEditor->m_selectedObject);
            return true;
        } else if (ev.keycode == grKeycode::GR_KEY_X) {
            m_axisKeyBits |= AXIS_KEY_X_BIT;
            return true;
        } else if (ev.keycode == grKeycode::GR_KEY_Y) {
            m_axisKeyBits |= AXIS_KEY_Y_BIT;
            return true;
        } else if (ev.keycode == grKeycode::GR_KEY_Z) {
            m_axisKeyBits |= AXIS_KEY_Z_BIT;
            return true;
        } else if (ev.keycode == grKeycode::GR_KEY_G) {
            m_snapToGrid = !m_snapToGrid;
            return true;
        }
    } else if (ev.action == GR_ACTION_KEY_RELEASED) {
        if (ev.keycode == grKeycode::GR_KEY_X) {
            m_axisKeyBits &= ~AXIS_KEY_X_BIT;
            return true;
        } else if (ev.keycode == grKeycode::GR_KEY_Y) {
            m_axisKeyBits &= ~AXIS_KEY_Y_BIT;
            return true;
        } else if (ev.keycode == grKeycode::GR_KEY_Z) {
            m_axisKeyBits &= ~AXIS_KEY_Z_BIT;
            return true;
        }
    }
    return true;
}

SceneEditorView::SceneEditorDragContext::SceneEditorDragContext(
    const int mouseButton,
    gnaWeakPointer<SceneEditorView> view,
    const gtlMath2::LocalTransform &initialLocalTransform,
    const gtlMath2::Transform &initialGlobalTransform,
    const gtlMath2::Vector2f &initialScreenPosition
) : grUiDragContext(view, mouseButton),
    m_view(view),
    m_initialLocalTransform(initialLocalTransform),
    m_initialGlobalTransform(initialGlobalTransform),
    m_initialScreenPosition(initialScreenPosition) {}

void SceneEditorView::SceneEditorDragContext::dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) {
    SceneEditor *editor = m_view->m_pEditor;

    if (editor->m_selectedObject) {
        grPoint relPos = m_view->computeRelativePosition(root);
        int actualX    = x - relPos.x;
        int actualY    = y - relPos.y;

        const auto &transform            = editor->m_selectedObject->m_localTransform;
        const auto &oldObjectTranslation = transform.translation;
        auto newTransform                = transform;
        auto &objectTranslation          = newTransform.translation;

        gtlMath2::Vector2f screenPosition = m_view->convertWindowSpaceToScreenSpace(actualX, actualY);

        gtlMath2::Vector3f screenspaceOrigin = m_view->m_camera->worldSpaceToScreenSpace(m_initialGlobalTransform.translation);

        gtlMath2::Vector3f screenspaceSource(m_initialScreenPosition, screenspaceOrigin.z);
        // gtlMath2::Vector3f worldspaceSource = m_view->m_camera->screenSpaceToWorldSpace(screenspaceSource);

        gtlMath2::Vector3f screenspaceTarget(
            screenspaceOrigin.x + (screenPosition.x - screenspaceSource.x),
            screenspaceOrigin.y + (screenPosition.y - screenspaceSource.y),
            screenspaceOrigin.z
        );
        gtlMath2::Vector3f worldspaceTarget = m_view->m_camera->screenSpaceToWorldSpace(screenspaceTarget);

        float scaleMultiplier      = m_initialGlobalTransform.scale / m_initialLocalTransform.scale;
        auto transformGlobalOffset = m_initialGlobalTransform.translation - m_initialLocalTransform.translation * scaleMultiplier;

        const float gridStep = 1.0f;

        if (m_view->m_snapToGrid) {
            worldspaceTarget /= gridStep;
            worldspaceTarget.x = std::round(worldspaceTarget.x);
            worldspaceTarget.y = std::round(worldspaceTarget.y);
            worldspaceTarget.z = std::round(worldspaceTarget.z);
            worldspaceTarget *= gridStep;

            // get rid of negative zeros
            if (worldspaceTarget.x == -0.f) worldspaceTarget.x = 0.f;
            if (worldspaceTarget.y == -0.f) worldspaceTarget.y = 0.f;
            if (worldspaceTarget.z == -0.f) worldspaceTarget.z = 0.f;
        }

        auto modifiedTranslation = (worldspaceTarget - transformGlobalOffset) / scaleMultiplier;

        if ((m_view->m_axisKeyBits == 0 || (m_view->m_axisKeyBits & AXIS_KEY_X_BIT)) && !isnan(modifiedTranslation.x)) {
            objectTranslation.x = modifiedTranslation.x;
        }
        if ((m_view->m_axisKeyBits == 0 || (m_view->m_axisKeyBits & AXIS_KEY_Y_BIT)) && !isnan(modifiedTranslation.y)) {
            objectTranslation.y = modifiedTranslation.y;
        }
        if ((m_view->m_axisKeyBits & AXIS_KEY_Z_BIT) && !isnan(modifiedTranslation.z)) {
            objectTranslation.z = modifiedTranslation.z;
        }

        if (oldObjectTranslation != objectTranslation) {
            editor->executeAction(gnaNew<action::ActionModifyProperty<gtlMath2::LocalTransform>>(
                property::EditableProperty<gtlMath2::LocalTransform>::fromProperty(
                    editor->m_selectedObject,
                    gtlProperty::findProperty(editor->m_selectedObject, "m_localTransform")
                ),
                newTransform
            ));
        }
    }
}
