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

#include "TabbedPane.h"

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/WidgetEmpty.h>
#include <grUi/Widget/WidgetText.h>
#include <grUi/Render/UiRenderer.h>

ged::ui::TabButtonWidget::TabButtonWidget(const grUiSprite &sprite) : sprite(sprite), m_pressedDown(false) {
    eventSink_mouseEnter.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseEnter));
    eventSink_mouseLeave.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseLeave));
    eventSink_mouseUp.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseUp));
    eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
}

grDimension ged::ui::TabButtonWidget::initialMeasure(int biasedSize) {
    return get_baseInsets().outsetDimension({ (int)sprite.dstWidth, (int)sprite.dstHeight });
}

void ged::ui::TabButtonWidget::draw(grUiRenderer *render) {
    grUiWidget::draw(render);

    grRectangle rc = get_baseInsets().insetDimensionToRect(get_size());

    render->drawSprite(rc.x, rc.y, sprite);
}

bool ged::ui::TabButtonWidget::onMouseEnter(grUiEventMouseEnter &ev) {
    background = gnaNew<grUiBackground>(grColor{ 0x40FFFFFF });

    return true;
}

bool ged::ui::TabButtonWidget::onMouseLeave(grUiEventMouseLeave &ev) {
    background    = gnaNew<grUiBackground>();
    m_pressedDown = false;

    return true;
}

bool ged::ui::TabButtonWidget::onMouseDown(grUiEventMouseDown &ev) {
    background    = gnaNew<grUiBackground>(grColor{ 0x40000000 });
    m_pressedDown = true;

    return false;
}

bool ged::ui::TabButtonWidget::onMouseUp(grUiEventMouseUp &ev) {
    if (m_pressedDown) {
        background    = gnaNew<grUiBackground>(grColor{ 0x40FFFFFF });
        m_pressedDown = false;

        grUiEventPerformAction ev1;
        eventSink_performAction.emit(ev1);
    }
    return true;
}

/////

ged::ui::TabWidget::TabWidget(TabInterface *tabIfc) : tabIfc(tabIfc) {
    this->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);

    set_padding({ 5 });

    auto lblTitle = gnaNew<grUiWidgetText>(tabIfc->get_tabTitle());
    add(lblTitle);

    grUiSprite sprClose = grUiSprite::createTexModalRect(GTXT("/textures/ui/engine_icons.png"), 0, 0, 16, 16, 64, 64);
    auto btnClose       = gnaNew<TabButtonWidget>(sprClose);
    add(btnClose);

    tabIfc->m_tabWidget = this;

    eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
    btnClose->eventSink_performAction.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onCloseButton));
    tabIfc->eventSink_onTabActivate.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onTabActivate), gnaEventPriority::PRIORITY_HIGHEST, this);
    tabIfc->eventSink_onTabDeactivate.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onTabDeactivate), gnaEventPriority::PRIORITY_MONITOR, this);
    tabIfc->eventSink_onTabClose.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onTabClose), gnaEventPriority::PRIORITY_MONITOR, this);
}

ged::ui::TabWidget::~TabWidget() {
    detachTabInterface();
}

bool ged::ui::TabWidget::onMouseDown(grUiEventMouseDown &ev) {
    tabIfc->tabActivate();

    return true;
}

bool ged::ui::TabWidget::onTabActivate(TabEvent &ev) {
    background = gnaNew<grUiBackground>(grColor{ 0xFF007ACC });

    eventSource_onTabActivate.emit(ev);

    return true;
}

bool ged::ui::TabWidget::onTabDeactivate(TabEvent &ev) {
    background = gnaNew<grUiBackground>();

    eventSource_onTabDeactivate.emit(ev);

    return true;
}

bool ged::ui::TabWidget::onTabClose(TabEvent &ev) {
    get_parent()->remove(this);
    detachTabInterface();

    return true;
}

bool ged::ui::TabWidget::onCloseButton(grUiEventPerformAction &ev) {
    tabIfc->tabClose();

    return true;
}

void ged::ui::TabWidget::detachTabInterface() {
    if (tabIfc) {
        tabIfc->eventSink_onTabActivate.removeHandlers(this);
        tabIfc->eventSink_onTabDeactivate.removeHandlers(this);
        tabIfc->eventSink_onTabClose.removeHandlers(this);
        tabIfc = nullptr;
    }
}

/////

ged::ui::TabStrip::TabStrip() {
    this->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);
}

void ged::ui::TabStrip::addTab(TabInterface *tabEl) {
    auto tabWidget = gnaNew<TabWidget>(tabEl);
    tabWidget->key = tabEl;
    tabWidget->eventSource_onTabActivate.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(eventSource_onTabActivate, emit));
    tabWidget->eventSource_onTabDeactivate.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(eventSource_onTabDeactivate, emit));
    add(tabWidget);
}

/////

ged::ui::TabbedPane::TabbedPane() : m_currentTabWidget(nullptr) {
    this->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);

    m_tabStrip = gnaNew<TabStrip>();
    m_tabStrip->set_layoutData(grUiLayoutLinear::ElementSpec::createMin(20));
    m_tabStrip->eventSource_onTabDeactivate.addHandler([this](auto &ev) {
        m_currentTab = nullptr;

        if (m_currentTabWidget) {
            remove(m_currentTabWidget);
            m_currentTabWidget = nullptr;
        }

        return true;
    });
    m_tabStrip->eventSource_onTabActivate.addHandler([this](auto &ev){
        if (m_currentTab == ev.tab) {
            return true;
        }

        auto contentWidget = ev.tab->get_tabContentWidget();

        if (m_currentTab) {
            m_currentTab->tabDeactivate();
        }
        m_currentTab = ev.tab;

        m_currentTabWidget = contentWidget ? contentWidget : nullptr;
        if (m_currentTabWidget) {
            m_currentTabWidget->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());
            add(m_currentTabWidget);
        }

        return true;
    });
    add(m_tabStrip);
}
