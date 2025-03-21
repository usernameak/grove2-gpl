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

#include <nxfUtil/BinaryResource.h>
#include <nxfSerialization/PrimitiveSerializers.h>
#include <nxfSerialization/NXFFileWriter.h>
#include <nxfSerialization/NXFFileReader.h>

GTL_RTTI_DEFINE(grDX11::PipelineObject, GTL_RTTI_INHERITS(grRenderCore::PipelineObject));
NXF_SERIALIZABLE_DEFINE(grDX11::PipelineObject, GR_DX11_DLLIMPEXP);

grDX11::PipelineObject::PipelineObject() = default;

grDX11::PipelineObject::~PipelineObject() {
    if (m_renderObject) {
        GR_FATAL(GTXT("Pipeline object not deinitialized correctly"));
    }
}

void grDX11::PipelineObject::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    grRenderCore::PipelineObject::cloneMembers(dest, cctx);

    auto destObj = dest.cast<PipelineObject>();

    destObj->m_vertexShaderBinary = m_vertexShaderBinary->clone(cctx).cast<nxfBinaryResource>();
    destObj->m_pixelShaderBinary  = m_pixelShaderBinary ? m_pixelShaderBinary->clone(cctx).cast<nxfBinaryResource>() : nullptr;

    // TODO: fix missing clone for some members for this and opengl too
}

void grDX11::PipelineObject::set_vertexShaderBinary(gnaPointer<nxfBinaryResource> resource) {
    m_vertexShaderBinary = std::move(resource);
}

void grDX11::PipelineObject::set_pixelShaderBinary(gnaPointer<nxfBinaryResource> resource) {
    m_pixelShaderBinary = std::move(resource);
}

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grDX11::PipelineObject::serializationImpl(TSerializationInterface &proxy) {
    GNA_CHECK_STATUS(grRenderCore::PipelineObject::serializationImpl(proxy));

    GNA_CHECK_STATUS(proxy.serialize("vertexShaderBinary", m_vertexShaderBinary));
    GNA_CHECK_STATUS(proxy.serialize("pixelShaderBinary", m_pixelShaderBinary));

    GNA_CHECK_STATUS(proxy.serialize("primitiveMode", m_primitiveMode));
    GNA_CHECK_STATUS(proxy.serialize("cullMode", m_cullMode));
    GNA_CHECK_STATUS(proxy.serialize("depthTest", m_depthTest));
    GNA_CHECK_STATUS(proxy.serialize("scissorTest", m_scissorTest));

    return GNA_E_OK;
}
