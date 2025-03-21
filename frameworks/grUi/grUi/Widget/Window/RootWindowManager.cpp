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

#include "RootWindowManager.h"

#include <grUi/Widget/Native/NativeFramePlatform.h>
#include <windows.h>

#include <grUi/Native/NativePlatformDevice.h>

grUiRootWindowManager::grUiRootWindowManager(grUiNativePlatformDevice *device) : grUiWindowManager() {
    m_nativeDevice = device;
    set_isRootWidget(true);

    eventSink_mouseMove.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseMove), gnaEventPriority::PRIORITY_HIGHEST);
    eventSink_mouseUp.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseUp), gnaEventPriority::PRIORITY_HIGHEST);
}

grUiRootWindowManager::~grUiRootWindowManager() = default;

void grUiRootWindowManager::startDragAndDrop(gnaPointer<grUiDragContext> context) {
    if (!m_dragAndDropContext) {
        m_dragAndDropContext = std::move(context);

        auto objectDragCtx = m_dragAndDropContext.rttiCast2<grUiObjectDragContext>();
        if (m_dragAndDropContext->m_holderWindow) {
            if (objectDragCtx) {
                m_dragAndDropContext->m_holderWindow->m_platform->startDragging(objectDragCtx);
            } else {
                m_dragAndDropContext->m_holderWindow->m_platform->set_mouseCaptured(true);
            }
        } else {
            get_nativeDevice()->set_globalMousePointer(m_dragAndDropContext->getCursor());

            // TODO: implement the opposite case
        }
    }
}

void grUiRootWindowManager::nativeWidgetDraw() {
    grUiWindowManager::nativeWidgetDraw();
    for (gnaWeakPointer<grUiWidget> widget : *this) {
        widget->nativeWidgetDraw();
    }
}

void grUiRootWindowManager::nativeWidgetPreDraw(float deltaTime) {
    grUiWidget::nativeWidgetPreDraw(deltaTime);
    for (gnaWeakPointer<grUiWidget> widget : *this) {
        widget->nativeWidgetPreDraw(deltaTime);
    }
}

void grUiRootWindowManager::nativeWidgetPresent() {
    grUiWindowManager::nativeWidgetPresent();
    for (gnaWeakPointer<grUiWidget> widget : *this) {
        widget->nativeWidgetPresent();
    }
}

void grUiRootWindowManager::update() {
    set_bounds(m_nativeDevice->get_displayBounds());
    if (!m_dragAndDropContext) {
        get_nativeDevice()->set_globalMousePointer(get_actualCursor());
    }

    grUiWindowManager::update();
}

void grUiRootWindowManager::endDragAndDrop() {
    gnaPointer<grUiDragContext> ctx = m_dragAndDropContext;
    m_dragAndDropContext            = nullptr;
    ctx->hideObject(this);
    ctx->dragRelease(this);
    if (ctx->m_holderWindow) {
        ctx->m_holderWindow->m_platform->set_mouseCaptured(false);
    }

    get_nativeDevice()->set_globalMousePointer(get_actualCursor());
}

bool grUiRootWindowManager::onMouseMove(grUiEventMouseMove &ev) {
    if (m_dragAndDropContext) {
        m_dragAndDropContext->dragMove(this, ev.x, ev.y, ev.dx, ev.dy);
        m_dragAndDropContext->showObject(this, ev.x, ev.y);
        // return false;
    }
    return true;
}

bool grUiRootWindowManager::onMouseUp(grUiEventMouseUp &ev) {
    if (m_dragAndDropContext && ev.button == m_dragAndDropContext->mouseButton) {
        auto octx = m_dragAndDropContext.rttiCast2<grUiObjectDragContext>();
        if (octx && octx->m_dragObject) {
            grUiEventObjectDrop ev1 {};
            ev1.object = octx->m_dragObject;
            ev1.mods   = ev.mods;
            ev1.x      = ev.x;
            ev1.y      = ev.y;

            bool result = !eventSink_objectDrop.emit(ev1);
            octx->objectDropped(result);
        }
        endDragAndDrop();
        return false;
    }
    return true;
}

bool grUiRootWindowManager::usesNativeChildEventBehavior() {
    return get_nativeDevice() && get_nativeDevice()->useNativeWindowManagerInputMechanism();
}

gnaPointer<grUiRootWindowManager> grUi_gRootWindowManager;

GTL_RTTI_DEFINE(grUiRootWindowManager, GTL_RTTI_INHERITS(grUiWindowManager));
