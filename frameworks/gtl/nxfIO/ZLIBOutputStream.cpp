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

#include "ZLIBOutputStream.h"

#include <gtlString/String.h>
#include <nxfIO/FsPlatform.h>

using namespace nxfIO;

ZLIBOutputStream::ZLIBOutputStream() : nxfOutputStream(), m_stream(nullptr) {
}

gnaStatus ZLIBOutputStream::open(gnaPointer<nxfOutputStream> stream) {
    m_stream = stream;

    memset(&m_mzstream, 0, sizeof(m_mzstream));
    m_mzstream.next_in = NULL;
    m_mzstream.avail_in = 0;
    m_mzstream.next_out = m_outputBuffer;
    m_mzstream.avail_out = GPK_ZLIB_BUFFER_SIZE;

    if(deflateInit(&m_mzstream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return GNA_E_FAILED;
    }

    return GNA_E_OK;
}

gnaStatus ZLIBOutputStream::write(const void *data, uint32_t size, uint32_t *bytesWritten) {
    if (m_stream == nullptr)
        return GNA_E_INVALID_STATE; // not opened

    if (size == 0) {
        return GNA_E_OK;
    }

    m_mzstream.next_in = (const unsigned char *) data;
    m_mzstream.avail_in = size;
    while (m_mzstream.avail_in) {
        m_mzstream.next_out = m_outputBuffer;
        m_mzstream.avail_out = GPK_ZLIB_BUFFER_SIZE;

        int dsta = deflate(&m_mzstream, Z_NO_FLUSH);
        if (dsta == Z_BUF_ERROR) {
            GR_FATAL(GTXT("Z_BUF_ERROR received from deflate, invalid state."));
        } else if (dsta != Z_OK) {
            return GNA_E_FAILED; // shit, compression failed
        }

        size_t outSize = m_mzstream.next_out - m_outputBuffer;
        GNA_CHECK_STATUS(m_stream->write(m_outputBuffer, (uint32_t) outSize));
    }

    return GNA_E_OK;
}

gnaStatus ZLIBOutputStream::flush() {
    return GNA_E_OK;
}

gnaStatus ZLIBOutputStream::finish() {
    if (m_stream == nullptr) {
        return GNA_E_INVALID_STATE;
    }

    m_mzstream.next_in = NULL;
    m_mzstream.avail_in = 0;

    while (true) {
        m_mzstream.next_out = m_outputBuffer;
        m_mzstream.avail_out = GPK_ZLIB_BUFFER_SIZE;

        int dsta = deflate(&m_mzstream, Z_FINISH);
        if (dsta != Z_OK && dsta != Z_BUF_ERROR && dsta != Z_STREAM_END) {
            deflateEnd(&m_mzstream);
            m_stream = nullptr;
            return GNA_E_FAILED; // shit, compression failed
        }

        size_t outSize = m_mzstream.next_out - m_outputBuffer;
        GNA_CHECK_STATUS(m_stream->write(m_outputBuffer, (uint32_t) outSize));

        if (dsta == Z_STREAM_END) {
            break;
        }
    }
    deflateEnd(&m_mzstream);
    m_stream = nullptr;
    return GNA_E_OK;
}

ZLIBOutputStream::~ZLIBOutputStream() {
    if (finish().errorCode != GNA_E_INVALID_STATE) {
        GR_WARNING(GTXT("ZlibOutputStream destroyed without calling finish(). Please, call finish() with proper error handling."));
    }
}
