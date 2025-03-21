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

#include "WidgetTabbedPane.h"
#include "WidgetEmpty.h"

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/WidgetText.h>

class grUiWidgetTabbedPane::TabbedPaneLayout : public grUiLayoutManager {
protected:
    grDimension initialMeasure(grUiWidgetLayout *parent, int biasedSize) override {
        grUiWidgetTabbedPane *tp = gtlRttiCast<grUiWidgetTabbedPane *>(parent);
        assert(tp);

        grDimension ribbonDim {0,0};
        if (tp->m_lwTabRibbon->get_parent() == tp) {
            ribbonDim = tp->m_lwTabRibbon->measure();
        }
        grDimension dim = ribbonDim;
        for (const PageInfo &pageInfo : tp->m_pages) {
            grDimension pageSize = pageInfo.page->measure();

            if (pageSize.width > dim.width) {
                dim.width = pageSize.width;
            }

            if (pageSize.height + ribbonDim.height > dim.height) {
                dim.height = pageSize.height + ribbonDim.height;
            }
        }

        return parent->get_baseInsets().outsetDimension(dim);
    }

    void layout(grUiWidgetLayout *parent) override {
        grUiWidgetTabbedPane *tp = gtlRttiCast<grUiWidgetTabbedPane *>(parent);
        assert(tp);

        grRectangle rc = parent->get_baseInsets().insetDimensionToRect(parent->get_size());

        grDimension ribbonDim {0, 0};
        if (tp->m_lwTabRibbon->get_parent() == tp) {
            ribbonDim = tp->m_lwTabRibbon->measure();
            tp->m_lwTabRibbon->set_bounds(rc.x, rc.y, rc.width, ribbonDim.height);
        }

        for (const PageInfo &pageInfo : tp->m_pages) {
            pageInfo.page->set_bounds(rc.x, rc.y + ribbonDim.height, rc.width, rc.height - ribbonDim.height);
        }
    }
};

grUiWidgetTabbedPane::grUiWidgetTabbedPane() : m_currentPageIndex(SIZE_MAX) {
    layout = gnaNew<TabbedPaneLayout>();

    m_lwTabRibbon = gnaNew<grUiWidgetLayout>();
    m_lwTabRibbon->add_styleClass("TabRibbon");
    m_lwTabRibbon->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);
    add(m_lwTabRibbon);

    // aligning tabs to center
    // left widget
    auto empty = gnaNew<grUiWidgetEmpty>();
    empty->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());
    m_lwTabRibbon->add(empty);

    m_tabEndEmptyWidget = gnaNew<grUiWidgetEmpty>();
    m_tabEndEmptyWidget->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());
    m_lwTabRibbon->add(m_tabEndEmptyWidget);
}

void grUiWidgetTabbedPane::addPage(gnaPointer<grUiWidgetTab> tab, gnaPointer<grUiWidget> page) {
    tab->set_layoutData(grUiLayoutLinear::ElementSpec::createMin(0, grUiLayoutLinear::SA_END));
    m_lwTabRibbon->insertBefore(tab, m_tabEndEmptyWidget);
    //m_lwTabRibbon->add(tab);

    PageInfo &info = m_pages.emplace_back();
    info.tab       = std::move(tab);
    info.page      = std::move(page);

    insertBefore(info.page, m_lwTabRibbon);
    info.page->set_visibility(VISIBILITY_INVISIBLE);
}

void grUiWidgetTabbedPane::addPageBegin(gnaPointer<grUiWidgetTab> tab, gnaPointer<grUiWidget> page) {
    tab->set_layoutData(grUiLayoutLinear::ElementSpec::createMin(0, grUiLayoutLinear::SA_END));
    auto widget_before = m_pages.empty() ? m_tabEndEmptyWidget : (gnaPointer<grUiWidget>) m_pages[0].tab;
    m_lwTabRibbon->insertBefore(tab, widget_before);
    //m_lwTabRibbon->add(tab);

    m_pages.insert(m_pages.begin(), {std::move(tab), std::move(page)});
    auto& info = m_pages[0];

    if (m_currentPageIndex != SIZE_MAX)
        ++m_currentPageIndex;

    insertBefore(info.page, m_lwTabRibbon);
    info.page->set_visibility(VISIBILITY_INVISIBLE);
}

