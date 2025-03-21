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

#include <gtlMath2/Quaternion/Quaternion.h>
#include <gtlTypeInfo/TypeInfo.h>

#include <gtlUtil/Misc.h>
#include <gtlMath2/Vector/Vector3.h>
#include <gtlMath2/Matrix/Matrix4x3.h>
#include <gtlMath2/Math2DLL.h>

namespace gtlMath2 {
    struct Transform {
        Vector3f translation;
        Quaternionf rotation;
        float scale;

        void makeIdentity() {
            scale       = 1.0f;
            rotation    = { 1.0f, 0.0f, 0.0f, 0.0f };
            translation = { 0.0f, 0.0f, 0.0f };
        }

        Transform operator*(const Transform &other) const {
            Transform ret;

            ret.scale       = scale * other.scale;
            ret.rotation    = rotation * other.rotation;
            auto tr         = other.translation * rotation;
            ret.translation = translation + scale * tr;

            return ret;
        }

        Matrix4x3f toMatrix4x3() const {
            Matrix4x3f rotationMatrix(rotation);
            Matrix4x3f matrix = {
                { rotationMatrix[0][0] * scale, rotationMatrix[0][1] * scale, rotationMatrix[0][2] * scale },
                { rotationMatrix[1][0] * scale, rotationMatrix[1][1] * scale, rotationMatrix[1][2] * scale },
                { rotationMatrix[2][0] * scale, rotationMatrix[2][1] * scale, rotationMatrix[2][2] * scale },
                { translation.x, translation.y, translation.z }
            };
            return matrix;
        }
    };

    struct LocalTransform {
        Vector3f translation;
        float scale;
        Vector3f rotation; // euler angle rotation XYZ

        constexpr void makeIdentity() {
            scale       = 1.0f;
            rotation    = { 0.0f, 0.0f, 0.0f };
            translation = { 0.0f, 0.0f, 0.0f };
        }

        explicit operator Transform() const {
            Transform ret;
            ret.scale = scale;
            ret.rotation = Quaternionf::fromEuler(rotation.x, rotation.y, rotation.z);
            ret.translation = translation;
            return ret;
        }
    };
}

GTL_TYPE_INFO_EXPORTED_DECLARE(GTL_MATH2_DLLIMPEXP, gtlMath2::Transform);
GTL_TYPE_INFO_EXPORTED_DECLARE(GTL_MATH2_DLLIMPEXP, gtlMath2::LocalTransform);
