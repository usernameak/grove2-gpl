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

#include "Border.h"

#include <grUi/Render/UiRenderer.h>
#include <grUi/Widget/Widget.h>

GTL_RTTI_DEFINE(grUiBorder, GTL_RTTI_INHERITS(grUiBorderBase));

grUiBorder::grUiBorder()
    : borderSize(0),
      color(grColor::C_TRANSPARENT) {
}

grUiBorder::grUiBorder(grUiUnitSizeI borderSize, grColor color)
    : borderSize(borderSize),
      color(color) {
}

void grUiBorder::draw(gnaWeakPointer<grUiWidget> widget, grUiRenderer *render, int x, int y, int width, int height) {
    if (color.getAlpha() != 0 && borderSize.value != 0) {
        int pxSize = borderSize.toPixels(widget->get_metricContext());
        render->drawRectf(x, y, pxSize, height, color.argb);
        render->drawRectf(x + width - pxSize, y, pxSize, height, color.argb);

        render->drawRectf(x + pxSize, y, width - 2 * pxSize, pxSize, color.argb);
        render->drawRectf(x + pxSize, y + height - pxSize, width - 2 * pxSize, pxSize, color.argb);
    }
}
