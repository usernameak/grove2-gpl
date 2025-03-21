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

#include "WidgetTooltip.h"

grUiWidgetTooltip::grUiWidgetTooltip() {
    set_ignoresMouse(true);
}

void grUiWidgetTooltip::displayTip(gnaPointer<grUiWindowManager> windowManager, int x, int y) {
    if (get_parent() != windowManager) {
        hideTip();

        windowManager->add(gnaWeakPointer(this));

        grUiWindowLayoutData::pack(this);
    }

    if (x + 30 + get_size().width > get_parent()->get_size().width) {
        x = x - 30 - get_size().width;
    } else {
        x += 30;
    }
    if (y + get_size().height > get_parent()->get_size().height) {
        y = get_parent()->get_size().height - get_size().height;
    }
    if (y < 0) {
        y = 0;
    }
    set_position(x, y);
}

void grUiWidgetTooltip::hideTip() {
    if (get_parent()) {
        get_parent()->remove(gnaWeakPointer(this));
    }
}

GTL_RTTI_DEFINE(grUiWidgetTooltip, GTL_RTTI_INHERITS(grUiWidgetLayout));
