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

#include "NativeFramePlatformW32.h"

#include <gtlUtil/Logging.h>

#include <utility>
#include <windowsx.h>

#include <grRenderCore/RenderInterface.h>
#include <grRenderCore/VideoOutput/VideoOutputManager.h>
#include <grEngine/Engine.h>

#include <grUi/Widget/Window/Frame.h>
#include <grUi/Drag/DragContext.h>
#include <grUi/Widget/Window/RootWindowManager.h>
#include <grUiNative/Render/UiRendererImpl.h>

#include "NativeDropDataObjectW32.h"
#include "NativeDropSourceW32.h"
#include "NativeDropTargetW32.h"

#define GRUI_NATIVE_FRAME_WNDCLASS L"GroveEngine_UI_WindowClass"

bool grUiNativeFramePlatformImpl::windowClassRegistered = false;

grUiNativeFramePlatformImpl::grUiNativeFramePlatformImpl(gnaWeakPointer<grUiWidget> frame)
    : grUiNativeFramePlatformShared(frame),
      m_hwnd(nullptr),
      m_oldX(0), m_oldY(0),
      m_mouseEntered(false),
      m_windowVisible(false) {

    if (!windowClassRegistered) {
        registerWindowClass();

        windowClassRegistered = true;
    }

    gnaWeakPointer<grUiFrame> nFrame = m_frame.rttiCast2<grUiFrame>();
    bool isFrame                     = nFrame.hasValue();

    DWORD dwExStyle = isFrame ? 0 : WS_EX_TOOLWINDOW;
    DWORD dwStyle   = isFrame ? WS_OVERLAPPEDWINDOW : (WS_OVERLAPPED | WS_POPUP);

    grPoint pos     = m_frame->get_position();
    grDimension dim = m_frame->get_size();

    m_hwnd = CreateWindowExW(
        dwExStyle,
        GRUI_NATIVE_FRAME_WNDCLASS,
        nFrame ? nFrame->get_title().toCString() : L"",
        dwStyle,
        pos.x, pos.y,
        dim.width, dim.height,
        nullptr, nullptr,
        GetModuleHandleW(nullptr),
        this);

    if (!m_hwnd) {
        GR_FATAL(GTXT("Failed to create window"));
    }

    grRenderCore::VideoOutputCreateOptions voCreateOpts{};
    m_videoOut = grRenderCore::g_renderInterface->get_videoOutputManager()->createFromNativeWindow(m_hwnd, voCreateOpts);

    m_dropSource = new grUiNativeDropSourcePlatformWin;
    m_dropTarget = new grUiNativeDropTargetPlatformWin(this);

    RegisterDragDrop(m_hwnd, m_dropTarget);
}

grUiNativeFramePlatformImpl::~grUiNativeFramePlatformImpl() {
    RevokeDragDrop(m_hwnd);
    m_dropTarget->Release();
    m_dropSource->Release();

    m_videoOut = nullptr;
    SetWindowLongPtrW(m_hwnd, GWLP_USERDATA, NULL);
    DestroyWindow(m_hwnd);
}

void grUiNativeFramePlatformImpl::set_windowTitle(const gtl::String &title) {
    SetWindowTextW(m_hwnd, title.toCString());
}

void grUiNativeFramePlatformImpl::set_windowVisible(bool value) {
    if (!value) {
        m_windowVisible = false;
    }
    ShowWindow(m_hwnd, value ? (m_frame->get_focused() ? SW_SHOW : SW_SHOWNA) : SW_HIDE);
    if (value) {
        m_windowVisible = true;
    }
}

grRectangle grUiNativeFramePlatformImpl::get_windowViewport() {
    RECT rc;
    GetClientRect(m_hwnd, &rc);
    POINT p1{ rc.left, rc.top };
    ClientToScreen(m_hwnd, &p1);
    RECT rcWindow;
    GetWindowRect(m_hwnd, &rcWindow);
    return {
        static_cast<int>(p1.x - rcWindow.left),
        static_cast<int>(p1.y - rcWindow.top),
        static_cast<int>(rc.right - rc.left),
        static_cast<int>(rc.bottom - rc.top),
    };
}

void grUiNativeFramePlatformImpl::set_mouseCaptured(bool value) {
    if (value) {
        SetCapture(m_hwnd);
    } else {
        ReleaseCapture();
    }
}

