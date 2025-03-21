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

#include "WidgetCheckbox.h"

#include <grUi/Render/UiRenderer.h>
#include <grUi/Utils/Sprite.h>

grUiWidgetCheckbox::grUiWidgetCheckbox(bool checked, const gtl::String text)
    : grUiWidgetIconText(text) {
    set_checked(checked);
    eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
}

grUiWidgetCheckbox::~grUiWidgetCheckbox() = default;

bool grUiWidgetCheckbox::onMouseDown(grUiEventMouseDown &ev) {
    set_checked(!m_checked);

    return true;
}

void grUiWidgetCheckbox::set_checked(bool checked, bool emitEvent) {
    if (m_checked == checked) return;

    m_checked = checked;

    if (checked) {
        set_styleStateBits(get_styleStateBits() | STSTBIT_CHECKED);
    } else {
        set_styleStateBits(get_styleStateBits() & ~STSTBIT_CHECKED);
    }

    if (emitEvent) {
        grUiEventCheckboxChanged ev1;
        ev1.newState = checked;
        eventSink_checkboxChanged.emit(ev1);
    }
}

GTL_RTTI_DEFINE(grUiWidgetCheckbox, GTL_RTTI_INHERITS(grUiWidgetIconText));
