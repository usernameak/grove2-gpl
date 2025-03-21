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

#include <grUi/UiDLL.h>
#include <grUi/Widget/WidgetLayout.h>
#include "WidgetEmpty.h"
#include "WidgetText.h"


class grUiWidgetTab;

class GR_UI_DLLIMPEXP grUiWidgetTabbedPane : public grUiWidgetLayout {
    class TabbedPaneLayout;
    friend class ::grUiWidgetTabbedPane::TabbedPaneLayout;

    struct PageInfo {
        gnaPointer<grUiWidgetTab> tab;
        gnaPointer<grUiWidget> page;
    };

    std::vector<PageInfo> m_pages;
    gnaPointer<grUiWidgetLayout> m_lwTabRibbon;
    gnaPointer<grUiWidgetEmpty> m_tabEndEmptyWidget;

public:
    size_t m_currentPageIndex;

    grUiWidgetTabbedPane();

    void addPage(gnaPointer<grUiWidgetTab> tab, gnaPointer<grUiWidget> page);
    void addPageBegin(gnaPointer<grUiWidgetTab> tab, gnaPointer<grUiWidget> page);
    void removePage(gnaPointer<grUiWidgetTab> tab);
    bool checkPageExists(gnaWeakPointer<grUiWidgetTab> tab);
    void setCurrentPage(gnaWeakPointer<grUiWidget> page);
    void setCurrentPage(size_t pageIndex);
    void deselectPage();
    void selectTab(gnaWeakPointer<grUiWidgetTab> tab);
    size_t getCurrentPage();

    gnaPointer<grUiWidgetLayout> ejectTabRibbon();

    gnaEventSink<grUiEventChangeTab> eventSink_changeTab;

public:
    GTL_RTTI_DECLARE();
};

class GR_UI_DLLIMPEXP grUiWidgetTab : public grUiWidgetText {
    gnaWeakPointer<grUiWidgetTabbedPane> m_pane;
public:
    grUiWidgetTab(gnaWeakPointer<grUiWidgetTabbedPane> pane, gtl::String tabName, bool largeTab = false);

private:
    bool onMouseDown(const grUiEventMouseDown &ev);
    bool onFocused(const grUiEventFocus &ev);

public:
    GTL_RTTI_DECLARE();
};