void grUiNativeFramePlatformImpl::startDragging(gnaPointer<grUiObjectDragContext> ctx) {
    grEngine::gEngine->m_taskQueue.enqueue([this, ctx]() {
        auto *ddo = new grUiNativeDropDataObjectW32(ctx);
        m_dropSource->set_dragContext(ctx);

        DWORD dwEffect;
        DoDragDrop(ddo, m_dropSource, DROPEFFECT_COPY | DROPEFFECT_LINK, &dwEffect);
        grUi_gRootWindowManager->endDragAndDrop();
        ddo->Release();

        m_dropSource->set_dragContext(nullptr);
    });
}

grRectangle grUiNativeFramePlatformImpl::outsetFrameBounds(const grRectangle &bounds) {
    RECT rc = { bounds.x, bounds.y, bounds.x + bounds.width, bounds.y + bounds.height };
    AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, FALSE, 0);
    return {
        static_cast<int>(rc.left),
        static_cast<int>(rc.top),
        static_cast<int>(rc.right - rc.left),
        static_cast<int>(rc.bottom - rc.top),
    };
}

LRESULT CALLBACK grUiNativeFramePlatformImpl::stWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    grUiNativeFramePlatformImpl *self;
    if (uMsg == WM_NCCREATE) {
        LPCREATESTRUCTW lpcs = reinterpret_cast<LPCREATESTRUCTW>(lParam);
        self                 = static_cast<grUiNativeFramePlatformImpl *>(lpcs->lpCreateParams);
        self->m_hwnd         = hwnd;
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    } else {
        self = reinterpret_cast<grUiNativeFramePlatformImpl *>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    }
    if (self) {
        return self->wndProc(
            uMsg,
            wParam,
            lParam);
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

void grUiNativeFramePlatformImpl::registerWindowClass() {
    WNDCLASSW wcls;
    ZeroMemory(&wcls, sizeof(wcls));
    wcls.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcls.lpfnWndProc   = &stWndProc;
    wcls.hInstance     = GetModuleHandleW(nullptr);
    wcls.hCursor       = LoadCursorA(nullptr, IDC_ARROW);
    wcls.hbrBackground = nullptr;
    wcls.lpszClassName = GRUI_NATIVE_FRAME_WNDCLASS;

    if (!RegisterClassW(&wcls)) {
        GR_FATAL(GTXT("Failed to register window class"));
    }
}

void grUiNativeFramePlatformImpl::emitMouseLeaveEvent() {
    gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference

    if (m_mouseEntered) {
        m_mouseEntered = false;

        grUiEventMouseLeave ev;
        m_frame->eventSink_mouseLeave.emit(ev);
    }
}

void grUiNativeFramePlatformImpl::emitObjectDropEvent(gnaPointer<grUiDragObject> obj) {
    gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference

    grUiEventObjectDrop ev;
    ev.object = obj;
    m_frame->eventSink_objectDrop.emit(ev);
}

void grUiNativeFramePlatformImpl::emitMouseMoveEvent(int x, int y) {
    gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference

    if (!m_mouseEntered) {
        m_mouseEntered = true;

        TRACKMOUSEEVENT tme;
        ZeroMemory(&tme, sizeof(tme));
        tme.cbSize      = sizeof(tme);
        tme.hwndTrack   = m_hwnd;
        tme.dwFlags     = TME_LEAVE;
        tme.dwHoverTime = 0;
        TrackMouseEvent(&tme);

        grUiEventMouseEnter ev;
        m_frame->eventSink_mouseEnter.emit(ev);
    }

    grRectangle viewport = get_windowViewport();

    grUiEventMouseMove ev;
    ev.x   = x + viewport.x;
    ev.y   = y + viewport.y;
    ev.dx  = ev.x - m_oldX;
    ev.dy  = ev.y - m_oldY;
    m_oldX = ev.x;
    m_oldY = ev.y;
    if (m_frame->get_parent() && m_frame->get_parent()->usesNativeChildEventBehavior()) {
        grPoint winPos = m_frame->get_position();

        grUiEventMouseMove ev1;
        ev1.x  = ev.x + winPos.x;
        ev1.y  = ev.y + winPos.y;
        ev1.dx = ev.dx;
        ev1.dy = ev.dy;
        m_frame->get_parent()->eventSink_mouseMove.emit(ev1);
    }
    m_frame->eventSink_mouseMove.emit(ev);
}

static grKeycode translateKeycode(WPARAM code, LPARAM lParam) {
    WPARAM new_vk = code;
    UINT scancode = (lParam & 0x00ff0000) >> 16;
    int extended  = (lParam & 0x01000000) != 0;

    switch (code) {
    case VK_SHIFT:
        new_vk = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
        break;
    case VK_CONTROL:
        new_vk = extended ? VK_RCONTROL : VK_LCONTROL;
        break;
    case VK_MENU:
        new_vk = extended ? VK_RMENU : VK_LMENU;
        break;
    default:
        new_vk = code;
        break;
    }

    switch (new_vk) {
    case VK_BACK:
        return grKeycode::GR_KEY_BACK;
    case VK_TAB:
        return grKeycode::GR_KEY_TAB;
    case VK_CLEAR:
        return grKeycode::GR_KEY_CLEAR;
    case VK_RETURN:
        return grKeycode::GR_KEY_RETURN;
    case VK_PAUSE:
        return grKeycode::GR_KEY_PAUSE;
    case VK_CAPITAL:
        return grKeycode::GR_KEY_CAPITAL;
    case VK_KANA:
        return grKeycode::GR_KEY_KANA;
    case VK_JUNJA:
        return grKeycode::GR_KEY_JUNJA;
    case VK_FINAL:
        return grKeycode::GR_KEY_FINAL;
    case VK_KANJI:
        return grKeycode::GR_KEY_KANJI;
    case VK_ESCAPE:
        return grKeycode::GR_KEY_ESCAPE;
    case VK_CONVERT:
        return grKeycode::GR_KEY_CONVERT;
    case VK_NONCONVERT:
        return grKeycode::GR_KEY_NONCONVERT;
    case VK_ACCEPT:
        return grKeycode::GR_KEY_ACCEPT;
    case VK_MODECHANGE:
        return grKeycode::GR_KEY_MODECHANGE;
    case VK_SPACE:
        return grKeycode::GR_KEY_SPACE;
    case VK_PRIOR:
        return grKeycode::GR_KEY_PRIOR;
    case VK_NEXT:
        return grKeycode::GR_KEY_NEXT;
    case VK_END:
        return grKeycode::GR_KEY_END;
    case VK_HOME:
        return grKeycode::GR_KEY_HOME;
    case VK_LEFT:
        return grKeycode::GR_KEY_LEFT;
    case VK_UP:
        return grKeycode::GR_KEY_UP;
    case VK_RIGHT:
        return grKeycode::GR_KEY_RIGHT;
    case VK_DOWN:
        return grKeycode::GR_KEY_DOWN;
    case VK_SELECT:
        return grKeycode::GR_KEY_SELECT;
    case VK_PRINT:
        return grKeycode::GR_KEY_PRINT;
    case VK_EXECUTE:
        return grKeycode::GR_KEY_EXECUTE;
    case VK_SNAPSHOT:
        return grKeycode::GR_KEY_SNAPSHOT;
    case VK_INSERT:
        return grKeycode::GR_KEY_INSERT;
    case VK_DELETE:
        return grKeycode::GR_KEY_DELETE;
    case VK_HELP:
        return grKeycode::GR_KEY_HELP;
    case '0':
        return grKeycode::GR_KEY_0;
    case '1':
        return grKeycode::GR_KEY_1;
    case '2':
        return grKeycode::GR_KEY_2;
    case '3':
        return grKeycode::GR_KEY_3;
    case '4':
        return grKeycode::GR_KEY_4;
    case '5':
        return grKeycode::GR_KEY_5;
    case '6':
        return grKeycode::GR_KEY_6;
    case '7':
        return grKeycode::GR_KEY_7;
    case '8':
        return grKeycode::GR_KEY_8;
    case '9':
        return grKeycode::GR_KEY_9;
    case 'A':
        return grKeycode::GR_KEY_A;
    case 'B':
        return grKeycode::GR_KEY_B;
    case 'C':
        return grKeycode::GR_KEY_C;
    case 'D':
        return grKeycode::GR_KEY_D;
    case 'E':
        return grKeycode::GR_KEY_E;
    case 'F':
        return grKeycode::GR_KEY_F;
    case 'G':
        return grKeycode::GR_KEY_G;
    case 'H':
        return grKeycode::GR_KEY_H;
    case 'I':
        return grKeycode::GR_KEY_I;
    case 'J':
        return grKeycode::GR_KEY_J;
    case 'K':
        return grKeycode::GR_KEY_K;
    case 'L':
        return grKeycode::GR_KEY_L;
    case 'M':
        return grKeycode::GR_KEY_M;
    case 'N':
        return grKeycode::GR_KEY_N;
    case 'O':
        return grKeycode::GR_KEY_O;
    case 'P':
        return grKeycode::GR_KEY_P;
    case 'Q':
        return grKeycode::GR_KEY_Q;
    case 'R':
        return grKeycode::GR_KEY_R;
    case 'S':
        return grKeycode::GR_KEY_S;
    case 'T':
        return grKeycode::GR_KEY_T;
    case 'U':
        return grKeycode::GR_KEY_U;
    case 'V':
        return grKeycode::GR_KEY_V;
    case 'W':
        return grKeycode::GR_KEY_W;
    case 'X':
        return grKeycode::GR_KEY_X;
    case 'Y':
        return grKeycode::GR_KEY_Y;
    case 'Z':
        return grKeycode::GR_KEY_Z;
    case VK_LWIN:
        return grKeycode::GR_KEY_LWIN;
    case VK_RWIN:
        return grKeycode::GR_KEY_RWIN;
    case VK_APPS:
        return grKeycode::GR_KEY_APPS;
    case VK_SLEEP:
        return grKeycode::GR_KEY_SLEEP;
    case VK_NUMPAD0:
        return grKeycode::GR_KEY_NUMPAD0;
    case VK_NUMPAD1:
        return grKeycode::GR_KEY_NUMPAD1;
    case VK_NUMPAD2:
        return grKeycode::GR_KEY_NUMPAD2;
    case VK_NUMPAD3:
        return grKeycode::GR_KEY_NUMPAD3;
    case VK_NUMPAD4:
        return grKeycode::GR_KEY_NUMPAD4;
    case VK_NUMPAD5:
        return grKeycode::GR_KEY_NUMPAD5;
    case VK_NUMPAD6:
        return grKeycode::GR_KEY_NUMPAD6;
    case VK_NUMPAD7:
        return grKeycode::GR_KEY_NUMPAD7;
    case VK_NUMPAD8:
        return grKeycode::GR_KEY_NUMPAD8;
    case VK_NUMPAD9:
        return grKeycode::GR_KEY_NUMPAD9;
    case VK_MULTIPLY:
        return grKeycode::GR_KEY_MULTIPLY;
    case VK_ADD:
        return grKeycode::GR_KEY_ADD;
    case VK_SEPARATOR:
        return grKeycode::GR_KEY_SEPARATOR;
    case VK_SUBTRACT:
        return grKeycode::GR_KEY_SUBTRACT;
    case VK_DECIMAL:
        return grKeycode::GR_KEY_DECIMAL;
    case VK_DIVIDE:
        return grKeycode::GR_KEY_DIVIDE;
    case VK_F1:
        return grKeycode::GR_KEY_F1;
    case VK_F2:
        return grKeycode::GR_KEY_F2;
    case VK_F3:
        return grKeycode::GR_KEY_F3;
    case VK_F4:
        return grKeycode::GR_KEY_F4;
    case VK_F5:
        return grKeycode::GR_KEY_F5;
    case VK_F6:
        return grKeycode::GR_KEY_F6;
    case VK_F7:
        return grKeycode::GR_KEY_F7;
    case VK_F8:
        return grKeycode::GR_KEY_F8;
    case VK_F9:
        return grKeycode::GR_KEY_F9;
    case VK_F10:
        return grKeycode::GR_KEY_F10;
    case VK_F11:
        return grKeycode::GR_KEY_F11;
    case VK_F12:
        return grKeycode::GR_KEY_F12;
    case VK_F13:
        return grKeycode::GR_KEY_F13;
    case VK_F14:
        return grKeycode::GR_KEY_F14;
    case VK_F15:
        return grKeycode::GR_KEY_F15;
    case VK_F16:
        return grKeycode::GR_KEY_F16;
    case VK_F17:
        return grKeycode::GR_KEY_F17;
    case VK_F18:
        return grKeycode::GR_KEY_F18;
    case VK_F19:
        return grKeycode::GR_KEY_F19;
    case VK_F20:
        return grKeycode::GR_KEY_F20;
    case VK_F21:
        return grKeycode::GR_KEY_F21;
    case VK_F22:
        return grKeycode::GR_KEY_F22;
    case VK_F23:
        return grKeycode::GR_KEY_F23;
    case VK_F24:
        return grKeycode::GR_KEY_F24;
    case VK_NUMLOCK:
        return grKeycode::GR_KEY_NUMLOCK;
    case VK_SCROLL:
        return grKeycode::GR_KEY_SCROLL;
    case VK_OEM_FJ_JISHO:
        return grKeycode::GR_KEY_OEM_FJ_JISHO;
    case VK_OEM_FJ_MASSHOU:
        return grKeycode::GR_KEY_OEM_FJ_MASSHOU;
    case VK_OEM_FJ_TOUROKU:
        return grKeycode::GR_KEY_OEM_FJ_TOUROKU;
    case VK_OEM_FJ_LOYA:
        return grKeycode::GR_KEY_OEM_FJ_LOYA;
    case VK_OEM_FJ_ROYA:
        return grKeycode::GR_KEY_OEM_FJ_ROYA;
    case VK_LSHIFT:
        return grKeycode::GR_KEY_LSHIFT;
    case VK_RSHIFT:
        return grKeycode::GR_KEY_RSHIFT;
    case VK_LCONTROL:
        return grKeycode::GR_KEY_LCONTROL;
    case VK_RCONTROL:
        return grKeycode::GR_KEY_RCONTROL;
    case VK_LMENU:
        return grKeycode::GR_KEY_LMENU;
    case VK_RMENU:
        return grKeycode::GR_KEY_RMENU;
    case VK_BROWSER_BACK:
        return grKeycode::GR_KEY_BROWSER_BACK;
    case VK_BROWSER_FORWARD:
        return grKeycode::GR_KEY_BROWSER_FORWARD;
    case VK_BROWSER_REFRESH:
        return grKeycode::GR_KEY_BROWSER_REFRESH;
    case VK_BROWSER_STOP:
        return grKeycode::GR_KEY_BROWSER_STOP;
    case VK_BROWSER_SEARCH:
        return grKeycode::GR_KEY_BROWSER_SEARCH;
    case VK_BROWSER_FAVORITES:
        return grKeycode::GR_KEY_BROWSER_FAVORITES;
    case VK_BROWSER_HOME:
        return grKeycode::GR_KEY_BROWSER_HOME;
    case VK_VOLUME_MUTE:
        return grKeycode::GR_KEY_VOLUME_MUTE;
    case VK_VOLUME_DOWN:
        return grKeycode::GR_KEY_VOLUME_DOWN;
    case VK_VOLUME_UP:
        return grKeycode::GR_KEY_VOLUME_UP;
    case VK_MEDIA_NEXT_TRACK:
        return grKeycode::GR_KEY_MEDIA_NEXT_TRACK;
    case VK_MEDIA_PREV_TRACK:
        return grKeycode::GR_KEY_MEDIA_PREV_TRACK;
    case VK_MEDIA_STOP:
        return grKeycode::GR_KEY_MEDIA_STOP;
    case VK_MEDIA_PLAY_PAUSE:
        return grKeycode::GR_KEY_MEDIA_PLAY_PAUSE;
    case VK_LAUNCH_MAIL:
        return grKeycode::GR_KEY_LAUNCH_MAIL;
    case VK_LAUNCH_MEDIA_SELECT:
        return grKeycode::GR_KEY_LAUNCH_MEDIA_SELECT;
    case VK_LAUNCH_APP1:
        return grKeycode::GR_KEY_LAUNCH_APP1;
    case VK_LAUNCH_APP2:
        return grKeycode::GR_KEY_LAUNCH_APP2;
    case VK_OEM_1:
        return grKeycode::GR_KEY_OEM_1;
    case VK_OEM_PLUS:
        return grKeycode::GR_KEY_OEM_PLUS;
    case VK_OEM_COMMA:
        return grKeycode::GR_KEY_OEM_COMMA;
    case VK_OEM_MINUS:
        return grKeycode::GR_KEY_OEM_MINUS;
    case VK_OEM_PERIOD:
        return grKeycode::GR_KEY_OEM_PERIOD;
    case VK_OEM_2:
        return grKeycode::GR_KEY_OEM_2;
    case VK_OEM_3:
        return grKeycode::GR_KEY_OEM_3;
    case VK_OEM_4:
        return grKeycode::GR_KEY_OEM_4;
    case VK_OEM_5:
        return grKeycode::GR_KEY_OEM_5;
    case VK_OEM_6:
        return grKeycode::GR_KEY_OEM_6;
    case VK_OEM_7:
        return grKeycode::GR_KEY_OEM_7;
    case VK_OEM_8:
        return grKeycode::GR_KEY_OEM_8;
    case VK_OEM_AX:
        return grKeycode::GR_KEY_OEM_AX;
    case VK_OEM_102:
        return grKeycode::GR_KEY_OEM_102;
    case VK_ICO_HELP:
        return grKeycode::GR_KEY_ICO_HELP;
    case VK_ICO_00:
        return grKeycode::GR_KEY_ICO_00;
    case VK_PROCESSKEY:
        return grKeycode::GR_KEY_PROCESSKEY;
    case VK_ICO_CLEAR:
        return grKeycode::GR_KEY_ICO_CLEAR;
    case VK_PACKET:
        return grKeycode::GR_KEY_PACKET;
    case VK_OEM_RESET:
        return grKeycode::GR_KEY_OEM_RESET;
    case VK_OEM_JUMP:
        return grKeycode::GR_KEY_OEM_JUMP;
    case VK_OEM_PA1:
        return grKeycode::GR_KEY_OEM_PA1;
    case VK_OEM_PA2:
        return grKeycode::GR_KEY_OEM_PA2;
    case VK_OEM_PA3:
        return grKeycode::GR_KEY_OEM_PA3;
    case VK_OEM_WSCTRL:
        return grKeycode::GR_KEY_OEM_WSCTRL;
    case VK_OEM_CUSEL:
        return grKeycode::GR_KEY_OEM_CUSEL;
    case VK_OEM_ATTN:
        return grKeycode::GR_KEY_OEM_ATTN;
    case VK_OEM_FINISH:
        return grKeycode::GR_KEY_OEM_FINISH;
    case VK_OEM_COPY:
        return grKeycode::GR_KEY_OEM_COPY;
    case VK_OEM_AUTO:
        return grKeycode::GR_KEY_OEM_AUTO;
    case VK_OEM_ENLW:
        return grKeycode::GR_KEY_OEM_ENLW;
    case VK_OEM_BACKTAB:
        return grKeycode::GR_KEY_OEM_BACKTAB;
    case VK_ATTN:
        return grKeycode::GR_KEY_ATTN;
    case VK_CRSEL:
        return grKeycode::GR_KEY_CRSEL;
    case VK_EXSEL:
        return grKeycode::GR_KEY_EXSEL;
    case VK_EREOF:
        return grKeycode::GR_KEY_EREOF;
    case VK_PLAY:
        return grKeycode::GR_KEY_PLAY;
    case VK_ZOOM:
        return grKeycode::GR_KEY_ZOOM;
    case VK_NONAME:
        return grKeycode::GR_KEY_NONAME;
    case VK_PA1:
        return grKeycode::GR_KEY_PA1;
    case VK_OEM_CLEAR:
        return grKeycode::GR_KEY_OEM_CLEAR;
    default:
        return grKeycode::GR_KEY_UNKNOWN;
    }
}

LRESULT grUiNativeFramePlatformImpl::wndProc(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT) {
        PAINTSTRUCT pst;
        HDC dc = BeginPaint(m_hwnd, &pst);
        EndPaint(m_hwnd, &pst);
        return 0;
    } else if (uMsg == WM_MOUSEMOVE) {
        emitMouseMoveEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

        return 0;
    } else if (uMsg == WM_MOUSELEAVE) {
        emitMouseLeaveEvent();
        return 0;
    } else if (uMsg == WM_SETFOCUS) {
        if (m_windowVisible) {
            gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference
            m_frame->set_focused(true);
        }
        return 0;
    } else if (uMsg == WM_KILLFOCUS) {
        if (m_windowVisible) {
            gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference
            m_frame->set_focused(false);
        }
        return 0;
    } else if (uMsg == WM_WINDOWPOSCHANGED) {
        gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference
        RECT rc;
        GetWindowRect(m_hwnd, &rc);
        grDimension dim = { static_cast<int>(rc.right - rc.left), static_cast<int>(rc.bottom - rc.top) };
        m_oldBounds     = { static_cast<int>(rc.left), static_cast<int>(rc.top), dim.width, dim.height };
        m_frame->set_bounds(m_oldBounds);
        if (m_videoOut) {
            RECT rcClient;
            GetClientRect(m_hwnd, &rcClient);

            m_videoOut->resizeBackbuffers(rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
        }
        return 0;
    } else if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP) {
        gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference

        int scancode = (HIWORD(lParam) & (KF_EXTENDED | 0xff));
        if (!scancode) {
            scancode = MapVirtualKeyW((UINT)wParam, MAPVK_VK_TO_VSC);
        }

        int mods = 0;
        if (GetKeyState(VK_CONTROL) & 0x8000) {
            mods |= GR_KEY_MOD_CTRL | GR_KEY_MOD_CTRL_OR_CMD;
        }
        if (GetKeyState(VK_SHIFT) & 0x8000) {
            mods |= GR_KEY_MOD_SHIFT;
        }
        if (GetKeyState(VK_MENU) & 0x8000) {
            mods |= GR_KEY_MOD_ALT;
        }
        if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000) {
            mods |= GR_KEY_MOD_SUPER;
        }

        grKeyAction action = (HIWORD(lParam) & KF_UP) ? GR_ACTION_KEY_RELEASED : GR_ACTION_KEY_PRESSED;
        bool repeat        = lParam & (1 << 30);
        int repeatCount    = LOWORD(lParam);

        grUiEventKeyPress ev;
        ev.mods     = mods;
        ev.scancode = scancode;
        ev.keycode  = translateKeycode(wParam, lParam);

        for (int i = 0; i < repeatCount; i++) {
            if (repeat && action == GR_ACTION_KEY_PRESSED) {
                action = GR_ACTION_KEY_REPEATED;
            }
            ev.action = action;
            m_frame->eventSink_keyEvent.emit(ev);
            repeat = true;
        }
        return 0;
    } else if (uMsg == WM_LBUTTONDOWN || uMsg == WM_RBUTTONDOWN || uMsg == WM_MBUTTONDOWN || uMsg == WM_XBUTTONDOWN ||
               uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONUP || uMsg == WM_MBUTTONUP || uMsg == WM_XBUTTONUP) {
        gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference

        int mouseButton;
        if (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP) {
            mouseButton = 0;
        }
        if (uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP) {
            mouseButton = 1;
        }
        if (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP) {
            mouseButton = 2;
        }
        if (uMsg == WM_XBUTTONDOWN || uMsg == WM_XBUTTONUP) {
            int xbwparm = GET_XBUTTON_WPARAM(wParam);
            if (xbwparm == XBUTTON1) {
                mouseButton = 3;
            } else if (xbwparm == XBUTTON2) {
                mouseButton = 4;
            } else {
                mouseButton = 0;
            }
        }

        int mods = 0;
        if (GET_KEYSTATE_WPARAM(wParam) & MK_CONTROL) {
            mods |= GR_KEY_MOD_CTRL | GR_KEY_MOD_CTRL_OR_CMD;
        }
        if (GET_KEYSTATE_WPARAM(wParam) & MK_SHIFT) {
            mods |= GR_KEY_MOD_SHIFT;
        }
        if (GetKeyState(VK_MENU) & 0x8000) {
            mods |= GR_KEY_MOD_ALT;
        }
        if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000) {
            mods |= GR_KEY_MOD_SUPER;
        }

        if (uMsg == WM_LBUTTONDOWN || uMsg == WM_RBUTTONDOWN || uMsg == WM_MBUTTONDOWN || uMsg == WM_XBUTTONDOWN) {
            grUiEventMouseDown ev;
            ev.button = mouseButton;
            ev.x      = m_oldX;
            ev.y      = m_oldY;
            if (m_frame->get_parent() && m_frame->get_parent()->usesNativeChildEventBehavior()) {
                grPoint winPos = m_frame->get_position();

                grUiEventMouseDown ev1;
                ev1.button = ev.button;
                ev1.x      = ev.x + winPos.x;
                ev1.y      = ev.y + winPos.y;
                m_frame->get_parent()->eventSink_mouseDown.emit(ev1);
            }
            m_frame->eventSink_mouseDown.emit(ev);
        } else if (uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONUP || uMsg == WM_MBUTTONUP || uMsg == WM_XBUTTONUP) {
            grUiEventMouseUp ev;
            ev.button = mouseButton;
            ev.x      = m_oldX;
            ev.y      = m_oldY;
            if (m_frame->get_parent() && m_frame->get_parent()->usesNativeChildEventBehavior()) {
                grPoint winPos = m_frame->get_position();

                grUiEventMouseUp ev1;
                ev1.button = ev.button;
                ev1.x      = ev.x + winPos.x;
                ev1.y      = ev.y + winPos.y;
                m_frame->get_parent()->eventSink_mouseUp.emit(ev1);
            }
            m_frame->eventSink_mouseUp.emit(ev);
        }

        return 0;
    } else if (uMsg == WM_CHAR) {
        gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference

        grUiEventTextInput ev;
        ev.c = wParam;
        m_frame->eventSink_textInput.emit(ev);
        return FALSE;
    } else if (uMsg == WM_MOUSEWHEEL) {
        gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference

        int mods = 0;
        if (GET_KEYSTATE_WPARAM(wParam) & MK_CONTROL) {
            mods |= GR_KEY_MOD_CTRL | GR_KEY_MOD_CTRL_OR_CMD;
        }
        if (GET_KEYSTATE_WPARAM(wParam) & MK_SHIFT) {
            mods |= GR_KEY_MOD_SHIFT;
        }
        if (GetKeyState(VK_MENU) & 0x8000) {
            mods |= GR_KEY_MOD_ALT;
        }
        if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000) {
            mods |= GR_KEY_MOD_SUPER;
        }

        grUiEventMouseWheel ev;
        ev.x     = m_oldX;
        ev.y     = m_oldY;
        ev.delta = GET_WHEEL_DELTA_WPARAM(wParam);
        ev.mods  = mods;
        if (m_frame->get_parent() && m_frame->get_parent()->usesNativeChildEventBehavior()) {
            grPoint winPos = m_frame->get_position();

            grUiEventMouseWheel ev1 = ev;
            ev1.x += winPos.x;
            ev1.y += winPos.y;
            m_frame->get_parent()->eventSink_mouseWheel.emit(ev1);
        }
        m_frame->eventSink_mouseWheel.emit(ev);
        return 0;
    } else if (uMsg == WM_CLOSE) {
        gnaPointer<grUiWidget> tmpPtr = m_frame; // store a temporary reference

        m_frame->get_parent()->remove(m_frame);
        return 0;
    } else {
        return DefWindowProcW(m_hwnd, uMsg, wParam, lParam);
    }
}

