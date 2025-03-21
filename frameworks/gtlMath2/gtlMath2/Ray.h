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

#include "Vector/Vector3.h"
#include "AABB.h"

namespace gtlMath2 {
    struct Ray {
        Vector3f origin;
        Vector3f dir;

        bool intersectAABB(const AABB &bbox, float &intersectionDistance) const {
            if (all(greaterOrEqual(origin, bbox.min)) && all(lessOrEqual(origin, bbox.max))) {
                intersectionDistance = 0;

                return true;
            }

            Vector3f plane = lerp(bbox.max, bbox.min, static_cast<Vector3f>(greater(dir, { 0, 0, 0 })));
            Vector3f t     = (plane - origin) / dir;

            int maxIdx = 0;
            for (int i = 1; i < 3; i++) {
                if (t[i] > t[maxIdx]) {
                    maxIdx = i;
                }
            }

            if (t[maxIdx] >= 0.0f) {
                Vector3f actualT = at(t[maxIdx]);

                int i1 = (maxIdx + 1) % 3;
                int i2 = (maxIdx + 2) % 3;

                if (actualT[i1] >= bbox.min[i1] && actualT[i1] <= bbox.max[i1] &&
                    actualT[i2] >= bbox.min[i2] && actualT[i2] <= bbox.max[i2]) {
                    intersectionDistance = minPerComponent(actualT);
                    return true;
                }
            }

            return false;
        }

        bool intersectTriangle(const Vector3f &v0, const Vector3f &v1, const Vector3f &v2, float &intersectionDistance) const {
            const float EPSILON = 0.0000001;
            Vector3f e1         = v1 - v0;
            Vector3f e2         = v2 - v0;
            Vector3f h          = cross(dir, e2);
            float a             = dot(e1, h);
            if (a > -EPSILON && a < EPSILON) {
                return false;
            }
            float f     = 1.0f / a;
            Vector3f s = origin - v0;
            float u     = f * dot(s, h);
            if (u < 0.0f || u > 1.0f) {
                return false;
            }
            Vector3f q = cross(s, e1);
            float v     = f * dot(dir, q);
            if (v < 0.0f || u + v >= 1.0f) {
                return false;
            }
            float t = f * dot(e2, q);
            if (t > EPSILON) {
                intersectionDistance = t;
                return true;
            } else {
                return false;
            }
        }

        Vector3f at(float p) const {
            return origin + dir * p;
        }
    };
}
