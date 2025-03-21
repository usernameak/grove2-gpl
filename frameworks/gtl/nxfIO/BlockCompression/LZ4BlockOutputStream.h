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

#include <nxfIO/OutputStream.h>
#include <lz4hc.h>

namespace nxfIO {
    class GTL_DLLIMPEXP LZ4BlockOutputStream : public nxfOutputStream {
        static constexpr size_t GPK_LZ4_BLOCK_SIZE = 1024 * 1024;

        gnaPointer<nxfOutputStream> m_stream;
        LZ4_streamHC_t *m_lzstream;

        size_t m_inputBufferOffset;
        unsigned char m_inputBuffer[GPK_LZ4_BLOCK_SIZE];
        unsigned char m_outputBuffer[LZ4_COMPRESSBOUND(GPK_LZ4_BLOCK_SIZE)];
        std::vector<uint64_t> m_blockIndex;
        uint64_t m_startOffset;
        uint64_t m_currentTellOffset;

    public:
        LZ4BlockOutputStream();

        virtual ~LZ4BlockOutputStream() override;

        /**
         * @brief Opens a stream and writes some initial LZ4 data
         * @return status
         */
        gnaStatus open(gnaPointer<nxfOutputStream> stream);

        /**
         * @brief Writes data to stream
         * @param data buffer to write into the stream
         * @param size buffer size
         * @param bytesWritten (out) count of bytes written, if required
         * @return gnaStatus status code
         */
        gnaStatus write(const void *data, uint32_t size, uint32_t *bytesWritten = nullptr) override;

        gnaStatus flush() override;

        gnaStatus writeBlockIndex();

        gnaStatus finish() override;

        uint64_t tell() override;

    private:
        gnaStatus flushLastBlock();
    };
}
