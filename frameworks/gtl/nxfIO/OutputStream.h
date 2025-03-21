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

#include <gtlMemory/RcObject.h>
#include <gnaStatus.h>
#include <gtlUtil/Logging.h>
#include <cstdint>
#include <type_traits>

class GTL_DLLIMPEXP nxfOutputStream : public gtlRcObject {
public:
    /**
     * @brief Writes data to stream
     * @param data buffer to write into the stream
     * @param size buffer size
     * @param bytesWritten (out) count of bytes written, if required
     * @return gnaStatus status code
     */
    virtual gnaStatus write(const void *data, uint32_t size, uint32_t *bytesWritten = nullptr) = 0;

    /**
     * @brief Seeks stream
     * @param offset position in file to seek into
     * @return true on success, false on error
     */
    virtual bool seek(uint64_t offset) {
        GR_FATAL(GTXT("Cannot seek stream: not implemented"));
    }

    /**
     * @brief Returns size of all written data in stream
     * @return size of all written data in stream on success, negative value on error
     */
    virtual int64_t get_size() {
        GR_FATAL(GTXT("Cannot get stream size: not implemented"));
    }

    virtual gnaStatus flush() {
        return GNA_E_OK;
    }

    /**
     * @brief Returns current position in stream
     * @return current position in stream
     */
    virtual uint64_t tell() {
        GR_FATAL(GTXT("Cannot tell stream: not implemented"));
    }

    virtual gnaStatus finish() {
        return GNA_E_OK;
    }
};
