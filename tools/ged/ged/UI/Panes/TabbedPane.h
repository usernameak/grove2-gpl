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
#include <grUi/Font/FontCache.h>
#include <gtlString/String.h>
#include <grUi/Utils/Sprite.h>

namespace ged {
    namespace ui {
        class TabWidget;
        class TabInterface;

        struct TabEvent {
            TabInterface *tab;
        };

        class TabInterface {
            bool m_tabActive;

        public:
            TabInterface() : m_tabActive(false) {}

            TabInterface(const TabInterface &) = delete;
            TabInterface(TabInterface &&)      = delete;

            TabInterface &operator=(const TabInterface &) = delete;
            TabInterface &operator=(TabInterface &&) = delete;

            virtual ~TabInterface() = default;

            gnaWeakPointer<TabWidget> m_tabWidget;

            virtual gtl::String get_tabTitle()                    = 0;
            virtual gnaPointer<grUiWidget> get_tabContentWidget() = 0;

            void tabActivate() {
                if (!m_tabActive) {
                    TabEvent actEv;
                    actEv.tab = this;
                    if (eventSink_onTabActivate.emit(actEv)) {
                        m_tabActive = true;
                    }
                }
            }

            void tabDeactivate() {
                if (m_tabActive) {
                    TabEvent deactEv;
                    deactEv.tab = this;
                    eventSink_onTabDeactivate.emit(deactEv);
                    m_tabActive = false;
                }
            }

            void tabClose() {
                tabDeactivate();

                TabEvent clsEv;
                clsEv.tab = this;
                eventSink_onTabClose.emit(clsEv);
            }

            void tabUpdateTitle() {
                TabEvent clsEv;
                clsEv.tab = this;
                eventSink_onTabUpdateTitle.emit(clsEv);
            }

            gnaEventSink<TabEvent> eventSink_onTabActivate;
            gnaEventSink<TabEvent> eventSink_onTabDeactivate;
            gnaEventSink<TabEvent> eventSink_onTabClose;
            gnaEventSink<TabEvent> eventSink_onTabUpdateTitle;
        };

        class TabButtonWidget : public grUiWidget {
            grUiSprite sprite;

            bool m_pressedDown;

        public:
            TabButtonWidget(const grUiSprite &sprite);

            virtual grDimension initialMeasure(int biasedSize) override;
            virtual void draw(grUiRenderer *) override;

            gnaEventSink<grUiEventPerformAction> eventSink_performAction;

        private:
            bool onMouseEnter(grUiEventMouseEnter &ev);
            bool onMouseLeave(grUiEventMouseLeave &ev);
            bool onMouseDown(grUiEventMouseDown &ev);
            bool onMouseUp(grUiEventMouseUp &ev);
        };

        class TabWidget : public grUiWidgetLayout {
            TabInterface *tabIfc;

        public:
            TabWidget(TabInterface *tabIfc);
            virtual ~TabWidget() override;

            gnaEventSink<TabEvent> eventSource_onTabActivate;
            gnaEventSink<TabEvent> eventSource_onTabDeactivate;

        private:
            bool onMouseDown(grUiEventMouseDown &ev);
            bool onTabActivate(TabEvent &ev);
            bool onTabDeactivate(TabEvent &ev);
            bool onTabClose(TabEvent &ev);
            bool onCloseButton(grUiEventPerformAction &ev);
            void detachTabInterface();
        };

        class TabStrip : public grUiWidgetLayout {
        public:
            TabStrip();

            void addTab(TabInterface *tabEl);

            gnaEventSink<TabEvent> eventSource_onTabActivate;
            gnaEventSink<TabEvent> eventSource_onTabDeactivate;
        };

        class TabbedPane : public grUiWidgetLayout {
            gnaPointer<TabStrip> m_tabStrip;
            gnaPointer<grUiWidget> m_currentTabWidget;

            TabInterface *m_currentTab = nullptr;

        public:
            TabbedPane();

            void addTab(TabInterface *tabEl) const {
                m_tabStrip->addTab(tabEl);
            }
        };
    }
}