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
#include <nxfIO/DelegatingInputStream.h>
#include <gtlString/PooledString.h>

class gtlObject;

namespace nxfSerialization {
    class GTL_DLLIMPEXP NXFFileReader : public nxfDelegatingInputStream {
    public:
        class GTL_DLLIMPEXP DataReader final : public SerializationInterfaceBase<DataReader> {
            NXFFileReader &m_reader;

        public:
            explicit DataReader(NXFFileReader &reader) : m_reader(reader) {}

            gnaStatus serializeObjectReference(const char *name, gnaWeakPointer<gtlObject> &obj);
            gnaStatus deserializeRawDataSize(size_t &size);
            gnaStatus deserializeRawData(void *, size_t size);

            SerializationDirection get_direction() const {
                return SerializationDirection::READ;
            }

            template <typename T>
            gnaStatus serializeValue(const char *name, T &value) {
                return m_reader >> value;
            }
        };
        static_assert(SerializationInterface<DataReader>);

    private:
        struct ObjectInfo {
            gnaPointer<gtlObject> object;
            uint64_t offset;
            uint64_t size;
            uint32_t typeId;

            ObjectInfo()
                : object(nullptr),
                  offset(0),
                  size(0),
                  typeId(UINT32_MAX) {}
        };

        std::vector<ObjectInfo> m_objects;
        std::vector<gtl::PooledAString> m_types;
        uint32_t m_currentReadObject;

        static constexpr uint32_t INVALID_REFERENCE = UINT32_MAX;

    public:
        explicit NXFFileReader(gnaPointer<nxfInputStream> stream);

        gnaStatus readNXFFile();

        gnaWeakPointer<gtlObject> queryObject(uint32_t index);
        template <typename T>
        gnaWeakPointer<T> queryObject(uint32_t index) {
            return queryObject(index).rttiCast2<T>();
        }

        gnaPointer<gtlObject> getRootObject() {
            return queryObject(0);
        }

        template <typename T>
        gnaPointer<T> getRootObject() {
            return getRootObject().rttiCast2<T>();
        }

    private:
        gnaStatus readHeader();
        gnaStatus readTypeTable();
        gnaStatus readObject(uint32_t index);
    };
}
