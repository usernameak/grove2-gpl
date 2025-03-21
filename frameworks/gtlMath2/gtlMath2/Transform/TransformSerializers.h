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

#include <gtlMath2/Vector/VectorSerializers.h>
#include <gtlMath2/Quaternion/QuaternionSerializers.h>
#include "Transform.h"

template <>
struct nxfSerialization::SerializationTraits<gtlMath2::Transform> {
    template <SerializationInterface TSerializationInterface>
    static gnaStatus serialize(const char *name, TSerializationInterface &ser, gtlMath2::Transform &value) {
        GNA_CHECK_STATUS(ser.beginCompound(name));
        GNA_CHECK_STATUS(ser.serialize("translation", value.translation));
        GNA_CHECK_STATUS(ser.serialize("rotation", value.rotation));
        GNA_CHECK_STATUS(ser.serialize("scale", value.scale));
        GNA_CHECK_STATUS(ser.endCompound());
        return GNA_E_OK;
    }
};

template <>
struct nxfSerialization::SerializationTraits<gtlMath2::LocalTransform> {
    template <SerializationInterface TSerializationInterface>
    static gnaStatus serialize(const char *name, TSerializationInterface &ser, gtlMath2::LocalTransform &value) {
        GNA_CHECK_STATUS(ser.beginCompound(name));
        GNA_CHECK_STATUS(ser.serialize("translation", value.translation));
        GNA_CHECK_STATUS(ser.serialize("rotation", value.rotation));
        GNA_CHECK_STATUS(ser.serialize("scale", value.scale));
        GNA_CHECK_STATUS(ser.endCompound());
        return GNA_E_OK;
    }
};
