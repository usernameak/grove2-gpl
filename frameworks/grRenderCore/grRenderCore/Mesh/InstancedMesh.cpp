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

#include "InstancedMesh.h"

GTL_RTTI_DEFINE(grRenderCore::InstancedMesh, GTL_RTTI_INHERITS(grRenderCore::Renderable));
NXF_SERIALIZABLE_DEFINE(grRenderCore::InstancedMesh, GR_RENDERCORE_DLLIMPEXP);

grRenderCore::InstancedMesh::InstancedMesh()
    : m_vertexFormat(0),
      m_instanceDataBuffer(nullptr),
      m_instanceCapacity(0),
      m_instanceCount(0),
      m_flags(FLAG_CLEAR_ON_UPLOAD) {}

grRenderCore::InstancedMesh::~InstancedMesh() {
    deallocateInstanceData();
}

void grRenderCore::InstancedMesh::clearInstanceData() {
    m_instanceCount = 0;
}

void grRenderCore::InstancedMesh::deallocateInstanceData() {
    clearInstanceData();

    gtlFree(m_instanceDataBuffer);
    m_instanceDataBuffer = nullptr;

    m_instanceCapacity = 0;
}

void grRenderCore::InstancedMesh::set_vertexFormat(std::underlying_type_t<grRenderCore::VertexFormatFlags> format) {
    if (m_vertexFormat == format) return;

    assert(m_vertexFormat == 0);

    m_vertexFormat             = format;
    m_instanceVertexFormatInfo = InstanceVertexFormatInfo(format);
}

void grRenderCore::InstancedMesh::set_instanceCapacity(uint32_t newCapacity) {
    assert(m_vertexFormat != 0);

    void *newBuffer = gtlRealloc(m_instanceDataBuffer, newCapacity * m_instanceVertexFormatInfo.m_stride);
    if (newCapacity && m_instanceVertexFormatInfo.m_stride && !newBuffer) {
        GR_FATAL(GTXT("Out of CPU memory allocating mesh data"));
    }
    m_instanceDataBuffer = (unsigned char *)newBuffer;

    m_instanceCapacity = newCapacity;
}

void grRenderCore::InstancedMesh::set_instanceCount(uint32_t newCount) {
    if (m_instanceCapacity < newCount) {
        set_instanceCapacity(newCount);
    }
    m_instanceCount = newCount;
}

uint32_t grRenderCore::InstancedMesh::grow_instanceCount(uint32_t amount) {
    uint32_t oldVertexCount = m_instanceCount;
    uint32_t newVertexCount = m_instanceCount + amount;
    if (m_instanceCapacity < newVertexCount) {
        uint32_t newCapacity = m_instanceCapacity + m_instanceCapacity / 2;
        if (newCapacity < newVertexCount) {
            newCapacity = newVertexCount;
        }
        set_instanceCapacity(newCapacity);
    }
    m_instanceCount = newVertexCount;
    return oldVertexCount;
}

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grRenderCore::InstancedMesh::serializationImpl(TSerializationInterface &srl) {
    GNA_CHECK_STATUS(Renderable::serializationImpl(srl));

    auto vertexFormat  = m_vertexFormat;
    auto instanceCount = m_instanceCount;

    GNA_CHECK_STATUS(srl.serialize("vertexFormat", vertexFormat));
    GNA_CHECK_STATUS(srl.serialize("instanceCount", instanceCount));

    if (srl.get_direction() == nxfSerialization::SerializationDirection::READ) {
        set_vertexFormat(vertexFormat);
        set_instanceCount(instanceCount);
    }

    size_t expectedDataSize = m_instanceCount * m_instanceVertexFormatInfo.m_stride;

    if (srl.get_direction() == nxfSerialization::SerializationDirection::WRITE) {
        GNA_CHECK_STATUS(srl.serializeRawData("instanceDataBuffer", m_instanceDataBuffer, expectedDataSize));
    } else if (srl.get_direction() == nxfSerialization::SerializationDirection::READ) {
        size_t size;
        GNA_CHECK_STATUS(srl.deserializeRawDataSize(size));
        if (size != expectedDataSize) {
            return { GNA_E_INVALID_DATA_FORMAT, GTXT("Instanced mesh data size invalid") };
        }

        GNA_CHECK_STATUS(srl.deserializeRawData(m_instanceDataBuffer, size));
    }

    return GNA_E_OK;
}
