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

#include <grUi/Widget/WidgetLayout.h>
#include <grUi/Widget/WidgetText.h>
#include <grUi/Widget/WidgetButton.h>
#include <grUi/UiDLL.h>

class GR_UI_DLLIMPEXP grUiDropDownMenuEntry : public grUiWidgetText {
public:
    grUiDropDownMenuEntry(gtl::String label);

    bool onFocus(grUiEventFocus &ev);
    bool onDefocus(grUiEventDefocus &ev);

    bool onMouseUp(const grUiEventMouseUp &ev);
    bool onMouseEnter(grUiEventMouseEnter &ev);
    bool onMouseLeave(grUiEventMouseLeave &ev);

    bool onButtonClick(const grUiEventPerformAction &ev);

    gnaEventSink<grUiEventPerformAction> eventSink_performAction;

    GTL_RTTI_DECLARE();
};

class GR_UI_DLLIMPEXP grUiDropDownMenu : public grUiWidgetLayout {
public:
    grUiDropDownMenu();

    virtual ~grUiDropDownMenu() override = default;

    bool onDefocus(grUiEventDefocus &ev);
    void showAt(int x, int y);
    void showAbove(gnaWeakPointer<grUiWidget> attachTo);

    GTL_RTTI_DECLARE();
};

namespace grUi {
    using DropDownMenuEntry = grUiDropDownMenuEntry;
    using DropDownMenu = grUiDropDownMenu;
}
