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

#include <grUi/Widget/Widget.h>
#include <grUi/Font/FontCache.h>
#include <grUi/UiDLL.h>
#include "WidgetIconText.h"

struct grUiEventCheckboxChanged {
    bool newState;
};

class GR_UI_DLLIMPEXP grUiWidgetCheckbox : public grUiWidgetIconText {
    grUiFontKey font = { GTXT("Default"), GR_UI_DEFAULT_FONT_SIZE };

    constexpr static int CHECK_MARK_PADDING = 6;

    bool m_checked;

public:
    grUiWidgetCheckbox(bool checked = false, const gtl::String text = GTXT(""));

    virtual ~grUiWidgetCheckbox() override;

    grColor color = grColor::WHITE;

    void set_checked(bool checked, bool emitEvent = true);
    bool get_checked() const {
        return m_checked;
    }

    gnaEventSink<grUiEventCheckboxChanged> eventSink_checkboxChanged;

private:
    bool onMouseDown(grUiEventMouseDown &ev);

public:
    GTL_RTTI_DECLARE();
};
