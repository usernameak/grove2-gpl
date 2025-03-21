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

#include "InputStream.h"

#include <nxfUtil/BinaryResource.h>

GTL_RTTI_DEFINE(nxfInputStream, GTL_RTTI_INHERITS(gtlRcObject));

gnaPointer<nxfBinaryResource> nxfInputStream::readAll() {
    gnaPointer<nxfBinaryResource> br;
    gnaStatus status = readAll(br);
    if (!status) return nullptr;
    return br;
}

gnaStatus nxfInputStream::readAll(gnaPointer<nxfBinaryResource> &resource) {
    int64_t size = get_size();
    if (size < 0) {
        return { GNA_E_FAILED, GTXT("Failed to get file size") };
    }

    resource = gnaNew<nxfBinaryResource>(size);
    GNA_CHECK_STATUS(read(resource->data, size));

    return GNA_E_OK;
}

gnaStatus nxfInputStream::readAllAsString(gtl::AString &str) {
    int64_t size = get_size();
    if (size < 0) {
        return { GNA_E_FAILED };
    }

    str.resize(size);
    return read(str.forceCopy(), size);
}
