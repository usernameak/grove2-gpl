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

#include <grRenderCore/RenderTypes.h>
#include <grRenderCore/RenderCoreDLL.h>
#include "VertexFormat.h"
#include "Renderable.h"

#include <type_traits>
#include <cassert>
#include <gtlObject/Object.h>
#include <gtlMath2/Vector/Vector3.h>
#include <gtlMath2/Vector/Vector4.h>

namespace grRenderCore {
    class MeshVertexAccessor;
    class Mesh;

    class MeshVertexAccessor {
        Mesh *m_mesh;
        uint32_t m_vertex;

    public:
        MeshVertexAccessor() : m_mesh(nullptr), m_vertex(0) {}

        MeshVertexAccessor(Mesh *mesh, uint32_t vertex)
            : m_mesh(mesh),
              m_vertex(vertex) {}

        void *getAttributePtr(VertexFormatAttribute attribute);
        const void *getAttributePtr(VertexFormatAttribute attribute) const;

        explicit operator bool() const {
            return m_mesh;
        }

    private:
        template <typename T, VertexFormatAttribute attribute>
        T &getAttributeRef() {
            return *static_cast<T *>(getAttributePtr(attribute));
        }

        template <typename T, VertexFormatAttribute attribute>
        const T &getAttributeRef() const {
            return *static_cast<const T *>(getAttributePtr(attribute));
        }

    public:
        auto &position() { return getAttributeRef<gtlMath2::Vector3f, VFA_POSITION>(); }
        auto &position() const { return getAttributeRef<gtlMath2::Vector3f, VFA_POSITION>(); }

        auto &texCoord() { return getAttributeRef<gtlMath2::Vector2f, VFA_TEXCOORD>(); }
        auto &texCoord() const { return getAttributeRef<gtlMath2::Vector2f, VFA_TEXCOORD>(); }

        auto &color() { return getAttributeRef<RGBAColor, VFA_COLOR>(); }
        auto &color() const { return getAttributeRef<RGBAColor, VFA_COLOR>(); }

        auto &normal() { return getAttributeRef<gtlMath2::Vector3f, VFA_NORMAL>(); }
        auto &normal() const { return getAttributeRef<gtlMath2::Vector3f, VFA_NORMAL>(); }

        auto &tangent() { return getAttributeRef<gtlMath2::Vector4f, VFA_TANGENT>(); }
        auto &tangent() const { return getAttributeRef<gtlMath2::Vector4f, VFA_TANGENT>(); }

        operator uint32_t() const { return m_vertex; }
    };

    class GR_RENDERCORE_DLLIMPEXP Mesh : public Renderable {
    public:
        GTL_RTTI_DECLARE();
        NXF_SERIALIZABLE_DECLARE();

        friend class MeshVertexAccessor;

        enum : uint32_t {
            GROW_FAILED         = UINT32_MAX,
            INVALID_INDEX_COUNT = UINT32_MAX
        };

        enum MeshFlags : uint16_t {
            /** Mesh is immutable. */
            FLAG_IMMUTABLE = GTL_BIT(0),
            /** Mesh data needs to be cleared after every upload. */
            FLAG_CLEAR_ON_UPLOAD = GTL_BIT(1),
            /** Mesh is dirty and needs to be reuploaded. */
            FLAG_DIRTY = GTL_BIT(2),
            /** Mesh cannot automatically grow. Functions like
             * addIndex, addQuadIndexes, addVertex, grow_indexCount
             * and grow_vertexCount will fail and restore to the
             * previous state when they would normally result
             * in mesh capacity growing. */
            FLAG_DONT_GROW_CAPACITY = GTL_BIT(3),
        };

        enum PrimitiveType : uint8_t {
            TYPE_TRIANGLES,
            TYPE_LINES,
        };

    public:
        /**
         * Bitmask of the mesh vertex format
         */
        std::underlying_type_t<VertexFormatFlags> m_vertexFormat;

