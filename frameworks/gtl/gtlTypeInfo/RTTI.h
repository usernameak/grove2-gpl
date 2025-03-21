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
#include <gtlUtil/FourCC.h>
#include "TypeInfo.h"

class gtlRTTI : public gtlTypeInfo {
    const gtlRTTI *m_baseClass;
    gnaFOURCC m_bindingType;
    size_t m_bindingOffset;

public:
    struct RttiCtorArgs {
        const gtlRTTI *baseClass = nullptr;
        gnaFOURCC bindingType    = 0;
        size_t bindingOffset     = 0;
    };

    constexpr explicit gtlRTTI(const char *className, const RttiCtorArgs &args) noexcept
        : gtlTypeInfo(className),
          m_baseClass(args.baseClass),
          m_bindingType(args.bindingType),
          m_bindingOffset(args.bindingOffset) {}

    template <typename T, typename S>
    static T rttiCast(S ptr) {
        static_assert(std::is_pointer_v<T> && std::is_pointer_v<S>, "non-pointer passed to gtlRttiCast");

        if (!ptr) return nullptr;

        const gtlRTTI *cur = ptr->get_rtti();
        while (cur) {
            if (&std::remove_pointer_t<T>::st_rtti == cur) {
                return static_cast<T>(ptr);
            }
            cur = cur->m_baseClass;
        }
        return nullptr;
    }

    template <typename T, typename S>
    static bool isKindOf(const S &ptr) {
        return rttiCast<T *>(&*ptr);
    }

    const gtlRTTI *get_baseClass() const { return m_baseClass; }
    gnaFOURCC get_bindingType() const { return m_bindingType; }
    size_t get_bindingOffset() const { return m_bindingOffset; }
};

#define GTL_RTTI_DECLARE()                                                  \
public:                                                                     \
    GNA_SUPPRESS_OVERRIDE_WARNING_START                                     \
    static const ::gtlRTTI st_rtti;                                         \
    virtual const ::gtlRTTI *get_rtti() const noexcept { return &st_rtti; } \
    GNA_SUPPRESS_OVERRIDE_WARNING_END                                       \
    static_assert(true)

#define GTL_RTTI_INHERITS(clazz) .baseClass = &clazz::st_rtti
#define GTL_RTTI_BINDING(type, offset) .bindingType = GNA_FOURCC(type), .bindingOffset = offset

#define GTL_RTTI_DEFINE(clazz, ...) const ::gtlRTTI(::clazz::st_rtti)(#clazz, { __VA_ARGS__ })

template <typename T, typename S>
T gtlRttiCast(S *ptr) {
    return gtlRTTI::rttiCast<T>(ptr);
}

template <typename T, typename S>
bool gtlIsKindOf(const S &ptr) {
    return gtlRTTI::isKindOf<T>(ptr);
}
