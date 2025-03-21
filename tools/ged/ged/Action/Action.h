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

#include <gtlString/String.h>
#include <gtlMemory/RcObject.h>
#include <gtlTypeInfo/RTTI.h>

namespace ged::action {
    class Action : public gtlRcObject {
    public:
        GTL_RTTI_DECLARE();

        ~Action() override = default;

        virtual void execute() = 0;
        virtual void executeReplacing(gnaWeakPointer<Action> replacedAction) {
            execute();
        }
        virtual void undo() = 0;

        virtual gtl::String describe() const = 0;

        virtual bool canBeReplacedWith(gnaWeakPointer<Action> action) const { return false; }
    };
}
