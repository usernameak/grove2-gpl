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

#include "nxfIO/FileInputStream.h"

#include <windows.h>
#include <nxfIO/FsPlatform.h>

GTL_RTTI_DEFINE(nxfFileInputStream, GTL_RTTI_INHERITS(nxfInputStream));

nxfFileInputStream::nxfFileInputStream() : nxfRAInputStream(), fh(INVALID_HANDLE_VALUE) {
}

gnaStatus nxfFileInputStream::open(gtl::String filename) {
    auto full_filename = GTXT("\\\\?\\") + grFsPlatform::normalizePath(filename);
    fh                 = CreateFileW(
                        full_filename.toCString(),
                        GENERIC_READ,
                        FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
                        NULL);
    if (fh == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
            return GNA_E_FILE_NOT_FOUND;
        // TODO: log error message if file exists but failed

        return GNA_E_FAILED;
    }

    return GNA_E_OK;
}

gnaStatus nxfFileInputStream::read(void *data, uint32_t size, uint32_t *bytesRead) {
    if (fh == INVALID_HANDLE_VALUE) {
        if (bytesRead)
            *bytesRead = 0;
        return GNA_E_INVALID_STATE; // not opened
    }

    DWORD dwBytesRead = 0;
    BOOL succ         = ReadFile(fh, data, size, &dwBytesRead, NULL);
    if (bytesRead)
        *bytesRead = dwBytesRead;
    if (succ) {
        return GNA_E_OK;
    } else {
        return GNA_E_FAILED;
    }
}

gnaStatus nxfFileInputStream::readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead) {
    if (fh == INVALID_HANDLE_VALUE) {
        if (bytesRead)
            *bytesRead = 0;
        return GNA_E_INVALID_STATE; // not opened
    }

    OVERLAPPED ovl;
    ZeroMemory(&ovl, sizeof(ovl));
    ovl.Offset     = (DWORD)offset;
    ovl.OffsetHigh = (DWORD)(offset >> 32ULL);
    BOOL succ      = ReadFile(fh, data, size, NULL, &ovl);

    if (!succ) {
        if (bytesRead) {
            *bytesRead = 0;
        }
        DWORD lastError = GetLastError();
        if (lastError == ERROR_HANDLE_EOF) {
            return GNA_E_OK;
        }

        return GNA_E_FAILED;
    }

    DWORD dwBytesRead;
    if (!GetOverlappedResult(fh, &ovl, &dwBytesRead, FALSE)) {
        return GNA_E_FAILED;
    }

    if (bytesRead) {
        *bytesRead = dwBytesRead;
    }

    return GNA_E_OK;
}

gnaStatus nxfFileInputStream::seek(uint64_t offset) {
    if (fh == INVALID_HANDLE_VALUE)
        return false; // not opened

    LARGE_INTEGER liDistanceToMove;
    liDistanceToMove.QuadPart = offset;

    BOOL result = SetFilePointerEx(fh, liDistanceToMove, NULL, FILE_BEGIN);
    return result ? GNA_E_OK : GNA_E_FAILED; // TODO: log error
}

int64_t nxfFileInputStream::get_size() {
    if (fh == INVALID_HANDLE_VALUE)
        return -1; // not opened

    LARGE_INTEGER liSize;
    if (!GetFileSizeEx(fh, &liSize)) {
        return -1; // TODO: log error
    }
    return liSize.QuadPart;
}

uint64_t nxfFileInputStream::tell() {
    if (fh == INVALID_HANDLE_VALUE)
        return 0; // not opened

    LARGE_INTEGER liPos;
    LARGE_INTEGER liDistanceToMove;
    liDistanceToMove.QuadPart = 0;

    SetFilePointerEx(fh, liDistanceToMove, &liPos, FILE_CURRENT); // TODO: handle errors
    return liPos.QuadPart;
}

nxfFileInputStream::~nxfFileInputStream() {
    if (fh != INVALID_HANDLE_VALUE) {
        CloseHandle(fh);
    }
}
