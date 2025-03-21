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

#include "DragOrClick.h"

#include "grUi/Widget/Window/RootWindowManager.h"

void grUiDragOrClickContext::dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) {
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    m_delta += dx + dy;

    if (m_delta >= DRAG_TOLERANCE) {
        addRef();
        root->endDragAndDrop();
        root->startDragAndDrop(m_dragCtx);
        release();
    }
}

void grUiDragOrClickContext::dragRelease(gnaWeakPointer<grUiRootWindowManager> root) {
    if (m_delta < DRAG_TOLERANCE) {
        grUiEventPerformAction ev;
        eventSink_performAction.emit(ev);
    }
}

gnaPointer<grUiDragOrClickContext> grUiStartDragOrClick(gnaWeakPointer<grUiWidget> widget, gnaPointer<grUiDragContext> ctx) {
    auto dragCtx = gnaNew<grUiDragOrClickContext>(widget, ctx->mouseButton, ctx);
    grUi_gRootWindowManager->startDragAndDrop(dragCtx);
    return dragCtx;
}
