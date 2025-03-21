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
#include <grUi/Utils/DoubleClickEventSink.h>
#include <grUi/Widget/DropDownMenu.h>

struct gedEventTreeListOpenEntry {
};

struct gedEventTreeListSelectEntry {
};

struct gedEventTreeListContextMenu {
    gnaPointer<grUi::DropDownMenu> dropDown;
};

namespace ged {
    namespace ui {
        struct EventListPopulate {
            std::vector<gnaPointer<grUiWidget>> list;
        };

        class ListWidget : public grUiWidgetLayout {
        public:
            ListWidget();

            void updateList();

            gnaEventSink<EventListPopulate> eventSink_populate;
        };

        class ListEntry : public grUiWidget {
        public:
            const grUiFontKey font = { GTXT("Default"), GR_UI_DEFAULT_FONT_SIZE };
            grUiSprite icon;
            gtl::String name;

            gnaPointer<grUiDragObject> m_dragObject;

            ListEntry(gtl::String text);

            grDimension initialMeasure(int biasedSize) override;
            void draw(grUiRenderer *) override;

            gnaEventSink<gedEventTreeListOpenEntry> eventSink_openEntry;
            gnaEventSink<gedEventTreeListSelectEntry> eventSink_selectEntry;
            gnaEventSink<gedEventTreeListContextMenu> eventSink_contextMenu;
            grDoubleClickEventSink eventSink_doubleClick;

        private:
            bool onMouseDown(const grUiEventMouseDown &ev);
            bool onKeyPress(const grUiEventKeyPress &ev);
            bool onDoubleClick(const grUiEventDoubleClick &ev);
            bool onFocus(const grUiEventFocus &ev);
        };
    }
}
