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

#include "MainPane.h"

#include <ged/ProjectExplorer/ProjectExplorerPane.h>
#include <ged/UI/Widget/MenuBar.h>
#include <ged/UI/Window/DataFilesPane.h>
#include <ged/UI/Window/EngineAboutWindow.h>
#include <ged/Editor/Editor.h>

#include <grApplication.h>

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/DropDownMenu.h>
#include <grUi/Widget/Window/WindowManager.h>
#include <grUi/Widget/Window/RootWindowManager.h>
#include <grGitRevision/Revision.h>

gnaPointer<gedMainPane> ged_gMainPane = nullptr;

gedMainPane::gedMainPane() : grUiFrame() {
    set_title(GTXT("GEd " GR_GIT_REVISION));

    set_bounds(0, 0, 300, 768);

    auto lwMain        = gnaNew<grUiWidgetLayout>();
    lwMain->background = gnaNew<grUiBackground>(0xFF2D2D30_grColor);
    lwMain->layout     = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);

    {
        auto menuBar = gnaNew<ged::UI::MenuBar>();
        menuBar->eventSink_populateMenu.addHandlerV(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onPopulateMenu));
        menuBar->updateMenus();

        lwMain->add(menuBar);
    }

    m_lwInner = gnaNew<grUiWidgetLayout>();
    {
        m_lwInner->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);

        m_projectExplorerPane = gnaNew<gedProjectExplorerPane>();
        m_projectExplorerPane->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());
        m_lwInner->add(m_projectExplorerPane);
    }
    m_lwInner->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());
    lwMain->add(m_lwInner);

    set_contentWidget(lwMain);

    eventSink_windowClose.addHandler([](auto &ev) {
        gr_gApplication->exitApplication();
        return true;
    });
}

void gedMainPane::openEditorTab(ged::Editor *editor) {
    editor->tabActivate();
    auto frame = editor->get_editorFrame();
    frame->eventSink_windowClose.addHandler([this, editor](auto &ev) {
        editor->tabClose();

        gtlDelete editor;

        return true;
    });
    grUi_gRootWindowManager->add(frame);
}

void gedMainPane::onPopulateMenu(ged::UI::EventPopulateMenu &entry) {
    auto eFile = gnaNew<ged::UI::MenuBarEntry>(GTXT("File"));
    eFile->eventSink_performAction.addHandler([this, eFile](auto &ev) {
        auto dropDownMenu = gnaNew<grUi::DropDownMenu>();

        auto eDataFiles = gnaNew<grUi::DropDownMenuEntry>(GTXT("Data Files..."));
        eDataFiles->eventSink_performAction.addHandler([this](auto &ev) {
            auto dataFilesPane = gnaNew<gedDataFilesPane>();
            dataFilesPane->set_focused(true);

            grUi_gRootWindowManager->add(dataFilesPane);

            grUiWindowLayoutData::pack(dataFilesPane, { 300, 0 });
            grUiWindowLayoutData::center(dataFilesPane, grUi_gRootWindowManager);
            return true;
        });
        dropDownMenu->add(eDataFiles);

        auto eExit = gnaNew<grUi::DropDownMenuEntry>(GTXT("Exit"));
        eExit->eventSink_performAction.addHandler([this](auto &ev) {
            gr_gApplication->exitApplication();
            return true;
        });
        dropDownMenu->add(eExit);

        eFile->displayDropDownMenu(dropDownMenu);

        return true;
    });
    entry.entries.push_back(eFile);

    auto eHelp = gnaNew<ged::UI::MenuBarEntry>(GTXT("Help"));
    eHelp->eventSink_performAction.addHandler([this, eHelp](auto &ev) {
        auto dropDownMenu = gnaNew<grUi::DropDownMenu>();

        auto eAbout = gnaNew<grUi::DropDownMenuEntry>(GTXT("About..."));
        eAbout->eventSink_performAction.addHandler([this](auto &ev) {
            auto frame = gnaNew<gedEngineAboutWindow>();
            frame->set_focused(true);
            grUi_gRootWindowManager->add(frame);
            grUiWindowLayoutData::pack(frame);
            grUiWindowLayoutData::center(frame, grUi_gRootWindowManager);
            return true;
        });
        dropDownMenu->add(eAbout);

        eHelp->displayDropDownMenu(dropDownMenu);

        return true;
    });
    entry.entries.push_back(eHelp);
}
