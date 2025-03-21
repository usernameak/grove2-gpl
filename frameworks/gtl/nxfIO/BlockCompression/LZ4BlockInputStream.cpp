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

#include "LZ4BlockInputStream.h"


#include "nxfSerialization/PrimitiveSerializers.h"

GTL_RTTI_DEFINE(nxfIO::LZ4BlockInputStream, GTL_RTTI_INHERITS(nxfInputStream));

nxfIO::LZ4BlockInputStream::LZ4BlockInputStream()
    : m_inputBuffer{},
      m_cacheBuffers{},
      m_startOffset(0),
      m_indexOffset(0),
      m_uncompressedSize(0),
      m_currentOffset(0) {}

nxfIO::LZ4BlockInputStream::~LZ4BlockInputStream() {
}

gnaStatus nxfIO::LZ4BlockInputStream::open(gnaPointer<nxfInputStream> stream) {
    m_stream        = stream;
    m_startOffset   = stream->tell();
    m_currentOffset = 0;

    for (uint32_t i = 0; i < NUM_BLOCKS_CACHED; i++) {
        m_cachedSizes[i]    = 0;
        m_cachedStatuses[i] = GNA_E_DATA_NOT_CACHED;
        CacheEntry entry{
            .blockIndex  = i,
            .bufferIndex = i
        };
        m_lruCacheList.push_front(entry);
        m_lruCacheMap[i] = m_lruCacheList.begin();
    }

    GNA_CHECK_STATUS(nxfDeserializeNumber(m_indexOffset, *stream));
    GNA_CHECK_STATUS(nxfDeserializeNumber(m_uncompressedSize, *stream));

    GNA_CHECK_STATUS(stream->seek(m_indexOffset + m_startOffset));

    uint32_t numBlocks;
    GNA_CHECK_STATUS(nxfDeserializeNumber(numBlocks, *stream));

    m_blockIndex.reserve(numBlocks);

    for (uint32_t i = 0; i < numBlocks; i++) {
        uint64_t blockOffset;
        GNA_CHECK_STATUS(nxfDeserializeNumber(blockOffset, *stream));

        m_blockIndex.push_back(blockOffset);
    }

    return GNA_E_OK;
}

gnaStatus nxfIO::LZ4BlockInputStream::read(void *data, uint32_t size, uint32_t *bytesRead) {
    uint32_t realBytesRead = 0;
    gnaStatus status       = readRA(data, m_currentOffset, size, &realBytesRead);
    if (!status) {
        return status;
    }
    m_currentOffset += realBytesRead;
    if (bytesRead) {
        *bytesRead = realBytesRead;
    }
    return status;
}

int64_t nxfIO::LZ4BlockInputStream::get_size() {
    return m_uncompressedSize;
}

gnaStatus nxfIO::LZ4BlockInputStream::readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead) {
    size_t currentBufferOffset = 0;
    uint64_t currentOffset     = offset;
    uint32_t sizeLeft          = size;
    uint32_t totalBytesRead    = 0;

    while (sizeLeft > 0) {
        // 4PB oughta be enough for anybody
        uint32_t blockIndex    = static_cast<uint32_t>(currentOffset / GPK_LZ4_BLOCK_SIZE);
        uint32_t offsetInBlock = static_cast<uint32_t>(currentOffset % GPK_LZ4_BLOCK_SIZE);

        uint32_t bufferIndex = 0;
        GNA_CHECK_STATUS(fetchBlock(blockIndex, bufferIndex));

        uint32_t actualBlockSize = m_cachedSizes[bufferIndex];
        uint32_t readChunkSize   = std::min(sizeLeft, static_cast<uint32_t>(GPK_LZ4_BLOCK_SIZE - offsetInBlock));
        bool endOfData           = false;
        if (offsetInBlock > actualBlockSize) {
            readChunkSize = 0;
            endOfData     = true;
        } else if (actualBlockSize - offsetInBlock < readChunkSize) {
            readChunkSize = actualBlockSize - offsetInBlock;
            endOfData     = true;
        }

        memcpy((unsigned char *)data + currentBufferOffset, m_cacheBuffers[bufferIndex] + offsetInBlock, readChunkSize);

        totalBytesRead += readChunkSize;
        currentOffset += readChunkSize;
        currentBufferOffset += readChunkSize;
        sizeLeft -= readChunkSize;

        if (endOfData) break;
    }

    if (bytesRead) {
        *bytesRead = totalBytesRead;
    }

    return GNA_E_OK;
}

gnaStatus nxfIO::LZ4BlockInputStream::seek(uint64_t offset) {
    m_currentOffset = offset;
    return GNA_E_OK;
}

uint64_t nxfIO::LZ4BlockInputStream::tell() {
    return m_currentOffset;
}

gnaStatus nxfIO::LZ4BlockInputStream::fetchBlock(uint32_t blockIndex, uint32_t &bufferIndex) {
    auto it = m_lruCacheMap.find(blockIndex);
    if (it != m_lruCacheMap.end()) {
        bufferIndex = it->second->bufferIndex;
        gnaStatus status = m_cachedStatuses[bufferIndex];
        if (it->second != m_lruCacheList.begin()) {
            m_lruCacheList.splice(
                m_lruCacheList.begin(),
                m_lruCacheList, it->second, std::next(it->second));
        }
        if (status.errorCode == GNA_E_DATA_NOT_CACHED) {
            return doFetchBlock(blockIndex, bufferIndex);
        }
        return status;
    }

    CacheEntry lruCacheEntry = m_lruCacheList.back();
    m_lruCacheMap.erase(lruCacheEntry.blockIndex);
    m_lruCacheList.pop_back();

    lruCacheEntry.blockIndex = blockIndex;
    m_lruCacheList.push_front(lruCacheEntry);
    m_lruCacheMap[blockIndex] = m_lruCacheList.begin();

    bufferIndex = lruCacheEntry.bufferIndex;

    return doFetchBlock(blockIndex, bufferIndex);
}

gnaStatus nxfIO::LZ4BlockInputStream::doFetchBlock(uint32_t blockIndex, uint32_t bufferIndex) {
    uint32_t blockSize = calculateBlockSize(blockIndex);

    gnaStatus status = GNA_E_OK;

    if (blockSize != 0) {
        status = m_stream->readRA(m_inputBuffer, calculateBlockOffset(blockIndex), blockSize);

        if (status) {
            int result = LZ4_decompress_safe(
                (const char *)m_inputBuffer,
                (char *)m_cacheBuffers[bufferIndex],
                blockSize,
                GPK_LZ4_BLOCK_SIZE);
            if (result < 0) {
                m_cachedSizes[bufferIndex] = 0;
                status                     = GNA_E_FAILED;
            } else {
                m_cachedSizes[bufferIndex] = result;
            }
        }
    }

    m_cachedStatuses[bufferIndex] = status;

    return status;
}

uint64_t nxfIO::LZ4BlockInputStream::calculateBlockOffset(uint32_t blockIndex) {
    if (blockIndex > m_blockIndex.size()) {
        return m_startOffset + 0;
    }
    return m_startOffset + m_blockIndex[blockIndex];
}

uint32_t nxfIO::LZ4BlockInputStream::calculateBlockSize(uint32_t blockIndex) {
    if (blockIndex > m_blockIndex.size()) {
        return 0;
    } else if (blockIndex == m_blockIndex.size() - 1) {
        return m_indexOffset - m_blockIndex.back();
    }
    return m_blockIndex[blockIndex + 1] - m_blockIndex[blockIndex];
}
