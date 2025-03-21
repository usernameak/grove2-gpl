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

#include "Mesh.h"
#include <gtlMath2/Matrix/Matrix4x3.h>

namespace grRenderCore {
    class MeshInstanceAccessor;
    class InstancedMesh;

    class MeshInstanceAccessor {
        InstancedMesh *m_instancedMesh;
        uint32_t m_instance;

    public:
        MeshInstanceAccessor() : m_instancedMesh(nullptr), m_instance(0) {}

        MeshInstanceAccessor(InstancedMesh *mesh, uint32_t instance)
            : m_instancedMesh(mesh),
              m_instance(instance) {}

        void *getAttributePtr(VertexFormatAttribute attribute);
        const void *getAttributePtr(VertexFormatAttribute attribute) const;

        explicit operator bool() const {
            return m_instancedMesh;
        }

    private:
        template <typename T, VertexFormatAttribute attribute>
        T &getAttributeRef() {
            return *reinterpret_cast<T *>(getAttributePtr(attribute));
        }

        template <typename T, VertexFormatAttribute attribute>
        const T &getAttributeRef() const {
            return *reinterpret_cast<const T *>(getAttributePtr(attribute));
        }

    public:
        auto &transform() { return getAttributeRef<gtlMath2::Matrix4x3f, VFA_INSTANCE_TRANSFORM>(); }
        auto &transform() const { return getAttributeRef<gtlMath2::Matrix4x3f, VFA_INSTANCE_TRANSFORM>(); }

        operator uint32_t() const { return m_instance; }
    };

    class GR_RENDERCORE_DLLIMPEXP InstancedMesh : public Renderable {
    public:
        enum InstancedMeshFlags : uint16_t {
            /** Instance data is immutable. */
            FLAG_IMMUTABLE = GTL_BIT(0),
            /** Instance data needs to be cleared after every upload. */
            FLAG_CLEAR_ON_UPLOAD = GTL_BIT(1),
            /** Instance data is dirty and needs to be reuploaded. */
            FLAG_DIRTY = GTL_BIT(2)
        };

        GTL_RTTI_DECLARE();
        NXF_SERIALIZABLE_DECLARE();

        /**
         * The vertex format, including the instancing bits
         */
        std::underlying_type_t<VertexFormatFlags> m_vertexFormat;
        InstanceVertexFormatInfo m_instanceVertexFormatInfo;

        std::underlying_type_t<InstancedMeshFlags> m_flags;

        uint32_t m_instanceCount;
        uint32_t m_instanceCapacity;
        unsigned char *m_instanceDataBuffer;

    public:
        InstancedMesh();

        virtual ~InstancedMesh() override;

        void clearInstanceData();
        void deallocateInstanceData();

        void set_vertexFormat(std::underlying_type_t<VertexFormatFlags> format);

        void set_instanceCapacity(uint32_t newCapacity);
        void set_instanceCount(uint32_t newCount);
        uint32_t grow_instanceCount(uint32_t amount);

        GTL_FORCEINLINE MeshInstanceAccessor getInstance(uint32_t instance) {
            return { this, instance };
        }

        GTL_FORCEINLINE MeshInstanceAccessor addInstance() {
            uint32_t newVertexIndex = grow_instanceCount(1);
            return getInstance(newVertexIndex);
        }

        void markDirty() {
            m_flags |= FLAG_DIRTY;
        }

        gnaPointer<gtlRcObject> renderer;

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy);
    };

    inline void *MeshInstanceAccessor::getAttributePtr(grRenderCore::VertexFormatAttribute attribute) {
        return &m_instancedMesh->m_instanceDataBuffer[m_instancedMesh->m_instanceVertexFormatInfo.m_stride * m_instance +
                                                      m_instancedMesh->m_instanceVertexFormatInfo.m_offsets[attribute]];
    }

    inline const void *MeshInstanceAccessor::getAttributePtr(grRenderCore::VertexFormatAttribute attribute) const {
        return &m_instancedMesh->m_instanceDataBuffer[m_instancedMesh->m_instanceVertexFormatInfo.m_stride * m_instance +
                                                      m_instancedMesh->m_instanceVertexFormatInfo.m_offsets[attribute]];
    }
}