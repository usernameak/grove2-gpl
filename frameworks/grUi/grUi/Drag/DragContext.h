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

#include <grUi/Widget/Widget.h>

#include <utility>

#include "DragObject.h"

class grUiRootWindowManager;

class GR_UI_DLLIMPEXP grUiDragContext : public gtlRcObject {
public:
    GTL_RTTI_DECLARE();

    gnaWeakPointer<grUiWidget> m_holderWindow;
    const int mouseButton;

    grUiDragContext(
        gnaWeakPointer<grUiWidget> holderWidget /* not same as holder window */,
        int mouseButton) : m_holderWindow(holderWidget->findNativeWindow()),
                           mouseButton(mouseButton) {}

    virtual void dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) = 0;
    virtual void dragRelease(gnaWeakPointer<grUiRootWindowManager> root) {}

    virtual void showObject(gnaWeakPointer<grUiRootWindowManager> root, int x, int y) {}
    virtual void hideObject(gnaWeakPointer<grUiRootWindowManager> root) {}

    virtual gtl::PooledAString getCursor() const {
        static gtl::PooledAString DEFAULT_CURSOR("");
        return DEFAULT_CURSOR;
    }
};

class GR_UI_DLLIMPEXP grUiObjectDragContext : public grUiDragContext {
public:
    GTL_RTTI_DECLARE();

    gnaPointer<grUiDragObject> m_dragObject;

    grUiObjectDragContext(
        gnaWeakPointer<grUiWidget> holderWidget,
        const int mouseButton,
        gnaPointer<grUiDragObject> dragObject)
        : grUiDragContext(holderWidget, mouseButton),
          m_dragObject(std::move(dragObject)) {}

    void dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) override {
    }

    void dragRelease(gnaWeakPointer<grUiRootWindowManager> root) override {
    }

    virtual void objectDropped(bool hasTarget) {
    }
};
