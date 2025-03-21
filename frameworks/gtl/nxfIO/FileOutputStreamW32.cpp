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

#include "nxfIO/FileOutputStream.h"

#include <windows.h>
#include <gtlString/String.h>
#include <nxfIO/FsPlatform.h>

nxfFileOutputStream::nxfFileOutputStream() : nxfOutputStream(), fh(INVALID_HANDLE_VALUE) {
}

gnaStatus nxfFileOutputStream::open(gtl::String filename) {
    auto full_filename = L"\\\\?\\" + grFsPlatform::normalizePath(filename);
    fh                 = CreateFileW(
                        full_filename.toCString(),
                        GENERIC_WRITE,
                        FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
    if (fh == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
            return GNA_E_FILE_NOT_FOUND;
        // TODO: log error message if file exists but failed

        return GNA_E_FAILED;
    }

    return GNA_E_OK;
}

gnaStatus nxfFileOutputStream::write(const void *data, uint32_t size, uint32_t *bytesWritten) {
    if (fh == INVALID_HANDLE_VALUE)
        return GNA_E_INVALID_STATE; // not opened

    DWORD dwBytesWritten;
    BOOL succ = WriteFile(fh, data, size, &dwBytesWritten, NULL);
    if (bytesWritten)
        *bytesWritten = dwBytesWritten;
    if (succ) {
        return GNA_E_OK;
    } else {
        return GNA_E_FAILED;
    }
}

bool nxfFileOutputStream::seek(uint64_t offset) {
    if (fh == INVALID_HANDLE_VALUE)
        return false; // not opened

    LARGE_INTEGER liDistanceToMove;
    liDistanceToMove.QuadPart = offset;

    return SetFilePointerEx(fh, liDistanceToMove, NULL, FILE_BEGIN); // TODO: log error
}

int64_t nxfFileOutputStream::get_size() {
    if (fh == INVALID_HANDLE_VALUE)
        return -1; // not opened

    LARGE_INTEGER liSize;
    if (!GetFileSizeEx(fh, &liSize)) {
        return -1; // TODO: log error
    }
    return liSize.QuadPart;
}

uint64_t nxfFileOutputStream::tell() {
    if (fh == INVALID_HANDLE_VALUE)
        return 0; // not opened

    LARGE_INTEGER liPos;
    LARGE_INTEGER liDistanceToMove;
    liDistanceToMove.QuadPart = 0;

    SetFilePointerEx(fh, liDistanceToMove, &liPos, FILE_CURRENT); // TODO: handle errors
    return liPos.QuadPart;
}

gnaStatus nxfFileOutputStream::flush() {
    if (fh == INVALID_HANDLE_VALUE)
        return GNA_E_INVALID_STATE; // not opened

    BOOL status = FlushFileBuffers(fh);
    if (!status) {
        DWORD err = GetLastError();
        if (err == ERROR_INVALID_HANDLE) {
            // this is stdin/stdout/stderr; this file
            // should not be flushed because it's not even buffered.
            return GNA_E_OK;
        }
        return GNA_E_FAILED;
    }
    return GNA_E_OK;
}

nxfFileOutputStream::~nxfFileOutputStream() {
    if (fh != INVALID_HANDLE_VALUE) {
        CloseHandle(fh);
    }
}