void grUiWidgetTabbedPane::removePage(gnaPointer<grUiWidgetTab> tab) {
    auto entry = std::find_if(m_pages.begin(), m_pages.end(), [tab](const auto& curr) {return curr.tab == tab;});
    if (entry == m_pages.end())
        return;
    auto delPageIndex = std::distance(m_pages.begin(), entry);

    // deselecting tab if selected
    if (m_currentPageIndex == delPageIndex) {
        m_pages[m_currentPageIndex].page->set_visibility(VISIBILITY_INVISIBLE);
        m_pages[m_currentPageIndex].tab->set_focused(false);
        m_currentPageIndex = SIZE_MAX;
    }
    // fixing current tab index after deleting the first tab
    else if (delPageIndex < m_currentPageIndex) {
        --m_currentPageIndex;
    }

    m_lwTabRibbon->remove(entry->tab, PFLAG_IF_EXISTS);
    remove(entry->page, PFLAG_IF_EXISTS);
    m_pages.erase(entry);
}

bool grUiWidgetTabbedPane::checkPageExists(gnaWeakPointer<grUiWidgetTab> tab) {
    return tab->get_parent() == m_lwTabRibbon;
}

void grUiWidgetTabbedPane::setCurrentPage(gnaWeakPointer<grUiWidget> page) {
    for (size_t i = 0; i < m_pages.size(); i++) {
        if (page == m_pages[i].page) {
            setCurrentPage(i);
            break;
        }
    }
}

void grUiWidgetTabbedPane::setCurrentPage(size_t pageIndex) {
    if (pageIndex == m_currentPageIndex) return;

    if (m_currentPageIndex != SIZE_MAX) {
        m_pages[m_currentPageIndex].page->set_visibility(VISIBILITY_INVISIBLE);
        m_pages[m_currentPageIndex].tab->set_focused(false);
    }
    m_currentPageIndex = pageIndex;
    m_pages[m_currentPageIndex].tab->set_focused(true);
    auto page = m_pages[m_currentPageIndex].page;
    page->set_visibility(VISIBILITY_VISIBLE);
    page->set_focused(true);

    grUiEventChangeTab ev{ (short) m_currentPageIndex };
    eventSink_changeTab.emit(ev);
}

void grUiWidgetTabbedPane::deselectPage() {
    if (m_currentPageIndex == SIZE_MAX)
        return;

    m_pages[m_currentPageIndex].page->set_visibility(VISIBILITY_INVISIBLE);
    m_pages[m_currentPageIndex].tab->set_focused(false);
    m_currentPageIndex = SIZE_MAX;
}

void grUiWidgetTabbedPane::selectTab(gnaWeakPointer<grUiWidgetTab> tab) {
    for (size_t i = 0; i < m_pages.size(); i++) {
        if (tab == m_pages[i].tab) {
            setCurrentPage(i);
            break;
        }
    }
}

size_t grUiWidgetTabbedPane::getCurrentPage() {
    return m_currentPageIndex;
}

gnaPointer<grUiWidgetLayout> grUiWidgetTabbedPane::ejectTabRibbon() {
    remove(m_lwTabRibbon);
    return m_lwTabRibbon;
}

GTL_RTTI_DEFINE(grUiWidgetTabbedPane, GTL_RTTI_INHERITS(grUiWidgetLayout));

// --- //

grUiWidgetTab::grUiWidgetTab(gnaWeakPointer<grUiWidgetTabbedPane> pane, gtl::String tabName, bool largeTab)
    : grUiWidgetText(tabName), m_pane(pane) {
    if (largeTab) {
        static gtl::PooledAString LARGE_STYLE_CLASS("LargeTab");
        add_styleClass(LARGE_STYLE_CLASS);
    }

    eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
    eventSink_focus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onFocused));
}

bool grUiWidgetTab::onMouseDown(const grUiEventMouseDown &ev) {
    set_focused(true);

    return false;
}

bool grUiWidgetTab::onFocused(const grUiEventFocus &ev) {
    m_pane->selectTab(gnaWeakPointer(this));

    return true;
}

GTL_RTTI_DEFINE(grUiWidgetTab, GTL_RTTI_INHERITS(grUiWidgetText));
