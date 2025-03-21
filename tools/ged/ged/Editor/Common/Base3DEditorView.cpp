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

#include "Base3DEditorView.h"

#include <grScene/Camera.h>
#include <utility>

#include <grRenderView/Render/RenderPassView.h>

using namespace ged::CommonEditor;

Base3DEditorView::Base3DEditorView(
    gnaPointer<grScene::Camera> camera) : grUiWidget3DView(),
                                   m_camera(camera) {
    m_renderPass               = new grRenderView::Render::RenderPassView();
    m_renderPass->m_cameraNode = camera;

    this->eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
    this->eventSink_mouseUp.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseUp));
    this->eventSink_keyEvent.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onKeyPress));

    background = gnaNew<grUiBackground>(grColor{ 0xff000000 });
}

void Base3DEditorView::update() {
    grUiWidget3DView::update();

    m_camera->m_localTransform.rotation = { 0, pitch, yaw };
}

void Base3DEditorView::tick(float deltaTime) {
    grUiWidget3DView::tick(deltaTime);

    if (rotatingCamera) {
        gtlMath2::Vector3f movementVector(0.0f);
        if (movementKeys & MKEY_FORWARD) {
            movementVector.x += deltaTime;
        }
        if (movementKeys & MKEY_BACK) {
            movementVector.x -= deltaTime;
        }
        if (movementKeys & MKEY_LEFT) {
            movementVector.y -= deltaTime;
        }
        if (movementKeys & MKEY_RIGHT) {
            movementVector.y += deltaTime;
        }
        if (movementKeys & MKEY_FAST) {
            movementVector *= 4.0f;
        }

        auto &xform           = m_camera->m_localTransform;
        gtlMath2::Vector4f v4 = gtlMath2::Matrix4x4f(gtlMath2::Transform(xform).rotation) * gtlMath2::Vector4f(movementVector, 1.0f);
        xform.translation += { v4.x, v4.y, v4.z };
    }
}

grRenderCore::RenderPass *Base3DEditorView::get_renderPass() {
    return m_renderPass;
}

void Base3DEditorView::on3DAction(gtlMath2::Vector2f position) {
}

gtlMath2::Vector2f Base3DEditorView::convertWindowSpaceToScreenSpace(int x, int y) const {
    grDimension size            = get_size();
    gtlMath2::Vector2f position = (gtlMath2::Vector2f(x, y) / gtlMath2::Vector2f(size.width, size.height) - .5f) * 2.f;
    position.y                  = -position.y;
    return position;
}

gtlMath2::Vector2f Base3DEditorView::windowSpaceDeltaToScreenSpace(int dx, int dy) const {
    grDimension size            = get_size();
    gtlMath2::Vector2f position = (gtlMath2::Vector2f(dx, dy) / gtlMath2::Vector2f(size.width, size.height)) * 2.f;
    position.y                  = -position.y;
    return position;
}

Base3DEditorView::~Base3DEditorView() {
    releaseLastRenderPass();
    gtlDelete m_renderPass;
}

bool Base3DEditorView::onKeyPress(const grUiEventKeyPress &ev) {
    if (ev.action == GR_ACTION_KEY_PRESSED) {
        if (ev.keycode == grKeycode::GR_KEY_W) {
            movementKeys |= MKEY_FORWARD;
        } else if (ev.keycode == grKeycode::GR_KEY_S) {
            movementKeys |= MKEY_BACK;
        } else if (ev.keycode == grKeycode::GR_KEY_A) {
            movementKeys |= MKEY_LEFT;
        } else if (ev.keycode == grKeycode::GR_KEY_D) {
            movementKeys |= MKEY_RIGHT;
        } else if (ev.keycode == grKeycode::GR_KEY_LSHIFT) {
            movementKeys |= MKEY_FAST;
        }
    } else if (ev.action == GR_ACTION_KEY_RELEASED) {
        if (ev.keycode == grKeycode::GR_KEY_W) {
            movementKeys &= ~MKEY_FORWARD;
        } else if (ev.keycode == grKeycode::GR_KEY_S) {
            movementKeys &= ~MKEY_BACK;
        } else if (ev.keycode == grKeycode::GR_KEY_A) {
            movementKeys &= ~MKEY_LEFT;
        } else if (ev.keycode == grKeycode::GR_KEY_D) {
            movementKeys &= ~MKEY_RIGHT;
        } else if (ev.keycode == grKeycode::GR_KEY_LSHIFT) {
            movementKeys &= ~MKEY_FAST;
        }
    }

    return true;
}

bool Base3DEditorView::onMouseDown(const grUiEventMouseDown &ev) {
    set_focused(true);

    if (ev.button == 0) {
        on3DAction(convertWindowSpaceToScreenSpace(ev.x, ev.y));
    } else if (ev.button == 1) {
        auto dndctx = gnaNew<SceneDnDContext>(ev.button, this);
        grUi_gRootWindowManager->startDragAndDrop(dndctx);
        rotatingCamera = true;
    }

    return true;
}

bool Base3DEditorView::onMouseUp(const grUiEventMouseUp &ev) {
    return true;
}


Base3DEditorView::SceneDnDContext::SceneDnDContext(
    const int in_mouseButton,
    gnaWeakPointer<Base3DEditorView> view) : grUiDragContext(view, in_mouseButton),
                                             m_view(view) {
}

void Base3DEditorView::SceneDnDContext::dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) {
    m_view->yaw += static_cast<float>(dx) * 0.01f;
    while (m_view->yaw < -gtlMath2::pi<float>) {
        m_view->yaw += gtlMath2::pi<float> * 2.f;
    }
    while (m_view->yaw > gtlMath2::pi<float>) {
        m_view->yaw -= gtlMath2::pi<float> * 2.f;
    }
    m_view->pitch += static_cast<float>(dy) * 0.01f;
    if (m_view->pitch < -gtlMath2::pi<float> * .5f) {
        m_view->pitch = -gtlMath2::pi<float> * .5f;
    }
    if (m_view->pitch > gtlMath2::pi<float> * .5f) {
        m_view->pitch = gtlMath2::pi<float> * .5f;
    }
}

void Base3DEditorView::SceneDnDContext::dragRelease(gnaWeakPointer<grUiRootWindowManager> root) {
    m_view->rotatingCamera = false;
}
