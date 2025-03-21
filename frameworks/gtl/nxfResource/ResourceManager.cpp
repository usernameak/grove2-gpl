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

#include "ResourceManager.h"

#include "Index/DirectGridResourceIndex.h"

static nxfResourceManager *nxf_gResourceManager;

GTL_RTTI_DEFINE(nxfResourceManager);

gnaPointer<nxfResource::GridResourceIndex> nxfResourceManager::getGridIndex(const gtl::String &root, const gtl::String &extension, bool allowDirect) {
    if (!allowDirect) {
        return nullptr;
    }
    return gnaNew<nxfResource::DirectGridResourceIndex>(this, root, extension);
}

gtl::String nxfResourceManager::normalizePath(const gtl::String path) {
    if (path.empty()) {
        return GTXT("/");
    }
    gtl::String outPath(path.size());
    if (path[0] != GTXT('/') && path[0] != GTXT('\\')) {
        outPath += GTXT('/');
    }
    for (wchar_t c : path) {
        if (c == GTXT('\\') || c == GTXT('/')) {
            if (!outPath.empty() && outPath[outPath.size() - 1] == GTXT('/')) {
                continue;
            }
            outPath += GTXT('/');
        } else {
            outPath += gtl::ToLower((gtl::WIDECHAR)c);
        }
    }
    if (outPath[outPath.size() - 1] == GTXT('/')) {
        outPath.resize(outPath.size() - 1);
    }
    return outPath;
}

gtl::String nxfResourceManager::parentPath(gtl::String path) {
    path = normalizePath(path);
    gtl::String resultPath = path.substr(0, path.lastIndexOf(GTXT('/')));
    if (resultPath.empty()) {
        static const gtl::String rootPath(GTXT("/"));
        resultPath = rootPath;
    }
    return resultPath;
}

nxfResourceManager *nxf_getRM() {
    return nxf_gResourceManager;
}

void nxf_setRM(nxfResourceManager *rm) {
    gtlDelete nxf_gResourceManager;
    nxf_gResourceManager = rm;
}
