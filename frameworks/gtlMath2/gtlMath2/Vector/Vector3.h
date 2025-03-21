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

#include "Vector2.h"

namespace gtlMath2 {
    template <typename T>
    struct Vector3 : VectorBase<3> {
        T x = 0;
        T y = 0;
        T z = 0;

        constexpr Vector3() = default;
        constexpr Vector3(T val) : x(val), y(val), z(val) {}
        constexpr Vector3(const Vector2<T> &vec, T z) : x(vec.x), y(vec.y), z(z) {}
        constexpr Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

        GTL_FORCEINLINE constexpr T &operator[](int i) {
            switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: assert(false);
            }
            std::unreachable();
        }

        GTL_FORCEINLINE constexpr const T &operator[](int i) const {
            switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: assert(false);
            }
            std::unreachable();
        }

        constexpr bool operator==(const Vector3 &other) const {
            return x == other.x && y == other.y && z == other.z;
        }

        constexpr bool operator!=(const Vector3 &other) const {
            return !operator==(other);
        }

        template <typename U>
        constexpr explicit operator Vector3<U>() const {
            return { static_cast<U>(x), static_cast<U>(y), static_cast<U>(z) };
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

        constexpr Vector3<T> &normalize() {
            T ilen = invLength();
            x *= ilen;
            y *= ilen;
            z *= ilen;
            return *this;
        }

        constexpr Vector3<T> normalized() {
            T ilen = invLength();
            return { x * ilen, y * ilen, z * ilen };
        }
    };

    template <typename T>
    constexpr Vector3<T> cross(Vector3<T> a, Vector3<T> b) {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
        };
    }

    template <>
    struct SizedVector_Base<3> {
        template <typename T>
        using type = Vector3<T>;
    };

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
    using Vector3i = Vector3<int>;
    using Vector3b = Vector3<bool>;
}
