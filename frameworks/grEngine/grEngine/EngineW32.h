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

#include "Engine.h"
#include <windows.h>

namespace grEngine {
    class EngineW32 : public Engine {
        HWND m_dummyPumpWindow;
        HANDLE m_pumpThread;

    public:
        EngineW32(IEngineApplication *app);
        virtual ~EngineW32();

        DWORD eventPumpThread();
        static DWORD stEventPumpThread(LPVOID);

        void eventLoopIteration();
        void runEventLoop() override;

        static LRESULT CALLBACK stEventPumpWndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
        LRESULT CALLBACK eventPumpWndProc(UINT uMsg, WPARAM wparam, LPARAM lparam);

        uint64_t renderEndTime = 0;
    };
}
