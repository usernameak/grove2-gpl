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

#include <gtlUtil/Misc.h>
#include <cstdint>
#include <grUi/Utils/Keycode.h>
#include <grUi/Drag/DragObject.h>

#define GR_UI_MAX_MOUSE_BUTTONS (16)

enum grKeyAction {
    GR_ACTION_KEY_RELEASED = 0,
    GR_ACTION_KEY_REPEATED = 1,
    GR_ACTION_KEY_PRESSED = 2
};

enum grKeyMods {
    GR_KEY_MOD_CTRL        = GTL_BIT(0),
    GR_KEY_MOD_CTRL_OR_CMD = GTL_BIT(1),
    GR_KEY_MOD_ALT         = GTL_BIT(2),
    GR_KEY_MOD_SHIFT       = GTL_BIT(3),
    GR_KEY_MOD_SUPER       = GTL_BIT(4)
};

struct grUiEventChangeTab {
    short tab_index = 0;
};

struct grUiEventTextInput {
    char32_t c;
};

struct grUiEventKeyPress {
    grKeycode keycode;
    int scancode;
    int mods;
    grKeyAction action;
};

struct grUiEventMouseMove {
    int x, y, dx, dy;
};

struct grUiEventMouseDown {
    int x, y, button, mods; // todo remake this shit to use enums instead of fucking ints
};

struct grUiEventMouseUp {
    int x, y, button, mods;
};

struct grUiEventMouseWheel {
    int x, y;
    int delta;
    int mods;
};

struct grUiEventMouseEnter {
};

struct grUiEventMouseLeave {
};

struct grUiEventFocus {
};

struct grUiEventDefocus {
};

struct grUiEventPerformAction {
};

struct grUiEventObjectDrop {
    gnaWeakPointer<grUiDragObject> object;
    int mods;
    int x, y;
};
