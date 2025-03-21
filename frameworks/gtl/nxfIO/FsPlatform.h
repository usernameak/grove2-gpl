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
#include <vector>
#include <unordered_set>

namespace nxfFsPlatform {
    enum class FileEntryType {
        INVALID,
        DIRECTORY,
        FILE
    };

    struct ListFilesEntry {
        gtl::String filename;
        FileEntryType type;

        bool operator==(const ListFilesEntry &other) const {
            return filename == other.filename && type == other.type;
        }
    };

    extern const gtl::WIDECHAR PATH_SEPARATOR;

    GTL_DLLIMPEXP gtl::String combinePaths(const gtl::String &dirname, const gtl::String &name);
    GTL_DLLIMPEXP gtl::String normalizePath(const gtl::String &name);
    GTL_DLLIMPEXP gtl::String parentPath(const gtl::String &name);
    GTL_DLLIMPEXP bool listFiles(gtl::String directory, std::unordered_set<ListFilesEntry> &filenames);
    GTL_DLLIMPEXP bool isFile(gtl::String path);
    GTL_DLLIMPEXP bool createDirectory(gtl::String path);
    GTL_DLLIMPEXP gtl::String getExecutablePath();
}

namespace grFsPlatform = nxfFsPlatform;

namespace std {
    template <>
    struct hash<nxfFsPlatform::ListFilesEntry> {
        inline size_t operator()(const nxfFsPlatform::ListFilesEntry &entry) const {
            return std::hash<gtl::String>{}(entry.filename);
        }
    };
}
