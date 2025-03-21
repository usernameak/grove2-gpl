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

#include "SerializationInterface.h"
#include <nxfUtil/BinaryResource.h>

namespace nxfSerialization {
    template <typename T>
    struct SerializationTraits {
        // a whole lot of nothing! this will fail to compile on unknown types.
    };

    template <typename T>
    concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_enum_v<T>;

    template <Numeric T>
    struct SerializationTraits<T> {
        template <SerializationInterface TSerializationInterface>
        static gnaStatus serialize(const char *name, TSerializationInterface &ser, T &value) {
            return ser.serializeValue(name, value);
        }
    };

    template <typename T>
    struct SerializationTraits<gnaPointer<T>> {
        template <SerializationInterface TSerializationInterface>
        static gnaStatus serialize(const char *name, TSerializationInterface &ser, gnaPointer<T> &value) {
            gnaWeakPointer<gtlObject> tmp = value;
            GNA_CHECK_STATUS(ser.serializeObjectReference(name, tmp));

            // check in case it was const and someone const_cast'ed it
            if (value != tmp) {
                value = tmp.rttiCast2<T>();
                if (tmp && !value) {
                    return GNA_E_INCOMPATIBLE_CLS;
                }
            }
            return GNA_E_OK;
        }
    };

    template <typename T>
    struct SerializationTraits<gnaWeakPointer<T>> {
        template <SerializationInterface TSerializationInterface>
        static gnaStatus serialize(const char *name, TSerializationInterface &ser, gnaWeakPointer<T> &value) {
            gnaWeakPointer<gtlObject> tmp = value;
            GNA_CHECK_STATUS(ser.serializeObjectReference(name, tmp));

            // check in case it was const and someone const_cast'ed it
            if (value != tmp) {
                value = tmp.rttiCast2<T>();
                if (tmp && !value) {
                    return GNA_E_INCOMPATIBLE_CLS;
                }
            }
            return GNA_E_OK;
        }
    };

    template <>
    struct SerializationTraits<gnaPointer<nxfBinaryResource>> {
        template <SerializationInterface TSerializationInterface>
        static gnaStatus serialize(const char *name, TSerializationInterface &ser, gnaPointer<nxfBinaryResource> &value) {
            if (ser.get_direction() == SerializationDirection::WRITE) {
                if (value) {
                    GNA_CHECK_STATUS(ser.serializeRawData(name, value->data, value->size));
                } else {
                    GNA_CHECK_STATUS(ser.serializeNullRawData(name));
                }
            } else if (ser.get_direction() == SerializationDirection::READ) {
                size_t size;
                GNA_CHECK_STATUS(ser.deserializeRawDataSize(size));
                if (size == SIZE_MAX) {
                    value = nullptr;
                } else {
                    value = gnaNew<nxfBinaryResource>(size);
                    GNA_CHECK_STATUS(ser.deserializeRawData(value->data, size));
                }
            }

            return GNA_E_OK;
        }
    };

    template <typename T>
    struct SerializationTraits<gtl::BaseString<T>> {
        template <SerializationInterface TSerializationInterface>
        static gnaStatus serialize(const char *name, TSerializationInterface &ser, gtl::BaseString<T> &value) {
            return ser.serializeValue(name, value);
        }
    };

    template <typename T>
    struct SerializationTraits<gtl::BasePooledString<T>> {
        template <SerializationInterface TSerializationInterface>
        static gnaStatus serialize(const char *name, TSerializationInterface &ser, gtl::BasePooledString<T> &value) {
            return ser.serializeValue(name, value);
        }
    };

    template <>
    struct SerializationTraits<nxfRID> {
        template <SerializationInterface TSerializationInterface>
        static gnaStatus serialize(const char *name, TSerializationInterface &ser, nxfRID &value) {
            return ser.serializeValue(name, value);
        }
    };

    template <
        typename Key,
        typename Hash,
        typename Equal,
        typename Allocator>
    struct SerializationTraits<std::unordered_set<Key, Hash, Equal, Allocator>> {
        template <SerializationInterface TSerializationInterface>
        static gnaStatus serialize(const char *name, TSerializationInterface &ser, std::unordered_set<Key, Hash, Equal, Allocator> &value) {
            size_t sizeRaw = value.size();
            if (sizeRaw > UINT32_MAX) {
                return GNA_E_BUFFER_TOO_BIG;
            }
            uint32_t size = sizeRaw;
            GNA_CHECK_STATUS(ser.beginList(name, size));
            if (ser.get_direction() == SerializationDirection::WRITE ||
                ser.get_direction() == SerializationDirection::REGISTER) {
                for (auto &key : value) {
                    GNA_CHECK_STATUS(ser.serialize(nullptr, const_cast<Key &>(key)));
                }
            } else {
                value.clear();
                for (uint32_t i = 0; i < size; i++) {
                    Key key;
                    GNA_CHECK_STATUS(ser.serialize(nullptr, key));

                    if (!value.insert(std::move(key)).second) {
                        return GNA_E_INVALID_DATA_FORMAT;
                    }
                }
            }
            GNA_CHECK_STATUS(ser.endList());
            return GNA_E_OK;
        }
    };

    template <
        typename Key,
        typename T,
        typename Hash,
        typename Equal,
        typename Allocator>
    struct SerializationTraits<std::unordered_map<Key, T, Hash, Equal, Allocator>> {
        template <SerializationInterface TSerializationInterface>
        static gnaStatus serialize(const char *name, TSerializationInterface &ser, std::unordered_map<Key, T, Hash, Equal, Allocator> &value) {
            size_t sizeRaw = value.size();
            if (sizeRaw > UINT32_MAX) {
                return GNA_E_BUFFER_TOO_BIG;
            }
            uint32_t size = sizeRaw;
            GNA_CHECK_STATUS(ser.beginList(name, size));
            if (ser.get_direction() == SerializationDirection::WRITE ||
                ser.get_direction() == SerializationDirection::REGISTER) {
                for (auto &pair : value) {
                    GNA_CHECK_STATUS(ser.beginCompound(nullptr));
                    GNA_CHECK_STATUS(ser.serialize("key", const_cast<Key &>(pair.first)));
                    GNA_CHECK_STATUS(ser.serialize("value", pair.second));
                    GNA_CHECK_STATUS(ser.endCompound());
                }
            } else {
                value.clear();
                for (uint32_t i = 0; i < size; i++) {
                    GNA_CHECK_STATUS(ser.beginCompound(nullptr));
                    Key key;
                    T val;
                    GNA_CHECK_STATUS(ser.serialize("key", key));
                    GNA_CHECK_STATUS(ser.serialize("value", val));
                    GNA_CHECK_STATUS(ser.endCompound());

                    if (!value.emplace(std::move(key), std::move(val)).second) {
                        return GNA_E_INVALID_DATA_FORMAT;
                    }
                }
            }
            GNA_CHECK_STATUS(ser.endList());
            return GNA_E_OK;
        }
    };
}
