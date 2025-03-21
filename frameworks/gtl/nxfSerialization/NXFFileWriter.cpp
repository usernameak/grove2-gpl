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

#include "NXFFileWriter.h"

#include "SerializationTypeRegistry.h"

nxfSerialization::NXFFileWriter::NXFFileWriter(gnaPointer<nxfOutputStream> stream)
    : nxfDelegatingOutputStream(std::move(stream)),
      m_objectOffsetsOffset(0),
      m_objectSizesOffset(0) {}

gnaStatus nxfSerialization::NXFFileWriter::writeNXFFile(gnaPointer<gtlObject> object) {
    registerObject(object);

    ObjectCollector collector(*this);
    GNA_CHECK_STATUS(object->serializationWrapper(collector));

    collectObjectTypes();

    assert(m_objects[0].object == object);

    GNA_CHECK_STATUS(writeHeader());
    GNA_CHECK_STATUS(writeTypeTable());
    GNA_CHECK_STATUS(writeObjects());
    GNA_CHECK_STATUS(writeObjectSizesAndOffsets());

    return GNA_E_OK;
}

bool nxfSerialization::NXFFileWriter::registerObject(gnaWeakPointer<gtlObject> object) {
    if (!object) return false;

    if (m_objectIDMap.contains(object)) return false;

    m_objectIDMap[object] = m_objects.size();
    m_objects.emplace_back(object);

    return true;
}

void nxfSerialization::NXFFileWriter::collectObjectTypes() {
    for (ObjectInfo &obj : m_objects) {
        gtl::PooledAString typeName = gnaSingleton<SerializationTypeRegistry>()->getNameFromObject(obj.object);

        auto it = m_typeIDMap.find(typeName);
        if (it != m_typeIDMap.end()) {
            obj.typeId = it->second;
            continue;
        }

        obj.typeId            = m_types.size();
        m_typeIDMap[typeName] = obj.typeId;
        m_types.emplace_back(typeName);
    }
}

gnaStatus nxfSerialization::NXFFileWriter::writeHeader() {
    char magic[]{ 'N', 'X', 'F', 'b' };
    GNA_CHECK_STATUS(write(&magic, 4));

    GNA_CHECK_STATUS(*this << (uint32_t)m_objects.size()); // number of objects

    m_objectOffsetsOffset = tell();
    for (size_t i = 0; i < m_objects.size(); i++) { // object offsets
        GNA_CHECK_STATUS(*this << (uint64_t)0);
    }

    m_objectSizesOffset = tell();
    for (size_t i = 0; i < m_objects.size(); i++) { // object sizes
        GNA_CHECK_STATUS(*this << (uint64_t)0);
    }

    for (size_t i = 0; i < m_objects.size(); i++) { // object types
        GNA_CHECK_STATUS(*this << m_objects[i].typeId);
    }

    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXFFileWriter::writeTypeTable() {
    GNA_CHECK_STATUS(*this << (uint32_t)m_types.size()); // number of types

    for (size_t i = 0; i < m_types.size(); i++) {
        GNA_CHECK_STATUS(*this << m_types[i]);
    }

    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXFFileWriter::writeObjects() {
    for (auto &info : m_objects) {
        info.offset = tell();

        DataWriter writer(*this);
        GNA_CHECK_STATUS(info.object->serializationWrapper(writer));

        info.size = tell() - info.offset;
    }

    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXFFileWriter::writeObjectSizesAndOffsets() {
    GNA_CHECK_STATUS(seek(m_objectOffsetsOffset));

    for (auto &info : m_objects) {
        GNA_CHECK_STATUS(*this << info.offset);
    }

    GNA_CHECK_STATUS(seek(m_objectSizesOffset));
    for (auto &info : m_objects) {
        GNA_CHECK_STATUS(*this << info.size);
    }

    return GNA_E_OK;
}

uint32_t nxfSerialization::NXFFileWriter::getObjectID(gnaWeakPointer<gtlObject> object) const {
    if (object == nullptr) return INVALID_REFERENCE;

    auto it = m_objectIDMap.find(object);
    if (it == m_objectIDMap.end()) {
        GR_FATAL(GTXT("object id not found"));
    }
    return it->second;
}

// --- //

gnaStatus nxfSerialization::NXFFileWriter::ObjectCollector::serializeObjectReference(const char *name, gnaWeakPointer<gtlObject> &obj) {
    if (m_writer.registerObject(obj)) {
        return obj->serializationWrapper(*this);
    } else {
        return GNA_E_OK;
    }
}

// --- //

gnaStatus nxfSerialization::NXFFileWriter::DataWriter::serializeObjectReference(const char *name, gnaWeakPointer<gtlObject> &obj) {
    return m_writer << m_writer.getObjectID(obj);
}

gnaStatus nxfSerialization::NXFFileWriter::DataWriter::serializeRawData(const char *name, const void *data, size_t size) {
    // do not touch this cast - it's intended for 32-bit systems
    // ReSharper disable once CppRedundantCastExpression
    GNA_CHECK_STATUS(m_writer << static_cast<uint64_t>(size));

    return m_writer.write(data, size);
}

gnaStatus nxfSerialization::NXFFileWriter::DataWriter::serializeNullRawData(const char *name) {
    return m_writer << UINT64_MAX;
}
