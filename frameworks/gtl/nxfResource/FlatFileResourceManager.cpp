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

#include "FlatFileResourceManager.h"

#include <nxfIO/FileInputStream.h>
#include <nxfIO/FileOutputStream.h>
#include <nxfIO/BufferedInputStream.h>

GTL_RTTI_DEFINE(nxfFlatFileResourceManager, GTL_RTTI_INHERITS(nxfMutableResourceManager));

nxfFlatFileResourceManager::nxfFlatFileResourceManager(gtl::String resourceDirectory) : resourceDirectory(resourceDirectory) {
}

bool nxfFlatFileResourceManager::isFile(gtl::String name) {
    return grFsPlatform::isFile(appendResourceDirectory(name));
}

gnaStatus nxfFlatFileResourceManager::get_resourceStream(gtl::String name, gnaPointer<nxfInputStream> &outStream, uint32_t flags) {
    gtl::String fullName = appendResourceDirectory(name);

    gnaPointer<nxfFileInputStream> stream = gnaNew<nxfFileInputStream>();
    GNA_CHECK_STATUS(stream->open(fullName));

    outStream = stream;

    if (!(flags & FLAG_UNBUFFERED)) {
        gnaPointer<nxfIO::BufferedInputStream> bstream = gnaNew<nxfIO::BufferedInputStream>(stream);
        outStream                                      = bstream;
    }

    return GNA_E_OK;
}

gnaStatus nxfFlatFileResourceManager::get_resourceOutputStream(gtl::String name, gnaPointer<nxfOutputStream> &outStream) {
    gtl::String fullName = appendResourceDirectory(name);

    gnaPointer<nxfFileOutputStream> stream = gnaNew<nxfFileOutputStream>();
    GNA_CHECK_STATUS(stream->open(fullName));

    outStream = stream;

    return GNA_E_OK;
}

gtl::String nxfFlatFileResourceManager::appendResourceDirectory(gtl::String name) {
    return grFsPlatform::combinePaths(resourceDirectory, name);
}

bool nxfFlatFileResourceManager::listFiles(gtl::String directory, std::unordered_set<grFsPlatform::ListFilesEntry> &filenames) {
    gtl::String appendedPath = appendResourceDirectory(directory);
    return grFsPlatform::listFiles(appendedPath, filenames);
}

bool nxfFlatFileResourceManager::createDirectory(gtl::String name) {
    return grFsPlatform::createDirectory(appendResourceDirectory(name));
}

bool nxfFlatFileResourceManager::findResourcePathFromNativePath(const gtl::String &nativePath, gtl::String &outResourcePath) {
    const gtl::String normalizedNativePath = grFsPlatform::normalizePath(nativePath);
    const gtl::String normalizedResDir     = grFsPlatform::normalizePath(resourceDirectory) + grFsPlatform::PATH_SEPARATOR;

    if (normalizedNativePath.startsWith(normalizedResDir)) {
        outResourcePath = gtl::String(grFsPlatform::PATH_SEPARATOR);
        outResourcePath += normalizedNativePath.substr(normalizedResDir.size());
        return true;
    }

    return nxfResourceManager::findResourcePathFromNativePath(nativePath, outResourcePath);
}
