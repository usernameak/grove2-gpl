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

#include "MemoryInputStream.h"

nxfMemoryInputStream::nxfMemoryInputStream() : m_data(nullptr), m_size(0), m_currentOffset(0) {
    
}

int32_t nxfMemoryInputStream::open(const void *buffer, size_t size) {
    gtlFree(m_data);
    m_data = gtlMalloc(size);
    if (!m_data) {
        return -1;
    }

    memcpy(m_data, buffer, size);
    m_size = size;
    m_currentOffset = 0;

    return 0;
}

gnaStatus nxfMemoryInputStream::read(void *data, uint32_t size, uint32_t *bytesRead) {
    uint32_t actualBytesRead;
    gnaStatus status = readRA(data, m_currentOffset, size, &actualBytesRead);
    if (bytesRead) {
        *bytesRead = actualBytesRead;
    }
    m_currentOffset += actualBytesRead;
    return status;
}

gnaStatus nxfMemoryInputStream::readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead) {
    if (!m_data) return GNA_E_INVALID_STATE;

    uint32_t actualBytesRead = size;
    if (offset >= m_size) {
        actualBytesRead = 0;
    } else if (offset + size > m_size) {
        actualBytesRead = (uint32_t)(m_size - offset);
    }

    memcpy(data, static_cast<unsigned char *>(m_data) + offset, actualBytesRead);

    if (bytesRead) {
        *bytesRead = actualBytesRead;
    }

    return GNA_E_OK;
}

gnaStatus nxfMemoryInputStream::seek(uint64_t offset) {
    m_currentOffset = offset;
    return GNA_E_OK;
}

int64_t nxfMemoryInputStream::get_size() {
    return m_size;
}

uint64_t nxfMemoryInputStream::tell() {
    return m_currentOffset;
}

nxfMemoryInputStream::~nxfMemoryInputStream() {
    gtlFree(m_data);
}
