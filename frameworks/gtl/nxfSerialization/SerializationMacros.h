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

#include "NXFFileReader.h"
#include "NXJFileWriter.h"
#include "NXFFileWriter.h"
#include "SerializationTraits.h"

#define NXF_SERIALIZABLE_DECLARE()                                                                      \
    virtual ::gnaStatus serializationWrapper(::nxfSerialization::NXFFileWriter::ObjectCollector &ser) { \
        return serializationImpl(ser);                                                                  \
    }                                                                                                   \
    virtual ::gnaStatus serializationWrapper(::nxfSerialization::NXFFileWriter::DataWriter &ser) {      \
        return serializationImpl(ser);                                                                  \
    }                                                                                                   \
    virtual ::gnaStatus serializationWrapper(::nxfSerialization::NXFFileReader::DataReader &ser) {      \
        return serializationImpl(ser);                                                                  \
    }                                                                                                   \
    virtual ::gnaStatus serializationWrapper(::nxfSerialization::NXJFileWriter::ObjectCollector &ser) { \
        return serializationImpl(ser);                                                                  \
    }                                                                                                   \
    virtual ::gnaStatus serializationWrapper(::nxfSerialization::NXJFileWriter::DataWriter &ser) {      \
        return serializationImpl(ser);                                                                  \
    }

#define NXF_DEFINE_SERIALIZABLE_INSTANTIATE_(type, impexp, interfaceType) \
    template ::gnaStatus impexp type::serializationImpl<interfaceType>(interfaceType & ser);

#define NXF_SERIALIZABLE_DEFINE(type, impexp)                                                              \
    NXF_DEFINE_SERIALIZABLE_INSTANTIATE_(type, impexp, ::nxfSerialization::NXFFileWriter::ObjectCollector) \
    NXF_DEFINE_SERIALIZABLE_INSTANTIATE_(type, impexp, ::nxfSerialization::NXFFileWriter::DataWriter)      \
    NXF_DEFINE_SERIALIZABLE_INSTANTIATE_(type, impexp, ::nxfSerialization::NXFFileReader::DataReader)      \
    NXF_DEFINE_SERIALIZABLE_INSTANTIATE_(type, impexp, ::nxfSerialization::NXJFileWriter::ObjectCollector) \
    NXF_DEFINE_SERIALIZABLE_INSTANTIATE_(type, impexp, ::nxfSerialization::NXJFileWriter::DataWriter)
