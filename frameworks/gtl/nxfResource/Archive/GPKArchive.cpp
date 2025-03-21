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

#include "GPKArchive.h"


#include "nxfIO/BlockCompression/LZ4BlockInputStream.h"

#include <nxfSerialization/PrimitiveSerializers.h>
#include <nxfIO/RegionInputStream.h>
#include <nxfIO/ZLIBInputStream.h>
#include <nxfIO/BufferedInputStream.h>

GTL_RTTI_DEFINE(nxfResource::GPKArchive, GTL_RTTI_INHERITS(nxfResourceManager));

nxfResource::GPKArchive::GPKArchive(gnaPointer<nxfRAInputStream> stream)
    : m_indexInitialized(false),
      m_stream(std::move(stream)),
      m_version(UINT32_MAX) {}

gnaPointer<nxfResource::GridResourceIndex> nxfResource::GPKArchive::getGridIndex(const gtl::String &root, const gtl::String &extension, bool allowDirect) {
    if (m_version >= 0x1002) {
        auto *entry = findEntry(root);
        if (entry && entry->size != 0) {
            gnaPointer<nxfInputStream> stream;
            if (!openStreamFromEntry(entry, stream, 0 /* buffered is fine */)) {
                return nullptr;
            }
            if (stream) {
                uint32_t flags;
                if (!nxfDeserializeNumber(flags, *stream)) return nullptr;

                if (flags & 0x1) {
                    // has a spatial index
                    auto index = gnaNew<GridIndexImpl>(this);
                    if (!index->deserialize(*stream)) {
                        return nullptr;
                    }

                    return index;
                }
            }
        }
    }
    return nxfResourceManager::getGridIndex(root, extension, allowDirect);
}

void nxfResource::GPKArchive::initializeIndex(bool reinitialize) {
    if (!reinitialize && m_indexInitialized) {
        return;
    }

    m_entryNameToID.clear();
    m_entries.clear();

    m_stream->seek(0);

    char magic[4];
    m_stream->read(&magic, 4);

    if (memcmp(magic, "GPK0", 4) != 0) {
        GR_WARNING(GTXT("invalid GPK archive magic"));
        return;
    }

    uint32_t flags;
    nxfDeserializeNumber(m_version, *m_stream);
    if (m_version < 0x1000 || m_version > 0x1003) {
        GR_WARNING(GTXT("incompatible GPK archive version 0x%04x"), m_version);
        return;
    }
    nxfDeserializeNumber(flags, *m_stream);

    uint8_t reserved;
    nxfDeserializeEnum(m_compressionMode, *m_stream);
    nxfDeserializeNumber(reserved, *m_stream);
    nxfDeserializeNumber(reserved, *m_stream);
    nxfDeserializeNumber(reserved, *m_stream);

    uint32_t numEntries;
    nxfDeserializeNumber(numEntries, *m_stream);

    for (uint32_t i = 0; i < numEntries; ++i) {
        EntryData entdat;
        nxfDeserializeEnum(entdat.type, *m_stream);
        nxfDeserializeString(entdat.name, *m_stream);
        if (m_version < 0x1001) {
            entdat.name = entdat.name.toLowerCase();
        }

        nxfDeserializeNumber<uint64_t>(entdat.offset, *m_stream);
        nxfDeserializeNumber<uint64_t>(entdat.size, *m_stream);
        nxfDeserializeNumber<uint64_t>(entdat.uncompressedSize, *m_stream);

        m_entryNameToID[entdat.name] = (EntryID)m_entries.size();
        m_entries.push_back(std::move(entdat));
    }

    m_blockDecompressStream = m_stream;

    if (m_compressionMode == GPKCOMPRESS_LZ4HC_BLOCK) {
        auto blockInputStream = gnaNew<nxfIO::LZ4BlockInputStream>();
        blockInputStream->open(m_stream);
        m_blockDecompressStream = blockInputStream;
    }
}

bool nxfResource::GPKArchive::isFile(gtl::String name) {
    auto *entry = findEntry(name);

    return entry && entry->type != GPKENT_DIRECTORY;
}

bool nxfResource::GPKArchive::listFiles(gtl::String directory, std::unordered_set<grFsPlatform::ListFilesEntry> &filenames) {
    // extremely inefficient!
    // we might need an additional index for this
    directory = normalizePath(directory);

    if (!directory.endsWith(GTXT("/"))) {
        directory += GTXT('/');
    }

    for (auto &pair : m_entryNameToID) {
        if (pair.first.startsWith(directory)) {
            gtl::String namePart = pair.first.substr(directory.size());
            if (namePart.indexOf(GTXT('/')) != namePart.size()) {
                continue;
            }

            grFsPlatform::ListFilesEntry entry;
            entry.filename = namePart;
            entry.type     = m_entries[pair.second].type == GPKENT_DIRECTORY ? grFsPlatform::FileEntryType::DIRECTORY : grFsPlatform::FileEntryType::FILE;

            filenames.insert(entry);
        }
    }

    return true;
}

