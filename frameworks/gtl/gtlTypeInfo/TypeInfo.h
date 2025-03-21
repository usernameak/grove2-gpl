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

#include <gtlUtil/Misc.h>
#include <concepts>

class gtlTypeInfo {
    const char *m_className;

public:
    constexpr explicit gtlTypeInfo(const char *className) noexcept
        : m_className(className) {}

    const char *get_className() const { return m_className; }

    template <typename T>
    static const gtlTypeInfo *of();
};

template <typename>
struct gtlTypeInfoImpl {
};

#define GTL_TYPE_INFO_DECLARE(T)           \
    template <>                            \
    struct gtlTypeInfoImpl<::T> {          \
        static const gtlTypeInfo typeInfo; \
    }

#define GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(DECLSPEC, T) \
    template <>                                               \
    struct DECLSPEC gtlTypeInfoImpl<T> {                      \
        static const gtlTypeInfo typeInfo;                    \
    }

#define GTL_TYPE_INFO_EXPORTED_DECLARE(DECLSPEC, T) GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(DECLSPEC, ::T)

#define GTL_TYPE_INFO_IMPLEMENT_PRIMITIVE(DECLSPEC, T) \
    DECLSPEC const gtlTypeInfo gtlTypeInfoImpl<T>::typeInfo { #T }

#define GTL_TYPE_INFO_IMPLEMENT(DECLSPEC, T) GTL_TYPE_INFO_IMPLEMENT_PRIMITIVE(DECLSPEC, ::T)

GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, char);
GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, signed char);
GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, unsigned char);

GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, short);
GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, unsigned short);

GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, int);
GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, unsigned int);

GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, long);
GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, unsigned long);

GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, long long);
GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, unsigned long long);

GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, float);
GTL_TYPE_INFO_EXPORTED_DECLARE_PRIMITIVE(GTL_DLLIMPEXP, double);

class gtlRTTI;

template <typename T>
concept HasRTTI = requires() {
    {
        &T::st_rtti
    } -> std::convertible_to<const gtlRTTI *>;
};

template <typename T>
const gtlTypeInfo *gtlTypeInfo::of() {
    if constexpr (HasRTTI<T>) {
        return &T::st_rtti;
    } else {
        return &gtlTypeInfoImpl<T>::typeInfo;
    }
}
