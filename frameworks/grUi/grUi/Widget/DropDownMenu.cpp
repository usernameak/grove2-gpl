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

#include "DropDownMenu.h"

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/Window/RootWindowManager.h>

//-/// grUiDropDownMenuEntry ///-//
grUiDropDownMenuEntry::grUiDropDownMenuEntry(gtl::String label) : grUiWidgetText(label) {
    alignment = (grUiTextAlignment)(GR_TEXT_ALIGN_LEFT | GR_TEXT_ALIGN_MIDDLE);
    set_padding(grUiUnitInsets{ 5 });

    this->eventSink_performAction.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onButtonClick), gnaEventPriority::PRIORITY_FINALIZER);

    this->eventSink_focus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onFocus));
    this->eventSink_defocus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onDefocus));

    this->eventSink_mouseUp.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseUp));
    this->eventSink_mouseEnter.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseEnter));
    this->eventSink_mouseLeave.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseLeave));
}

bool grUiDropDownMenuEntry::onMouseUp(const grUiEventMouseUp &ev) {
    if (ev.button == 0) {
        grUiEventPerformAction ev1;
        this->eventSink_performAction.emit(ev1);
    }

    return true;
}

bool grUiDropDownMenuEntry::onFocus(grUiEventFocus &ev) {
    set_styleStateBits((get_styleStateBits() | STSTBIT_HOVERED) & ~(STSTBIT_PRESSED));
    return true;
}

bool grUiDropDownMenuEntry::onDefocus(grUiEventDefocus &ev) {
    set_styleStateBits(get_styleStateBits() & ~(STSTBIT_HOVERED | STSTBIT_PRESSED));
    return true;
}

bool grUiDropDownMenuEntry::onMouseEnter(grUiEventMouseEnter &ev) {
    set_focused(true);
    return true;
}

bool grUiDropDownMenuEntry::onMouseLeave(grUiEventMouseLeave &ev) {
    set_focused(false);
    return true;
}

bool grUiDropDownMenuEntry::onButtonClick(const grUiEventPerformAction &ev) {
    // FIXME: this is dirty as fuck and wouldn't work for nested menus
    grUi_gRootWindowManager->remove(get_parent(), true);
    return true;
}

GTL_RTTI_DEFINE(grUiDropDownMenuEntry, GTL_RTTI_INHERITS(grUiWidgetText));

//-/// grUiDropDownMenu ///-//

grUiDropDownMenu::grUiDropDownMenu() : grUiWidgetLayout() {
    layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);

    background = gnaNew<grUiBackground>(0xFF1B1B1C_grColor);
    set_border(gnaNew<grUiBorder>(1, 0xFF333337_grColor));

    this->eventSink_defocus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onDefocus));
}

bool grUiDropDownMenu::onDefocus(grUiEventDefocus &ev) {
    get_parent()->remove(this, PFLAG_IF_EXISTS);
    return true;
}

void grUiDropDownMenu::showAt(int x, int y) {
    set_focused(true);
    grUi_gRootWindowManager->add(gnaWeakPointer(this));
    grUiWindowLayoutData::pack(this);
    set_position(x, y);
}

void grUiDropDownMenu::showAbove(gnaWeakPointer<grUiWidget> attachTo) {
    grPoint relPos = attachTo->computeRelativePosition(grUi_gRootWindowManager);

    set_focused(true);
    grUi_gRootWindowManager->add(gnaWeakPointer(this));
    grUiWindowLayoutData::pack(this);
    set_position(relPos.x, relPos.y - get_size().height);
}

GTL_RTTI_DEFINE(grUiDropDownMenu, GTL_RTTI_INHERITS(grUiWidgetLayout));
