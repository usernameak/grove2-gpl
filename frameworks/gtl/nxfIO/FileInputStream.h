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

#include <nxfIO/RAInputStream.h>
#include <gtlString/String.h>

class GTL_DLLIMPEXP nxfFileInputStream : public nxfRAInputStream {
#ifdef _WIN32
    void *fh;
#else
    int fh;
#endif

public:
    GTL_RTTI_DECLARE();

    nxfFileInputStream();

    /**
     * @brief Opens a file
     * @param filename filename
     * @return status of the operation
     */
    gnaStatus open(gtl::String filename);

    gnaStatus read(void *data, uint32_t size, uint32_t *bytesRead = nullptr) override;

    gnaStatus readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead = nullptr) override;

    gnaStatus seek(uint64_t offset) override;

    int64_t get_size() override;

    uint64_t tell() override;

    uint32_t get_capabilities() const override {
        return CAP_RANDOM_ACCESS | CAP_THREADSAFE_ACCESS;
    }

    virtual ~nxfFileInputStream() override;
};
