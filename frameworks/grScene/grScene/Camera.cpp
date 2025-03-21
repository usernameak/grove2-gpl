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

#include "Camera.h"

GTL_DEFINE_OBJECT_CLONE(grScene::Camera);
GTL_RTTI_DEFINE(grScene::Camera, GTL_RTTI_INHERITS(grScene::SceneObject));
NXF_SERIALIZABLE_DEFINE(grScene::Camera, GR_SCENE_DLLIMPEXP);

void grScene::Camera::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    grScene::SceneObject::cloneMembers(dest, cctx);
}

void grScene::Camera::setupPerspective(float width, float height) {
    projectionMatrix = gtlMath2::Matrix4x4f::perspectiveLH(
        gtlMath2::pi<float> * .5f,
        width / height,
        0.1f,
        1000.0f);
}

void grScene::Camera::update(float deltaTime) {
    grScene::SceneObject::update(deltaTime);

    viewMatrix = gtlMath2::Matrix4x4f::lookAtLH(
        gtlMath2::Vector3f(0.0f, 0.0f, 0.0f),
        gtlMath2::Vector3f(1.0f, 0.0f, 0.0f),
        gtlMath2::Vector3f(0.0f, 0.0f, 1.0f));

    gtlMath2::Quaternionf q = m_globalTransform.rotation;
    q.inverse();
    viewMatrix *= static_cast<gtlMath2::Matrix4x4f>(q);
    viewMatrix.translate(-m_globalTransform.translation);
}

bool grScene::Camera::rayCastAgainst(gnaWeakPointer<grScene::SceneObject> obj, grScene::RayCastResult &result, gtlMath2::Vector2f screenPosition) const {
    auto ray = computeRay(screenPosition);

    float intersectionDistance;
    if (ray.intersectAABB(obj->m_globalBounds, intersectionDistance)) {
        if (obj->rayCast(ray, result)) {
            return true;
        }
    }
    return false;
}

gtlMath2::Ray grScene::Camera::computeRay(gtlMath2::Vector2f screenPosition) const {
    gtlMath2::Matrix4x4f invProjection = projectionMatrix;
    invProjection.inverse();
    gtlMath2::Vector4f origin4 = invProjection * gtlMath2::Vector4f(screenPosition, -1, 1);
    origin4 /= origin4.w;
    gtlMath2::Vector4f end4 = invProjection * gtlMath2::Vector4f(screenPosition, 1, 1);
    end4 /= end4.w;
    gtlMath2::Matrix4x4f invView = viewMatrix;
    invView.inverse();
    origin4 = invView * origin4;
    end4    = invView * end4;

    gtlMath2::Vector3f origin = { origin4.x, origin4.y, origin4.z };
    gtlMath2::Vector3f dir    = gtlMath2::Vector3f{ end4.x, end4.y, end4.z } - origin;
    dir.normalize();

    return { origin, dir };
}

gtlMath2::Vector3f grScene::Camera::worldSpaceToScreenSpace(gtlMath2::Vector3f worldPosition) const {
    gtlMath2::Vector4f pos4(worldPosition, 1);

    pos4 = viewMatrix * pos4;
    pos4 = projectionMatrix * pos4;

    pos4 /= pos4.w;

    return { pos4.x, pos4.y, pos4.z };
}

gtlMath2::Vector3f grScene::Camera::screenSpaceToWorldSpace(gtlMath2::Vector3f screenPosition) const {
    gtlMath2::Matrix4x4f invProjection = projectionMatrix;
    invProjection.inverse();

    gtlMath2::Vector4f pos4 = invProjection * gtlMath2::Vector4f(screenPosition, 1);
    pos4 /= pos4.w;

    gtlMath2::Matrix4x4f invView = viewMatrix;
    invView.inverse();
    pos4 = invView * pos4;

    return { pos4.x, pos4.y, pos4.z };
}
