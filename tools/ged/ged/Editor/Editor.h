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


#include <gtlMemory/RcObject.h>
#include <gtlUtil/Singleton.h>

#include <grUi/Widget/Window/Frame.h>
#include <grUi/Widget/WidgetScrollPane.h>

#include <ged/Action/ActionExecutor.h>
#include <ged/Document/Document.h>
#include <ged/UI/Panes/TabbedPane.h>
#include <ged/UI/Widget/MenuBar.h>

namespace ged {
    class Editor : public ui::TabInterface, public action::ActionExecutor {
        gnaPointer<grUiFrame> m_editorFrame;

        gnaPointer<grUiWidgetScrollPane> m_propertyListScroll;

    public:
        document::Document *const m_document;

        explicit Editor(document::Document *document);
        ~Editor() override;

        void initializeEditor();

        void executeAction(gnaPointer<action::Action> action) override;
        gtl::String get_tabTitle() override;

        void save();

        gnaWeakPointer<grUiFrame> get_editorFrame() const {
            return m_editorFrame;
        }

        virtual void selectObject(gnaWeakPointer<gtlObject> obj);

    protected:
        virtual void doInitializeEditor();
        virtual void onPopulateMenu(UI::EventPopulateMenu &entry);

    private:
        gnaPointer<grUiFrame> createEditorFrame();
    };

    class EditorManager {
        std::vector<ged::document::Document *> m_openDocuments;

    public:
        ~EditorManager();

        void openEditor(ged::Editor *editor);

        void openDocument(ged::document::Document *document);
    };
}

GNA_SINGLETON_DECLARE(ged::EditorManager);
