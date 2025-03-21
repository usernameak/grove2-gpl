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

#include "VectorTraits.h"
#include <nxfSerialization/SerializationTraits.h>

template <gtlMath2::VectorType T>
struct nxfSerialization::SerializationTraits<T> {
    template <SerializationInterface TSerializationInterface>
    static gnaStatus serialize(const char *name, TSerializationInterface &ser, T &value) {
        uint32_t tempNum = T::numComponents;
        GNA_CHECK_STATUS(ser.beginList(name, tempNum));
        if (tempNum != T::numComponents) {
            return GNA_E_INVALID_DATA_FORMAT;
        }
        for (int i = 0; i < T::numComponents; i++) {
            GNA_CHECK_STATUS(ser.serializeValue(nullptr, value[i]));
        }
        GNA_CHECK_STATUS(ser.endList());
        return GNA_E_OK;
    }
};
