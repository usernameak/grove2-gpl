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

#include <gtlMath2/Vector/Vector4.h>
#ifdef GTL_MATH_USE_SSE2
#include "thirdparty/small-matrix-inverse/invert4x4_sse.h"
#else
#include "thirdparty/small-matrix-inverse/invert4x4_c.h"
#endif

namespace gtlMath2 {
    struct Matrix4x4f {
        // row major
        Vector4f m[4]{ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

        constexpr Matrix4x4f()                   = default; // identity matrix
        constexpr Matrix4x4f(const Matrix4x4f &) = default;
        constexpr Matrix4x4f(const Vector4f &col0, const Vector4f &col1, const Vector4f &col2, const Vector4f &col3) {
            m[0][0] = col0.x;
            m[0][1] = col1.x;
            m[0][2] = col2.x;
            m[0][3] = col3.x;
            m[1][0] = col0.y;
            m[1][1] = col1.y;
            m[1][2] = col2.y;
            m[1][3] = col3.y;
            m[2][0] = col0.z;
            m[2][1] = col1.z;
            m[2][2] = col2.z;
            m[2][3] = col3.z;
            m[3][0] = col0.w;
            m[3][1] = col1.w;
            m[3][2] = col2.w;
            m[3][3] = col3.w;
        }

        const float *valuePtr() const {
            return reinterpret_cast<const float *>(m);
        }

        float *valuePtr() {
            return reinterpret_cast<float *>(m);
        }

        constexpr Vector4f operator*(const Vector4f &vec) const {
            return {
                vec.x * m[0][0] + vec.y * m[0][1] + vec.z * m[0][2] + vec.w * m[0][3],
                vec.x * m[1][0] + vec.y * m[1][1] + vec.z * m[1][2] + vec.w * m[1][3],
                vec.x * m[2][0] + vec.y * m[2][1] + vec.z * m[2][2] + vec.w * m[2][3],
                vec.x * m[3][0] + vec.y * m[3][1] + vec.z * m[3][2] + vec.w * m[3][3]
            };
        }

        constexpr Matrix4x4f &operator*=(const Matrix4x4f &o) {
            Matrix4x4f tmp = *this;

            m[0][0] = tmp.m[0][0] * o.m[0][0] + tmp.m[0][1] * o.m[1][0] + tmp.m[0][2] * o.m[2][0] + tmp.m[0][3] * o.m[3][0];
            m[0][1] = tmp.m[0][0] * o.m[0][1] + tmp.m[0][1] * o.m[1][1] + tmp.m[0][2] * o.m[2][1] + tmp.m[0][3] * o.m[3][1];
            m[0][2] = tmp.m[0][0] * o.m[0][2] + tmp.m[0][1] * o.m[1][2] + tmp.m[0][2] * o.m[2][2] + tmp.m[0][3] * o.m[3][2];
            m[0][3] = tmp.m[0][0] * o.m[0][3] + tmp.m[0][1] * o.m[1][3] + tmp.m[0][2] * o.m[2][3] + tmp.m[0][3] * o.m[3][3];

            m[1][0] = tmp.m[1][0] * o.m[0][0] + tmp.m[1][1] * o.m[1][0] + tmp.m[1][2] * o.m[2][0] + tmp.m[1][3] * o.m[3][0];
            m[1][1] = tmp.m[1][0] * o.m[0][1] + tmp.m[1][1] * o.m[1][1] + tmp.m[1][2] * o.m[2][1] + tmp.m[1][3] * o.m[3][1];
            m[1][2] = tmp.m[1][0] * o.m[0][2] + tmp.m[1][1] * o.m[1][2] + tmp.m[1][2] * o.m[2][2] + tmp.m[1][3] * o.m[3][2];
            m[1][3] = tmp.m[1][0] * o.m[0][3] + tmp.m[1][1] * o.m[1][3] + tmp.m[1][2] * o.m[2][3] + tmp.m[1][3] * o.m[3][3];

            m[2][0] = tmp.m[2][0] * o.m[0][0] + tmp.m[2][1] * o.m[1][0] + tmp.m[2][2] * o.m[2][0] + tmp.m[2][3] * o.m[3][0];
            m[2][1] = tmp.m[2][0] * o.m[0][1] + tmp.m[2][1] * o.m[1][1] + tmp.m[2][2] * o.m[2][1] + tmp.m[2][3] * o.m[3][1];
            m[2][2] = tmp.m[2][0] * o.m[0][2] + tmp.m[2][1] * o.m[1][2] + tmp.m[2][2] * o.m[2][2] + tmp.m[2][3] * o.m[3][2];
            m[2][3] = tmp.m[2][0] * o.m[0][3] + tmp.m[2][1] * o.m[1][3] + tmp.m[2][2] * o.m[2][3] + tmp.m[2][3] * o.m[3][3];

            m[3][0] = tmp.m[3][0] * o.m[0][0] + tmp.m[3][1] * o.m[1][0] + tmp.m[3][2] * o.m[2][0] + tmp.m[3][3] * o.m[3][0];
            m[3][1] = tmp.m[3][0] * o.m[0][1] + tmp.m[3][1] * o.m[1][1] + tmp.m[3][2] * o.m[2][1] + tmp.m[3][3] * o.m[3][1];
            m[3][2] = tmp.m[3][0] * o.m[0][2] + tmp.m[3][1] * o.m[1][2] + tmp.m[3][2] * o.m[2][2] + tmp.m[3][3] * o.m[3][2];
            m[3][3] = tmp.m[3][0] * o.m[0][3] + tmp.m[3][1] * o.m[1][3] + tmp.m[3][2] * o.m[2][3] + tmp.m[3][3] * o.m[3][3];

            return *this;
        }

        constexpr Matrix4x4f operator*(const Matrix4x4f &o) const {
            Matrix4x4f tmp = *this;
            tmp *= o;
            return tmp;
        }

        GTL_FORCEINLINE constexpr Vector4f &operator[](int i) {
            return m[i];
        }

        GTL_FORCEINLINE constexpr const Vector4f &operator[](int i) const {
            return m[i];
        }

        static Matrix4x4f perspectiveLH(float fovy, float aspect, float zNear, float zFar) {
            assert(aspect > 0.0f);

            const float height = 1.f / std::tan(fovy / 2.f);
            const float width = height / aspect;
            const float range = zFar / (zFar - zNear);

            Matrix4x4f mat;
            mat[0][0] = width;
            mat[1][1] = height;
            mat[2][2] = range;
            mat[3][3] = 0.0f;
            mat[3][2] = 1.f;
            mat[2][3] = -range * zNear;
            return mat;
        }

        static Matrix4x4f lookAtLH(const Vector3f &eye, const Vector3f &center, const Vector3f &up) {
            Vector3f f(center - eye);
            f.normalize();
            Vector3f s(cross(up, f));
            s.normalize();
            Vector3f u(cross(f, s));
            Matrix4x4f mat;
            mat[0][0] = s.x;
            mat[0][1] = s.y;
            mat[0][2] = s.z;
            mat[1][0] = u.x;
            mat[1][1] = u.y;
            mat[1][2] = u.z;
            mat[2][0] = f.x;
            mat[2][1] = f.y;
            mat[2][2] = f.z;
            mat[0][3] = -dot(s, eye);
            mat[1][3] = -dot(u, eye);
            mat[2][3] = -dot(f, eye);
            return mat;
        }

        constexpr static Matrix4x4f ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
            float reciprocalWidth = 1.0f / (right - left);
            float reciprocalHeight = 1.0f / (top - bottom);
            float fRange = 1.0f / (zFar - zNear);
            return {
                {reciprocalWidth + reciprocalWidth, 0.f, 0.f, 0.f},
                {0.f, reciprocalHeight + reciprocalHeight, 0.f, 0.f},
                {0.f, 0.f, fRange, 0.f},
                {-(left + right) * reciprocalWidth, -(top + bottom) * reciprocalHeight, -fRange * zNear, 1.f},
            };
        }

        constexpr Matrix4x4f &translate(const Vector4f &vec) {
            m[0][3] = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3] * vec.w;
            m[1][3] = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3] * vec.w;
            m[2][3] = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3] * vec.w;
            m[3][3] = m[3][0] * vec.x + m[3][1] * vec.y + m[3][2] * vec.z + m[3][3] * vec.w;

            return *this;
        }

        constexpr Matrix4x4f &translate(const Vector3f &vec) {
            return translate({ vec, 1.f });
        }

        Matrix4x4f &inverse() {
            Matrix4x4f tmp;
            invert4x4(valuePtr(), tmp.valuePtr());
            return *this = tmp;
        }
    };
}
