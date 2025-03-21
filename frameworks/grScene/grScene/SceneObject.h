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

#include "SceneDLL.h"

#include <gtlMath2/Transform/Transform.h>
#include <gtlMath2/AABB.h>
#include <gtlMath2/Ray.h>
#include <gtlObject/Object.h>

namespace grScene {
    class Camera;
    class Scene;
    class Node;
    class SceneObject;

    struct RayCastResult {
        gnaWeakPointer<SceneObject> object;
        float intersectionDistance;

        RayCastResult() : object(nullptr), intersectionDistance(INFINITY) {
        }
    };
};

class GR_SCENE_DLLIMPEXP grScene::SceneObject : public gtlObject {
    gnaWeakPointer<SceneObject> m_prevSibling;
    gnaPointer<SceneObject> m_nextSibling;

    friend class Scene;
    friend class Node;

public:
    GTL_DECLARE_ABSTRACT_OBJECT_CLONE;
    GTL_RTTI_DECLARE();
    GTL_OBJECT_PROPERTY_TABLE_DECLARE();
    NXF_SERIALIZABLE_DECLARE();

    gnaWeakPointer<Node> m_parent;

    gtl::PooledString name;
    gtlMath2::LocalTransform m_localTransform;
    /**
     * the transform given to this object by parent node,
     * e.g. the entity transform in world
     */
    gtlMath2::Transform m_sourceTransform;
    gtlMath2::Transform m_globalTransform;
    gtlMath2::AABB m_globalBounds;

public:
    SceneObject();

    ~SceneObject() override = 0;

    template <nxfSerialization::SerializationInterface TSerializationInterface>
    gnaStatus serializationImpl(TSerializationInterface &proxy);

    /**
     * casts ray against the object. this assumes that
     * the ray intersects this objects' AABB unless
     * it's a grScene::Node
     *
     * @param ray - the ray to cast
     * @param result - reference to result of raycast
     * @return whether ray hit the object
     */
    virtual bool rayCast(const gtlMath2::Ray &ray, grScene::RayCastResult &result) {
        return false;
    }

    void set_parent(gnaWeakPointer<grScene::Node> parent);

    virtual void update(float deltaTime);
    virtual void postUpdate(float deltaTime);
    virtual void updateGlobalBounds() {}

    void updateGlobalTransforms();

    static void staticInit();
    static void staticRelease();

    gnaWeakPointer<grScene::SceneObject> prevSibling() const {
        return m_prevSibling;
    }

    gnaWeakPointer<grScene::SceneObject> nextSibling() const {
        return m_nextSibling;
    }
};
