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
#include "gtlString/PooledString.h"
#include "nlohmann/json.hpp"
#include "nxfIO/OutputStream.h"
#include "nxfResource/RID.h"

class gtlObject;

namespace nxfSerialization {
    class GTL_DLLIMPEXP NXJFileWriter : public gtlRcObject {
    public:
        class GTL_DLLIMPEXP ObjectCollector final : public SerializationInterfaceBase<ObjectCollector> {
            NXJFileWriter &m_writer;

        public:
            explicit ObjectCollector(NXJFileWriter &writer) : m_writer(writer) {}

            gnaStatus serializeObjectReference(const char *name,gnaWeakPointer<gtlObject> &obj);

            SerializationDirection get_direction() const {
                return SerializationDirection::REGISTER;
            }
        };
        static_assert(SerializationInterface<ObjectCollector>);

        class GTL_DLLIMPEXP DataWriter final : public SerializationInterfaceBase<DataWriter> {
            NXJFileWriter &m_writer;

        public:
            explicit DataWriter(NXJFileWriter &writer) : m_writer(writer) {}

            gnaStatus serializeObjectReference(const char *name,gnaWeakPointer<gtlObject> &obj);

            gnaStatus serializeRawData(const char *name, const void *data, size_t size);
            gnaStatus serializeNullRawData(const char *name);

            SerializationDirection get_direction() const {
                return SerializationDirection::WRITE;
            }

            template <typename T>
            nlohmann::json &writeJsonValue(const char *name, const T &value) {
                auto &node = (*m_writer.m_currentJsonNodes.back());
                if (!name) {
                    node.push_back(value);
                    return node.back();
                } else {
                    return node[name] = value;
                }
            }

            template <std::integral T>
            gnaStatus serializeValue(const char *name, T &value) {
                writeJsonValue(name, value);
                return GNA_E_OK;
            }

            template <std::floating_point T>
            gnaStatus serializeValue(const char *name, T &value) {
                writeJsonValue(name, value);
                return GNA_E_OK;
            }

            template <typename T>
                requires(std::is_enum_v<T>)
            gnaStatus serializeValue(const char *name, T &value) {
                writeJsonValue(name, value);
                return GNA_E_OK;
            }

            template <typename T>
            gnaStatus serializeValue(const char *name, gtl::BaseString<T> &value) {
                // terribly inefficient
                gtl::AString asciiString = value;
                std::string stdString(asciiString.toCString(), asciiString.size());
                writeJsonValue(name, stdString);
                return GNA_E_OK;
            }

            template <typename T>
            gnaStatus serializeValue(const char *name, gtl::BasePooledString<T> &value) {
                // terribly inefficient
                gtl::BaseString<T> baseString = static_cast<gtl::BaseString<T>>(value);
                gtl::AString asciiString      = static_cast<gtl::AString>(baseString);
                std::string stdString(asciiString.toCString(), asciiString.size());
                writeJsonValue(name, stdString);
                return GNA_E_OK;
            }

            gnaStatus serializeValue(const char *name, nxfRID &value) {
                return serializeValue(name, value.name);
            }

            gnaStatus beginList(const char *name, uint32_t &size);
            gnaStatus endList();

            gnaStatus beginCompound(const char *name);
            gnaStatus endCompound();
        };
        static_assert(SerializationInterface<DataWriter>);

    private:
        struct ObjectInfo {
            gnaPointer<gtlObject> object;
            nlohmann::json jsonObject;

            explicit ObjectInfo(gnaPointer<gtlObject> object)
                : object(std::move(object)) {}
        };

        std::vector<ObjectInfo> m_objects;
        std::unordered_map<gnaPointer<gtlObject>, uint32_t> m_objectIDMap;

        nlohmann::json m_json;
        std::vector<nlohmann::json *> m_currentJsonNodes;

        friend class DataWriter;

        gnaPointer<nxfOutputStream> m_stream;

        static constexpr uint32_t INVALID_REFERENCE = UINT32_MAX;

    public:
        explicit NXJFileWriter(gnaPointer<nxfOutputStream> stream);

        gnaStatus writeNXJFile(gnaPointer<gtlObject> object);
        bool registerObject(gnaWeakPointer<gtlObject> object);

        uint32_t getObjectID(gnaWeakPointer<gtlObject> object) const;
    };
}
