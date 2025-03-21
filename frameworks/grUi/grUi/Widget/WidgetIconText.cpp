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

#include "WidgetIconText.h"

#include <grUi/Style/GSS/Props/Icon.h>

GTL_RTTI_DEFINE(grUiWidgetIconText, GTL_RTTI_INHERITS(grUiWidgetText));

grDimension grUiWidgetIconText::initialMeasure(int biasedSize) {
    grDimension dim  = get_insets(INSET_BASE).outsetDimension({ (int)m_icon.dstWidth, (int)m_icon.dstHeight });
    if (get_text().empty()) {
        return dim;
    }
    grDimension tdim = grUiWidgetText::initialMeasure(biasedSize);
    return { tdim.width, std::max(dim.height, tdim.height) };
}

void grUiWidgetIconText::draw(grUiRenderer *render) {
    grUiWidgetText::draw(render);

    grRectangle rc = get_insets(INSET_BASE).insetDimensionToRect(get_size());

    if (m_icon) {
        auto tint = m_highlighted ? 0xFFFFF569 : 0xFFFFFFFF;
        if (get_text().empty()) {
            render->drawSprite(
                    rc.x + std::floor((rc.width - m_icon.dstWidth) / 2),
                    rc.y + std::floor((rc.height - m_icon.dstHeight) / 2),
                    m_icon, tint);
        } else {
            render->drawSprite(rc.x, rc.y + std::floor((rc.height - m_icon.dstHeight) / 2), m_icon, tint);
        }
    }
}

bool grUiWidgetIconText::applyStyleProperty(const gtl::PooledAString &name, gnaWeakPointer<grUiGSSPropVal> value) {
    bool superResult = grUiWidgetText::applyStyleProperty(name, value);

    static gtl::PooledAString NAME_ICON("-gr-icon");
    if (name == NAME_ICON) {
        set_icon(value.cast<grUiGSSIconPropVal>()->icon);
    } else {
        return superResult;
    }

    return true;
}

void grUiWidgetIconText::setIconHighlighted(bool highlighted) {
    m_highlighted = highlighted;
}
