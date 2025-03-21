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

#include "Editor.h"

#include "ged/ObjEditor/ObjEditor.h"

#include <ged/UI/Panes/MainPane.h>
#include <ged/UI/Widget/MenuBar.h>
#include <ged/UI/Window/ErrorWindow.h>

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/Window/RootWindowManager.h>

ged::Editor::Editor(document::Document *document)
    : m_document(document) {

    // this probably is bad
    m_document->onEditorOpened(this);
    eventSink_onTabClose.addHandlerV([this](auto &ev) {
        m_document->onEditorClosed(this);
    });
}

ged::Editor::~Editor() = default;

void ged::Editor::initializeEditor() {
    doInitializeEditor();

    m_editorFrame = createEditorFrame();

    selectObject(m_document->get_asset());
}

void ged::Editor::doInitializeEditor() {
}

void ged::Editor::save() {
    gnaStatus status = m_document->saveDocument();

    if (!status) {
        auto dialog = gnaNew<gedErrorWindow>(status.get_errorMessage());
        grUi_gRootWindowManager->displayCenteredDialog(dialog);
    }
}

gtl::String ged::Editor::get_tabTitle() {
    return m_document->get_documentTitle();
}

void ged::Editor::executeAction(gnaPointer<action::Action> action) {
    m_document->m_undoStack.addAndExecuteAction(action);
}

ged::EditorManager::~EditorManager() {
    for (auto *document : m_openDocuments) {
        delete document;
    }
}

void ged::EditorManager::openEditor(Editor *editor) {
    editor->initializeEditor();
    ged_gMainPane->openEditorTab(editor);
}

void ged::EditorManager::openDocument(document::Document *document) {
    document->eventSink_onAllEditorsClosed.addHandlerV([this, document](auto &ev) {
        GR_INFO(GTXT("Closing an open document %ls"), document->get_documentTitle().toCString());

        std::erase(m_openDocuments, document);
        delete document;
    });

    if (gnaStatus status = document->loadDocument()) {
        m_openDocuments.push_back(document);

        openEditor(document->createDefaultEditor());
    } else {
        delete document;

        auto dialog = gnaNew<gedErrorWindow>(status.get_errorMessage());
        dialog->displayPopup(grUi_gRootWindowManager);
    }
}

void ged::Editor::onPopulateMenu(UI::EventPopulateMenu &entry) {
    auto eFile = gnaNew<ged::UI::MenuBarEntry>(GTXT("File"));
    eFile->eventSink_performAction.addHandlerV([this, eFile](auto &) {
        auto dropDownMenu = gnaNew<grUi::DropDownMenu>();

        auto eSave = gnaNew<grUi::DropDownMenuEntry>(GTXT("Save Document"));
        eSave->eventSink_performAction.addHandlerV([this](auto &) {
            save();
        });
        dropDownMenu->add(eSave);

        eFile->displayDropDownMenu(dropDownMenu);
    });
    entry.entries.push_back(eFile);

    auto eEdit = gnaNew<ged::UI::MenuBarEntry>(GTXT("Edit"));
    eEdit->eventSink_performAction.addHandlerV([this, eEdit](auto &) {
        auto dropDownMenu = gnaNew<grUi::DropDownMenu>();

        auto eUndo = gnaNew<grUi::DropDownMenuEntry>(GTXT("Undo"));
        eUndo->eventSink_performAction.addHandlerV([this](auto &) {
            m_document->m_undoStack.undo();
        });
        dropDownMenu->add(eUndo);

        auto eRedo = gnaNew<grUi::DropDownMenuEntry>(GTXT("Redo"));
        eRedo->eventSink_performAction.addHandlerV([this](auto &) {
            m_document->m_undoStack.redo();
        });
        dropDownMenu->add(eRedo);

        eEdit->displayDropDownMenu(dropDownMenu);
    });
    entry.entries.push_back(eEdit);
}

gnaPointer<grUiFrame> ged::Editor::createEditorFrame() {
    auto frame = gnaNew<grUiFrame>();
    frame->set_title(GTXT("GEd - ") + get_tabTitle());
    frame->set_focused(true);
    frame->set_bounds({ 0, 0, 1024, 768 });

    auto frameLayout        = gnaNew<grUiWidgetLayout>(gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y));
    frameLayout->background = gnaNew<grUiBackground>(0xFF2D2D30_grColor);

    auto menuBar = gnaNew<UI::MenuBar>();
    menuBar->eventSink_populateMenu.addHandlerV(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onPopulateMenu));
    menuBar->updateMenus();
    frameLayout->add(menuBar);

    auto subLayout    = gnaNew<grUiWidgetLayout>();
    subLayout->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);

    if (auto content = get_tabContentWidget()) {
        subLayout->add(std::move(content), grUiLayoutLinear::ElementSpec::createGrow());
    }

    m_propertyListScroll = gnaNew<grUiWidgetScrollPane>();
    m_propertyListScroll->set_layoutData(grUiLayoutLinear::ElementSpec::createFixed(300));
    subLayout->add(m_propertyListScroll);

    frameLayout->add(std::move(subLayout), grUiLayoutLinear::ElementSpec::createGrow());

    frame->set_contentWidget(frameLayout);

    return frame;
}

void ged::Editor::selectObject(gnaWeakPointer<gtlObject> obj) {
    if (obj) {
        auto factory = gnaSingleton<ObjEditorRegistry>()->findEditor(obj->get_rtti());
        if (factory) {
            auto container = gnaNew<grUiWidgetLayout>(gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y));
            container->add_styleClass("GED_PropertyListInner");
            factory->populatePropertyGui(this, &*obj, container);
            m_propertyListScroll->set_contentWidget(container);
        } else {
            m_propertyListScroll->set_contentWidget(nullptr);
        }
    } else {
        m_propertyListScroll->set_contentWidget(nullptr);
    }
}

GNA_SINGLETON_IMPLEMENT(ged::EditorManager);
