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

#include "Mesh.h"

#include <gtlMemory/MemAlloc.h>
#include <gtlString/CString.h>
#include <gtlUtil/Logging.h>
#include <gtlMath2/MathUtils.h>
#include <gtlMath2/Vector/VectorSerializers.h>

GTL_RTTI_DEFINE(grRenderCore::Mesh, GTL_RTTI_INHERITS(grRenderCore::Renderable));
NXF_SERIALIZABLE_DEFINE(grRenderCore::Mesh, GR_RENDERCORE_DLLIMPEXP);

grRenderCore::Mesh::Mesh()
    : m_vertexFormat(0),
      m_flags(FLAG_CLEAR_ON_UPLOAD),
      m_primitiveType(TYPE_TRIANGLES),
      m_vertexCount(0),
      m_vertexCapacity(0),
      m_geometryDataBuffer(nullptr),
      m_indexCount(INVALID_INDEX_COUNT),
      m_indexCapacity(0),
      m_indices(nullptr),
      m_bboxMin(-INFINITY), m_bboxMax(INFINITY) {}

grRenderCore::Mesh::~Mesh() {
    deallocateMeshData();
}

void grRenderCore::Mesh::clearMeshData() {
    m_vertexCount = 0;

    if (m_indexCount != INVALID_INDEX_COUNT) {
        m_indexCount = 0;
    }
}
void grRenderCore::Mesh::deallocateMeshData() {
    clearMeshData();

    gtlFree(m_geometryDataBuffer);
    gtlFree(m_indices);

    m_geometryDataBuffer = nullptr;
    m_indices            = nullptr;

    m_vertexCapacity = 0;
    m_indexCapacity  = 0;
}

void grRenderCore::Mesh::set_vertexFormat(std::underlying_type_t<grRenderCore::VertexFormatFlags> format) {
    if (m_vertexFormat == format) return;

    assert(m_vertexFormat == 0);

    m_vertexFormat     = format;
    m_vertexFormatInfo = VertexFormatInfo(format);
}

void grRenderCore::Mesh::set_vertexCapacity(uint32_t newCapacity) {
    assert(m_vertexFormat != 0);

    void *newBuffer = gtlRealloc(m_geometryDataBuffer, newCapacity * m_vertexFormatInfo.m_stride);
    if (newCapacity && m_vertexFormatInfo.m_stride && !newBuffer) {
        GR_FATAL(GTXT("Out of CPU memory allocating mesh data"));
    }
    m_geometryDataBuffer = (unsigned char *)newBuffer;

    m_vertexCapacity = newCapacity;
}

void grRenderCore::Mesh::set_vertexCount(uint32_t newCount) {
    if (m_vertexCapacity < newCount) {
        set_vertexCapacity(newCount);
    }
    m_vertexCount = newCount;
}

uint32_t grRenderCore::Mesh::grow_vertexCount(uint32_t amount) {
    uint32_t oldVertexCount = m_vertexCount;
    uint32_t newVertexCount = m_vertexCount + amount;
    if (m_vertexCapacity < newVertexCount) {
        if (m_flags & FLAG_DONT_GROW_CAPACITY) return GROW_FAILED;

        uint32_t newCapacity = m_vertexCapacity + m_vertexCapacity / 2;
        if (newCapacity < newVertexCount) {
            newCapacity = newVertexCount;
        }
        set_vertexCapacity(newCapacity);
    }
    m_vertexCount = newVertexCount;
    return oldVertexCount;
}

void grRenderCore::Mesh::set_indexCapacity(uint32_t newCapacity) {
    assert(m_indexCount != INVALID_INDEX_COUNT);

    auto newIndexes = (uint32_t *)gtlRealloc(m_indices, sizeof(*m_indices) * newCapacity);
    assert(newIndexes);
    m_indices = newIndexes;

    m_indexCapacity = newCapacity;
}

void grRenderCore::Mesh::set_indexCount(uint32_t newCount) {
    if (m_indexCapacity < newCount) {
        if (m_indexCount == INVALID_INDEX_COUNT) m_indexCount = 0;
        set_indexCapacity(newCount);
    }
    m_indexCount = newCount;
}

