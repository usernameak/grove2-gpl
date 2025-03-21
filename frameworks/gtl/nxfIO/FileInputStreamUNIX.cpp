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

#include <fcntl.h>
#include <nxfIO/FsPlatform.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

nxfFileInputStream::nxfFileInputStream() : nxfRAInputStream(), fh(-1) {
}

int32_t nxfFileInputStream::open(gtl::String filename) {
    auto normalizedFilename = grFsPlatform::normalizePath(filename);
    gtl::AString utfFilename(normalizedFilename.toCString(), gtl::AString::S_CHARSET_UTF8);
    fh = ::open(utfFilename.toCString(), O_RDONLY);
    if (fh == -1) {
        if (errno == ENOENT)
            return -1;
        // TODO: log error message if file exists but failed

        return -2;
    }

    return 0;
}

gnaStatus nxfFileInputStream::read(void *data, uint32_t size, uint32_t *bytesRead) {
    if (fh == -1) {
        if (bytesRead)
            *bytesRead = 0;
        return GNA_E_INVALID_STATE; // not opened
    }

    ssize_t bytesReadVal = ::read(fh, data, (size_t) size);
    if (bytesReadVal < 0) {
        if (bytesRead) {
            *bytesRead = 0;
        }
        return GNA_E_FAILED;
    }
    if (bytesRead) {
        *bytesRead = (uint32_t) bytesReadVal;
    }
    return GNA_E_OK;
}

gnaStatus nxfFileInputStream::readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead) {
    if (fh == -1) {
        if (bytesRead)
            *bytesRead = 0;
        return GNA_E_INVALID_STATE; // not opened
    }

    ssize_t bytesReadVal = pread(fh, data, (size_t) size, (off_t) offset);

    if (bytesReadVal < 0) {
        if (bytesRead) {
            *bytesRead = 0;
        }
        return GNA_E_FAILED;
    }
    if (bytesRead) {
        *bytesRead = (uint32_t) bytesReadVal;
    }
    return GNA_E_OK;
}

bool nxfFileInputStream::seek(uint64_t offset) {
    if (fh == -1)
        return false; // not opened

    return ::lseek(fh, (off_t) offset, SEEK_SET) != (off_t) -1;
}

int64_t nxfFileInputStream::get_size() {
    if (fh == -1)
        return -1; // not opened

    struct ::stat64 st {};
    if (::fstat64(fh, &st) == -1) {
        return -1;
    }

    return (int64_t) st.st_size;
}

uint64_t nxfFileInputStream::tell() {
    if (fh == -1)
        return 0; // not opened

    return (uint64_t) ::lseek(fh, 0, SEEK_CUR); // TODO: handle errors
}

nxfFileInputStream::~nxfFileInputStream() {
    if (fh != -1) {
        ::close(fh);
    }
}
