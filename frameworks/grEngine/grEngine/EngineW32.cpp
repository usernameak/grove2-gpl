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

#include "EngineW32.h"

#include <gtlUtil/Logging.h>
#include <gtlMemory/MemAlloc.h>

// This thing implements an ultimately overcomplicated event loop.
// Reasons, you would ask? Some UI-related WinAPI functions are
// synchronous (e.g. DoDragDrop()) so we need to run game loop one
// way or another. This way is dirty but, well, it works.

#define EPUMP_WINDOW_CLASS L"GroveEngine_Engine_EventPump_WindowClass"

using namespace grEngine;

EngineW32::EngineW32(IEngineApplication *app) : Engine(app) {
    WNDCLASSEXW wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEXW);
    wc.lpszClassName = EPUMP_WINDOW_CLASS;
    wc.hInstance     = GetModuleHandleW(NULL);
    wc.lpfnWndProc   = stEventPumpWndProc;

    if (!RegisterClassExW(&wc)) {
        GR_FATAL(GTXT("cannot register event pump window class"));
    }

    m_dummyPumpWindow = CreateWindowExW(
        0,
        EPUMP_WINDOW_CLASS,
        L"GroveEngine: EventPump",
        0,
        0, 0,
        0, 0,
        HWND_MESSAGE,
        NULL,
        GetModuleHandleW(NULL),
        this);
}

EngineW32::~EngineW32() {
    DestroyWindow(m_dummyPumpWindow);
}

DWORD EngineW32::eventPumpThread() {
    while (true) {
        if (!SendMessageW(m_dummyPumpWindow, WM_USER, 0, 0)) {
            return 0;
        }
    }
}

DWORD EngineW32::stEventPumpThread(LPVOID self) {
    return ((EngineW32 *)self)->eventPumpThread();
}

void EngineW32::eventLoopIteration() {
    MSG msg;

    if (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);

        m_taskQueue.enqueue([this]() { eventLoopIteration(); });
    }
}

void EngineW32::runEventLoop() {
    m_pumpThread = CreateThread(NULL, 0, stEventPumpThread, this, 0, NULL);

    m_taskQueue.enqueue([this]() { eventLoopIteration(); });

    m_taskQueue.runLoop();

    MSG msg;
    // dispatch all the remaining messages
    while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    WaitForSingleObject(m_pumpThread, INFINITE);
}

LRESULT EngineW32::stEventPumpWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    EngineW32 *self;
    if (uMsg == WM_NCCREATE) {
        LPCREATESTRUCTW lpcs    = reinterpret_cast<LPCREATESTRUCTW>(lParam);
        self                    = static_cast<EngineW32 *>(lpcs->lpCreateParams);
        self->m_dummyPumpWindow = hwnd;
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    } else {
        self = reinterpret_cast<EngineW32 *>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    }
    if (self) {
        return self->eventPumpWndProc(
            uMsg,
            wParam,
            lParam);
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT EngineW32::eventPumpWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT) {
        PAINTSTRUCT ps;
        BeginPaint(m_dummyPumpWindow, &ps);
        EndPaint(m_dummyPumpWindow, &ps);
        return 0;
    } else if (uMsg == WM_USER) {
        if (m_taskQueue.get_policy() == gtl::Concurrency::TaskQueue::POLICY_FORCE_TERMINATE) {
            return 0;
        }
        static int64_t perfFreq = -1;

        LARGE_INTEGER liTime;
        QueryPerformanceCounter(&liTime);
        int64_t time      = liTime.QuadPart;
        int64_t deltaTime = renderEndTime == 0 ? 0 : (time - renderEndTime);
        if (perfFreq == -1) {
            LARGE_INTEGER liFreq;
            QueryPerformanceFrequency(&liFreq);
            perfFreq = liFreq.QuadPart;
        }
        float deltaTimeF = static_cast<double>(deltaTime) / perfFreq;
        renderEndTime    = time;

        tick(deltaTimeF);
        return 1;
    }
    return DefWindowProcW(m_dummyPumpWindow, uMsg, wParam, lParam);
}

Engine *Engine::createEngine(IEngineApplication *app) {
    return gtlNew EngineW32(app);
}
