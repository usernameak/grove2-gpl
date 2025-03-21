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

#include "BufferedTextInputStream.h"

nxfIO::BufferedTextInputStream::BufferedTextInputStream(gnaPointer<nxfInputStream> stream)
    : m_stream(std::move(stream)),
      m_bufferOffset(0),
      m_bufferRemaining(0) {}

gnaStatus nxfIO::BufferedTextInputStream::read(gtl::ASCIICHAR *data, uint32_t size, uint32_t *charsRead) {
    uint32_t totalRead     = 0;
    uint32_t remainingRead = size;
    if (m_bufferRemaining < size) {
        memcpy(data + totalRead, m_buffer + m_bufferOffset, m_bufferRemaining);

        remainingRead -= m_bufferRemaining;
        totalRead += m_bufferRemaining;

        m_bufferRemaining = 0;
        m_bufferOffset    = 0;
    } else {
        memcpy(data + totalRead, m_buffer + m_bufferOffset, size);

        remainingRead -= size;
        totalRead += size;

        m_bufferRemaining -= size;
        m_bufferOffset += size;

        if (charsRead) {
            *charsRead = totalRead;
        }

        return GNA_E_OK;
    }
    if (remainingRead >= BUF_SIZE) {
        uint32_t totalDirectRead;
        GNA_CHECK_STATUS(m_stream->read(data + totalRead, remainingRead, &totalDirectRead));

        totalRead += totalDirectRead;
        remainingRead -= totalDirectRead;

        if (charsRead) {
            *charsRead = totalRead;
        }

        return GNA_E_OK;
    }

    GNA_CHECK_STATUS(refillBuffer());

    if (m_bufferRemaining < size) {
        memcpy(data + totalRead, m_buffer + m_bufferOffset, m_bufferRemaining);

        remainingRead -= m_bufferRemaining;
        totalRead += m_bufferRemaining;

        m_bufferRemaining = 0;
        m_bufferOffset    = 0;
    } else {
        memcpy(data + totalRead, m_buffer + m_bufferOffset, size);

        remainingRead -= size;
        totalRead += size;

        m_bufferRemaining -= size;
        m_bufferOffset += size;
    }

    if (charsRead) {
        *charsRead = totalRead;
    }

    return GNA_E_OK;
}

gnaStatus nxfIO::BufferedTextInputStream::readLine(gtl::AString &outStr) {
    bool anyRead = false;
    while (true) {
        gtl::ASCIICHAR c;
        uint32_t charsRead = 0;
        GNA_CHECK_STATUS(this->read(&c, 1, &charsRead));
        if (charsRead == 0) {
            if (!anyRead) {
                return GNA_E_END_OF_DATA;
            }
            break;
        }
        if (c == '\r') {
            GNA_CHECK_STATUS(this->read(&c, 1, &charsRead));
            if (charsRead > 0 && c == '\n') {
                break;
            }
            outStr += '\r';
            if (charsRead == 0) {
                break;
            }
        }
        if (c == '\n') {
            break;
        }
        anyRead = true;
        outStr += c;
    }

    return GNA_E_OK;
}

gnaStatus nxfIO::BufferedTextInputStream::refillBuffer() {
    m_bufferOffset = 0;

    GNA_CHECK_STATUS(m_stream->read(m_buffer, BUF_SIZE, &m_bufferRemaining));

    return GNA_E_OK;
}
