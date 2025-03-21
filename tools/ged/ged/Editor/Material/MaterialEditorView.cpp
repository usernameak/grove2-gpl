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

#include "MaterialEditorView.h"

#include <ged/Editor/Material/MaterialEditor.h>

ged::MaterialEditor::MaterialEditorView::MaterialEditorView(MaterialEditor *pEditor) : m_pEditor(pEditor) {
    background = gnaNew<grUiBackground>(grColor{ 0xff000000 });
}

void ged::MaterialEditor::MaterialEditorView::update() {
}

grRenderCore::RenderPass *ged::MaterialEditor::MaterialEditorView::get_renderPass() {
    return m_pEditor->m_renderPass;
}

ged::MaterialEditor::MaterialEditorView::~MaterialEditorView() {
    releaseLastRenderPass();
}
