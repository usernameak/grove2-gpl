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

#include <type_traits>
#include <cstdint>
#include <cstdarg>

#include <gtlUtil/Misc.h>

namespace gtl {
#undef StrCmp
#undef StrCpy

#ifdef _WIN32
    typedef wchar_t WIDECHAR;
#define GTXT_PASTE(x) L##x
#define GTL_WIDECHAR_IS_WCHAR 1
#else
    typedef char16_t WIDECHAR;
#define GTXT_PASTE(x) u##x
#endif
#define GTXT(x) GTXT_PASTE(x)

    typedef char ASCIICHAR;

    GTL_DLLIMPEXP size_t StrLen(const WIDECHAR *);
    GTL_DLLIMPEXP WIDECHAR *StrCpy(WIDECHAR *, const WIDECHAR *);
    GTL_DLLIMPEXP int StrCmp(const WIDECHAR *, const WIDECHAR *);
    GTL_DLLIMPEXP int VSPrintf(WIDECHAR *ws, size_t len, const WIDECHAR *format, va_list arg);
    GTL_DLLIMPEXP double StrToD(const WIDECHAR *ws, WIDECHAR **endptr);
    GTL_DLLIMPEXP unsigned long StrToUL(const WIDECHAR *ws, WIDECHAR **endptr, int radix);
    GTL_DLLIMPEXP long long StrToLL(const WIDECHAR *ws, WIDECHAR **endptr, int radix);
    GTL_DLLIMPEXP WIDECHAR ToLower(WIDECHAR c);
    GTL_DLLIMPEXP WIDECHAR ToUpper(WIDECHAR c);
    
    GTL_DLLIMPEXP size_t StrLen(const ASCIICHAR *);
    GTL_DLLIMPEXP ASCIICHAR *StrCpy(ASCIICHAR *, const ASCIICHAR *);
    GTL_DLLIMPEXP int StrCmp(const ASCIICHAR *, const ASCIICHAR *);
    GTL_DLLIMPEXP int VSPrintf(ASCIICHAR *str, size_t len, const ASCIICHAR *format, va_list arg);
    GTL_DLLIMPEXP double StrToD(const ASCIICHAR *ws, ASCIICHAR **endptr);
    GTL_DLLIMPEXP unsigned long StrToUL(const ASCIICHAR *ws, ASCIICHAR **endptr, int radix);
    GTL_DLLIMPEXP long long StrToLL(const ASCIICHAR *ws, ASCIICHAR **endptr, int radix);
    GTL_DLLIMPEXP ASCIICHAR ToLower(ASCIICHAR c);
    GTL_DLLIMPEXP ASCIICHAR ToUpper(ASCIICHAR c);

    GTL_DLLIMPEXP ASCIICHAR *WCSToUTF8(const WIDECHAR *ws);
    GTL_DLLIMPEXP void FreeUTF8(ASCIICHAR *str);
}
