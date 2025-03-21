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

#include <grUi/Layout/Layout.h>
#include <grUi/Utils/UnitSize.h>
#include <grUi/UiDLL.h>
#include <gtlString/String.h>

class GR_UI_DLLIMPEXP grUiLayoutAbsolute : public grUiLayoutManager {
    grUiUnitSizeI m_width, m_height;

public:
    GTL_RTTI_DECLARE();

    struct GR_UI_DLLIMPEXP ElementSpec : public gtlRcObject {
        GTL_RTTI_DECLARE();

        grUiUnitSizeI m_x, m_y;
        grUiUnitSizeI m_width, m_height;

        ElementSpec(grUiUnitSizeI x, grUiUnitSizeI y, grUiUnitSizeI width, grUiUnitSizeI height)
            : m_x(x), m_y(y),
              m_width(width), m_height(height) {}
    };

    grUiLayoutAbsolute(grUiUnitSizeI width, grUiUnitSizeI height);

protected:
    grDimension initialMeasure(grUiWidgetLayout *parent, int biasedSize) override;

    void layout(grUiWidgetLayout *parent) override;
};
