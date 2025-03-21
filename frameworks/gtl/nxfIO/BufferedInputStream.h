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
#include <mutex>

namespace nxfIO {
    /**
     * Buffered input stream.
     *
     * This is threadsafe iff the underlying stream has CAP_THREADSAFE_ACCESS.
     * This stream has a separate seek tracking from the underlying stream
     * and the seek position in the underlying stream is undefined after
     * any operation on this stream.
     */
    class GTL_DLLIMPEXP BufferedInputStream : public nxfInputStream {
        gnaPointer<nxfInputStream> m_stream;

        uint32_t m_bufferBlockSize;
        uint8_t *m_buffer;
        uint64_t m_bufferBlockIndex;
        uint32_t m_bufferCurrentBlockSize;

        uint64_t m_currentOffset;

        bool m_isSequential;

        mutable std::mutex m_mutex;

    public:
        BufferedInputStream(gnaPointer<nxfInputStream> stream, uint32_t bufferBlockSize = 4096);

        virtual ~BufferedInputStream() override;

        gnaStatus read(void *data, uint32_t size, uint32_t *bytesRead = nullptr) override {
            return readCommon(data, m_currentOffset, size, bytesRead);
        }

        gnaStatus readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead = nullptr) override {
            if (m_isSequential) {
                GR_FATAL(GTXT("readRA cannot be called on a sequential buffered stream"));
            }
            return readCommon(data, offset, size, bytesRead);
        }

        gnaStatus seek(uint64_t offset) override;

        int64_t get_size() override;

        uint64_t tell() override;

        uint32_t get_capabilities() const override {
            return m_stream->get_capabilities();
        }

    private:
        gnaStatus populateBufferBlock(uint64_t blockIndex);

        gnaStatus readCommon(void *data, uint64_t &offset, uint32_t size, uint32_t *bytesRead = nullptr);
    };
}
