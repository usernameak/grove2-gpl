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

#include "MenuBar.h"

#include <grUi/Widget/Window/RootWindowManager.h>
#include <grUi/Widget/DropDownMenu.h>
#include <grUi/Text/TextRenderer.h>

ged::UI::MenuBar::MenuBar() {
    this->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);
}

void ged::UI::MenuBar::updateMenus() {
    EventPopulateMenu ev;
    eventSink_populateMenu.emit(ev);

    removeAll();
    for (gnaWeakPointer<MenuBarEntry> entry : ev.entries) {
        add(entry);
    }
}

ged::UI::MenuBarEntry::MenuBarEntry(const gtl::String &label) : label(label) {
    set_padding({ 5 });

    this->eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
}

grDimension ged::UI::MenuBarEntry::initialMeasure(int biasedSize) {
    grUiTextRenderer tr(get_metricContext(), font);

    int width       = (int)ceil(tr.get_width(label));
    grDimension dim = { width, (int)ceil(tr.get_lineHeight()) };

    return get_baseInsets().outsetDimension(dim);
}

void ged::UI::MenuBarEntry::draw(grUiRenderer *render) {
    grUiTextRenderer tr(get_metricContext(), font);

    grRectangle rc = get_baseInsets().insetDimensionToRect(get_size());

    tr.setOrigin(rc.x, (int)(rc.y + tr.get_baselineOffsetFromLineTop()));
    tr.render(render, label);
}

void ged::UI::MenuBarEntry::displayDropDownMenu(gnaWeakPointer<grUi::DropDownMenu> menu) {
    grPoint relPos = computeRelativePosition(grUi_gRootWindowManager);
    int x          = relPos.x;
    int y          = relPos.y + get_size().height;
    menu->showAt(x, y);
}

bool ged::UI::MenuBarEntry::onMouseDown(const grUiEventMouseDown &ev) {
    if (ev.button == 0) {
        grUiEventPerformAction ev1;
        this->eventSink_performAction.emit(ev1);
    }
    return true;
}
