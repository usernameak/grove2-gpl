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

#include "SceneObject.h"

#include <gtlMath2/Transform/TransformSerializers.h>
#include <grScene/SceneNode.h>
#include <nxfSerialization/NXFFileWriter.h>
#include <nxfSerialization/NXFFileReader.h>

GTL_DEFINE_OBJECT_CLONE(grScene::SceneObject);
GTL_RTTI_DEFINE(grScene::SceneObject, GTL_RTTI_INHERITS(gtlObject));
GTL_OBJECT_PROPERTY_TABLE_DEFINE(
    grScene::SceneObject,
    gtlObject,
    gtlProperty::create<grScene::SceneObject, gtlMath2::LocalTransform, &grScene::SceneObject::m_localTransform>("m_localTransform")
);
NXF_SERIALIZABLE_DEFINE(grScene::SceneObject, GR_SCENE_DLLIMPEXP);

grScene::SceneObject::SceneObject() {
    m_localTransform.makeIdentity();
    m_globalTransform.makeIdentity();
    m_sourceTransform.makeIdentity();
    m_globalBounds = { 0, 0 };
}

grScene::SceneObject::~SceneObject() = default;

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grScene::SceneObject::serializationImpl(TSerializationInterface &proxy) {
    GNA_CHECK_STATUS(gtlObject::serializationImpl(proxy));

    GNA_CHECK_STATUS(proxy.serialize("name", name));
    GNA_CHECK_STATUS(proxy.serialize("localTransform", m_localTransform));

    return GNA_E_OK;
}

void grScene::SceneObject::set_parent(gnaWeakPointer<grScene::Node> parent) {
    this->m_parent = parent;
}

void grScene::SceneObject::update(float deltaTime) {
    updateGlobalTransforms();
}

void grScene::SceneObject::postUpdate(float deltaTime) {
    updateGlobalBounds();
}

void grScene::SceneObject::updateGlobalTransforms() {
    if (m_parent) {
        m_globalTransform = m_parent->m_globalTransform * m_sourceTransform * gtlMath2::Transform(m_localTransform);
    } else {
        m_globalTransform = m_sourceTransform * gtlMath2::Transform(m_localTransform);
    }
}

void grScene::SceneObject::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    gtlObject::cloneMembers(dest, cctx);

    gnaWeakPointer<SceneObject> cDest = dest.cast<SceneObject>();
    cDest->name                       = name;
    cDest->m_localTransform           = m_localTransform;
}

void grScene::SceneObject::staticInit() {
}

void grScene::SceneObject::staticRelease() {
}
