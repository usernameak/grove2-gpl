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

#include <unordered_map>

#include <gtlUtil/Misc.h>
#include <gtlUtil/Singleton.h>
#include <gtlObject/Object.h>
#include <gtlString/PooledString.h>

namespace nxfSerialization {
    class SerializationTypeRegistry {
        typedef gnaPointer<gtlObject> FactoryFunction();

        std::unordered_map<gtl::PooledAString, FactoryFunction *> m_typesByName;
        std::unordered_map<const gtlRTTI *, gtl::PooledAString> m_namesByType;

    public:
        template <typename T>
        void registerType(gtl::PooledAString typeName) {
            if (m_typesByName.contains(typeName)) {
                GR_FATAL(GTXT("Duplicate serialization type name %hs"), typeName.toCString());
            }

            m_typesByName[typeName]    = []() -> gnaPointer<gtlObject> { return gnaNew<T>(); };
            m_namesByType[&T::st_rtti] = typeName;
        }

        void unregisterType(gtl::PooledAString typeName) {
            m_typesByName.erase(typeName);
        }

        gnaStatus createTypeObject(gtl::PooledAString typeName, gnaPointer<gtlObject> &objRef) const {
            auto it = m_typesByName.find(typeName);
            if (it == m_typesByName.end()) {
                return { GNA_E_CLS_NOT_FOUND, GTXT("Object serialization type %hs not found") };
            }
            objRef = it->second();
            return GNA_E_OK;
        }

        gtl::PooledAString getNameFromObject(gnaWeakPointer<gtlObject> obj) const {
            auto rtti = obj->get_rtti();
            auto it   = m_namesByType.find(rtti);
            if (it == m_namesByType.end()) {
                GR_FATAL(GTXT("Serialization type does not exist for type with RTTI %hs"), rtti->get_className());
            }
            return it->second;
        }
    };

}

GNA_SINGLETON_EXPORTED_DECLARE(GTL_DLLIMPEXP, nxfSerialization::SerializationTypeRegistry);
