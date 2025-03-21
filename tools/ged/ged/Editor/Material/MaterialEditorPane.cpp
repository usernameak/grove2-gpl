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

#include "MaterialEditorPane.h"

#include <ged/ObjEditor/ObjEditor.h>
#include <grUi/Layout/LayoutLinear.h>
#include <utility>

using namespace ged::MaterialEditor;

MaterialEditorPane::MaterialEditorPane(MaterialEditor *pEditor) : m_pEditor(std::move(pEditor)) {
    layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);

    m_materialEditorView = gnaNew<MaterialEditorView>(m_pEditor);
    m_materialEditorView->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());
    add(m_materialEditorView);
}

MaterialEditorPane::~MaterialEditorPane() = default;
