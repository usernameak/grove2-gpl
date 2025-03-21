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

#include "ColorPicker.h"

#include <grUi/Render/UiRenderer.h>

void ged::ui::ColorPickerField::draw(grUiRenderer *render) {
    grUiWidget::draw(render);

    grInsets ins = get_baseInsets();

    grRectangle rc = ins.insetDimensionToRect(get_size());

    render->drawRectf(rc.x, rc.y, rc.width, rc.height, m_color.argb);
}

grDimension ged::ui::ColorPickerField::initialMeasure(int biasedSize) {
    return { 16, 16 };
}
