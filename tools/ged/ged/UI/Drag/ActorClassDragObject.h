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

#include <grUi/Drag/DragObject.h>

#include <grWorld/Actor/Class/ActorClassRegistry.h>

namespace ged {
    namespace ui {
        class ActorClassDragObject : public grUiDragObject {
        public:
            const gtl::PooledString m_className;

            explicit ActorClassDragObject(gtl::PooledString className) : m_className(std::move(className)) {}

            Type get_type() const override { return TYPE_SPECIAL; }
        };
    }
}
