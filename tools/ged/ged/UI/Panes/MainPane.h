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
#include <grUi/Widget/Window/Frame.h>

#include <ged/ProjectExplorer/ProjectExplorerPane.h>
#include <ged/UI/Panes/TabbedPane.h>

namespace ged {
    class Editor;
    namespace UI {
        struct EventPopulateMenu;
    }
}

class gedMainPane : public grUiFrame {
    gnaPointer<grUiWidgetLayout> m_lwInner;

public:
    gedMainPane();

    void openEditorTab(ged::Editor *editor);

    gnaPointer<gedProjectExplorerPane> m_projectExplorerPane;

private:
    void onPopulateMenu(ged::UI::EventPopulateMenu &entry);
};

extern gnaPointer<gedMainPane> ged_gMainPane;
