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

#include "ErrorWindow.h"

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/WidgetButton.h>

gedErrorWindow::gedErrorWindow(gtl::String errorMessage) {
    set_title(GTXT("Error message"));

    auto lwMain = gnaNew<grUiWidgetLayout>();

    lwMain->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);

    gnaPointer<grUiWidgetText> lblMessage = gnaNew<grUiWidgetText>(errorMessage);
    lblMessage->set_padding({ 5 });
    lwMain->add(lblMessage);

    gnaPointer<grUiWidgetButton> btnOk = gnaNew<grUiWidgetButton>(GTXT("OK"));
    btnOk->eventSink_performAction.addHandler([this](const auto &ev) {
        get_parent()->remove(this);
        return true;
    });
    lwMain->add(btnOk);

    set_contentWidget(lwMain);
}
