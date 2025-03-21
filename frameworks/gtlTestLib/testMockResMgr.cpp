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

#include "testMockResMgr.h"

GTL_RTTI_DEFINE(testMockResourceManager, GTL_RTTI_INHERITS(nxfResourceManager));

gnaStatus testMockResourceManager::get_resourceStream(gtl::String name, gnaPointer<nxfInputStream> &stream, uint32_t flags) {
    return { GNA_E_FILE_NOT_FOUND, GTXT("This is a mock resource manager") };
}

void testMockResourceManager::initializeIndex(bool reinitialize) {
}

bool testMockResourceManager::isFile(gtl::String name) {
    return false;
}

bool testMockResourceManager::listFiles(gtl::String directory, std::unordered_set<grFsPlatform::ListFilesEntry> &filenames) {
    return false;
}
