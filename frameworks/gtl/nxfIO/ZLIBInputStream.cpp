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

#include "ZLIBInputStream.h"

nxfIO::ZLIBInputStream::ZLIBInputStream()
    : m_streamDone(true),
      m_inputBufferAvailable(0),
      m_inputBufferOffset(0),
      m_uncompressedSize(UINT64_MAX) {
    memset(&m_zStream, 0, sizeof(m_zStream));
}

gnaStatus nxfIO::ZLIBInputStream::open(gnaPointer<nxfInputStream> stream, uint64_t uncompressedSize) {
    m_stream = stream;
    memset(&m_zStream, 0, sizeof(m_zStream));
    int status             = inflateInit(&m_zStream);
    m_streamDone           = false;
    m_inputBufferAvailable = 0;
    m_inputBufferOffset    = 0;
    m_uncompressedSize     = uncompressedSize;

    return status == Z_OK;
}

gnaStatus nxfIO::ZLIBInputStream::read(void *data, uint32_t size, uint32_t *bytesRead) {
    if (m_streamDone || size == 0) {
        if (bytesRead) {
            *bytesRead = 0;
        }
        return GNA_E_OK;
    }

    uint32_t outStreamRemaining = size;

    m_zStream.next_out  = (unsigned char *)data;
    m_zStream.avail_out = outStreamRemaining;

    while (outStreamRemaining > 0) {
        m_zStream.next_in  = m_inputBuffer + m_inputBufferOffset;
        m_zStream.avail_in = m_inputBufferAvailable;

        int inflate_res;
        do {
            inflate_res = inflate(&m_zStream, Z_SYNC_FLUSH);

            if (inflate_res == Z_STREAM_END) {
                m_streamDone = true;

                outStreamRemaining = m_zStream.avail_out;
                goto leave;
            }

            if (inflate_res == Z_STREAM_ERROR) {
                return { GNA_E_FAILED, GTXT("Decompression failed, stream error") };
            } else if (inflate_res == Z_PARAM_ERROR) {
                return { GNA_E_FAILED, GTXT("Decompression failed, param error") };
            } else if (inflate_res == Z_DATA_ERROR) {
                return { GNA_E_FAILED, GTXT("Decompression failed, data error") };
            } else if (inflate_res == Z_BUF_ERROR) {
                break;
            }
        } while (m_zStream.avail_in && m_zStream.avail_out);

        if (inflate_res == Z_BUF_ERROR || inflate_res == Z_OK) {
            m_inputBufferOffset    = (uint32_t)(m_zStream.next_in - m_inputBuffer);
            m_inputBufferAvailable = m_zStream.avail_in;

            outStreamRemaining = m_zStream.avail_out;
            if (outStreamRemaining == 0) {
                break;
            }

            assert(m_inputBufferAvailable == 0);

            m_inputBufferOffset = 0;
            GNA_CHECK_STATUS(m_stream->read(m_inputBuffer, ZLIBSTREAM_INPUT_BUFFER_SIZE, &m_inputBufferAvailable));
            if (inflate_res == Z_BUF_ERROR && m_inputBufferAvailable == 0) {
                return { GNA_E_FAILED, GTXT("Decompression failed, premature end of stream") };
            }

            m_zStream.next_in  = m_inputBuffer + m_inputBufferOffset;
            m_zStream.avail_in = m_inputBufferAvailable;
        }
    }
leave:
    if (outStreamRemaining == size) {
        assert(m_streamDone);
    }
    if (bytesRead) {
        *bytesRead = size - outStreamRemaining;
    }
    return GNA_E_OK;
}

int64_t nxfIO::ZLIBInputStream::get_size() {
    if (m_uncompressedSize == UINT64_MAX) {
        GR_FATAL("nxfIO::ZLIBInputStream::get_size(): cannot get stream size, the stream does not have uncompressed data size specified");
    }
    return (int64_t)m_uncompressedSize;
}

nxfIO::ZLIBInputStream::~ZLIBInputStream() {
    inflateEnd(&m_zStream);
}
