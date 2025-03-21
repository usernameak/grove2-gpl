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

#include <gtlObject/Object.h>

#include <functional>

namespace ged::property {
    template <typename T>
    struct EditableProperty {
    private:
        template <typename VT>
        struct ReferenceSelectorHelper {
            typedef const VT &type;
        };

        template <typename VT>
            requires(std::is_integral_v<VT> || std::is_floating_point_v<VT> || std::is_enum_v<VT>)
        struct ReferenceSelectorHelper<VT> {
            typedef VT type;
        };

    public:
        typedef typename ReferenceSelectorHelper<T>::type PreferredReferenceType;

        const char *name;
        const void *undoKey;
        const std::function<PreferredReferenceType()> get;
        const std::function<void(PreferredReferenceType)> set;

        EditableProperty(
            const char *name,
            const void *undoKey,
            std::function<PreferredReferenceType()> getter,
            std::function<void(PreferredReferenceType)> setter
        ) : name(name),
            undoKey(undoKey),
            get(std::move(getter)),
            set(std::move(setter)) {}

        static EditableProperty fromProperty(gnaPointer<gtlObject> object, const gtlProperty *property) {
            return EditableProperty(
                property->m_name,
                property,
                [object, property]() -> const T & {
                    return property->get<T>(object);
                },
                [object, property](const T &value) {
                    property->set<T>(object, value);
                }
            );
        }
    };
}
