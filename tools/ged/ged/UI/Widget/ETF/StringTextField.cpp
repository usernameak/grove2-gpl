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

#include "StringTextField.h"

#include <grUi/Layout/LayoutLinear.h>

using namespace ged::ui;

StringTextField::StringTextField(gtl::String *valuePtr) : valuePtr(valuePtr) {
    background = gnaNew<grUiBackground>(grColor{ 0xFF1E1E1D });

    layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);

    m_widgetTextValue = gnaNew<grUiWidgetText>();
    updateText();

    m_textField = gnaNew<grUiWidgetTextField>();

    gnaPointer<grUiLayoutLinear::ElementSpec> espec = grUiLayoutLinear::ElementSpec::createGrow();
    espec->minSecondarySize                         = m_textField->initialMeasure(0).height;
    m_widgetTextValue->set_layoutData(espec);
    add(m_widgetTextValue);

    m_textField->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());

    eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
    m_textField->eventSink_parentDefocus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onFieldDefocus));
    m_textField->eventSink_defocus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onFieldDefocus));
    m_textField->eventSink_textFieldConfirm.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onFieldConfirm));
}

void StringTextField::update() {
    grUiWidgetLayout::update();

    if (m_state != STATE_EDIT) {
        if (oldValue != *valuePtr) {
            updateText();
        }
    }
}

void StringTextField::updateText() {
    m_widgetTextValue->set_text(getValueText());
    oldValue = *valuePtr;
}

gtl::String StringTextField::getValueText() const {
    return *valuePtr;
}

void StringTextField::enterEditState() {
    if (m_state == STATE_EDIT) {
        return;
    }
    m_state = STATE_EDIT;
    remove(m_widgetTextValue);
    add(m_textField);
    m_textField->set_text(getValueText());
    m_textField->selectAll();
    m_textField->set_focused(true);
}

void StringTextField::enterIdleState() {
    if (m_state == STATE_EDIT) {
        remove(m_textField);
        add(m_widgetTextValue);
    }
    m_state = STATE_IDLE;
}

void StringTextField::confirmField() {
    *valuePtr = m_textField->get_text();

    enterIdleState();
}

bool StringTextField::onMouseDown(grUiEventMouseDown &ev) {
    if (ev.button == 0) {
        if (m_state == STATE_IDLE) {
            enterEditState();
        }
    }

    return true;
}

bool StringTextField::onFieldDefocus(grUiEventDefocus &ev) {
    confirmField();

    return true;
}

bool StringTextField::onFieldConfirm(grUiEventPerformAction &ev) {
    confirmField();

    return true;
}
