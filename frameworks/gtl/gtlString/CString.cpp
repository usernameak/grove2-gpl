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

#include "CString.h"

#include <gtlMemory/MemAlloc.h>

#include <stdio.h>
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace gtl;

size_t gtl::StrLen(const WIDECHAR *strarg) {
    const WIDECHAR *str = strarg;
    for (; *str; ++str) {
    }
    return str - strarg;
}

WIDECHAR *gtl::StrCpy(WIDECHAR *dest, const WIDECHAR *src) {
    WIDECHAR *save = dest;
    while ((*dest++ = *src++)) {
    }
    return save;
}

int gtl::StrCmp(const WIDECHAR *s1, const WIDECHAR *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const WIDECHAR *)s1 - *(const WIDECHAR *)s2;
}

int gtl::VSPrintf(gtl::WIDECHAR *ws, size_t len, const gtl::WIDECHAR *format, va_list arg) {
#ifdef GTL_WIDECHAR_IS_WCHAR
    return vswprintf(ws, len, format, arg);
#else
#error "Unsupported platform"
#endif
}

double gtl::StrToD(const gtl::WIDECHAR *ws, gtl::WIDECHAR **endptr) {
#ifdef GTL_WIDECHAR_IS_WCHAR
    return wcstod(ws, endptr);
#else
#error "Unsupported platform"
#endif
}

long long gtl::StrToLL(const gtl::WIDECHAR *ws, gtl::WIDECHAR **endptr, int radix) {
#ifdef GTL_WIDECHAR_IS_WCHAR
    return wcstoll(ws, endptr, radix);
#else
#error "Unsupported platform"
#endif
}

WIDECHAR gtl::ToLower(WIDECHAR c) {
    return (WIDECHAR) towlower((wint_t) c);
}

WIDECHAR gtl::ToUpper(WIDECHAR c) {
    return (WIDECHAR) towupper((wint_t) c);
}

ASCIICHAR gtl::ToLower(ASCIICHAR c) {
    return (ASCIICHAR) tolower(c);
}

ASCIICHAR gtl::ToUpper(ASCIICHAR c) {
    return (ASCIICHAR) toupper(c);
}

gtl::ASCIICHAR *gtl::WCSToUTF8(const gtl::WIDECHAR *ws) {
#ifdef _WIN32
    int buffer_size = WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS, ws, -1, NULL, 0, NULL, NULL);
    char *utfString = static_cast<char *>(gtlMalloc(buffer_size));
    WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS, ws, -1, utfString, buffer_size, NULL, NULL);
    return utfString;
#else
#error "Unsupported platform"
#endif
}

void gtl::FreeUTF8(gtl::ASCIICHAR *str) {
    gtlFree(str);
}

size_t gtl::StrLen(const ASCIICHAR *strarg) {
    const ASCIICHAR *str = strarg;
    for (; *str; ++str) {
    }
    return str - strarg;
}

ASCIICHAR *gtl::StrCpy(ASCIICHAR *dest, const ASCIICHAR *src) {
    ASCIICHAR *save = dest;
    while ((*dest++ = *src++)) {
    }
    return save;
}

int gtl::StrCmp(const ASCIICHAR *s1, const ASCIICHAR *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const ASCIICHAR *)s1 - *(const ASCIICHAR *)s2;
}

int gtl::VSPrintf(gtl::ASCIICHAR *str, size_t len, const gtl::ASCIICHAR *format, va_list arg) {
    return vsnprintf(str, len, format, arg);
}

double gtl::StrToD(const gtl::ASCIICHAR *ws, gtl::ASCIICHAR **endptr) {
    return strtod(ws, endptr);
}

unsigned long gtl::StrToUL(const ASCIICHAR *ws, ASCIICHAR **endptr, int radix) {
    return strtoul(ws, endptr, radix);
}

unsigned long gtl::StrToUL(const WIDECHAR *ws, WIDECHAR **endptr, int radix) {
#ifdef GTL_WIDECHAR_IS_WCHAR
    return wcstoul(ws, endptr, radix);
#else
#error "Unsupported platform"
#endif
}

long long gtl::StrToLL(const ASCIICHAR *ws, ASCIICHAR **endptr, int radix) {
    return strtoll(ws, endptr, radix);
}
