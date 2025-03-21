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

#define GNA_XSTR(s) GNA_STR(s)
#define GNA_STR(s) #s

#define GNA_EMPTY

#ifdef __clang__
#define GNA_SUPPRESS_OVERRIDE_WARNING_START \
    _Pragma("clang diagnostic push")        \
        _Pragma("clang diagnostic ignored \"-Winconsistent-missing-override\"")

#define GNA_SUPPRESS_OVERRIDE_WARNING_END \
    _Pragma("clang diagnostic pop")
#else
#define GNA_SUPPRESS_OVERRIDE_WARNING_START
#define GNA_SUPPRESS_OVERRIDE_WARNING_END
#endif

#define GTL_BIT(x) (1 << (x))

#ifdef _MSC_VER
#define GTL_FORCEINLINE __forceinline
#elif defined(__GNUC__)
#define GTL_FORCEINLINE [[gnu::always_inline]]
#else
#define GTL_FORCEINLINE inline
#endif

#ifdef _MSC_VER
#define GTL_UNREACHABLE __assume(0)
#elif defined(__GNUC__)
#define GTL_UNREACHABLE __builtin_unreachable()
#endif

#ifdef _WIN32
#if defined(GTL_BUILD_DLL)
#define GTL_DLLIMPEXP __declspec( dllexport )
#elif defined(GTL_LOAD_DLL)
#define GTL_DLLIMPEXP __declspec( dllimport )
#else
#define GTL_DLLIMPEXP
#endif
#else
#define GTL_DLLIMPEXP
#endif

#ifdef _WIN32
#define GTL_VECTORCALL __vectorcall
#else
#define GTL_VECTORCALL
#endif

#ifdef __RESHARPER__
#define GTL_PASS_BY_VALUE [[jetbrains::pass_by_value]]
#else
#define GTL_PASS_BY_VALUE
#endif
