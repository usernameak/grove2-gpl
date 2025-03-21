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

#include "SystemResourceManager.h"

#include <nxfIO/FileOutputStream.h>
#include <nxfIO/BufferedInputStream.h>
#include <nxfIO/FileInputStream.h>

const gtl::String nxfSystemResourceManager::PATH_PREFIX = GTXT("/_system_res/");

GTL_RTTI_DEFINE(nxfSystemResourceManager, GTL_RTTI_INHERITS(nxfMutableResourceManager));

nxfSystemResourceManager::nxfSystemResourceManager() {
}

bool nxfSystemResourceManager::isFile(gtl::String name) {
    if (name.startsWith(PATH_PREFIX)) {
        return grFsPlatform::isFile(name.substr(PATH_PREFIX.size()));
    }
    return false;
}

bool nxfSystemResourceManager::listFiles(gtl::String directory, std::unordered_set<grFsPlatform::ListFilesEntry> &filenames) {
    if (directory.startsWith(PATH_PREFIX)) {
        return grFsPlatform::listFiles(directory.substr(PATH_PREFIX.size()), filenames);
    }
    return false;
}

bool nxfSystemResourceManager::createDirectory(gtl::String name) {
    if (name.startsWith(PATH_PREFIX)) {
        return grFsPlatform::createDirectory(name.substr(PATH_PREFIX.size()));
    }
    return false;
}

gnaStatus nxfSystemResourceManager::get_resourceStream(gtl::String name, gnaPointer<nxfInputStream> &outStream, uint32_t flags) {
    if (!name.startsWith(PATH_PREFIX)) return GNA_E_INVALID_ARGUMENT;

    auto stream = gnaNew<nxfFileInputStream>();
    GNA_CHECK_STATUS(stream->open(name.substr(PATH_PREFIX.size())));

    outStream = stream;

    if (!(flags & FLAG_UNBUFFERED)) {
        gnaPointer<nxfIO::BufferedInputStream> bstream = gnaNew<nxfIO::BufferedInputStream>(stream);
        outStream                                      = bstream;
    }

    return GNA_E_OK;
}

gnaStatus nxfSystemResourceManager::get_resourceOutputStream(gtl::String name, gnaPointer<nxfOutputStream> &stream) {
    if (!name.startsWith(PATH_PREFIX)) return { GNA_E_FILE_NOT_FOUND };

    gnaPointer<nxfFileOutputStream> fStream = gnaNew<nxfFileOutputStream>();

    if (!fStream->open(name.substr(PATH_PREFIX.size())))
        return { GNA_E_FILE_NOT_FOUND };

    stream = fStream;

    return GNA_E_OK;
}

bool nxfSystemResourceManager::findResourcePathFromNativePath(const gtl::String &nativePath, gtl::String &outResourcePath) {
    outResourcePath = PATH_PREFIX + nativePath;
    return true;
}
