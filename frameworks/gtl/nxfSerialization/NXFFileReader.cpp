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

#include "NXFFileReader.h"

#include "PrimitiveSerializers.h"
#include "SerializationTypeRegistry.h"

nxfSerialization::NXFFileReader::NXFFileReader(gnaPointer<nxfInputStream> stream)
    : nxfDelegatingInputStream(stream),
      m_currentReadObject(INVALID_REFERENCE) {
    assert(stream->get_capabilities() & CAP_RANDOM_ACCESS);
}

gnaStatus nxfSerialization::NXFFileReader::readNXFFile() {
    GNA_CHECK_STATUS(readHeader());
    GNA_CHECK_STATUS(readTypeTable());

    auto *registry = gnaSingleton<SerializationTypeRegistry>();
    for (ObjectInfo &info : m_objects) {
        GNA_CHECK_STATUS(registry->createTypeObject(m_types[info.typeId], info.object));
    }

    for (uint32_t i = 0; i < m_objects.size(); i++) {
        GNA_CHECK_STATUS(readObject(i));
    }

    for (uint32_t i = 0; i < m_objects.size(); i++) {
        m_objects[i].object->postDeserialize();
    }

    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXFFileReader::readHeader() {
    char magic[4];
    GNA_CHECK_STATUS(read(&magic, 4));
    if (memcmp(magic, (const char *)"NXFb", 4) != 0) {
        return { GNA_E_INVALID_DATA_FORMAT, GTXT("NXFFileReader: NXFb signature invalid") };
    }

    uint32_t numObjects;
    GNA_CHECK_STATUS(*this >> numObjects);

    m_objects.resize(numObjects);
    for (uint32_t i = 0; i < numObjects; i++) {
        GNA_CHECK_STATUS(*this >> m_objects[i].offset);
    }
    for (uint32_t i = 0; i < numObjects; i++) {
        GNA_CHECK_STATUS(*this >> m_objects[i].size);
    }
    for (uint32_t i = 0; i < numObjects; i++) {
        GNA_CHECK_STATUS(*this >> m_objects[i].typeId);
    }

    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXFFileReader::readTypeTable() {
    uint32_t numTypes;
    GNA_CHECK_STATUS(*this >> numTypes);

    m_types.resize(numTypes);
    for (uint32_t i = 0; i < numTypes; i++) {
        GNA_CHECK_STATUS(*this >> m_types[i]);
    }

    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXFFileReader::readObject(uint32_t index) {
    assert(index < m_objects.size());
    m_currentReadObject = index;

    GNA_CHECK_STATUS(seek(m_objects[index].offset));

    DataReader reader(*this);
    GNA_CHECK_STATUS(m_objects[index].object->serializationWrapper(reader));

    m_currentReadObject = INVALID_REFERENCE;

    return GNA_E_OK;
}

gnaWeakPointer<gtlObject> nxfSerialization::NXFFileReader::queryObject(uint32_t index) {
    if (index == INVALID_REFERENCE || index >= m_objects.size()) return nullptr;
    return m_objects[index].object;
}

// --- //

gnaStatus nxfSerialization::NXFFileReader::DataReader::serializeObjectReference(const char *name, gnaWeakPointer<gtlObject> &obj) {
    uint32_t id;
    GNA_CHECK_STATUS(m_reader >> id);
    obj = m_reader.queryObject(id);
    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXFFileReader::DataReader::deserializeRawDataSize(size_t &size) {
    uint64_t size64;
    GNA_CHECK_STATUS(m_reader >> size64);
    if (size64 > SIZE_MAX) {
        size = SIZE_MAX;
    } else {
        size = size64;
    }
    return GNA_E_OK;
}

gnaStatus nxfSerialization::NXFFileReader::DataReader::deserializeRawData(void *data, size_t size) {
    return m_reader.read(data, size);
}

