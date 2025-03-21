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

#include "WidgetIconText.h"
#include <grUi/UiDLL.h>

class GR_UI_DLLIMPEXP grUiWidgetButton : public grUiWidgetIconText {
public:
    enum State : unsigned int {
        STATE_IDLE = 0,
        STATE_HOVERED = 1,
        STATE_PRESSED = 2
    };

private:
    State state : 2;
    bool m_disabled : 1;

public:
    grUiWidgetButton();
    grUiWidgetButton(gtl::String label);

    gnaEventSink<grUiEventPerformAction> eventSink_performAction;

    void clickButton();

    State get_buttonState() const { return state; }

    void set_disabled(bool disabled) {
        if (m_disabled == disabled)
            return;

        m_disabled = disabled;

        updateVisualsFromState();
    }

    bool get_disabled() { return m_disabled; }

    virtual void updateVisualsFromState();

private:
    void init();

    bool onMouseDown(const grUiEventMouseDown &ev);
    bool onMouseUp(const grUiEventMouseUp &ev);
    bool onMouseEnter(const grUiEventMouseEnter &ev);
    bool onMouseLeave(const grUiEventMouseLeave &ev);

public:
    GTL_RTTI_DECLARE();
};
