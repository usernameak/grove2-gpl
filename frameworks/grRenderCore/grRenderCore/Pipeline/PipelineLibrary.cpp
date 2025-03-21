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

#include "PipelineLibrary.h"

#include <nxfSerialization/PrimitiveSerializers.h>
#include <nxfSerialization/NXFFileWriter.h>
#include <nxfSerialization/NXFFileReader.h>
#include "PipelineObject.h"

GTL_RTTI_DEFINE(grRenderCore::PipelineLibrary, GTL_RTTI_INHERITS(gtlObject));
NXF_SERIALIZABLE_DEFINE(grRenderCore::PipelineLibrary, GR_RENDERCORE_DLLIMPEXP);

grRenderCore::PipelineLibrary::PipelineLibrary() = default;
grRenderCore::PipelineLibrary::~PipelineLibrary() = default;

void grRenderCore::PipelineLibrary::addPipeline(gnaPointer<PipelineObject> pipeline) {
    PipelineKey key {
        .name = pipeline->get_name(),
        .vertexFormat = pipeline->get_vertexFormat(),
        .blendMode = pipeline->get_blendMode(),
        .keywords = pipeline->get_keywords()
    };
    m_pipelineMap[key] = pipeline;
}

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grRenderCore::PipelineLibrary::serializationImpl(TSerializationInterface &proxy) {
    GNA_CHECK_STATUS(gtlObject::serializationImpl(proxy));

    GNA_CHECK_STATUS(proxy.serialize("pipelineMap", m_pipelineMap));

    return GNA_E_OK;
}
