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

#include "DelegatingInputStream.h"

gnaStatus nxfDelegatingInputStream::read(void *data, uint32_t size, uint32_t *bytesRead) {
    return m_underlyingStream->read(data, size, bytesRead);
}

gnaStatus nxfDelegatingInputStream::readRA(void *data, uint64_t offset, uint32_t size, uint32_t *bytesRead) {
    return m_underlyingStream->readRA(data, offset, size, bytesRead);
}

gnaStatus nxfDelegatingInputStream::seek(uint64_t offset) {
    return m_underlyingStream->seek(offset);
}

int64_t nxfDelegatingInputStream::get_size() {
    return m_underlyingStream->get_size();
}

uint64_t nxfDelegatingInputStream::tell() {
    return m_underlyingStream->tell();
}

uint32_t nxfDelegatingInputStream::get_capabilities() const {
    return m_underlyingStream->get_capabilities();
}
