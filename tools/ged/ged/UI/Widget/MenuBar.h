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
#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Font/FontCache.h>

class grUiDropDownMenu;

namespace ged {
    namespace UI {
        class MenuBarEntry : public grUiWidget {
            gtl::String label;
            grUiFontKey font = { GTXT("Default"), GR_UI_DEFAULT_FONT_SIZE };

        public:
            MenuBarEntry(const gtl::String &label);

            grDimension initialMeasure(int biasedSize) override;
            void draw(grUiRenderer *) override;

            gnaEventSink<grUiEventPerformAction> eventSink_performAction;

            void displayDropDownMenu(gnaWeakPointer<grUiDropDownMenu> menu);

        private:
            bool onMouseDown(const grUiEventMouseDown &ev);
        };

        struct EventPopulateMenu {
            std::vector<gnaPointer<MenuBarEntry>> entries;
        };

        class MenuBar : public grUiWidgetLayout {
        public:
            MenuBar();

            gnaEventSink<EventPopulateMenu> eventSink_populateMenu;

            void updateMenus();
        };
    }
}