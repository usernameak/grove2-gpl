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

#include "ImageEditor.h"

#include "ImageEditorPane.h"

ged::ImageEditor::ImageEditor::ImageEditor(document::Document *document)
    : Editor(document),
      m_editedImage(document->get_asset().rttiCast2<grImg::Image>()) {

    assert(m_editedImage);

    m_imageEditorPane = gnaNew<ImageEditorPane>(this);
}

ged::ImageEditor::ImageEditor::~ImageEditor() = default;

gnaPointer<grUiWidget> ged::ImageEditor::ImageEditor::get_tabContentWidget() {
    return m_imageEditorPane;
}
