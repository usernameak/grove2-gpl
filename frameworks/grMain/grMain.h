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

#ifdef _WIN32
#define GR_MAIN_CALLCONV __stdcall
#else
#define GR_MAIN_CALLCONV
#endif

#ifdef __cplusplus
extern "C"
#endif
int GR_MAIN_CALLCONV grMain(int argc, gtl::WIDECHAR **wargv);

#ifdef _WIN32
#ifndef _WIN64
#pragma comment(linker, "/include:_wmain")
#else
#pragma comment(linker, "/include:wmain")
#endif
#endif
