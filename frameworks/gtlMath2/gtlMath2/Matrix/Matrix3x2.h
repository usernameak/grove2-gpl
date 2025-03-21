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

#include <gtlMath2/Vector/Vector3.h>
#include <cmath>

namespace gtlMath2 {
    struct Matrix3x2f {
        // row major
        Vector3f m[2]{ { 1, 0, 0 }, { 0, 1, 0 } };

        constexpr Matrix3x2f()                   = default; // identity matrix
        constexpr Matrix3x2f(const Matrix3x2f &) = default;
        constexpr Matrix3x2f(const Vector2f &col0, const Vector2f &col1, const Vector2f &col2) {
            m[0][0] = col0.x;
            m[0][1] = col1.x;
            m[0][2] = col2.x;
            m[1][0] = col0.y;
            m[1][1] = col1.y;
            m[1][2] = col2.y;
        }

        constexpr Matrix3x2f &operator=(const Matrix3x2f &) = default;

        constexpr Matrix3x2f &makeIdentity() {
            m[0][0] = 1;
            m[0][1] = 0;
            m[0][2] = 0;
            m[1][0] = 0;
            m[1][1] = 1;
            m[1][2] = 0;

            return *this;
        }

        constexpr Vector2f operator*(const Vector3f &vec) const {
            return { vec.x * m[0][0] + vec.y * m[0][1] + vec.z * m[0][2],
                vec.x * m[1][0] + vec.y * m[1][1] + vec.z * m[1][2] };
        }

        constexpr Matrix3x2f &operator*=(const Matrix3x2f &o) {
            Matrix3x2f tmp = *this;

            m[0][0] = tmp.m[0][0] * o.m[0][0] + tmp.m[0][1] * o.m[1][0];
            m[0][1] = tmp.m[0][0] * o.m[0][1] + tmp.m[0][1] * o.m[1][1];
            m[0][2] = tmp.m[0][0] * o.m[0][2] + tmp.m[0][1] * o.m[1][2] + tmp.m[0][2];
            m[1][0] = tmp.m[1][0] * o.m[0][0] + tmp.m[1][1] * o.m[1][0];
            m[1][1] = tmp.m[1][0] * o.m[0][1] + tmp.m[1][1] * o.m[1][1];
            m[1][2] = tmp.m[1][0] * o.m[0][2] + tmp.m[1][1] * o.m[1][2] + tmp.m[1][2];

            return *this;
        }

        constexpr Matrix3x2f operator*(const Matrix3x2f &o) const {
            Matrix3x2f tmp = *this;
            tmp *= o;
            return tmp;
        }

        constexpr Matrix3x2f &translate(const Vector2f &vec) {
            m[0][2] = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2];
            m[1][2] = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2];

            return *this;
        }

        /* constexpr */ Matrix3x2f &rotate(float angle) { // no constexpr std::sin/cos for us :(
            Matrix3x2f rotMat{
                { std::cos(angle), std::sin(angle) },
                { -std::sin(angle), std::cos(angle) },
                { 0.f, 0.f }
            };

            return operator*=(rotMat);
        }
    };
}
