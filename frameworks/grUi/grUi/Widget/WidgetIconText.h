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

#include "WidgetText.h"

class GR_UI_DLLIMPEXP grUiWidgetIconText : public grUiWidgetText {
    grUiSprite m_icon;
    bool m_highlighted = false;

public:
    GTL_RTTI_DECLARE();

    using grUiWidgetText::grUiWidgetText;

    void draw(grUiRenderer *renderer) override;
    grDimension initialMeasure(int biasedSize) override;

    void set_icon(grUiSprite icon) {
        m_icon = std::move(icon);
        set_layoutDirty(true);
    }

    const grUiSprite &get_icon() const {
        return m_icon;
    }

    grInsets get_extendedInsets(EnumInsetType type) override {
        if (type == INSET_TEXT) {
            int dw       = static_cast<int>(m_icon.dstWidth);
            grInsets ins = get_insets(INSET_BASE);
            ins.left += dw;
            if (dw > 0 && !get_text().empty()) {
                ins.left += 5;
            }
            return ins;
        } else {
            return grUiWidgetText::get_extendedInsets(type);
        }
    }

    void setIconHighlighted(bool highlighted);

    bool applyStyleProperty(const gtl::PooledAString &name, gnaWeakPointer<grUiGSSPropVal> value) override;
};
