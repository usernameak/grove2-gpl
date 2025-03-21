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

#include <nxfIO/InputStream.h>
#include <lz4hc.h>

namespace nxfIO {
    class GTL_DLLIMPEXP LZ4BlockInputStream : public nxfInputStream {
        static constexpr size_t GPK_LZ4_BLOCK_SIZE  = 1024 * 1024;
        static constexpr uint32_t NUM_BLOCKS_CACHED = 8;

        unsigned char m_inputBuffer[LZ4_COMPRESSBOUND(GPK_LZ4_BLOCK_SIZE)];

        unsigned char m_cacheBuffers[NUM_BLOCKS_CACHED][GPK_LZ4_BLOCK_SIZE];
        gnaStatus m_cachedStatuses[NUM_BLOCKS_CACHED];
        uint32_t m_cachedSizes[NUM_BLOCKS_CACHED];

        gnaPointer<nxfInputStream> m_stream;

        struct CacheEntry {
            uint32_t blockIndex;
            uint32_t bufferIndex;
        };

        // [block index -> buffer index] cache
        std::unordered_map<uint32_t, std::list<CacheEntry>::iterator> m_lruCacheMap;
        std::list<CacheEntry> m_lruCacheList;

        uint64_t m_startOffset;

        uint64_t m_indexOffset;
        std::vector<uint64_t> m_blockIndex;

        uint64_t m_uncompressedSize;

        uint64_t m_currentOffset;

    public:
        GTL_RTTI_DECLARE();

        LZ4BlockInputStream();

        /**
         * @brief Opens a stream as a LZ4 block-compressed stream
         * @param stream - stream with the compressed data
         * @return status of the operation
         */
        gnaStatus open(gnaPointer<nxfInputStream> stream);

        gnaStatus read(void *data, uint32_t size, uint32_t *bytesRead = nullptr) override;
        gnaStatus readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead) override;

        gnaStatus seek(uint64_t offset) override;

        uint64_t tell() override;

        int64_t get_size() override;

        uint32_t get_capabilities() const override {
            return CAP_RANDOM_ACCESS; // TODO: threadsafe access
        }

        virtual ~LZ4BlockInputStream() override;

    private:
        uint64_t calculateBlockOffset(uint32_t blockIndex);
        uint32_t calculateBlockSize(uint32_t blockIndex);
        gnaStatus fetchBlock(uint32_t blockIndex, uint32_t &bufferIndex);
        gnaStatus doFetchBlock(uint32_t blockIndex, uint32_t bufferIndex);
    };
}
