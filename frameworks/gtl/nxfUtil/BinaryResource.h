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

#include <gtlObject/Cloneable.h>

class GTL_DLLIMPEXP nxfBinaryResource final : public gtlCloneable {
public:
    GTL_DECLARE_OBJECT_CLONE;
    GTL_RTTI_DECLARE();

    void *data;
    uint32_t size;

    nxfBinaryResource() : size(0), data(nullptr) {}

    explicit nxfBinaryResource(uint32_t size) : size(size), data(gtlNew unsigned char[size]) {
    }

    explicit nxfBinaryResource(uint32_t size, const void *data) : nxfBinaryResource(size) {
        memcpy(this->data, data, size);
    }

    ~nxfBinaryResource() override { gtlDeleteArray (unsigned char *)data; }
};
