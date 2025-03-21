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

#include <gtlUtil/Logging.h>
#include <gtlString/String.h>
#include <array>

#include <nxfResource/ResourceManager.h>
#include <nxfResource/FlatFileResourceManager.h>
#include <nxfResource/Archive/GPKArchive.h>
#include <nxfIO/FileOutputStream.h>
#include <nxfSerialization/PrimitiveSerializers.h>
#include <nxfUtil/EntryListReader.h>
#include <nxfIO/ZLIBOutputStream.h>
#include <nxfIO/FileInputStream.h>
#include <nxfIO/Text/BufferedTextInputStream.h>
#include <nxfIO/BlockCompression/LZ4BlockOutputStream.h>

#include <grMain.h>

enum GPKEntryType : uint16_t {
    GPKENT_FILE      = 0,
    GPKENT_DIRECTORY = 1,

// legacy entry types, now compression method is a global flag
#if 0
    GPKENT_ZLIBFILE = 2,
    GPKENT_LZ4HC_BLOCK_FILE = 3,
#endif
};

enum GPKCompresionMethod : uint8_t {
    GPKCOMPRESS_NONE        = 0,
    GPKCOMPRESS_ZLIB        = 1,
    GPKCOMPRESS_LZ4HC_BLOCK = 2,
};

struct GPKSpatialIndexCoords {
    long long x, y;

    bool operator==(GPKSpatialIndexCoords other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(GPKSpatialIndexCoords other) const {
        return !operator==(other);
    }
};

namespace std {
    template <>
    struct hash<GPKSpatialIndexCoords> {
        std::size_t operator()(GPKSpatialIndexCoords s) const noexcept {
            std::size_t h = s.x;
            h             = 31 * h + s.y;
            return h;
        }
    };
}

struct GPKConfigArchiveEntry {
    gtl::String archiveName;
    std::vector<gtl::String> includes;
    std::vector<gtl::String> excludes;

    GPKCompresionMethod compressionMode;
    bool useSpatialIndexes : 1;
};

struct GPKEntryData {
    GPKEntryType type;
    gtl::String name;

