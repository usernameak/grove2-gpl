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

#include <gnaEventSink.h>
#include <grUi/Utils/DoubleClickEventSink.h>
#include <nxfResource/ResourceManager.h>
#include <grUi/Font/FontRenderer.h>
#include <grUi/Font/FontCache.h>
#include <grUi/Widget/Widget.h>
#include <grUi/Widget/WidgetLayout.h>
#include <grUi/Utils/Sprite.h>
#include <grUi/Drag/DragContext.h>

#include "ListWidget.h"

class gedTreeList;
class gedTreeListEntryInterface;

struct gedEventTreeListPopulateSublist {
    struct Entry {
        gnaPointer<grUiWidget> widget;
        gedTreeListEntryInterface *entry;
    };
    std::vector<Entry> sublist;

    template <typename T>
    void addEntry(gnaPointer<T> w) {
        Entry e = { w, &*w };
        sublist.push_back(e);
    }
};
class gedTreeListEntryInterface {
public:
    bool isExpandable : 1;
    bool expanded     : 1;

    int nestingLevel;

    gnaWeakPointer<grUiWidget> parentEntry;

    gedTreeListEntryInterface() : expanded(false), isExpandable(false), nestingLevel(0) {}

    virtual ~gedTreeListEntryInterface() = default;

    virtual gnaWeakPointer<grUiWidget> get_widget() = 0;

    gnaEventSink<gedEventTreeListPopulateSublist> eventSink_populateSublist;
    gnaEventSink<gedEventTreeListOpenEntry> eventSink_openEntry;
    gnaEventSink<gedEventTreeListSelectEntry> eventSink_selectEntry;
    gnaEventSink<gedEventTreeListContextMenu> eventSink_contextMenu;
};

class gedTreeListEntryWidget : public grUiWidget, public gedTreeListEntryInterface {
public:
    const grUiFontKey font = { GTXT("Default"), GR_UI_DEFAULT_FONT_SIZE };
    grUiSprite icon;
    gtl::String name;

    gnaPointer<grUiDragObject> m_dragObject;

    gedTreeListEntryWidget();

    grDimension initialMeasure(int biasedSize) override;
    void draw(grUiRenderer *) override;
    void flipExpand();

    gnaWeakPointer<grUiWidget> get_widget() override {
        return this;
    }

private:
    bool onMouseDown(const grUiEventMouseDown &ev);
    bool onKeyPress(const grUiEventKeyPress &ev);
    bool onDoubleClick(const grUiEventDoubleClick &ev);
    bool onFocus(const grUiEventFocus &ev);

    grDoubleClickEventSink eventSink_doubleClick;
};

class gedTreeList : public grUiWidgetLayout {
public:
    GTL_RTTI_DECLARE();

    gedTreeList();

    gnaEventSink<gedEventTreeListPopulateSublist> eventSink_populateSublist;

    void updateList();
    void expandEntry(gedTreeListEntryInterface *entryInterface);
    void collapseEntry(gedTreeListEntryInterface *entryInterface);

private:
    bool onKeyPress(const grUiEventKeyPress &ev);
};
