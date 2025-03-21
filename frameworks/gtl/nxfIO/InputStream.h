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
#include <gtlUtil/Logging.h>
#include <gnaStatus.h>
#include <cstdint>
#include <type_traits>

class nxfInputStream;
class nxfBinaryResource;

class GTL_DLLIMPEXP nxfInputStream : public gtlRcObject {
public:
    GTL_RTTI_DECLARE();

    enum StreamCapabilities : uint32_t {
        /**
         * seek and readRA are available
         */
        CAP_RANDOM_ACCESS = GTL_BIT(1),

        /**
         * readRA function is thread-safe
         */
        CAP_THREADSAFE_ACCESS = GTL_BIT(2)
    };

    /**
     * @brief Reads data from stream
     * @param data buffer to read stream into
     * @param size buffer size
     * @return number of bytes read on success, negative value on error
     */
    virtual gnaStatus read(void *data, uint32_t size, uint32_t *bytesRead = nullptr) = 0;

    /**
     * @brief Reads data from stream from arbitrary offset
     *
     * No guarantees are given on the seek position after this method is invoked.
     * This is thread-safe only if the stream implementation supports thread safety
     * (i.e. CAP_THREADSAFE_ACCESS is set in capabilities).
     *
     * @param data buffer to read stream into
     * @param offset into file
     * @param size buffer size
     * @param bytesRead pointer where number of bytes read will be stored
     * @return status of the operation
     */
    virtual gnaStatus readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead = nullptr) {
        GNA_CHECK_STATUS(seek(offset));
        return read(data, size, bytesRead);
    }

    /**
     * @brief Seeks stream
     * @param offset position in file to seek into
     * @return true on success, false on error
     */
    virtual gnaStatus seek(uint64_t offset) {
        GR_FATAL(GTXT("Cannot seek stream: not implemented"));
    }

    /**
     * @brief Returns size of all readable data in stream
     * @return size of all readable data in stream on success, negative value on error
     */
    virtual int64_t get_size() {
        GR_FATAL(GTXT("Cannot get stream size: not implemented"));
    }

    /**
     * @brief Returns current position in stream
     * @return current position in stream
     */
    virtual uint64_t tell() {
        GR_FATAL(GTXT("Cannot tell stream position: not implemented"));
    }

    virtual uint32_t get_capabilities() const {
        return 0;
    }

    [[deprecated]] gnaPointer<nxfBinaryResource> readAll();
    gnaStatus readAll(gnaPointer<nxfBinaryResource> &resource);

    gnaStatus readAllAsString(gtl::AString &str);
};
