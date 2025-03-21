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

#include <nxfSerialization/PrimitiveSerializers.h>
#include <nxfIO/InputStream.h>
#include <nxfIO/OutputStream.h>
#include "Quaternion.h"

namespace gtlMath2 {
    template <typename T>
    gnaStatus operator<<(nxfOutputStream &stream, const Quaternion<T> &q) {
        GNA_CHECK_STATUS(stream << q.x);
        GNA_CHECK_STATUS(stream << q.y);
        GNA_CHECK_STATUS(stream << q.z);
        GNA_CHECK_STATUS(stream << q.w);
        return GNA_E_OK;
    }

    template <typename T>
    gnaStatus operator>>(nxfInputStream &stream, Quaternion<T> &q) {
        GNA_CHECK_STATUS(stream >> q.x);
        GNA_CHECK_STATUS(stream >> q.y);
        GNA_CHECK_STATUS(stream >> q.z);
        GNA_CHECK_STATUS(stream >> q.w);
        return GNA_E_OK;
    }
}
