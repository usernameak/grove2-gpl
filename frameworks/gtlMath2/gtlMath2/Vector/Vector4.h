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

#include "Vector3.h"

namespace gtlMath2 {
    template <typename T>
    struct Vector4 : VectorBase<4> {
        T x = 0;
        T y = 0;
        T z = 0;
        T w = 1;

        constexpr Vector4() = default;
        constexpr Vector4(const Vector2<T> &vec, T z, T w) : x(vec.x), y(vec.y), z(z), w(w) {}
        constexpr Vector4(const Vector3<T> &vec, T w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}
        constexpr Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

        const T *valuePtr() const {
            return &x;
        }

        T *valuePtr() {
            return &x;
        }

        GTL_FORCEINLINE constexpr T &operator[](int i) {
            switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: assert(false);
            }
            std::unreachable();
        }

        GTL_FORCEINLINE constexpr const T &operator[](int i) const {
            switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: assert(false);
            }
            std::unreachable();
        }

        constexpr bool operator==(const Vector4 &other) const {
            return x == other.x && y == other.y && z == other.z && z == other.w;
        }

        constexpr bool operator!=(const Vector4 &other) const {
            return !operator==(other);
        }

        template <typename U>
        constexpr explicit operator Vector4<U>() const {
            return { static_cast<U>(x), static_cast<U>(y), static_cast<U>(z), static_cast<U>(w) };
        }

        constexpr T lengthSquared() const {
            return dot(*this, *this);
        }

        T length() const {
            return std::sqrt(lengthSquared());
        }

        T invLength() const {
            return rsqrt(lengthSquared());
        }
    };

    template <>
    struct SizedVector_Base<4> {
        template <typename T>
        using type = Vector4<T>;
    };

    using Vector4f = Vector4<float>;
    using Vector4i = Vector4<int>;
}
