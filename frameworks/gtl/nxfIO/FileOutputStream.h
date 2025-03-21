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
#include <gtlString/String.h>

class GTL_DLLIMPEXP nxfFileOutputStream : public nxfOutputStream {
    void *fh;

public:
    nxfFileOutputStream();

    /**
     * @brief Opens a file
     * @param filename filename
     * @return 0 on success, negative value on failure
     */
    gnaStatus open(gtl::String filename);

    /**
     * @brief Writes data to stream
     * @param data buffer to write into the stream
     * @param size buffer size
     * @param bytesWritten (out) count of bytes written, if required
     * @return gnaStatus status code
     */
    gnaStatus write(const void *data, uint32_t size, uint32_t *bytesWritten = nullptr) override;

    /**
     * @brief Seeks stream
     * @param offset position in file to seek into
     * @return true on success, false on error
     */
    bool seek(uint64_t offset) override;

    /**
     * @brief Returns size of all written data in stream
     * @return size of all written data in stream on success, negative value on error
     */
    int64_t get_size() override;

    /**
     * @brief Returns current position in stream
     * @return current position in stream
     */
    uint64_t tell() override;

    gnaStatus flush() override;

    virtual ~nxfFileOutputStream() override;
};
