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

#include "Background.h"

#include <grUi/Render/UiRenderer.h>

GTL_RTTI_DEFINE(grUiBackground, GTL_RTTI_INHERITS(grUiBackgroundBase));

void grUiBackground::draw(grUiRenderer *render, int x, int y, int width, int height) {
    if (m_color.getAlpha() != 0) {
        render->drawRectf((float)x,
            (float)y,
            (float)width,
            (float)height,
            m_color.argb);
    }
    if (m_sprite) {
        render->drawSprite((float)x, (float)y, m_sprite.withDstSize((float)width, (float)height));
    }
}

grDimension grUiBackground::get_dimensions() const {
    return m_sprite ? grDimension{ (int)m_sprite.dstWidth, (int)m_sprite.dstHeight }
                  : grDimension{ 0, 0 };
}

void grUiBackground::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    gtlCloneable::cloneMembers(dest, cctx);

    auto cDest = dest.cast<grUiBackground>();
    cDest->m_sprite = m_sprite;
    cDest->m_color = m_color;
}
