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

#include <type_traits>
#include <nxfIO/OutputStream.h>
#include <nxfIO/InputStream.h>
#include <nxfResource/RID.h>
#include <gtlString/PooledString.h>
#include <gnaStatus.h>

#include <concepts>

inline gnaStatus operator>>(nxfInputStream &stream, std::integral auto &val) {
    return stream.read(&val, sizeof(val));
}

inline gnaStatus operator>>(nxfInputStream &stream, std::floating_point auto &val) {
    return stream.read(&val, sizeof(val));
}

template <typename T>
inline gnaStatus operator>>(nxfInputStream &stream, gtl::BaseString<T> &val) {
    uint16_t len;
    GNA_CHECK_STATUS(stream >> len);
    val.resize(len);
    if (len) {
        GNA_CHECK_STATUS(stream.read(val.forceCopy(), len * sizeof(T)));
    }
    return GNA_E_OK;
}

template <typename T>
inline gnaStatus operator>>(nxfInputStream &stream, gtl::BasePooledString<T> &val) {
    uint16_t len;
    GNA_CHECK_STATUS(stream >> len);
    auto *strdata = gtlNew T[len + 1];
    strdata[len]  = 0;
    if (len) {
        gnaStatus status = stream.read(strdata, len * sizeof(*strdata));
        if (!status) {
            gtlDeleteArray strdata;
            return status;
        }
    }
    val = strdata;
    gtlDeleteArray strdata;
    return GNA_E_OK;
}

template <typename T>
    requires(std::is_enum_v<T>)
inline gnaStatus operator>>(nxfInputStream &stream, T &val) {
    std::underlying_type_t<T> tmp = 0;
    gnaStatus status              = stream >> tmp;
    if (status) {
        val = static_cast<T>(tmp);
    }
    return status;
}

inline gnaStatus operator<<(nxfOutputStream &stream, std::integral auto val) {
    return stream.write(&val, sizeof(val));
}

inline gnaStatus operator<<(nxfOutputStream &stream, std::floating_point auto val) {
    return stream.write(&val, sizeof(val));
}

template <typename T>
inline gnaStatus operator<<(nxfOutputStream &stream, gtl::BaseString<T> val) {
    uint16_t len = (uint16_t)val.size();
    GNA_CHECK_STATUS(stream << len);
    GNA_CHECK_STATUS(stream.write(val.toCString(), len * sizeof(T)));
    return GNA_E_OK;
}

template <typename T>
inline gnaStatus operator<<(nxfOutputStream &stream, gtl::BasePooledString<T> val) {
    uint16_t len = (uint16_t)val.size();
    GNA_CHECK_STATUS(stream << len);
    GNA_CHECK_STATUS(stream.write(val.toCString(), len * sizeof(T)));
    return GNA_E_OK;
}

template <typename T>
    requires(std::is_enum_v<T>)
inline gnaStatus operator<<(nxfOutputStream &stream, T val) {
    return stream << static_cast<std::underlying_type_t<T>>(val);
}

// legacy functions:

inline gnaStatus nxfDeserializeBool(bool &val, nxfInputStream &stream) {
    uint8_t byVal;
    gnaStatus status = stream.read(&byVal, sizeof(byVal));
    if (!status) return status;
    val = byVal != 0;
    return val;
}

template <typename T>
[[deprecated]] gnaStatus nxfSerializeNumber(T val, nxfOutputStream &stream) {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "nxfSerializeNumber non-number");

    return stream << val;
}

[[deprecated]] inline gnaStatus nxfSerializeBool(bool val, nxfOutputStream &stream) {
    return stream << val;
}

template <typename T>
[[deprecated]] gnaStatus nxfSerializeEnum(T val, nxfOutputStream &stream) {
    static_assert(std::is_enum_v<T>);

    return stream << val;
}

template <typename T>
[[deprecated]] gnaStatus nxfDeserializeNumber(T &val, nxfInputStream &stream) {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "nxfDeserializeNumber non-number");

    return stream >> val;
}

template <typename T>
[[deprecated]] gnaStatus nxfDeserializeEnum(T &val, nxfInputStream &stream) {
    static_assert(std::is_enum_v<T>);

    return stream >> val;
}

inline gnaStatus nxfSerializeString(gtl::String val, nxfOutputStream &stream) {
    uint16_t len = (uint16_t)val.size();
    GNA_CHECK_STATUS(nxfSerializeNumber(len, stream));
    GNA_CHECK_STATUS(stream.write(val.toCString(), len * sizeof(gtl::String::CharType)));
    return GNA_E_OK;
}

inline gnaStatus nxfSerializeAStringDirect(gtl::AString val, nxfOutputStream &stream) {
    uint16_t len = (uint16_t)val.size();
    GNA_CHECK_STATUS(stream.write(val.toCString(), len * sizeof(gtl::AString::CharType)));
    return GNA_E_OK;
}

inline gnaStatus nxfDeserializeString(gtl::String &val, nxfInputStream &stream) {
    uint16_t len;
    GNA_CHECK_STATUS(nxfDeserializeNumber(len, stream));
    val.resize(len);
    if (len) {
        GNA_CHECK_STATUS(stream.read(val.forceCopy(), len * sizeof(gtl::String::CharType)));
    }
    return GNA_E_OK;
}

template <typename T>
inline gnaStatus nxfSerializeString(gtl::BasePooledString<T> val, nxfOutputStream &stream) {
    return stream << val;
}

template <typename T>
inline gnaStatus nxfDeserializeString(gtl::BasePooledString<T> &val, nxfInputStream &stream) {
    return stream >> val;
}

inline gnaStatus operator<<(nxfOutputStream &stream, const nxfRID &val) {
    GNA_CHECK_STATUS(nxfSerializeNumber<uint8_t>(0, stream));
    GNA_CHECK_STATUS(nxfSerializeString(val.name, stream));
    return GNA_E_OK;
}

inline gnaStatus operator>>(nxfInputStream &stream, nxfRID &val) {
    uint8_t dummy;
    GNA_CHECK_STATUS(nxfDeserializeNumber<uint8_t>(dummy, stream));
    GNA_CHECK_STATUS(nxfDeserializeString(val.name, stream));
    return GNA_E_OK;
}