    uint64_t entryOffsetSizeOffset;
    uint64_t entryOffset;
    uint32_t entryIndex;
};

static bool buildEntryList(nxfResourceManager *inRM, std::list<GPKEntryData> &outEntries, gtl::String rootPath) {
    std::vector<grFsPlatform::ListFilesEntry> inEntries;
    if (!inRM->listFiles(rootPath, inEntries)) return false;

    for (auto &ent : inEntries) {
        GPKEntryData entdata;
        entdata.type = ent.type == grFsPlatform::FileEntryType::DIRECTORY ? GPKENT_DIRECTORY : GPKENT_FILE;

        gtl::String fullName = rootPath;
        fullName += ent.filename;
        entdata.name = fullName;

        outEntries.push_back(entdata);

        if (ent.type == grFsPlatform::FileEntryType::DIRECTORY) {
            fullName += GTXT('/');
            if (!buildEntryList(inRM, outEntries, fullName)) return false;
        }
    }

    return true;
}

static bool checkExceptions(gtl::String filename, const GPKConfigArchiveEntry &archent) {
    bool includePassed = false;
    for (const gtl::String &include : archent.includes) {
        if (filename == include || filename.startsWith(include + GTXT('/'))) {
            includePassed = true;
            break;
        }
    }
    if (!includePassed) return false;
    for (const gtl::String &exclude : archent.excludes) {
        if (filename == exclude || filename.startsWith(exclude + GTXT('/'))) {
            return false;
        }
    }
    return true;
}

static gnaStatus packFile(nxfResourceManager *inRM, std::list<GPKEntryData> &entryList, const gtl::String &packagesPath, const GPKConfigArchiveEntry &archent) {
    gtl::String packagePath = grFsPlatform::combinePaths(packagesPath, archent.archiveName);

    gnaPointer<nxfFileOutputStream> stream = gnaNew<nxfFileOutputStream>();
    GNA_CHECK_STATUS(stream->open(packagePath));

    char magic[]{ 'G', 'P', 'K', '0' };
    GNA_CHECK_STATUS(stream->write(&magic, 4));
    GNA_CHECK_STATUS(nxfSerializeNumber<uint32_t>(0x1003, *stream));                 // version
    GNA_CHECK_STATUS(nxfSerializeNumber<uint32_t>(0, *stream));                      // flags
    GNA_CHECK_STATUS(nxfSerializeNumber<uint8_t>(archent.compressionMode, *stream)); // compression mode
    GNA_CHECK_STATUS(nxfSerializeNumber<uint8_t>(0, *stream));                       // reserved
    GNA_CHECK_STATUS(nxfSerializeNumber<uint8_t>(0, *stream));                       // reserved
    GNA_CHECK_STATUS(nxfSerializeNumber<uint8_t>(0, *stream));                       // reserved

    std::vector<GPKEntryData> usedEntryList;

    for (auto it = entryList.begin(); it != entryList.end();) {
        if (checkExceptions(it->name, archent)) {
            usedEntryList.push_back(*it);
            auto &entry = usedEntryList.back();
            it          = entryList.erase(it);
        } else {
            ++it;
        }
    }

    uint32_t nextEntryIndex = 0;
    GNA_CHECK_STATUS(nxfSerializeNumber<uint32_t>((uint32_t)usedEntryList.size(), *stream));
    for (GPKEntryData &entdat : usedEntryList) {
        entdat.entryIndex  = nextEntryIndex++;
        entdat.entryOffset = stream->tell();
        GNA_CHECK_STATUS(nxfSerializeNumber<uint16_t>(entdat.type, *stream));     // type
        GNA_CHECK_STATUS(nxfSerializeString(entdat.name.toLowerCase(), *stream)); // filename
        entdat.entryOffsetSizeOffset = stream->tell();
        GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(0, *stream)); // offset
        GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(0, *stream)); // compressed size
        GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(0, *stream)); // uncompressed size
    }

    gnaPointer<nxfOutputStream> bcStream = stream;
    if (archent.compressionMode == GPKCOMPRESS_LZ4HC_BLOCK) {
        gnaPointer<nxfIO::LZ4BlockOutputStream> lz4stream = gnaNew<nxfIO::LZ4BlockOutputStream>();
        GNA_CHECK_STATUS(lz4stream->open(stream));
        bcStream = lz4stream;
    }

    for (GPKEntryData &entdat : usedEntryList) {
        uint64_t compressedStartOffset = bcStream->tell();
        uint64_t uncompressedSize      = 0ULL;
        if (entdat.type == GPKENT_FILE) {
            auto assetStream = inRM->get_resourceStream(entdat.name);
            if (!assetStream) {
                return GNA_E_FAILED;
            }

            uncompressedSize = (uint64_t)assetStream->get_size();

            gnaPointer<nxfOutputStream> compressionStream = bcStream;
            bool isFileCompressed                         = false;
            if (archent.compressionMode == GPKCOMPRESS_ZLIB) {
                gnaPointer<nxfIO::ZLIBOutputStream> zlibStream = gnaNew<nxfIO::ZLIBOutputStream>();
                GNA_CHECK_STATUS(zlibStream->open(bcStream));
                compressionStream = zlibStream;
                isFileCompressed  = true;
            }
            while (true) {
                char databuf[256 * 1024];
                uint32_t bytesRead;
                GNA_CHECK_STATUS(assetStream->read(databuf, 256 * 1024, &bytesRead));
                if (bytesRead == 0) {
                    break;
                }

                GNA_CHECK_STATUS(compressionStream->write(databuf, bytesRead));
            }
            if (isFileCompressed) {
                GNA_CHECK_STATUS(compressionStream->finish());
            }
        } else if (entdat.type == GPKENT_DIRECTORY) {
            // initialize the spatial index, if required

            std::unordered_map<GPKSpatialIndexCoords, GPKEntryData *> spatialIndex;

            long long minX = LLONG_MAX,
                      maxX = LLONG_MIN,
                      minY = LLONG_MAX,
                      maxY = LLONG_MIN;

            if (archent.useSpatialIndexes) {
                for (GPKEntryData &subentdat : usedEntryList) {
                    gtl::String slashedDirName = entdat.name + GTXT('/');
                    if (!subentdat.name.startsWith(slashedDirName)) {
                        continue;
                    }
                    gtl::String fileName = subentdat.name.substr(slashedDirName.size());
                    if (fileName.indexOf(GTXT('/')) != fileName.size()) {
                        continue;
                    }

                    static const gtl::String smPrefix(GTXT("sm_"));
                    if (!fileName.startsWith(smPrefix)) {
                        continue;
                    }
                    gtl::String indexPart(fileName.substr(
                        smPrefix.size(),
                        fileName.lastIndexOf(GTXT('.'))));
                    gtl::String xPart(indexPart.substr(0, indexPart.indexOf(GTXT('_'))));
                    gtl::String yPart(indexPart.substr(indexPart.indexOf(GTXT('_')) + 1));

                    long long x, y;
                    if (!xPart.toLongLong(x)) {
                        continue;
                    }
                    if (!yPart.toLongLong(y)) {
                        continue;
                    }

                    spatialIndex[{ x, y }] = &subentdat;
                }

                if (spatialIndex.empty()) {
                    continue;
                }

                for (auto &pair : spatialIndex) {
                    if (pair.first.x < minX) {
                        minX = pair.first.x;
                    }
                    if (pair.first.x > maxX) {
                        maxX = pair.first.x;
                    }
                    if (pair.first.y < minY) {
                        minY = pair.first.y;
                    }
                    if (pair.first.y > maxY) {
                        maxY = pair.first.y;
                    }
                }

                GR_INFO(GTXT("Found %llux%llu spatial index at %ls"),
                    (unsigned long long)(maxX - minX) + 1,
                    (unsigned long long)(maxY - minY) + 1,
                    entdat.name.toCString());
            }

            // write various directory indexes

            uint32_t flags = 0;
            if (!spatialIndex.empty()) {
                flags |= 0x1;
            }
            GNA_CHECK_STATUS(nxfSerializeNumber(flags, *bcStream));

            if (!spatialIndex.empty()) {
                GNA_CHECK_STATUS(nxfSerializeNumber<int64_t>(minX, *bcStream));
                GNA_CHECK_STATUS(nxfSerializeNumber<int64_t>(maxX, *bcStream));
                GNA_CHECK_STATUS(nxfSerializeNumber<int64_t>(minY, *bcStream));
                GNA_CHECK_STATUS(nxfSerializeNumber<int64_t>(maxY, *bcStream));
                for (long long y = minY; y <= maxY; y++) {
                    for (long long x = minX; x <= maxX; x++) {
                        auto it = spatialIndex.find({ x, y });
                        if (it == spatialIndex.end()) {
                            GNA_CHECK_STATUS(nxfSerializeNumber<uint32_t>(UINT32_MAX, *bcStream));
                        } else {
                            GNA_CHECK_STATUS(nxfSerializeNumber<uint32_t>(it->second->entryIndex, *bcStream));
                        }
                    }
                }
            }
        }
        uint64_t compressedEndOffset = bcStream->tell();
        uint64_t endOffset           = stream->tell();
        GNA_CHECK_STATUS(stream->seek(entdat.entryOffsetSizeOffset));

        // offset
        GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(compressedStartOffset, *stream));
        // compressed size (or same as uncompressed size if block-compresed)
        GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(compressedEndOffset - compressedStartOffset, *stream));
        // uncompressed size
        GNA_CHECK_STATUS(nxfSerializeNumber<uint64_t>(uncompressedSize, *stream));

        GNA_CHECK_STATUS(stream->seek(endOffset));
    }
    GNA_CHECK_STATUS(bcStream->finish());

    return GNA_E_OK;
}

