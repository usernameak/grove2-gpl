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

#include <gtlString/String.h>
#include <nxfIO/InputStream.h>
#include <nxfIO/FsPlatform.h>
#include <nxfResource/RID.h>
#include <unordered_set>

namespace nxfResource {
    class GridResourceIndex;
}

class nxfResourceManager;

GTL_DLLIMPEXP nxfResourceManager *nxf_getRM();
GTL_DLLIMPEXP void nxf_setRM(nxfResourceManager *rm);

class GTL_DLLIMPEXP nxfResourceManager {
public:
    GTL_RTTI_DECLARE();

    enum : uint32_t {
        FLAG_UNBUFFERED = GTL_BIT(0)
    };

    virtual ~nxfResourceManager() = default;

    virtual gnaStatus get_resourceStream(gtl::String name, gnaPointer<nxfInputStream> &stream, uint32_t flags = 0) = 0;

    gnaPointer<nxfInputStream> get_resourceStream(gtl::String name, uint32_t flags = 0) {
        gnaPointer<nxfInputStream> stream;
        if (!get_resourceStream(name, stream, flags)) {
            return nullptr;
        }
        return stream;
    }

    virtual void initializeIndex(bool reinitialize = false) = 0;

    virtual gnaPointer<nxfResource::GridResourceIndex> getGridIndex(
        const gtl::String &root,
        const gtl::String &extension,
        bool allowDirect = true);

    void reload() {
        initializeIndex(true);
    }

    virtual bool isFile(gtl::String name)                                                                      = 0;
    virtual bool listFiles(gtl::String directory, std::unordered_set<grFsPlatform::ListFilesEntry> &filenames) = 0;

    bool listFiles(const gtl::String &directory, std::vector<grFsPlatform::ListFilesEntry> &filenames) {
        std::unordered_set<grFsPlatform::ListFilesEntry> set;
        bool ret = listFiles(directory, set);
        filenames.insert(filenames.cend(), set.begin(), set.end());
        return ret;
    }

    virtual bool findResourcePathFromNativePath(const gtl::String &nativePath, gtl::String &outResourcePath) {
        return false;
    }

    static gtl::String normalizePath(gtl::String path);
    static gtl::String parentPath(gtl::String path);

    static nxfResourceManager *getGlobalResourceManager() {
        return nxf_getRM();
    }

    static void setGlobalResourceManager(nxfResourceManager *rm) {
        nxf_setRM(rm);
    }
};
