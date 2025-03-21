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

#include <gtlString/String.h>

#include <grUi/Widget/Widget.h>
#include <grUi/Drag/DragObject.h>
#include <grUi/Style/Border/BorderNative.h>

class grUiObjectDragContext;

class GR_UI_DLLIMPEXP grUiNativeFramePlatform {
protected:
    gnaWeakPointer<grUiWidget> m_frame;

public:
    GTL_RTTI_DECLARE();

    grUiNativeFramePlatform(gnaWeakPointer<grUiWidget> frame) : m_frame(frame) {
    }
    virtual ~grUiNativeFramePlatform() = default;

    virtual void set_windowTitle(const gtl::String &title) = 0;
    virtual void set_windowVisible(bool value)             = 0;
    virtual grRectangle get_windowViewport()               = 0;
    virtual void set_mouseCaptured(bool value)             = 0;

    virtual grRectangle outsetFrameBounds(const grRectangle &bounds) = 0;

    gnaWeakPointer<grUiWidget> get_frame() const { return m_frame; }

    virtual void startDragging(gnaPointer<grUiObjectDragContext> ctx) = 0;

    virtual void emitMouseMoveEvent(int x, int y)                    = 0;
    virtual void emitMouseLeaveEvent()                               = 0;
    virtual void emitObjectDropEvent(gnaPointer<grUiDragObject> obj) = 0;

    virtual void update() {}

    virtual bool updateNativeBorderInsets(gnaWeakPointer<grUiBorderNative> border) {
        return border->updateInsets({ 0, 0, 0, 0 });
    }

    virtual void nativeWidgetPresent() {}

    /**
     * @return DPI scale factor, e.g. 100 is 100%, 125 is 125% etc
     */
    virtual int get_scaleFactor() { return 100; }

    virtual bool usesExternalWindowManager() { return true; }
};
