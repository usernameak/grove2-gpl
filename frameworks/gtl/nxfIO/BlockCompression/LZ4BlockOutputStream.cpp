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

#include "LZ4BlockOutputStream.h"

#include <nxfSerialization/PrimitiveSerializers.h>

nxfIO::LZ4BlockOutputStream::LZ4BlockOutputStream()
    : m_lzstream(nullptr),
      m_inputBufferOffset(0),
      m_inputBuffer{},
      m_outputBuffer{},
      m_startOffset(0),
      m_currentTellOffset(0) {
}

nxfIO::LZ4BlockOutputStream::~LZ4BlockOutputStream() {
    if (finish().errorCode != GNA_E_INVALID_STATE) {
        GR_WARNING(GTXT("LZ4BlockOutputStream destroyed without calling finish(). Please, call finish() with proper error handling."));
    }
}

gnaStatus nxfIO::LZ4BlockOutputStream::open(gnaPointer<nxfOutputStream> stream) {
    m_stream            = stream;
    m_lzstream          = LZ4_createStreamHC();
    m_inputBufferOffset = 0;

    m_startOffset       = m_stream->tell();
    m_currentTellOffset = 0;

    GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(0xDEADBEEFCAFEBABE, *stream)); // will be the index offset
    GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(0x1337133713371337, *stream)); // will be the uncompressed size

    return GNA_E_OK;
}

gnaStatus nxfIO::LZ4BlockOutputStream::write(const void *data, uint32_t size, uint32_t *bytesWritten) {
    if (bytesWritten) {
        *bytesWritten = 0;
    }

    if (!m_stream)
        return GNA_E_INVALID_STATE; // not opened

    if (size == 0)
        return GNA_E_OK;

    size_t sizeLeft   = size;
    size_t dataOffset = 0;

    while (sizeLeft > GPK_LZ4_BLOCK_SIZE - m_inputBufferOffset) {
        size_t chunkSize = GPK_LZ4_BLOCK_SIZE - m_inputBufferOffset;

        memcpy(m_inputBuffer + m_inputBufferOffset, (const unsigned char *)data + dataOffset, chunkSize);

        LZ4_resetStreamHC_fast(m_lzstream, LZ4HC_CLEVEL_DEFAULT);

        int numBytes = LZ4_compress_HC_continue(
            m_lzstream,
            (char *)m_inputBuffer, (char *)m_outputBuffer,
            sizeof(m_inputBuffer), sizeof(m_outputBuffer));

        if (numBytes == 0) {
            return { GNA_E_FAILED, GTXT("LZ4 Compression failed") };
        }

        m_blockIndex.push_back(m_stream->tell() - m_startOffset);

        GNA_CHECK_STATUS(m_stream->write(m_outputBuffer, numBytes));

        m_inputBufferOffset = 0;

        sizeLeft -= chunkSize;
        dataOffset += chunkSize;
    }

    memcpy(m_inputBuffer + m_inputBufferOffset, (const unsigned char *)data + dataOffset, sizeLeft);
    m_inputBufferOffset += sizeLeft;

    m_currentTellOffset += size;

    if (bytesWritten) {
        *bytesWritten = size;
    }

    return GNA_E_OK;
}

gnaStatus nxfIO::LZ4BlockOutputStream::flush() {
    return GNA_E_OK;
}

uint64_t nxfIO::LZ4BlockOutputStream::tell() {
    return m_currentTellOffset;
}

gnaStatus nxfIO::LZ4BlockOutputStream::writeBlockIndex() {
    flushLastBlock();

    LZ4_freeStreamHC(m_lzstream);
    m_lzstream = nullptr;

    uint64_t indexOffset = m_stream->tell() - m_startOffset;
    GNA_CHECK_STATUS(nxfSerializeNumber<uint32_t>(m_blockIndex.size(), *m_stream));
    for (uint64_t offset : m_blockIndex) {
        GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(offset, *m_stream));
    }
    uint64_t endOffset = m_stream->tell();

    GNA_CHECK_STATUS(seek(m_startOffset));

    GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(indexOffset, *m_stream));
    GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(m_currentTellOffset, *m_stream));

    GNA_CHECK_STATUS(m_stream->seek(endOffset));

    return GNA_E_OK;
}

gnaStatus nxfIO::LZ4BlockOutputStream::finish() {
    if (m_stream == nullptr) {
        return GNA_E_INVALID_STATE;
    }

    writeBlockIndex();

    m_stream = nullptr;

    return GNA_E_OK;
}

gnaStatus nxfIO::LZ4BlockOutputStream::flushLastBlock() {
    if (m_inputBufferOffset != 0) {
        assert(m_lzstream);

        LZ4_resetStreamHC_fast(m_lzstream, LZ4HC_CLEVEL_DEFAULT);

        int numBytes = LZ4_compress_HC_continue(
            m_lzstream,
            (char *)m_inputBuffer, (char *)m_outputBuffer,
            m_inputBufferOffset, sizeof(m_outputBuffer));

        if (numBytes == 0) {
            return { GNA_E_FAILED, GTXT("LZ4 Compression failed") };
        }

        m_blockIndex.push_back(m_stream->tell() - m_startOffset);

        GNA_CHECK_STATUS(m_stream->write(m_outputBuffer, numBytes));

        m_inputBufferOffset = 0;
    }

    return GNA_E_OK;
}
