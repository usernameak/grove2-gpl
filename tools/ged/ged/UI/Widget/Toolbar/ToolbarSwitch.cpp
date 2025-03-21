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

#include "ToolbarSwitch.h"

ged::ui::ToolbarSwitch::ToolbarSwitch(bool checked) {
    set_checked(checked);

    eventSink_performAction.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onPerformAction));
}

bool ged::ui::ToolbarSwitch::onPerformAction(grUiEventPerformAction &ev) {
    set_checked(!get_checked());

    EventSwitched ev1;
    eventSink_switched.emit(ev1);

    return true;
}
