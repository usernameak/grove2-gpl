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

#include <concepts>
#include <cmath>
#include <gtlMath2/Vector/VectorTraits.h>

#ifdef GTL_MATH_USE_SSE2
#include <xmmintrin.h>
#endif

namespace gtlMath2 {
    template<class T>
    constexpr T pi = T(3.1415926535897932385L);

    template <typename T>
    T divFloor(T a, T b) {
        int d = a / b;
        return d * b == a ? d : d - ((a < 0) ^ (b < 0));
    }

    template <typename T>
    T modFloor(T i, T n) {
        return (i % n + n) % n;
    }

    template <typename T>
    T modulo(T value, T m) {
        T mod = value % m;
        if (mod < 0) {
            mod += m;
        }
        return mod;
    }

    template <VectorOrNumeric T>
    T lerp(T a, T b, UnderlyingNumericType<T> val) {
        return a * (T(1) - val) + b * val;
    }

    template <VectorType T>
    T lerp(T a, T b, T val) {
        return a * (T(1) - val) + b * val;
    }

    template <VectorType T>
    constexpr T min(T a, T b) {
        T vec;
        for (int i = 0; i < T::numComponents; i++) {
            vec[i] = a[i] < b[i] ? a[i] : b[i];
        }
        return vec;
    }

    template <VectorType T>
    constexpr T max(T a, T b) {
        T vec;
        for (int i = 0; i < T::numComponents; i++) {
            vec[i] = a[i] > b[i] ? a[i] : b[i];
        }
        return vec;
    }

    template <typename T>
    T rsqrt(T val) {
        return T(1) / std::sqrt(val);
    }

#ifdef GTL_MATH_USE_SSE2
    inline float rsqrt(float val) {
        __m128 m = _mm_set_ss(val);
        m = _mm_rsqrt_ss(m);
        return _mm_cvtss_f32(m);
    }
#endif

    template <typename T>
    T rcp(T val) {
        return T(1) / val;
    }

#ifdef GTL_MATH_USE_SSE2
    inline float rcp(float val) {
        __m128 m = _mm_set_ss(val);
        m = _mm_rcp_ss(m);
        return _mm_cvtss_f32(m);
    }
#endif
}