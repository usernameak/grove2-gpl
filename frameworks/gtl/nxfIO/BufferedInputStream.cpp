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

#include "BufferedInputStream.h"

nxfIO::BufferedInputStream::BufferedInputStream(gnaPointer<nxfInputStream> stream, uint32_t bufferBlockSize)
    : m_stream(std::move(stream)),
      m_bufferBlockSize(bufferBlockSize),
      m_buffer(gtlNew uint8_t[bufferBlockSize]),
      m_bufferBlockIndex(UINT64_MAX),
      m_bufferCurrentBlockSize(0),
      m_currentOffset(0),
      m_isSequential(!(m_stream->get_capabilities() & CAP_RANDOM_ACCESS)) {
}

nxfIO::BufferedInputStream::~BufferedInputStream() {
    gtlDeleteArray m_buffer;
}

gnaStatus nxfIO::BufferedInputStream::seek(uint64_t offset) {
    if (m_isSequential) {
        GR_FATAL(GTXT("seek cannot be called on a sequential buffered stream"));
    }
    m_currentOffset = offset;
    return GNA_E_OK;
}

int64_t nxfIO::BufferedInputStream::get_size() {
    return m_stream->get_size();
}

uint64_t nxfIO::BufferedInputStream::tell() {
    return m_currentOffset;
}

gnaStatus nxfIO::BufferedInputStream::populateBufferBlock(uint64_t blockIndex) {
    if (blockIndex == m_bufferBlockIndex) {
        return GNA_E_OK;
    }

    uint64_t offset    = blockIndex * m_bufferBlockSize;
    m_bufferBlockIndex = blockIndex;
    if (m_isSequential) {
        return m_stream->read(m_buffer, m_bufferBlockSize, &m_bufferCurrentBlockSize);
    }
    return m_stream->readRA(m_buffer, offset, m_bufferBlockSize, &m_bufferCurrentBlockSize);
}

gnaStatus nxfIO::BufferedInputStream::readCommon(void *data, uint64_t &offset, uint32_t size, uint32_t *bytesRead) {
    std::lock_guard lock(m_mutex);
    if (bytesRead) *bytesRead = 0;
    while (size) {
        uint64_t blockIndex    = offset / m_bufferBlockSize;
        uint32_t inBlockOffset = offset % m_bufferBlockSize;
        GNA_CHECK_STATUS(populateBufferBlock(blockIndex));

        uint32_t inBlockSize = m_bufferCurrentBlockSize - inBlockOffset;
        if (size < inBlockSize) inBlockSize = size;

        memcpy(data, m_buffer + inBlockOffset, inBlockSize);
        data = static_cast<uint8_t *>(data) + inBlockSize;
        size -= inBlockSize;
        offset += inBlockSize;
        if (bytesRead) *bytesRead += inBlockSize;

        if (m_bufferCurrentBlockSize != m_bufferBlockSize) {
            break;
        }
    }
    return GNA_E_OK;
}
