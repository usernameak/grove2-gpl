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

#include "SceneNode.h"

#include <nxfSerialization/NXFFileWriter.h>
#include <nxfSerialization/NXFFileReader.h>

NXF_SERIALIZABLE_DEFINE(grScene::Node, GR_SCENE_DLLIMPEXP);
GTL_DEFINE_OBJECT_CLONE(grScene::Node);
GTL_RTTI_DEFINE(grScene::Node, GTL_RTTI_INHERITS(grScene::SceneObject));

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grScene::Node::serializationImpl(TSerializationInterface &proxy) {
    GNA_CHECK_STATUS(grScene::SceneObject::serializationImpl(proxy));

    if (proxy.get_direction() == nxfSerialization::SerializationDirection::READ) {
        uint32_t count = 0;
        GNA_CHECK_STATUS(proxy.beginList("children", count));
        for (uint32_t i = 0; i < count; i++) {
            gnaPointer<grScene::SceneObject> child;
            GNA_CHECK_STATUS(proxy.serialize(nullptr, child));
            addChild(child);
        }
        GNA_CHECK_STATUS(proxy.endList());
    } else {
        uint32_t count = 0;
        for (gnaWeakPointer<grScene::SceneObject> child = m_firstChild; child; child = child->nextSibling()) {
            count++;
        }
        GNA_CHECK_STATUS(proxy.beginList("children", count));
        for (gnaWeakPointer<grScene::SceneObject> child = m_firstChild; child; child = child->nextSibling()) {
            GNA_CHECK_STATUS(proxy.serialize(nullptr, child));
        }
        GNA_CHECK_STATUS(proxy.endList());
    }

    return GNA_E_OK;
}

void grScene::Node::update(float deltaTime) {
    grScene::SceneObject::update(deltaTime);

    for (gnaWeakPointer<grScene::SceneObject> node = m_firstChild; node; node = node->nextSibling()) {
        node->m_sourceTransform.makeIdentity();
        node->update(deltaTime);
    }
}

void grScene::Node::postUpdate(float deltaTime) {
    for (gnaWeakPointer<grScene::SceneObject> node = m_firstChild; node; node = node->nextSibling()) {
        node->postUpdate(deltaTime);
    }

    grScene::SceneObject::postUpdate(deltaTime);
}

void grScene::Node::updateGlobalBounds() {
    m_globalBounds = { INFINITY, -INFINITY }; // FIXME: this stuff will not work with -ffast-math
    for (gnaWeakPointer<grScene::SceneObject> node = m_firstChild; node; node = node->nextSibling()) {
        m_globalBounds.merge(node->m_globalBounds);
    }
}

bool grScene::Node::rayCast(const gtlMath2::Ray &ray, grScene::RayCastResult &result) {
    if (grScene::SceneObject::rayCast(ray, result)) {
        return true;
    }

    bool found = false;

    for (gnaWeakPointer<grScene::SceneObject> node = m_firstChild; node; node = node->nextSibling()) {
        float aabbIDist;
        if (ray.intersectAABB(node->m_globalBounds, aabbIDist)) {
            if (aabbIDist < result.intersectionDistance) {
                if (node->rayCast(ray, result)) {
                    found = true;
                }
            }
        }
    }

    return found;
}

void grScene::Node::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    grScene::SceneObject::cloneMembers(dest, cctx);

    gnaWeakPointer<grScene::Node> cDest = dest.cast<grScene::Node>();

    gnaWeakPointer<grScene::SceneObject> child = m_firstChild;
    while (child) {
        cDest->addChild(child);
        child = child->nextSibling();
    }
}

void grScene::Node::addChild(gnaWeakPointer<grScene::SceneObject> obj) {
    if (m_firstChild) {
        m_lastChild->m_nextSibling = obj;
        obj->m_prevSibling         = m_lastChild;
    } else {
        m_firstChild = obj;
    }
    m_lastChild   = obj;
    obj->m_parent = this;
}

void grScene::Node::removeChild(gnaWeakPointer<grScene::SceneObject> obj) {
    assert(obj->m_parent == this);

    obj->m_parent = nullptr;

    gnaWeakPointer<grScene::SceneObject> prevSibling = obj->m_prevSibling;
    gnaPointer<grScene::SceneObject> nextSibling     = obj->m_nextSibling;

    if (nextSibling) {
        nextSibling->m_prevSibling = prevSibling;
        obj->m_nextSibling         = nullptr;
    } else if (m_lastChild == obj) {
        m_lastChild = nullptr;
    } else {
        assert(false);
    }

    if (m_firstChild == obj) {
        m_firstChild = nullptr;
    } else if (prevSibling) {
        obj->m_prevSibling         = nullptr;
        prevSibling->m_nextSibling = std::move(nextSibling);
    } else {
        assert(false);
    }
}
