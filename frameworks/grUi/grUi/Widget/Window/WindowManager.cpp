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

#include "WindowManager.h"

#include <grUi/Layout/Layout.h>

///// grUiWindowLayoutData /////

void grUiWindowLayoutData::pack(gnaWeakPointer<grUiWidget> window, grDimension minSize) {
    window->pack(minSize);
}

void grUiWindowLayoutData::center(gnaWeakPointer<grUiWidget> window, gnaWeakPointer<grUiWidget> parent) {
    window->center(parent);
}

///// grUiWindowManager /////

grUiWindowManager::grUiWindowManager() : grUiWidgetLayout() {
    layout = nullptr;
}

void grUiWindowManager::displayProportionalDialog(gnaWeakPointer<grUiWidget> win, float x, float y) {
    if (!win->get_parent()) {
        add(win);
    }

    grUiWindowLayoutData::pack(win);
    grDimension dims = win->get_size();
    win->set_position(
        static_cast<int>((float)(get_size().width - dims.width) * x),
        static_cast<int>((float)(get_size().height - dims.height) * y));
}

void grUiWindowManager::displayCenteredDialog(gnaWeakPointer<grUiWidget> win) {
    if (!win->get_parent()) {
        add(win);
    }

    grUiWindowLayoutData::pack(win);
    grUiWindowLayoutData::center(win, this);
}

GTL_RTTI_DEFINE(grUiWindowManager, GTL_RTTI_INHERITS(grUiWidgetLayout));
