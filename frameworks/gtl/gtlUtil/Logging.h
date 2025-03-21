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

#include <gtlString/CString.h>
#include <exception>

GTL_DLLIMPEXP void grLogShowErrorMessageBox(const gtl::WIDECHAR *format, ...);
GTL_DLLIMPEXP void grLogMessage(const gtl::WIDECHAR *format, ...);

#define GR_FATAL(...)                                           \
    do {                                                        \
        grLogShowErrorMessageBox(GTXT("[FATAL] ") __VA_ARGS__); \
        std::terminate();                                       \
    } while (false)

#define GR_INFO(...)                               \
    do {                                           \
        grLogMessage(GTXT("[INFO] ") __VA_ARGS__); \
    } while (false)

#define GR_WARNING(...)                            \
    do {                                           \
        grLogMessage(GTXT("[WARN] ") __VA_ARGS__); \
    } while (false)

#define GTL_NOT_IMPLEMENTED GR_FATAL(GTXT("Not implemented: %hs:%d"), __FILE__, __LINE__)

GTL_DLLIMPEXP extern bool grLog_useWindowsDebugOutput;