        std::underlying_type_t<MeshFlags> m_flags;
        PrimitiveType m_primitiveType;
        VertexFormatInfo m_vertexFormatInfo;

        uint32_t m_vertexCount;
        uint32_t m_vertexCapacity;
        unsigned char *m_geometryDataBuffer;

        uint32_t m_indexCount;
        uint32_t m_indexCapacity;
        uint32_t *m_indices;

        /**
         * Minimum bounding box of the mesh
         */
        gtlMath2::Vector3f m_bboxMin;

        /**
         * Maximum bounding box of the mesh
         */
        gtlMath2::Vector3f m_bboxMax;

    public:
        Mesh();
        virtual ~Mesh() override;

        void clearMeshData();
        void deallocateMeshData();

        void set_vertexFormat(std::underlying_type_t<VertexFormatFlags> format);

        void set_vertexCapacity(uint32_t newCapacity);
        void set_vertexCount(uint32_t newCount);
        uint32_t grow_vertexCount(uint32_t amount);

        void set_indexCapacity(uint32_t newCapacity);
        void set_indexCount(uint32_t newCount);
        uint32_t grow_indexCount(uint32_t amount);

        void recomputeBoundingBox();

        GTL_FORCEINLINE MeshVertexAccessor getVertex(uint32_t vertex) {
            return { this, vertex };
        }

        GTL_FORCEINLINE MeshVertexAccessor addVertex() {
            uint32_t newVertexIndex = grow_vertexCount(1);
            if (newVertexIndex == GROW_FAILED) return {};
            return getVertex(newVertexIndex);
        }

        bool addIndex(uint32_t index) {
            assert(m_indexCount != INVALID_INDEX_COUNT);

            uint32_t indexOffset = grow_indexCount(1);
            if (indexOffset == GROW_FAILED) return false;
            m_indices[indexOffset] = index;
            return true;
        }

        bool addQuadIndexes(uint32_t index0, uint32_t index1, uint32_t index2, uint32_t index3) {
            uint32_t initialIndexCount = m_indexCount;
            if (!addIndex(index0)) goto fail;
            if (!addIndex(index1)) goto fail;
            if (!addIndex(index2)) goto fail;
            if (!addIndex(index2)) goto fail;
            if (!addIndex(index3)) goto fail;
            if (!addIndex(index0)) goto fail;
            return true;

        fail:
            m_indexCount = initialIndexCount;
            return false;
        }

        uint32_t get_currentIndex() {
            return m_indexCount;
        }

        void markDirty() {
            m_flags |= FLAG_DIRTY;
        }

        gnaPointer<gtlRcObject> renderer;

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy);
    };

    inline void *MeshVertexAccessor::getAttributePtr(grRenderCore::VertexFormatAttribute attribute) {
        return &m_mesh->m_geometryDataBuffer[m_mesh->m_vertexFormatInfo.m_stride * m_vertex + m_mesh->m_vertexFormatInfo.m_offsets[attribute]];
    }

    inline const void *MeshVertexAccessor::getAttributePtr(grRenderCore::VertexFormatAttribute attribute) const {
        return &m_mesh->m_geometryDataBuffer[m_mesh->m_vertexFormatInfo.m_stride * m_vertex + m_mesh->m_vertexFormatInfo.m_offsets[attribute]];
    }

    struct MeshRegion {
        gnaPointer<Mesh> mesh;
        uint32_t regionStartOffset;
        uint32_t regionVertexCount;

        static constexpr uint32_t INVALID_OFFSET = UINT32_MAX;

        MeshRegion(gnaPointer<Mesh> mesh) : mesh(mesh),
                                            regionStartOffset(0),
                                            regionVertexCount(INVALID_OFFSET) {}

        MeshRegion() : MeshRegion(nullptr) {}

        MeshRegion(gnaPointer<Mesh> mesh, uint32_t regionStartOffset, uint32_t regionVertexCount)
            : mesh(mesh),
              regionStartOffset(regionStartOffset),
              regionVertexCount(regionVertexCount) {
        }
    };

}
