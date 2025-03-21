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

#include "SerializationInterface.h"
#include "PrimitiveSerializers.h"
#include <nxfIO/DelegatingOutputStream.h>
#include <vector>

class gtlObject;

namespace nxfSerialization {
    class GTL_DLLIMPEXP NXFFileWriter : public nxfDelegatingOutputStream {
    public:
        class GTL_DLLIMPEXP ObjectCollector final : public SerializationInterfaceBase<ObjectCollector> {
            NXFFileWriter &m_writer;

        public:
            explicit ObjectCollector(NXFFileWriter &writer) : m_writer(writer) {}

            gnaStatus serializeObjectReference(const char *name, gnaWeakPointer<gtlObject> &obj);

            SerializationDirection get_direction() const {
                return SerializationDirection::REGISTER;
            }
        };
        static_assert(SerializationInterface<ObjectCollector>);

        class GTL_DLLIMPEXP DataWriter final : public SerializationInterfaceBase<DataWriter> {
            NXFFileWriter &m_writer;

        public:
            explicit DataWriter(NXFFileWriter &writer) : m_writer(writer) {}

            gnaStatus serializeObjectReference(const char *name, gnaWeakPointer<gtlObject> &obj);

            gnaStatus serializeRawData(const char *name, const void *data, size_t size);
            gnaStatus serializeNullRawData(const char *name);

            SerializationDirection get_direction() const {
                return SerializationDirection::WRITE;
            }

            template <typename T>
            gnaStatus serializeValue(const char *name, T &value) {
                return m_writer << value;
            }
        };
        static_assert(SerializationInterface<DataWriter>);

    private:
        struct ObjectInfo {
            gnaPointer<gtlObject> object;
            uint64_t offset;
            uint64_t size;
            uint32_t typeId;

            explicit ObjectInfo(gnaPointer<gtlObject> object)
                : object(std::move(object)),
                  offset(0),
                  size(0),
                  typeId(UINT32_MAX) {}
        };

        std::vector<ObjectInfo> m_objects;
        std::unordered_map<gnaPointer<gtlObject>, uint32_t> m_objectIDMap;

        std::vector<gtl::PooledAString> m_types;
        std::unordered_map<gtl::PooledAString, uint32_t> m_typeIDMap;

        uint64_t m_objectOffsetsOffset;
        uint64_t m_objectSizesOffset;

        static constexpr uint32_t INVALID_REFERENCE = UINT32_MAX;

    public:
        explicit NXFFileWriter(gnaPointer<nxfOutputStream> stream);

        gnaStatus writeNXFFile(gnaPointer<gtlObject> object);
        bool registerObject(gnaWeakPointer<gtlObject> object);

        uint32_t getObjectID(gnaWeakPointer<gtlObject> object) const;

    private:
        void collectObjectTypes();

        gnaStatus writeHeader();
        gnaStatus writeTypeTable();
        gnaStatus writeObjects();
        gnaStatus writeObjectSizesAndOffsets();
    };
}
