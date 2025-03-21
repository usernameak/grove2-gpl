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

#include <cassert>
#include <gtlMath2/Vector/Vector3.h>
#include <gtlMath2/MathUtils.h>
#include <gtlMath2/Matrix/Matrix4x4.h>
#include <gtlMath2/Matrix/Matrix4x3.h>

namespace gtlMath2 {
    template <typename T>
    struct Quaternion {
        T x = 0, y = 0, z = 0, w = 1;

    public:
        constexpr Quaternion() = default;
        constexpr Quaternion(T w, T x, T y, T z) : x(x), y(y), z(z), w(w) {}

        const T *valuePtr() const {
            return &x;
        }

        T *valuePtr() {
            return &x;
        }

        constexpr T &operator[](int i) {
            switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: assert(false);
            }
            return x;
        }

        constexpr T operator[](int i) const {
            switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: assert(false);
            }
            return 0;
        }

        template <typename U>
        constexpr explicit operator Quaternion<U>() const {
            return { static_cast<U>(x), static_cast<U>(y), static_cast<U>(z), static_cast<U>(w) };
        }

        constexpr Quaternion &operator*=(const Quaternion &o) {
            float newW = w * o.w - x * o.x - y * o.y - z * o.z;
            float newX = w * o.x + x * o.w + y * o.z - z * o.y;
            float newY = w * o.y - x * o.z + y * o.w + z * o.x;
            float newZ = w * o.z + x * o.y - y * o.x + z * o.w;

            w = newW;
            x = newX;
            y = newY;
            z = newZ;

            return *this;
        }

        constexpr Quaternion operator*(const Quaternion &o) const {
            Quaternion res = *this;
            res *= o;
            return res;
        }

        Quaternion &inverse() {
            float r = rcp(x * x + y * y + z * z + w * w);
            x *= -r;
            y *= -r;
            z *= -r;
            w *= r;
            return *this;
        }

        constexpr explicit operator Matrix4x4f() const {
            Matrix4x4f mat;
            mat[0] = {
                2.f * (w * w + x * x) - 1.f,
                2.f * (x * y - w * z),
                2.f * (x * z + w * y),
                0.0f
            };
            mat[1] = {
                2.f * (x * y + w * z),
                2.f * (w * w + y * y) - 1.f,
                2.f * (y * z - w * x),
                0.0f
            };
            mat[2] = {
                2 * (x * z - w * y),
                2 * (y * z + w * x),
                2 * (w * w + z * z) - 1.f,
                0.0f
            };
            mat[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
            return mat;
        }

        constexpr explicit operator Matrix4x3f() const {
            Matrix4x3f mat;
            mat[0] = {
                2.f * (w * w + x * x) - 1.f,
                2.f * (x * y - w * z),
                2.f * (x * z + w * y),
                0.0f
            };
            mat[1] = {
                2.f * (x * y + w * z),
                2.f * (w * w + y * y) - 1.f,
                2.f * (y * z - w * x),
                0.0f
            };
            mat[2] = {
                2 * (x * z - w * y),
                2 * (y * z + w * x),
                2 * (w * w + z * z) - 1.f,
                0.0f
            };
            return mat;
        }

        static Quaternion rotationX(T angle) {
            return { std::cos(angle / T(2)), std::sin(angle / T(2)), 0, 0 };
        }

        static Quaternion rotationY(T angle) {
            return { std::cos(angle / T(2)), 0, std::sin(angle / T(2)), 0 };
        }

        static Quaternion rotationZ(T angle) {
            return { std::cos(angle / T(2)), 0, 0, std::sin(angle / T(2)) };
        }

        static Quaternion fromEuler(T x, T y, T z) {
            T cr = std::cos(x * T(0.5));
            T sr = std::sin(x * T(0.5));
            T cp = std::cos(y * T(0.5));
            T sp = std::sin(y * T(0.5));
            T cy = std::cos(z * T(0.5));
            T sy = std::sin(z * T(0.5));

            Quaternion q{
                cr * cp * cy + sr * sp * sy,
                sr * cp * cy - cr * sp * sy,
                cr * sp * cy + sr * cp * sy,
                cr * cp * sy - sr * sp * cy
            };

            return q;
        }

        static Quaternion fromEuler(const Vector3<T> &v) {
            return fromEuler(v.x, v.y, v.z);
        }

        Vector3<T> toEuler() const {
            Vector3<T> angles;

            // roll (x-axis rotation)
            double sinr_cosp = 2 * (w * x + y * z);
            double cosr_cosp = 1 - 2 * (x * x + y * y);
            angles.x         = std::atan2(sinr_cosp, cosr_cosp);

            // pitch (y-axis rotation)
            double sinp = std::sqrt(1 + 2 * (w * y - x * z));
            double cosp = std::sqrt(1 - 2 * (w * y - x * z));
            angles.y    = 2 * std::atan2(sinp, cosp) - pi<float> / 2;

            // yaw (z-axis rotation)
            double siny_cosp = 2 * (w * z + x * y);
            double cosy_cosp = 1 - 2 * (y * y + z * z);
            angles.z         = std::atan2(siny_cosp, cosy_cosp);

            return angles;
        }

        Quaternion &normalize() {
            T ilen = rsqrt(x * x + y * y + z * z + w * w);
            w *= ilen;
            x *= ilen;
            y *= ilen;
            z *= ilen;
            return *this;
        }

        static Quaternion slerp(const Quaternion &q1, const Quaternion &q2, float t) {
            // http://number-none.com/product/Hacking%20Quaternions/index.html

            T cosAlpha = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
            T tp;
            if (t < 0.5f) {
                tp = slerpCorrection(t, cosAlpha);
            } else {
                tp = 1.0f - slerpCorrection(1.0f - t, cosAlpha);
            }

            Quaternion q(
                lerp(q1.w, q2.w, tp),
                lerp(q1.x, q2.x, tp),
                lerp(q1.y, q2.y, tp),
                lerp(q1.z, q2.z, tp));
            q.normalize();
            return q;
        }

    private:
        static GTL_FORCEINLINE T slerpCorrection(T t, T cosAlpha) {
            const float ATTENUATION = 0.8228677f;
            const float K           = 0.5855064f;

            T factor = T(1 - ATTENUATION * cosAlpha);
            factor *= factor;
            float k = K * factor;

            T b = T(2) * k;
            T c = T(-3) * k;
            T d = T(1) + k;

            T tprime_divided_by_t = t * (b * t + c) + d;
            return t * tprime_divided_by_t;
        }
    };

    template <typename T>
    Vector3<T> &operator*=(Vector3<T> &vec, const Quaternion<T> &q) {
        // https://gamedev.stackexchange.com/a/50545
        Vector3<T> u{ q.x, q.y, q.z };
        T s = q.w;
        vec = T(2) * dot(u, vec) * u + (s * s - u.lengthSquared()) * vec + T(2) * s * cross(u, vec);
        return vec;
    }

    template <typename T>
    Vector3<T> operator*(const Vector3<T> &vec, const Quaternion<T> &q) {
        Vector3<T> newVec = vec;
        newVec *= q;
        return newVec;
    }

    using Quaternionf = Quaternion<float>;
}
