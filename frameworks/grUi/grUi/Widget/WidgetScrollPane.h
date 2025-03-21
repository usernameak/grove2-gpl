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
#include <grUi/UiDLL.h>

class GR_UI_DLLIMPEXP grUiWidgetScrollPane : public grUiWidgetLayout {
protected:
    class ScrollLayout;

    gnaWeakPointer<grUiWidget> contentWidget;
    gnaWeakPointer<grUiWidget> scrollbarWidget;

    int scrollOffset;
    grRectangle contentRect;

    int lastMouseX;
    int lastMouseY;

    uint32_t m_scrollFlags;

public:
    class ScrollInterface {
    public:
        struct EventScroll {
            int targetPosition;
        };

        virtual ~ScrollInterface() = default;

        virtual void set_scrollContentSize(int size) = 0;
        virtual void set_scrollPosition(int offset) = 0;

        gnaEventSink<EventScroll> eventSink_scroll;
    };

    enum ScrollFlags {
        SCROLL_FLAG_INVERT_OFFSET = GTL_BIT(0)
    };

    grUiWidgetScrollPane();

    void set_contentWidget(gnaWeakPointer<grUiWidget> widget);
    gnaWeakPointer<grUiWidget> get_contentWidget() {
        return contentWidget;
    }

    void set_scrollbarWidget(gnaWeakPointer<grUiWidget> widget);
    gnaWeakPointer<grUiWidget> get_scrollbarWidget() {
        return scrollbarWidget;
    }

    void set_scrollFlags(uint32_t flags) {
        m_scrollFlags = flags;
        scrollToTop();
    }

    uint32_t get_scrollFlags() const {
        return m_scrollFlags;
    }

    void scrollToTop();
    void scrollToEnd();

private:
    void forceUpdateMouse();

    bool onMouseWheel(const grUiEventMouseWheel &ev);
    bool onMouseMove(grUiEventMouseMove &ev);
    bool onMouseLeave(grUiEventMouseLeave &ev);

public:
    GTL_RTTI_DECLARE();
};
