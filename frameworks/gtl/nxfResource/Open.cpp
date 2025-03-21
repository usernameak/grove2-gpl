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

#include "nxfResource/Open.h"

#include <nxfResource/ResourceManager.h>

gnaPointer<nxfInputStream> nxfOpen(const nxfRID &rid) {
    return nxf_getRM()->get_resourceStream(rid.name);
}

gnaPointer<nxfBinaryResource> nxfOpenBinary(const nxfRID &rid) {
    gnaPointer<nxfInputStream> stream = nxf_getRM()->get_resourceStream(rid.name);
    if (!stream) {
        return nullptr;
    }
    return stream->readAll();
}
