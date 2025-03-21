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

#include "TextInputStream.h"
#include <nxfIO/InputStream.h>

namespace nxfIO {
    class GTL_DLLIMPEXP BufferedTextInputStream : public TextInputStream {
        gnaPointer<nxfInputStream> m_stream;

        static constexpr uint32_t BUF_SIZE = 4096;

        gtl::ASCIICHAR m_buffer[BUF_SIZE]; // why static buffer size?
        uint32_t m_bufferOffset, m_bufferRemaining;

    public:
        BufferedTextInputStream(gnaPointer<nxfInputStream> stream);

        gnaStatus read(gtl::ASCIICHAR *data, uint32_t size, uint32_t *charsRead = nullptr) override;
        gnaStatus readLine(gtl::AString &outStr);

    private:
        gnaStatus refillBuffer();
    };
}
