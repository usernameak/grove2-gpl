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

#include "Object.h"

GTL_RTTI_DEFINE(gtlObject, GTL_RTTI_INHERITS(gtlCloneable));
NXF_SERIALIZABLE_DEFINE(gtlObject, GTL_DLLIMPEXP);

const gtlPropertyTable gtlObject::st_propertyTable{ nullptr, 0 };

const gtlProperty *gtlProperty::findProperty(gnaWeakPointer<gtlObject> object, const char *name) {
    // TODO: this is slow. make it faster
    for (int i = 0;; i++) {
        auto *table = object->get_propertyTable(i);
        if (!table) break;

        size_t count = table->get_propertyCount();
        for (int j = 0; j < count; j++) {
            auto &property = table->getProperty(j);
            if (strcmp(name, property.m_name) == 0) {
                return &property;
            }
        }
    }
    return nullptr;
}

const gtlPropertyTable *gtlObject::get_propertyTable(int baseIndex) const {
    if (baseIndex > 0) return nullptr;

    return &st_propertyTable;
}

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus gtlObject::serializationImpl(TSerializationInterface &) {
    return GNA_E_OK;
}
