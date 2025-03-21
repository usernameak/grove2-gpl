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

#include "PipelineObject.h"

GTL_RTTI_DEFINE(grRenderCore::PipelineObject, GTL_RTTI_INHERITS(gtlObject));
GTL_DEFINE_OBJECT_CLONE(grRenderCore::PipelineObject);
NXF_SERIALIZABLE_DEFINE(grRenderCore::PipelineObject, GR_RENDERCORE_DLLIMPEXP);

grRenderCore::PipelineObject::~PipelineObject() = default;

void grRenderCore::PipelineObject::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    gtlObject::cloneMembers(dest, cctx);

    auto destObj = dest.cast<PipelineObject>();
    destObj->m_name = m_name;
    destObj->m_vertexFormat = m_vertexFormat;
    destObj->m_blendMode = m_blendMode;
    destObj->m_keywords = m_keywords;
}

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grRenderCore::PipelineObject::serializationImpl(TSerializationInterface &proxy) {
    GNA_CHECK_STATUS(gtlObject::serializationImpl(proxy));

    GNA_CHECK_STATUS(proxy.serialize("name", m_name));
    GNA_CHECK_STATUS(proxy.serialize("vertexFormat", m_vertexFormat));
    GNA_CHECK_STATUS(proxy.serialize("blendMode", m_blendMode));
    GNA_CHECK_STATUS(proxy.serialize("keywords", m_keywords));

    return GNA_E_OK;
}
