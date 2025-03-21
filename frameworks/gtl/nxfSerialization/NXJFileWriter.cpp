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

#include "NXJFileWriter.h"

#include "SerializationTypeRegistry.h"

#include <gtlObject/Object.h>

nxfSerialization::NXJFileWriter::NXJFileWriter(gnaPointer<nxfOutputStream> stream) : m_stream(stream) {
}

gnaStatus nxfSerialization::NXJFileWriter::writeNXJFile(gnaPointer<gtlObject> object) {
    registerObject(object);

    ObjectCollector collector(*this);
    GNA_CHECK_STATUS(object->serializationWrapper(collector));

    for (uint32_t i = 0; i < m_objects.size(); i++) {
        auto &info                = m_objects[i];
        info.jsonObject["__id"]   = i;
        info.jsonObject["__type"] = gnaSingleton<SerializationTypeRegistry>()->getNameFromObject(info.object).toCString();
    }

    auto &objectsArray = m_json["objects"] = nlohmann::json::array();

    for (uint32_t i = 0; i < m_objects.size(); i++) {
        auto &info = m_objects[i];
        m_currentJsonNodes.push_back(&info.jsonObject);

        DataWriter writer(*this);
        info.object->serializationWrapper(writer);

        m_currentJsonNodes.clear();

        objectsArray.push_back(info.jsonObject);
    }

    std::string data = m_json.dump(4);

    return m_stream->write(data.c_str(), data.size());
}

bool nxfSerialization::NXJFileWriter::registerObject(gnaWeakPointer<gtlObject> object) {
    if (!object) return false;

    if (m_objectIDMap.find(object) != m_objectIDMap.end()) return false;

    m_objectIDMap[object] = m_objects.size();
    m_objects.emplace_back(object);

    return true;
}

uint32_t nxfSerialization::NXJFileWriter::getObjectID(gnaWeakPointer<gtlObject> object) const {
    if (object == nullptr) return INVALID_REFERENCE;

    auto it = m_objectIDMap.find(object);
    if (it == m_objectIDMap.end()) {
        GR_FATAL(GTXT("object id not found"));
    }
    return it->second;
}

gnaStatus nxfSerialization::NXJFileWriter::ObjectCollector::serializeObjectReference(const char *name, gnaWeakPointer<gtlObject> &obj) {
    if (m_writer.registerObject(obj)) {
        return obj->serializationWrapper(*this);
    } else {
        return GNA_E_OK;
    }
}

gnaStatus nxfSerialization::NXJFileWriter::DataWriter::serializeObjectReference(const char *name, gnaWeakPointer<gtlObject> &obj) {
    uint32_t id = m_writer.getObjectID(obj);
    if (id == INVALID_REFERENCE) {
        writeJsonValue(name, nullptr);
    } else {
        writeJsonValue(name, id);
    }
    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXJFileWriter::DataWriter::serializeRawData(const char *name, const void *data, size_t size) {
    // do we want to use hexdump?
    char hextab[] = "0123456789ABCDEF";
    std::string hexdump(size * 2, '0');
    uint8_t *rawdata = (uint8_t *)data;
    for (size_t i = 0; i < size; i++) {
        hexdump[i * 2]     = hextab[rawdata[i] >> 4];
        hexdump[i * 2 + 1] = hextab[rawdata[i] & 0xF];
    }
    writeJsonValue(name, hexdump);
    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXJFileWriter::DataWriter::serializeNullRawData(const char *name) {
    writeJsonValue(name, nullptr);
    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXJFileWriter::DataWriter::beginList(const char *name, uint32_t &size) {
    auto &ref = writeJsonValue(name, nlohmann::json::array());
    m_writer.m_currentJsonNodes.push_back(&ref);
    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXJFileWriter::DataWriter::endList() {
    m_writer.m_currentJsonNodes.pop_back();
    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXJFileWriter::DataWriter::beginCompound(const char *name) {
    auto &ref = writeJsonValue(name, nlohmann::json::object());
    m_writer.m_currentJsonNodes.push_back(&ref);
    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXJFileWriter::DataWriter::endCompound() {
    m_writer.m_currentJsonNodes.pop_back();
    return GNA_E_OK;
}
