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

#include "VectorTraits.h"
#include "VectorCommon.h"
#include <gtlMath2/MathUtils.h>
#include <gtlUtil/Misc.h>
#include <cassert>

namespace gtlMath2 {
    template <typename T>
    struct Vector2 : VectorBase<2> {
        T x = 0;
        T y = 0;

        constexpr Vector2() = default;
        constexpr Vector2(T val) : x(val), y(val) {}
        constexpr Vector2(T x, T y) : x(x), y(y) {}

        constexpr Vector2 operator+(const Vector2 &other) const {
            return { x + other.x, y + other.y };
        }

        constexpr Vector2 &operator+=(const Vector2 &other) {
            x += other.x;
            y += other.y;

            return *this;
        }

        GTL_FORCEINLINE constexpr T &operator[](int i) {
            switch (i) {
            case 0: return x;
            case 1: return y;
            default: assert(false);
            }
            std::unreachable();
        }

        GTL_FORCEINLINE constexpr const T &operator[](int i) const {
            switch (i) {
            case 0: return x;
            case 1: return y;
            default: assert(false);
            }
            std::unreachable();
        }

        template <typename U>
        constexpr explicit operator Vector2<U>() const {
            return { static_cast<U>(x), static_cast<U>(y) };
        }
    };

    template <>
    struct SizedVector_Base<2> {
        template <typename T>
        using type = Vector2<T>;
    };

    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>;
}
