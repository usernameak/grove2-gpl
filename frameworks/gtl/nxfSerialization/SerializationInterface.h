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

#include <gnaStatus.h>

class gtlObject;

namespace nxfSerialization {
    template <typename T>
    struct SerializationTraits;

    enum class SerializationDirection {
        READ,
        WRITE,
        REGISTER
    };

    template <typename Self>
    class SerializationInterfaceBase {
    public:
        gnaStatus serializeObjectReference(const char *name, gnaWeakPointer<gtlObject> &obj) {
            return GNA_E_OK;
        }

        gnaStatus serializeRawData(const char *name, const void *data, size_t size) {
            return GNA_E_UNSUPPORTED;
        }

        gnaStatus serializeNullRawData(const char *name) {
            return GNA_E_UNSUPPORTED;
        }

        gnaStatus deserializeRawDataSize(size_t &size) {
            return GNA_E_UNSUPPORTED;
        }

        gnaStatus deserializeRawData(void *, size_t size) {
            return GNA_E_UNSUPPORTED;
        }

        SerializationDirection get_direction() const = delete;

        template <typename T>
        gnaStatus serializeValue(const char *name, T &value) {
            return GNA_E_OK;
        }

        template <typename T>
        gnaStatus serialize(const char *name, T &value) {
            return SerializationTraits<T>::serialize(name, *static_cast<Self *>(this), value);
        }

        gnaStatus beginList(const char *name, uint32_t &size) {
            return serialize(name, size);
        }

        gnaStatus endList() {
            return GNA_E_OK;
        }

        gnaStatus beginCompound(const char *name) {
            return GNA_E_OK;
        }

        gnaStatus endCompound() {
            return GNA_E_OK;
        }
    };

    template <typename T>
    concept SerializationInterface = std::derived_from<T, SerializationInterfaceBase<T>>;
}
