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

#include "DoubleClickEventSink.h"

#include "grUi/Native/NativePlatformDevice.h"

grDoubleClickEventSink::grDoubleClickEventSink(gnaWeakPointer<grUiWidget> widget)
    : buttonTime(GR_UI_UNDEFINED_TIME),
      m_widget(std::move(widget)) {
}

bool grDoubleClickEventSink::onMouseDown(const grUiEventMouseDown &ev) {
    if (ev.button == 0) {
        bool firstClick = buttonTime == GR_UI_UNDEFINED_TIME;
        if (!firstClick) {
            unsigned int doubleClickDelay = m_widget->get_nativeDevice() ? m_widget->get_nativeDevice()->get_doubleClickDelayMs() : 1000;
            firstClick |= buttonTime + doubleClickDelay < grUi_gTimeMs;
            firstClick |= buttonX != ev.x;
            firstClick |= buttonY != ev.y;
        }

        if (firstClick) {
            buttonTime = grUi_gTimeMs;
            buttonX    = ev.x;
            buttonY    = ev.y;

            return true;
        } else {
            buttonTime = GR_UI_UNDEFINED_TIME;
            grUiEventDoubleClick ev1;
            ev1.x = ev.x;
            ev1.y = ev.y;
            emit(ev1);
            return false;
        }
    }
    return true;
}