uint32_t grRenderCore::Mesh::grow_indexCount(uint32_t amount) {
    uint32_t oldIndexCount = m_indexCount;
    uint32_t newIndexCount = m_indexCount + amount;
    if (m_indexCapacity < newIndexCount) {
        if (m_flags & FLAG_DONT_GROW_CAPACITY) return GROW_FAILED;

        uint32_t newCapacity = m_indexCapacity + m_indexCapacity / 2;
        if (newCapacity < newIndexCount) {
            newCapacity = newIndexCount;
        }
        set_indexCapacity(newCapacity);
    }
    m_indexCount = newIndexCount;
    return oldIndexCount;
}

void grRenderCore::Mesh::recomputeBoundingBox() {
    m_bboxMin = { INFINITY };
    m_bboxMax = { -INFINITY };

    for (uint32_t i = 0; i < m_vertexCount; i++) {
        auto vpos = getVertex(i).position();
        m_bboxMin = gtlMath2::min(vpos, m_bboxMin);
        m_bboxMax = gtlMath2::max(vpos, m_bboxMax);
    }

    m_bboxMin = gtlMath2::min(m_bboxMax, m_bboxMin); // ensure that bboxMin <= bboxMax
}

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grRenderCore::Mesh::serializationImpl(TSerializationInterface &srl) {
    GNA_CHECK_STATUS(Renderable::serializationImpl(srl));

    auto vertexFormat  = m_vertexFormat;
    auto vertexCount  = m_vertexCount;
    auto indexCount  = m_indexCount;

    GNA_CHECK_STATUS(srl.serialize("vertexFormat", vertexFormat));
    GNA_CHECK_STATUS(srl.serialize("vertexCount", vertexCount));
    GNA_CHECK_STATUS(srl.serialize("indexCount", indexCount));

    if (srl.get_direction() == nxfSerialization::SerializationDirection::READ) {
        set_vertexFormat(vertexFormat);
        set_vertexCount(vertexCount);
        if (indexCount != INVALID_INDEX_COUNT) {
            set_indexCount(indexCount);
        }
    }

    GNA_CHECK_STATUS(srl.serialize("primitiveType", m_primitiveType));
    GNA_CHECK_STATUS(srl.serialize("bboxMin", m_bboxMin));
    GNA_CHECK_STATUS(srl.serialize("bboxMax", m_bboxMax));

    size_t expectedGeomDataSize = m_vertexCount * m_vertexFormatInfo.m_stride;

    if (srl.get_direction() == nxfSerialization::SerializationDirection::WRITE) {
        GNA_CHECK_STATUS(srl.serializeRawData("geometryDataBuffer", m_geometryDataBuffer, expectedGeomDataSize));
    } else if (srl.get_direction() == nxfSerialization::SerializationDirection::READ) {
        size_t size;
        GNA_CHECK_STATUS(srl.deserializeRawDataSize(size));
        if (size != expectedGeomDataSize) {
            return { GNA_E_INVALID_DATA_FORMAT, GTXT("Mesh geometry data size invalid") };
        }

        GNA_CHECK_STATUS(srl.deserializeRawData(m_geometryDataBuffer, size));
    }

    size_t expectedIdxDataSize = m_indexCount * sizeof(*m_indices);

    if (srl.get_direction() == nxfSerialization::SerializationDirection::WRITE) {
        GNA_CHECK_STATUS(srl.serializeRawData("indices", m_indices, expectedIdxDataSize));
    } else if (srl.get_direction() == nxfSerialization::SerializationDirection::READ) {
        size_t size;
        GNA_CHECK_STATUS(srl.deserializeRawDataSize(size));
        if (size != expectedIdxDataSize) {
            return { GNA_E_INVALID_DATA_FORMAT, GTXT("Mesh geometry data size invalid") };
        }

        GNA_CHECK_STATUS(srl.deserializeRawData(m_indices, size));
    }

    if (srl.get_direction() == nxfSerialization::SerializationDirection::READ) {
        m_flags |= FLAG_IMMUTABLE;
        markDirty();
    }

    return GNA_E_OK;
}