void grUiNativeFramePlatformImpl::update() {
    grUiNativeFramePlatform::update();

    auto newBounds = m_frame->get_bounds();
    if (newBounds != m_oldBounds) {
        SetWindowPos(m_hwnd, NULL, newBounds.x, newBounds.y, newBounds.width, newBounds.height, SWP_NOACTIVATE);
    }
}

bool grUiNativeFramePlatformImpl::updateNativeBorderInsets(gnaWeakPointer<grUiBorderNative> border) {
    RECT rc{ 0, 0, 0, 0 };
    AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, FALSE, 0);
    return border->updateInsets({
        (int)-rc.left,
        (int)-rc.top,
        (int)rc.right,
        (int)rc.bottom,
    });
}

gnaWeakPointer<grRenderCore::VideoOutput> grUiNativeFramePlatformImpl::get_videoOutput() {
    return m_videoOut;
}

void grUiNativeFramePlatformImpl::nativeWidgetPresent() {
    m_videoOut->swapBuffers();
}

int grUiNativeFramePlatformImpl::get_scaleFactor() {
    HMODULE user32 = GetModuleHandleW(L"user32.dll");

    UINT dpi = 96;

    if (user32) {
        typedef UINT(WINAPI * PFNGetDpiForWindow)(HWND hwnd);
        auto fnGetDpiForWindow = (PFNGetDpiForWindow)GetProcAddress(user32, "GetDpiForWindow");
        if (fnGetDpiForWindow) {
            dpi = fnGetDpiForWindow(m_hwnd);
        }
    }
    return dpi * 100 / 96;
}
