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

#include <nxfResource/ResourceManager.h>
#include <nxfIO/RAInputStream.h>
#include <unordered_map>
#include <nxfResource/Index/GridResourceIndex.h>
#include <limits>

namespace nxfResource {
    class GTL_DLLIMPEXP GPKArchive : public nxfResourceManager {
        typedef uint32_t EntryID;
        static constexpr EntryID INVALID_ENTRY_ID = std::numeric_limits<EntryID>::max();

        class GridIndexImpl : public GridResourceIndex {
            GPKArchive *m_arch;
            int64_t m_minX, m_maxX, m_minY, m_maxY;
            uint64_t m_stride;
            EntryID *m_indexData;
        public:
            GridIndexImpl(GPKArchive *arch);
            virtual ~GridIndexImpl() override;

            gnaStatus get_nodeByIndex(int64_t x, int64_t y, gnaPointer<nxfInputStream> &stream, uint32_t flags = 0) override;

            gnaStatus deserialize(nxfInputStream &stream);
        };

        bool m_indexInitialized;

        enum EntryType : uint16_t {
            GPKENT_FILE,
            GPKENT_DIRECTORY,
            GPKENT_ZLIBFILE,
        };

        enum CompresionMethod : uint8_t {
            GPKCOMPRESS_NONE        = 0,
            GPKCOMPRESS_ZLIB        = 1,
            GPKCOMPRESS_LZ4HC_BLOCK = 2,
        };

        gnaPointer<nxfRAInputStream> m_stream;
        gnaPointer<nxfInputStream> m_blockDecompressStream;

        struct EntryData {
            EntryType type;
            gtl::String name;

            uint64_t offset, size, uncompressedSize;
        };

        std::unordered_map<gtl::String, EntryID> m_entryNameToID;
        std::vector<EntryData> m_entries;

        uint32_t m_version;
        CompresionMethod m_compressionMode;

    public:
        GTL_RTTI_DECLARE();

        GPKArchive(gnaPointer<nxfRAInputStream> stream);
        
        gnaPointer<GridResourceIndex> getGridIndex(
            const gtl::String &root,
            const gtl::String &extension,
            bool allowDirect = true) override;

        void initializeIndex(bool reinitialize = false) override;

        bool isFile(gtl::String name) override;

        bool listFiles(gtl::String directory, std::unordered_set<grFsPlatform::ListFilesEntry> &filenames) override;

        gnaStatus get_resourceStream(gtl::String name, gnaPointer<nxfInputStream> &outStream, uint32_t flags) override;

    private:
        EntryData *findEntry(gtl::String name);

        gnaStatus openStreamFromEntryID(EntryID id, gnaPointer<nxfInputStream> &outStream, uint32_t flags);

        gnaStatus openStreamFromEntry(EntryData *entry, gnaPointer<nxfInputStream> &stream, uint32_t flags);
    };
}
