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

#include "OutputStream.h"

#include <miniz.h>

namespace nxfIO {
    class GTL_DLLIMPEXP ZLIBOutputStream : public nxfOutputStream {
        static constexpr size_t GPK_ZLIB_BUFFER_SIZE = 4096;

        gnaPointer<nxfOutputStream> m_stream;
        mz_stream m_mzstream;
        unsigned char m_outputBuffer[GPK_ZLIB_BUFFER_SIZE];

    public:
        ZLIBOutputStream();

        virtual ~ZLIBOutputStream() override;

        /**
         * @brief Opens a stream and writes some initial zlib data
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

        gnaStatus finish() override;
    };
}
