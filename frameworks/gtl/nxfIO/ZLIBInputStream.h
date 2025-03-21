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

#include "InputStream.h"
#include <miniz.h>

namespace nxfIO {
    class GTL_DLLIMPEXP ZLIBInputStream : public nxfInputStream {
        gnaPointer<nxfInputStream> m_stream;
        z_stream m_zStream;
        bool m_streamDone;

        static constexpr uint32_t ZLIBSTREAM_INPUT_BUFFER_SIZE = 4096;

        unsigned char m_inputBuffer[4096];
        uint32_t m_inputBufferAvailable;
        uint32_t m_inputBufferOffset;

        uint64_t m_uncompressedSize;

    public:
        ZLIBInputStream();

        /**
         * @brief Opens a stream as a ZLIB compressed stream
         * @param stream - stream with the compressed data
         * @return status of the operation
         */
        gnaStatus open(gnaPointer<nxfInputStream> stream, uint64_t uncompressedSize = UINT64_MAX);

        gnaStatus read(void *data, uint32_t size, uint32_t *bytesRead = nullptr) override;

        int64_t get_size() override;

        uint32_t get_capabilities() const override {
            return 0;
        }

        virtual ~ZLIBInputStream() override;
    };
}
