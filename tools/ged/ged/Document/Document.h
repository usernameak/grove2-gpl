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

#include <gtlObject/Object.h>
#include <gtlString/PooledString.h>

#include <ged/Action/ActionExecutor.h>
#include <ged/Action/UndoStack.h>
#include <gnaEventSink.h>
#include <gnaStatus.h>

namespace ged {
    class Editor;
}

namespace ged::document {
    struct EventDocumentDirtyStatusChanged {
        /**
         * New dirty status
         */
        bool newStatus;
    };

    struct EventAllEditorsClosed {
    };

    class Document : public action::ActionExecutor {
        bool m_isDirty;
        uint32_t m_numOpenEditors;

        gtl::PooledString m_path;
        gnaPointer<gtlObject> m_asset;

    public:
        /**
         * The undo stack of this document's context
         */
        action::UndoStack m_undoStack;

        explicit Document(gtl::PooledString path);
        ~Document() override = default;

        /**
         * @return the path to the document asset
         */
        const gtl::PooledString &get_path() const {
            return m_path;
        }

        /**
         * @return the path to the asset object
         */
        gnaWeakPointer<gtlObject> get_asset() const {
            return m_asset;
        }

        /**
         * Executes an (undo-able) action in this document's context
         * @param action the action to execute
         */
        void executeAction(gnaPointer<action::Action> action) override;

        /**
         * Loads the document from disk. This must be called after construction.
         * @return status of the operation
         */
        gnaStatus loadDocument();

        /**
         * Saves the document to disk.
         * @return status of the operation
         */
        gnaStatus saveDocument();

        /**
         * @return true if the document was modified since last save, false otherwise
         */
        bool get_isDirty() const {
            return m_isDirty;
        }

        /**
         * Creates a default editor instance for this document.
         * @return the editor instance
         */
        // TODO: maybe proper document associations?
        ged::Editor *createDefaultEditor();

        /**
         * @return document title, that might be displayed in UI
         */
        gtl::String get_documentTitle() const;

        /**
         * Called when an editor for this document is opened
         */
        void onEditorOpened(ged::Editor *editor);

        /**
         * Called when an editor for this document is closed
         */
        void onEditorClosed(ged::Editor *editor);

        /**
         * Event sink for isDirty state change, see also get_isDirty()
         */
        gnaEventSink<EventDocumentDirtyStatusChanged> eventSink_onDirtyStatusChanged;

        /**
         * Event sink <all editors are closed>
         */
        gnaEventSink<EventAllEditorsClosed> eventSink_onAllEditorsClosed;

    private:
        void set_isDirty(bool dirty);

        gnaStatus doLoadDocument();
        gnaStatus doSaveDocument();
    };
}
