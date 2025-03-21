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

#include "RegionInputStream.h"

nxfIO::RegionInputStream::RegionInputStream()
    : m_stream(nullptr),
      m_regionOffset(0),
      m_regionSize(0),
      m_curOffset(0) {
}

gnaStatus nxfIO::RegionInputStream::open(gnaPointer<nxfRAInputStream> stream, uint64_t offset, uint64_t size) {
    m_stream       = stream;
    m_regionOffset = offset;
    m_regionSize   = size;
    m_curOffset    = 0ULL;

    return GNA_E_OK;
}

gnaStatus nxfIO::RegionInputStream::read(void *data, uint32_t size, uint32_t *bytesRead) {
    uint32_t bytesReadReal = 0;
    uint64_t endPosition   = m_curOffset + size;
    if (endPosition > m_regionSize) {
        endPosition = m_regionSize;
    }
    if (m_curOffset > endPosition) {
        if (bytesRead) {
            *bytesRead = 0;
        }
        return GNA_E_OK;
    }
    size = (uint32_t)(endPosition - m_curOffset);

    gnaStatus status = m_stream->readRA(data, m_curOffset + m_regionOffset, size, &bytesReadReal);
    if (bytesRead) {
        *bytesRead = bytesReadReal;
    }
    m_curOffset += bytesReadReal;

    return status;
}

gnaStatus nxfIO::RegionInputStream::readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead) {
    uint64_t endPosition = offset + size;
    if (endPosition > m_regionSize) {
        endPosition = m_regionSize;
    }
    if (offset > endPosition) {
        if (bytesRead) {
            *bytesRead = 0;
        }
        return GNA_E_OK;
    }
    size = (uint32_t)(endPosition - offset);
    return m_stream->readRA(data, offset + m_regionOffset, size, bytesRead);
}

gnaStatus nxfIO::RegionInputStream::seek(uint64_t offset) {
    if (offset > m_regionSize) {
        return GNA_E_OUT_OF_BOUNDS;
    }
    m_curOffset = offset;
    return GNA_E_OK;
}

int64_t nxfIO::RegionInputStream::get_size() {
    return (int64_t)m_regionSize;
}

uint64_t nxfIO::RegionInputStream::tell() {
    return m_curOffset;
}

nxfIO::RegionInputStream::~RegionInputStream() = default;
