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

#include "Document.h"

#include "ged/Editor/Image/ImageEditor.h"
#include "ged/Editor/Scene/SceneEditor.h"

#include <nxfResource/Asset/AssetManager.h>

ged::document::Document::Document(gtl::PooledString path)
    : m_isDirty(false),
      m_numOpenEditors(0),
      m_path(std::move(path)) {}

gtl::String ged::document::Document::get_documentTitle() const {
    return static_cast<gtl::String>(m_path);
}

gnaStatus ged::document::Document::doLoadDocument() {
    // TODO: allow deep copies in clone context
    return gnaSingleton<nxfAssetManager>()->loadAssetAsCopy(m_path, m_asset);
}

gnaStatus ged::document::Document::doSaveDocument() {
    return gnaSingleton<nxfAssetManager>()->saveAsset(m_path, m_asset);
}

void ged::document::Document::executeAction(gnaPointer<action::Action> action) {
    m_isDirty = true;
    m_undoStack.addAndExecuteAction(action);
}

gnaStatus ged::document::Document::loadDocument() {
    gnaStatus status = doLoadDocument();
    if (status) {
        set_isDirty(false);
    }
    return status;
}

gnaStatus ged::document::Document::saveDocument() {
    gnaStatus status = doSaveDocument();
    if (status) {
        set_isDirty(false);
    }
    return status;
}

void ged::document::Document::set_isDirty(bool dirty) {
    if (dirty != m_isDirty) {
        m_isDirty = dirty;

        EventDocumentDirtyStatusChanged ev{ dirty };
        eventSink_onDirtyStatusChanged.emit(ev);
    }
}

void ged::document::Document::onEditorOpened(ged::Editor *editor) {
    m_numOpenEditors++;
}

void ged::document::Document::onEditorClosed(ged::Editor *editor) {
    if (--m_numOpenEditors <= 0) {
        EventAllEditorsClosed ev{};
        eventSink_onAllEditorsClosed.emit(ev);
    }
}

ged::Editor *ged::document::Document::createDefaultEditor() {
    if (m_asset.rttiCast2<grScene::Scene>()) {
        return gtlNew SceneEditor::SceneEditor(this);
    } else if (m_asset.rttiCast2<grImg::Image>()) {
        return gtlNew ImageEditor::ImageEditor(this);
    } else {
        return nullptr;
    }
}