static gnaStatus unpackArchive(nxfResourceManager *inRM, const gtl::String &outDir, const gtl::String &currentRoot = GTXT("/")) {
    std::vector<grFsPlatform::ListFilesEntry> inEntries;
    if (!inRM->listFiles(currentRoot, inEntries)) return false;

    grFsPlatform::createDirectory(outDir + currentRoot);

    for (auto &ent : inEntries) {
        GPKEntryData entdata;
        entdata.type = ent.type == grFsPlatform::FileEntryType::DIRECTORY ? GPKENT_DIRECTORY : GPKENT_FILE;

        gtl::String fullName = currentRoot;
        fullName += ent.filename;
        entdata.name = fullName;

        if (ent.type == grFsPlatform::FileEntryType::DIRECTORY) {
            fullName += GTXT('/');

            GNA_CHECK_STATUS(unpackArchive(inRM, outDir, fullName));
        } else if (ent.type == grFsPlatform::FileEntryType::FILE) {
            auto assetStream = inRM->get_resourceStream(fullName);
            auto outStream   = gnaNew<nxfFileOutputStream>();
            GNA_CHECK_STATUS(outStream->open(outDir + fullName));

            std::vector<unsigned char> databuf;
            databuf.resize(256 * 1024);
            while (true) {
                uint32_t bytesRead;
                GNA_CHECK_STATUS(assetStream->read(databuf.data(), (uint32_t)databuf.size(), &bytesRead));
                if (bytesRead == 0) {
                    break;
                }

                GNA_CHECK_STATUS(outStream->write(databuf.data(), bytesRead));
            }
        }
    }

    return GNA_E_OK;
}

