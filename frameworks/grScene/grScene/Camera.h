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

#include "SceneObject.h"

namespace grScene {
    class GR_SCENE_DLLIMPEXP Camera : public grScene::SceneObject {
    public:
        GTL_RTTI_DECLARE();
        GTL_DECLARE_OBJECT_CLONE;
        NXF_SERIALIZABLE_DECLARE();

        gtlMath2::Matrix4x4f projectionMatrix;
        gtlMath2::Matrix4x4f viewMatrix;

        void setupPerspective(float width, float height);
        void update(float deltaTime) override;

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy) {
            return grScene::SceneObject::serializationImpl(proxy);
        }

        /**
         * @brief Casts a ray from this camera against another object
         * @param obj - the object to cast the ray against
         * @param result - reference where the result will be stored
         * @param screenPosition - screen position, [-1, -1] is bottom-left, [1, 1] is top-right, [0, 0] (default) is the center
         * @return whether the ray hit any object
         */
        bool rayCastAgainst(gnaWeakPointer<grScene::SceneObject> obj, grScene::RayCastResult &result, gtlMath2::Vector2f screenPosition = { 0, 0 }) const;

        gtlMath2::Ray computeRay(gtlMath2::Vector2f screenPosition = { 0, 0 }) const;

        gtlMath2::Vector3f worldSpaceToScreenSpace(gtlMath2::Vector3f worldPosition) const;
        gtlMath2::Vector3f screenSpaceToWorldSpace(gtlMath2::Vector3f screenPosition) const;
    };
}
