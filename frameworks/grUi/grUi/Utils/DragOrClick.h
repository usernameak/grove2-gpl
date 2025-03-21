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

#include <grUi/Drag/DragContext.h>

class GR_UI_DLLIMPEXP grUiDragOrClickContext : public grUiDragContext {
    int m_delta;
    gnaPointer<grUiDragContext> m_dragCtx;

public:
    grUiDragOrClickContext(
        gnaWeakPointer<grUiWidget> holderWidget,
        const int mouseButton,
        gnaPointer<grUiDragContext> dragCtx)
        : grUiDragContext(holderWidget, mouseButton),
          m_delta(0),
          m_dragCtx(std::move(dragCtx)) {}

    void dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) override;

    void dragRelease(gnaWeakPointer<grUiRootWindowManager> root) override;

    gnaEventSink<grUiEventPerformAction> eventSink_performAction;

    static constexpr int DRAG_TOLERANCE = 5;
};

gnaPointer<grUiDragOrClickContext> GR_UI_DLLIMPEXP grUiStartDragOrClick(gnaWeakPointer<grUiWidget> widget, gnaPointer<grUiDragContext> ctx);