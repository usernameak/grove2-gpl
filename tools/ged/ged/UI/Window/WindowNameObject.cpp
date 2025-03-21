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

#include "WindowNameObject.h"

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/WidgetText.h>
#include <grUi/Widget/WidgetTextField.h>
#include <grUi/Widget/WidgetButton.h>

ged::ui::WindowNameObject::WindowNameObject(gtl::String title, gtl::String nameTitle) {
    set_title(title);

    auto lytMain        = gnaNew<grUiWidgetLayout>();
    lytMain->background = gnaNew<grUiBackground>(0xFF2D2D30_grColor);
    lytMain->set_padding({ 8 });
    lytMain->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);

    auto lblObjName = gnaNew<grUiWidgetText>(nameTitle);
    lblObjName->set_margin({ 0, 5, 0, 0 });
    lytMain->add(lblObjName);

    auto tfObjName = gnaNew<grUiWidgetTextField>();
    lytMain->add(tfObjName);

    auto btnOk = gnaNew<grUiWidgetButton>(GTXT("OK"));
    btnOk->eventSink_performAction.addHandler([this, tfObjName](grUiEventPerformAction &) {
        EventConfirmed ev;
        ev.name = tfObjName->get_text();
        if (eventSink_confirmed.emit(ev)) {
            closeFrame();
        }

        return true;
    });
    lytMain->add(btnOk);

    set_contentWidget(lytMain);

    grUiWindowLayoutData::pack(this, { 300, 0 });
}
