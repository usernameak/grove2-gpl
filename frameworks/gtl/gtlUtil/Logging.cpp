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

#include "Logging.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <cstdio>
#include <cwchar>
#include <cstdarg>
#include <gtlMemory/MemAlloc.h>

bool grLog_useWindowsDebugOutput = true;

void grLogShowErrorMessageBox(const gtl::WIDECHAR *format, ...) {
    va_list args;
    va_list argscopy;
    va_start(args, format);
    va_copy(argscopy, args);
    int length = gtl::VSPrintf(NULL, 0, format, args);
    va_end(args);
    if (length < 0) {
        va_end(argscopy);
        GR_FATAL(GTXT("error logging message"));
        return;
    }
    gtl::WIDECHAR *str = gtlNew gtl::WIDECHAR[length + 1];
    gtl::VSPrintf(str, length + 1, format, argscopy);
    va_end(argscopy);
#ifdef _WIN32
    if (grLog_useWindowsDebugOutput) {
        MessageBoxW(NULL, str, L"Error", MB_OK | MB_ICONERROR);
        OutputDebugStringW(str);
        OutputDebugStringW(L"\n");
    } else {
#endif
        fputws(str, stderr);
        fputwc((wchar_t) GTXT('\n'), stderr);
#ifdef _WIN32
    }
#endif
    gtlDeleteArray str;
} 

void grLogMessage(const gtl::WIDECHAR *format, ...) {
    va_list args;
    va_list argscopy;
    va_start(args, format);
    va_copy(argscopy, args);
    int length = gtl::VSPrintf(NULL, 0, format, args);
    va_end(args);
    if (length < 0) {
        va_end(argscopy);
        GR_FATAL(GTXT("error logging message"));
        return;
    }
    gtl::WIDECHAR *str = gtlNew gtl::WIDECHAR[length + 1];
    gtl::VSPrintf(str, length + 1, format, argscopy);
    va_end(argscopy);
#ifdef _WIN32
    if (grLog_useWindowsDebugOutput) {
        OutputDebugStringW(str);
        OutputDebugStringW(L"\n");
    } else {
#endif
        fputws(str, stderr);
        fputwc((wchar_t) GTXT('\n'), stderr);
#ifdef _WIN32
    }
#endif
    gtlDeleteArray str;
}
