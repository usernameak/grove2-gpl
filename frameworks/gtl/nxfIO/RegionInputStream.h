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

#include "RAInputStream.h"

namespace nxfIO {
    class RegionInputStream : public nxfRAInputStream {
        gnaPointer<nxfRAInputStream> m_stream;
        uint64_t m_regionOffset;
        uint64_t m_regionSize;
        uint64_t m_curOffset;
    public:
        RegionInputStream();

        /**
         * @brief Opens a subregion of another stream
         * @param stream the stream to open a subregion of 
         * @param offset the offset of the subregion
         * @param size the size of the subregion
         * @return status of the operation
         */
        gnaStatus open(gnaPointer<nxfRAInputStream> stream, uint64_t offset, uint64_t size);

        gnaStatus read(void *data, uint32_t size, uint32_t *bytesRead = nullptr) override;

        gnaStatus readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead = nullptr) override;

        gnaStatus seek(uint64_t offset) override;

        int64_t get_size() override;

        uint64_t tell() override;

        uint32_t get_capabilities() const override {
            return CAP_RANDOM_ACCESS | m_stream->get_capabilities();
        }

        virtual ~RegionInputStream() override;
    };
}
