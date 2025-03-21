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

#include "FsPlatform.h"

#include <windows.h>

const gtl::WIDECHAR nxfFsPlatform::PATH_SEPARATOR = GTXT('\\');

static void normalizePath_step(gtl::String &pathPart, gtl::String &normalizedName) {
    if (!pathPart.empty()) {
        if (pathPart == GTXT("..")) {
            int lio = normalizedName.lastIndexOf(GTXT('\\'));
            if (lio == normalizedName.size()) {
                normalizedName.resize(0);
            } else {
                normalizedName.resize(lio);
            }
            pathPart = GTXT("");
        } else if (pathPart == GTXT(".")) {
            pathPart = GTXT("");
        } else {
            if (!normalizedName.empty()) {
                normalizedName += GTXT('\\');
            }
            normalizedName += pathPart;
            pathPart = GTXT("");
        }
    }
}

gtl::String nxfFsPlatform::normalizePath(const gtl::String &name) {
    gtl::String normalizedName;
    normalizedName.reserve(name.size());
    gtl::String pathPart;
    pathPart.reserve(name.size());

    int type = 0;
    if (name.size() >= 3 && name[1] == ':') {
        type = 1;
    } else if (!name.empty() && name[0] == GTXT('/') && name[0] == GTXT('\\')) {
        // TODO: drive-relative-paths
        type = 2;
    } else {
        DWORD bufSize = GetCurrentDirectoryW(NULL, 0);
        gtl::String curDir(bufSize);
        curDir.resize(GetCurrentDirectoryW(bufSize, curDir.forceCopy()));
        return combinePaths(curDir, name);
    }

    for (gtl::WIDECHAR wc : name) {
        if (wc == GTXT('/') || wc == GTXT('\\')) {
            normalizePath_step(pathPart, normalizedName);
        } else {
            pathPart += wc;
        }
    }
    normalizePath_step(pathPart, normalizedName);

    return normalizedName;
}

gtl::String nxfFsPlatform::parentPath(const gtl::String &name) {
    gtl::String normalizedName = normalizePath(name);
    for (uint32_t i = normalizedName.size() - 1; i != UINT32_MAX; i--) {
        if (normalizedName[i] == GTXT('/') || normalizedName[i] == GTXT('\\')) {
            normalizedName.resize(i);
            break;
        }
    }
    return normalizedName;
}

bool nxfFsPlatform::listFiles(gtl::String directory, std::unordered_set<ListFilesEntry> &filenames) {
    if (directory.empty()) {
        DWORD dwLogicalDrives = GetLogicalDrives();
        for (int i = 0; i < 26; i++) {
            if ((dwLogicalDrives >> i) & 1) {
                ListFilesEntry e;
                e.filename = gtl::String(2);
                e.filename += (GTXT('A') + i);
                e.filename += ':';
                e.type = FileEntryType::DIRECTORY;
                filenames.insert(e);
            }
        }
        return true;
    }

    gtl::String fullName = GTXT("\\\\?\\") + normalizePath(directory);
    if (directory[directory.size() - 1] == GTXT('\\')) {
        fullName += GTXT("*");
    } else {
        fullName += GTXT("\\*");
    }

    HANDLE hfind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAW ffd;

    hfind = FindFirstFileW(fullName.toCString(), &ffd);

    if (INVALID_HANDLE_VALUE == hfind) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
            return true;
        return false;
    }

    do {
        if (wcscmp(ffd.cFileName, GTXT(".")) == 0 || wcscmp(ffd.cFileName, GTXT("..")) == 0)
            continue;
        filenames.insert({ ffd.cFileName,
            (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? FileEntryType::DIRECTORY : FileEntryType::FILE });
    } while (FindNextFileW(hfind, &ffd) != 0);

    DWORD dwError = GetLastError();
    FindClose(hfind);
    return dwError == ERROR_NO_MORE_FILES;
}

bool nxfFsPlatform::isFile(gtl::String path) {
    gtl::String fullName = GTXT("\\\\?\\") + normalizePath(path);
    DWORD dwAttrs        = GetFileAttributesW(fullName.toCString());
    if (dwAttrs == INVALID_FILE_ATTRIBUTES || dwAttrs & FILE_ATTRIBUTE_DIRECTORY) {
        return false;
    }
    return true;
}

bool nxfFsPlatform::createDirectory(gtl::String path) {
    gtl::String fullName = GTXT("\\\\?\\") + normalizePath(path);
    return CreateDirectoryW(fullName.toCString(), NULL);
}

gtl::String nxfFsPlatform::combinePaths(const gtl::String &dirname, const gtl::String &name) {
    gtl::String ret = dirname;
    /*if (dirname.empty()) {
        ret += GTXT('.');
    }*/
    if (!name.empty()) {
        ret += GTXT('\\');
    }
    ret += name;
    return normalizePath(ret);
}

gtl::String nxfFsPlatform::getExecutablePath() {
#ifdef _WIN32
    gtl::String str(MAX_PATH);
    str.resize(GetModuleFileNameW(nullptr, str.forceCopy(), MAX_PATH));
    return str;
#else
#error "Unsupported platform"
#endif
}
