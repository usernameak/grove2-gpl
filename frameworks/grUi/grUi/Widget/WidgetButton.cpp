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

#include "WidgetButton.h"

grUiWidgetButton::grUiWidgetButton()
    : grUiWidgetIconText(),
      state(STATE_IDLE),
      m_disabled(false) {
    init();
}

grUiWidgetButton::grUiWidgetButton(gtl::String label)
    : grUiWidgetIconText(label),
      state(STATE_IDLE),
      m_disabled(false) {
    init();
}

void grUiWidgetButton::updateVisualsFromState() {
    auto newBits = get_styleStateBits() & ~(STSTBIT_HOVERED | STSTBIT_PRESSED | STSTBIT_DISABLED);
    if (m_disabled) {
        newBits |= STSTBIT_DISABLED;
    } else {
        switch (state) {
        case STATE_IDLE:
            break;
        case STATE_HOVERED:
            newBits |= STSTBIT_HOVERED;
            break;
        case STATE_PRESSED:
            newBits |= STSTBIT_HOVERED | STSTBIT_PRESSED;
            break;
        }
    }
    set_styleStateBits(newBits);
}

void grUiWidgetButton::init() {
    updateVisualsFromState();

    this->eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
    this->eventSink_mouseUp.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseUp));
    this->eventSink_mouseEnter.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseEnter));
    this->eventSink_mouseLeave.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseLeave));
}

bool grUiWidgetButton::onMouseEnter(const grUiEventMouseEnter &ev) {
    state = STATE_HOVERED;
    updateVisualsFromState();
    return true;
}

bool grUiWidgetButton::onMouseLeave(const grUiEventMouseLeave &ev) {
    state = STATE_IDLE;
    updateVisualsFromState();
    return true;
}

bool grUiWidgetButton::onMouseDown(const grUiEventMouseDown &ev) {
    if (ev.button == 0 && !m_disabled) {
        state = STATE_PRESSED;
        updateVisualsFromState();
    }

    return false;
}

bool grUiWidgetButton::onMouseUp(const grUiEventMouseUp &ev) {
    if (ev.button == 0) {
        if (state == STATE_PRESSED) {
            state = STATE_HOVERED;
            updateVisualsFromState();

            clickButton();
        }
    }

    return false;
}

void grUiWidgetButton::clickButton() {
    grUiEventPerformAction ev1;
    this->eventSink_performAction.emit(ev1);
}

GTL_RTTI_DEFINE(grUiWidgetButton, GTL_RTTI_INHERITS(grUiWidgetIconText));