int GR_MAIN_CALLCONV grMain(int argc, gtl::WIDECHAR *argv[]) {
    grLog_useWindowsDebugOutput = false;

    if (argc < 2) {
        GR_FATAL(GTXT(
                     "invalid arguments.\n"
                     "usage: %ls -pack <directory> <packages_directory>\n"
                     "       %ls -unpack <filename.gpk> <out_directory>\n"),
            argv[0],
            argv[0]);
    }

    gtl::String mode = argv[1];
    if (mode == GTXT("-pack")) {
        if (argc != 4) {
            GR_FATAL(GTXT(
                         "invalid arguments.\n"
                         "usage: %ls -pack <directory> <packages_directory>\n"),
                argv[0]);
        }
        gtl::String inputDir = argv[2];

        nxfResourceManager *inRM = gtlNew nxfFlatFileResourceManager(inputDir);

        std::vector<GPKConfigArchiveEntry> archEntries;

        {
            auto cfgStream = inRM->get_resourceStream(GTXT("/gpkconfig.cfg"));
            if (!cfgStream) {
                GR_FATAL(GTXT("gpkconfig.cfg not found"));
            }

            GPKConfigArchiveEntry *curArchEntry = nullptr;

            nxfUtil::EntryListReader rd(cfgStream);
            gtl::AString entryName;
            gtl::AString entryValue;
            while (rd.readEntry(entryName, entryValue)) {
                if (entryName == "archive") {
                    curArchEntry                    = &archEntries.emplace_back();
                    curArchEntry->archiveName       = gtl::String(entryValue.toCString(), gtl::String::S_CHARSET_UTF8);
                    curArchEntry->compressionMode   = GPKCOMPRESS_LZ4HC_BLOCK;
                    curArchEntry->useSpatialIndexes = false;
                } else if (!curArchEntry) {
                    continue;
                } else if (entryName == "include") {
                    curArchEntry->includes.emplace_back(entryValue.toCString(), gtl::String::S_CHARSET_UTF8);
                } else if (entryName == "exclude") {
                    curArchEntry->excludes.emplace_back(entryValue.toCString(), gtl::String::S_CHARSET_UTF8);
                } else if (entryName == "compression") {
                    if (entryValue == "lz4hc_block") {
                        curArchEntry->compressionMode = GPKCOMPRESS_LZ4HC_BLOCK;
                    } else if (entryValue == "zlib") {
                        curArchEntry->compressionMode = GPKCOMPRESS_ZLIB;
                    } else {
                        curArchEntry->compressionMode = GPKCOMPRESS_NONE;
                    }
                } else if (entryName == "spatialIndex") {
                    curArchEntry->useSpatialIndexes = entryValue == "true";
                }
            }
        }

        std::list<GPKEntryData> entryList;
        if (!buildEntryList(inRM, entryList, GTXT("/"))) {
            GR_FATAL(GTXT("Could not traverse directory tree"));
        }

        gtl::String packagesDir = argv[3];
        grFsPlatform::createDirectory(packagesDir);

        for (const auto &ent : archEntries) {
            GR_INFO(GTXT("Building archive %ls"), ent.archiveName.toCString());
            gnaStatus status = packFile(inRM, entryList, packagesDir, ent);
            if (!status) {
                GR_FATAL(GTXT("error %08x: %ls"), status.errorCode, status.get_errorMessage().toCString());
            }
        }
    } else if (mode == GTXT("-unpack")) {
        if (argc != 4) {
            GR_FATAL(GTXT(
                         "invalid arguments.\n"
                         "usage: %ls -unpack <filename.gpk> <out_directory>\n"),
                argv[0]);
        }
        gtl::String inputFile = argv[2];
        gtl::String outputDir = argv[3];

        auto stream      = gnaNew<nxfFileInputStream>();
        gnaStatus status = stream->open(inputFile);
        if (!status) {
            GR_FATAL(GTXT("error %08x: %ls"), status.errorCode, status.get_errorMessage().toCString());
        }
        nxfResource::GPKArchive *archive = gtlNew nxfResource::GPKArchive(stream);
        archive->initializeIndex();

        status = unpackArchive(archive, outputDir);
        if (!status) {
            GR_FATAL(GTXT("error %08x: %ls"), status.errorCode, status.get_errorMessage().toCString());
        }
    } else if (mode == GTXT("-test")) {
        gtl::String inputFile = argv[2];

        auto archstream                  = gnaNew<nxfFileInputStream>();
        gnaStatus status                 = archstream->open(inputFile);
        nxfResource::GPKArchive *archive = gtlNew nxfResource::GPKArchive(archstream);
        archive->initializeIndex();

        auto stream     = archive->nxfResourceManager::get_resourceStream(GTXT("/scripts/table/CharacterInfo.txt"));
        auto textStream = gnaNew<nxfIO::BufferedTextInputStream>(stream);

        while (true) {
            gtl::AString str;
            status = textStream->readLine(str);
            if (status.errorCode == GNA_E_END_OF_DATA) {
                break;
            }
            if (!status) {
                GR_FATAL(GTXT("error %08x: %ls"), status.errorCode, status.get_errorMessage().toCString());
            }
            GR_INFO(GTXT("%hs"), str.toCString());
        }
    }

    return 0;
}