gnaStatus nxfResource::GPKArchive::get_resourceStream(gtl::String name, gnaPointer<nxfInputStream> &outStream, uint32_t flags) {
    auto *entry = findEntry(name);

    if (!entry) {
        return GNA_E_FILE_NOT_FOUND;
    }
    if (entry->type == GPKENT_DIRECTORY) {
        return GNA_E_IS_A_DIR;
    }

    return openStreamFromEntry(entry, outStream, flags);
}

nxfResource::GPKArchive::EntryData *nxfResource::GPKArchive::findEntry(gtl::String name) {
    name = normalizePath(name);

    auto it = m_entryNameToID.find(name);
    if (it == m_entryNameToID.end()) {
        return nullptr;
    }

    return &m_entries[it->second];
}

gnaStatus nxfResource::GPKArchive::openStreamFromEntryID(EntryID id, gnaPointer<nxfInputStream> &outStream, uint32_t flags) {
    if (id >= m_entries.size()) {
        return GNA_E_FILE_NOT_FOUND;
    }
    return openStreamFromEntry(&m_entries[id], outStream, flags);
}

gnaStatus nxfResource::GPKArchive::openStreamFromEntry(EntryData *entry, gnaPointer<nxfInputStream> &stream, uint32_t flags) {
    if (!entry) {
        return GNA_E_INVALID_ARGUMENT;
    }

    {
        auto regionStream = gnaNew<nxfIO::RegionInputStream>();
        GNA_CHECK_STATUS(regionStream->open(m_blockDecompressStream, entry->offset, entry->size));
        stream = regionStream;
    }
    if (entry->type == GPKENT_ZLIBFILE || m_compressionMode == GPKCOMPRESS_ZLIB) {
        auto zlibStream = gnaNew<nxfIO::ZLIBInputStream>();
        GNA_CHECK_STATUS(zlibStream->open(stream, entry->uncompressedSize));
        stream = zlibStream;
    }
    if (m_blockDecompressStream == m_stream && !(flags & FLAG_UNBUFFERED)) {
        stream = gnaNew<nxfIO::BufferedInputStream>(stream);
    }
    return GNA_E_OK;
}

nxfResource::GPKArchive::GridIndexImpl::GridIndexImpl(GPKArchive *arch)
    : m_arch(arch),
      m_minX(0),
      m_maxX(0),
      m_minY(0),
      m_maxY(0),
      m_stride(0),
      m_indexData(nullptr) {
}

nxfResource::GPKArchive::GridIndexImpl::~GridIndexImpl() {
    gtlDeleteArray m_indexData;
}

gnaStatus nxfResource::GPKArchive::GridIndexImpl::get_nodeByIndex(int64_t x, int64_t y, gnaPointer<nxfInputStream> &stream, uint32_t flags) {
    if (!m_indexData) {
        return GNA_E_INVALID_STATE;
    }
    if (x < m_minX || x > m_maxX) {
        return GNA_E_FILE_NOT_FOUND;
    }
    if (y < m_minY || x > m_maxY) {
        return GNA_E_FILE_NOT_FOUND;
    }
    auto offsetX = (uint64_t)(x - m_minX);
    auto offsetY = (uint64_t)(y - m_minY);
    auto index   = offsetX + offsetY * m_stride;

    EntryID entryID = m_indexData[index];
    if (entryID == INVALID_ENTRY_ID) {
        return GNA_E_FILE_NOT_FOUND;
    }

    return m_arch->openStreamFromEntryID(entryID, stream, flags);
}

gnaStatus nxfResource::GPKArchive::GridIndexImpl::deserialize(nxfInputStream &stream) {
    GNA_CHECK_STATUS(nxfDeserializeNumber<int64_t>(m_minX, stream));
    GNA_CHECK_STATUS(nxfDeserializeNumber<int64_t>(m_maxX, stream));
    GNA_CHECK_STATUS(nxfDeserializeNumber<int64_t>(m_minY, stream));
    GNA_CHECK_STATUS(nxfDeserializeNumber<int64_t>(m_maxY, stream));
    m_stride = m_maxX - m_minX + 1;

    m_indexData = gtlNew EntryID[(m_maxY - m_minY + 1) * (m_maxX - m_minX + 1)];

    size_t i = 0;
    for (int64_t y = m_minY; y <= m_maxY; y++) {
        for (int64_t x = m_minX; x <= m_maxX; x++) {
            GNA_CHECK_STATUS(nxfDeserializeNumber<uint32_t>(m_indexData[i++], stream));
        }
    }

    return GNA_E_OK;
}
