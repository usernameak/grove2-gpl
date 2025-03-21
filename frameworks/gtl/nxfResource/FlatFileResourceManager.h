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

#include <nxfResource/MutableResourceManager.h>
#include <gtlString/String.h>

class GTL_DLLIMPEXP nxfFlatFileResourceManager : public nxfMutableResourceManager {
    gtl::String resourceDirectory;

public:
    GTL_RTTI_DECLARE();

    nxfFlatFileResourceManager(gtl::String resourceDirectory);

    void initializeIndex(bool reinitialize) override {}

    bool isFile(gtl::String name) override;

    bool listFiles(gtl::String directory, std::unordered_set<grFsPlatform::ListFilesEntry> &filenames) override;

    bool createDirectory(gtl::String name) override;

    gnaStatus get_resourceStream(gtl::String name, gnaPointer<nxfInputStream> &stream, uint32_t flags) override;

    gnaStatus get_resourceOutputStream(gtl::String name, gnaPointer<nxfOutputStream> &stream) override;
    bool findResourcePathFromNativePath(const gtl::String &nativePath, gtl::String &outResourcePath) override;

private:
    gtl::String appendResourceDirectory(gtl::String name);
};
