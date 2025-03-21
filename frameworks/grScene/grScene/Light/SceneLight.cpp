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

#include "SceneLight.h"

GTL_RTTI_DEFINE(grScene::Light, GTL_RTTI_INHERITS(grScene::SceneObject));

// === //

NXF_SERIALIZABLE_DEFINE(grScene::DirectionalLight, GR_SCENE_DLLIMPEXP);
GTL_DEFINE_OBJECT_CLONE(grScene::DirectionalLight);
GTL_RTTI_DEFINE(grScene::DirectionalLight, GTL_RTTI_INHERITS(grScene::Light));

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grScene::DirectionalLight::serializationImpl(TSerializationInterface &proxy) {
    GNA_CHECK_STATUS(grScene::SceneObject::serializationImpl(proxy));

    GNA_CHECK_STATUS(proxy.serialize("r", m_color.r));
    GNA_CHECK_STATUS(proxy.serialize("g", m_color.g));
    GNA_CHECK_STATUS(proxy.serialize("b", m_color.b));

    return GNA_E_OK;
}

void grScene::DirectionalLight::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    grScene::SceneObject::cloneMembers(dest, cctx);

    gnaWeakPointer<grScene::DirectionalLight> cDest = dest.cast<grScene::DirectionalLight>();

    cDest->m_color = m_color;
}
