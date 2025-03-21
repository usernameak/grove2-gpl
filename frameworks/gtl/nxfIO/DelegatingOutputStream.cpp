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

#include "DelegatingOutputStream.h"

gnaStatus nxfDelegatingOutputStream::write(const void *data, uint32_t size, uint32_t *bytesWritten) {
    return m_underlyingStream->write(data, size, bytesWritten);
}

bool nxfDelegatingOutputStream::seek(uint64_t offset) {
    return m_underlyingStream->seek(offset);
}

int64_t nxfDelegatingOutputStream::get_size() {
    return m_underlyingStream->get_size();
}

gnaStatus nxfDelegatingOutputStream::flush() {
    return m_underlyingStream->flush();
}

uint64_t nxfDelegatingOutputStream::tell() {
    return m_underlyingStream->tell();
}

gnaStatus nxfDelegatingOutputStream::finish() {
    return m_underlyingStream->finish();
}
