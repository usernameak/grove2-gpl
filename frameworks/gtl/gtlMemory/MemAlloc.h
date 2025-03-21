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

#if defined(_MSC_VER) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#endif
#include <stdlib.h>
#include <new>

#define gtlFree free
#define gtlMalloc malloc
#define gtlMallocAligned _aligned_malloc
#define gtlFreeAligned _aligned_free
#define gtlRealloc realloc
#if defined(_DEBUG) && defined(_MSC_VER)
#define gtlNewWithFileLine(file, line) new (_NORMAL_BLOCK, file, line)
#define gtlNewWithFileLineNothrow(file, line) gtlNewWithFileLine(file, line)
#define gtlNew new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define gtlNewNothrow new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define gtlNewWithFileLine(file, line) new
#define gtlNewWithFileLineNothrow(file, line) new (std::nothrow)
#define gtlNew new
#define gtlNewNothrow new (std::nothrow)
#endif
#define gtlDelete delete
#define gtlDeleteArray delete[]
