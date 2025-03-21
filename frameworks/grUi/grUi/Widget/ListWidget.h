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

struct grUiEventTreeListOpenEntry {
};

struct grUiEventTreeListSelectEntry {
};

struct grUiEventTreeListContextMenu {
    gnaPointer<grUi::DropDownMenu> dropDown;
};

struct grUiEventListPopulate {
    std::vector<gnaPointer<grUiWidget>> list;
};

class GR_UI_DLLIMPEXP grUiListWidget : public grUiWidgetLayout {
public:
    GTL_RTTI_DECLARE();

    grUiListWidget();

    void updateList();

    gnaEventSink<grUiEventListPopulate> eventSink_populate;
};

class GR_UI_DLLIMPEXP grUiListEntry : public grUiWidget {
public:
    GTL_RTTI_DECLARE();

    const grUiFontKey font = { GTXT("Default"), GR_UI_DEFAULT_FONT_SIZE };
    grUiSprite icon;
    gtl::String name;
    grColor m_textColor;

    gnaPointer<grUiDragObject> m_dragObject;

    grUiListEntry(gtl::String text);

    grDimension initialMeasure(int biasedSize) override;
    void draw(grUiRenderer *) override;

    bool applyStyleProperty(const gtl::PooledAString &name, gnaWeakPointer<grUiGSSPropVal> value) override;

    gnaEventSink<grUiEventTreeListOpenEntry> eventSink_openEntry;
    gnaEventSink<grUiEventTreeListSelectEntry> eventSink_selectEntry;
    gnaEventSink<grUiEventTreeListContextMenu> eventSink_contextMenu;
    grDoubleClickEventSink eventSink_doubleClick;

private:
    bool onMouseDown(const grUiEventMouseDown &ev);
    bool onKeyPress(const grUiEventKeyPress &ev);
    bool onDoubleClick(const grUiEventDoubleClick &ev);
    bool onFocus(const grUiEventFocus &ev);
};
