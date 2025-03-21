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
#include <grUi/UiDLL.h>
#include <gtlString/String.h>

#include <grUi/Utils/UnitSize.h>

class GR_UI_DLLIMPEXP grUiLayoutOverlay : public grUiLayoutManager {
public:
    GTL_RTTI_DECLARE();

    struct GR_UI_DLLIMPEXP ElementSpec : gtlRcObject {
        GTL_RTTI_DECLARE();

        static constexpr float FILL_PARENT = -1.0f;

        float relativePositionX;
        float relativePositionY;

        grUiUnitSizeI offsetX;
        grUiUnitSizeI offsetY;

        ElementSpec(float relativePositionX = FILL_PARENT,
            float relativePositionY         = FILL_PARENT,
            grUiUnitSizeI offsetX           = 0,
            grUiUnitSizeI offsetY           = 0)
            : relativePositionX(relativePositionX),
              relativePositionY(relativePositionY),
              offsetX(offsetX),
              offsetY(offsetY) {}
    };

protected:
    grDimension initialMeasure(grUiWidgetLayout *parent, int biasedSize) override;

    void layout(grUiWidgetLayout *parent) override;
};
