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

#include <windows.h>
#include <ole2.h>

#include <gtlString/String.h>
#include <grUi/Drag/DragObject.h>
#include "NativeFramePlatformShared.h"

class grUiObjectDragContext;
class grUiNativeDropSourcePlatformWin;
class grUiNativeDropTargetPlatformWin;

class grUiNativeFramePlatformImpl : public grUiNativeFramePlatformShared {
    HWND m_hwnd;
    gnaPointer<grRenderCore::VideoOutput> m_videoOut;
    static bool windowClassRegistered;
    int m_oldX;
    int m_oldY;
    bool m_mouseEntered;
    bool m_windowVisible;
    grUiNativeDropSourcePlatformWin *m_dropSource;
    grUiNativeDropTargetPlatformWin *m_dropTarget;

    grRectangle m_oldBounds;

    friend class grUiNativeDropTargetPlatformWin;

public:
    grUiNativeFramePlatformImpl(gnaWeakPointer<grUiWidget> frame);
    virtual ~grUiNativeFramePlatformImpl() override;
    void set_windowTitle(const gtl::String &title) override;
    void set_windowVisible(bool value) override;
    grRectangle get_windowViewport() override;
    void set_mouseCaptured(bool value) override;

    grRectangle outsetFrameBounds(const grRectangle &bounds) override;

    void startDragging(gnaPointer<grUiObjectDragContext> ctx) override;

    void emitMouseMoveEvent(int x, int y) override;
    void emitMouseLeaveEvent() override;
    void emitObjectDropEvent(gnaPointer<grUiDragObject> obj) override;
    void update() override;
    bool updateNativeBorderInsets(gnaWeakPointer<grUiBorderNative> border) override;
    void nativeWidgetPresent() override;
    gnaWeakPointer<grRenderCore::VideoOutput> get_videoOutput() override;

    int get_scaleFactor() override;

private:
    static LRESULT CALLBACK stWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static void registerWindowClass();
    LRESULT wndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
