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

namespace gtlMath2 {
    template <VectorType T>
    constexpr auto less(T a, T b) {
        VectorAs<T, bool> vec;
        for (int i = 0; i < T::numComponents; i++) {
            vec[i] = a[i] < b[i];
        }
        return vec;
    }

    template <VectorType T>
    constexpr auto lessOrEqual(T a, T b) {
        VectorAs<T, bool> vec;
        for (int i = 0; i < T::numComponents; i++) {
            vec[i] = a[i] <= b[i];
        }
        return vec;
    }

    template <VectorType T>
    constexpr auto greater(T a, T b) {
        VectorAs<T, bool> vec;
        for (int i = 0; i < T::numComponents; i++) {
            vec[i] = a[i] > b[i];
        }
        return vec;
    }

    template <VectorType T>
    constexpr auto greaterOrEqual(T a, T b) {
        VectorAs<T, bool> vec;
        for (int i = 0; i < T::numComponents; i++) {
            vec[i] = a[i] >= b[i];
        }
        return vec;
    }

    template <VectorType T>
    constexpr auto minPerComponent(T vec) {
        auto val = vec[0];
        for (int i = 1; i < T::numComponents; i++) {
            val = val < vec[i] ? val : vec[i];
        }
        return val;
    }

    template <VectorType T>
    constexpr auto maxPerComponent(T vec) {
        auto val = vec[0];
        for (int i = 1; i < T::numComponents; i++) {
            val = val > vec[i] ? val : vec[i];
        }
        return val;
    }

    template <VectorType T>
    constexpr T &operator+=(T &a, const T &b) {
        for (int i = 0; i < T::numComponents; i++) {
            a[i] += b[i];
        }
        return a;
    }

    template <VectorType T>
    constexpr auto operator+(T a, T b) {
        T vec = a;
        vec += b;
        return vec;
    }

    template <VectorType T>
    constexpr auto operator-(T a, T b) {
        T vec;
        for (int i = 0; i < T::numComponents; i++) {
            vec[i] = a[i] - b[i];
        }
        return vec;
    }

    template <VectorType T>
    constexpr auto operator-(T a, VectorUnderlyingType<T> b) {
        T vec;
        for (int i = 0; i < T::numComponents; i++) {
            vec[i] = a[i] - b;
        }
        return vec;
    }

    template <VectorType T>
    constexpr auto operator-(VectorUnderlyingType<T> a, T b) {
        T vec;
        for (int i = 0; i < T::numComponents; i++) {
            vec[i] = a - b[i];
        }
        return vec;
    }

    template <VectorType T>
    constexpr T &operator*=(T &a, const T &b) {
        for (int i = 0; i < T::numComponents; i++) {
            a[i] *= b[i];
        }
        return a;
    }

    template <VectorType T>
    constexpr T &operator*=(T &a, VectorUnderlyingType<T> b) {
        for (int i = 0; i < T::numComponents; i++) {
            a[i] *= b;
        }
        return a;
    }

    template <VectorType T>
    constexpr T operator*(T a, T b) {
        T vec = a;
        vec *= b;
        return vec;
    }

    template <VectorType T>
    constexpr T operator*(VectorUnderlyingType<T> a, T b) {
        T vec = b;
        vec *= a;
        return vec;
    }

    template <VectorType T>
    constexpr T operator*(T a, VectorUnderlyingType<T> b) {
        T vec = a;
        vec *= b;
        return vec;
    }


    template <VectorType T>
    constexpr T &operator/=(T &a, const T &b) {
        for (int i = 0; i < T::numComponents; i++) {
            a[i] /= b[i];
        }
        return a;
    }

    template <VectorType T>
    constexpr T &operator/=(T &a, VectorUnderlyingType<T> b) {
        for (int i = 0; i < T::numComponents; i++) {
            a[i] /= b;
        }
        return a;
    }

    template <VectorType T>
    constexpr T operator/(T a, T b) {
        T vec = a;
        vec /= b;
        return vec;
    }

    template <VectorType T>
    constexpr T operator/(VectorUnderlyingType<T> a, T b) {
        T vec = b;
        vec /= a;
        return vec;
    }

    template <VectorType T>
    constexpr T operator/(T a, VectorUnderlyingType<T> b) {
        T vec = a;
        vec /= b;
        return vec;
    }

    template <VectorType T>
    constexpr T operator-(T a) {
        T vec;
        for (int i = 0; i < T::numComponents; i++) {
            vec[i] = -a[i];
        }
        return vec;
    }

    template <VectorType T>
    constexpr auto dot(T a, T b) {
        VectorUnderlyingType<T> val{ 0 };
        for (int i = 0; i < T::numComponents; i++) {
            val += a[i] * b[i];
        }
        return val;
    }

    template <VectorType T>
    constexpr bool all(T vec) {
        for (int i = 0; i < T::numComponents; i++) {
            if (!vec[i]) return false;
        }
        return true;
    }

    template <VectorType T>
    constexpr bool any(T vec) {
        for (int i = 0; i < T::numComponents; i++) {
            if (vec[i]) return true;
        }
        return false;
    }

    template <VectorType T>
    constexpr bool none(T vec) {
        return !any<T>(vec);
    }
}
