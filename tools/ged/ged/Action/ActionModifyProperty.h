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

#include "Action.h"
#include "ged/Property/EditableProperty.h"

#include <gtlObject/Object.h>

namespace ged::action {
    class ActionModifyPropertyBase : public Action {
        const void *m_undoKey;

    public:
        GTL_RTTI_DECLARE();

        explicit ActionModifyPropertyBase(const void *undoKey)
            : m_undoKey(undoKey) {}

        bool canBeReplacedWith(gnaWeakPointer<Action> action) const override {
            if (auto mp = action.rttiCast2<ActionModifyPropertyBase>()) {
                return mp->m_undoKey == m_undoKey;
            }
            return false;
        }
    };

    template <typename T>
    class ActionModifyProperty final : public ActionModifyPropertyBase {
        property::EditableProperty<T> m_property;

        T m_originalValue;
        T m_value;

    public:
        ActionModifyProperty(
            property::EditableProperty<T> property,
            T value
        )
            : ActionModifyPropertyBase(property.undoKey),
              m_property(property),
              m_value(value) {}

        void execute() override {
            m_originalValue = m_property.get();
            m_property.set(m_value);
        }

        void executeReplacing(gnaWeakPointer<Action> replacedAction) override {
            replacedAction->undo();
            execute();
        }

        void undo() override {
            m_property.set(m_originalValue);
        }

        gtl::String describe() const override {
            return m_property.name;
        }
    };
}
