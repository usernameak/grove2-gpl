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
#include "LayoutEnums.h"

class GR_UI_DLLIMPEXP grUiLayoutLinear : public grUiLayoutManager {
public:
    enum Axis {
        AXIS_X = 0,
        AXIS_Y = 1
    };

    enum SizeMode {
        SIZEMODE_MIN    = 0,
        SIZEMODE_FIXED  = 1,
        SIZEMODE_GROW   = 2,
        SIZEMODE_SQUARE = 3
    };

    enum SecondaryAlignment {
        SA_FILL   = 0,
        SA_START  = 1,
        SA_MIDDLE = 2,
        SA_END    = 3
    };

    struct GR_UI_DLLIMPEXP ElementSpec : gtlRcObject {
        GTL_RTTI_DECLARE();

        SizeMode sizeMode;
        int sizeModeParam; // size or weight
        grUiUnitSizeI minSecondarySize;
        SecondaryAlignment secondaryAlignment;

        static gnaPointer<ElementSpec> createMin(int size = 0, SecondaryAlignment sa = SA_FILL) {
            auto spec                = gnaNew<ElementSpec>();
            spec->sizeMode           = SIZEMODE_MIN;
            spec->sizeModeParam      = size;
            spec->minSecondarySize   = 0;
            spec->secondaryAlignment = sa;
            return spec;
        }

        static gnaPointer<ElementSpec> createFixed(int size, SecondaryAlignment sa = SA_FILL) {
            auto spec                = gnaNew<ElementSpec>();
            spec->sizeMode           = SIZEMODE_FIXED;
            spec->sizeModeParam      = size;
            spec->minSecondarySize   = 0;
            spec->secondaryAlignment = sa;
            return spec;
        }

        static gnaPointer<ElementSpec> createGrow(int weight = 100, SecondaryAlignment sa = SA_FILL) {
            auto spec                = gnaNew<ElementSpec>();
            spec->sizeMode           = SIZEMODE_GROW;
            spec->sizeModeParam      = weight;
            spec->minSecondarySize   = 0;
            spec->secondaryAlignment = sa;
            return spec;
        }

        static gnaPointer<ElementSpec> createSquare(SecondaryAlignment sa = SA_FILL) {
            auto spec                = gnaNew<ElementSpec>();
            spec->sizeMode           = SIZEMODE_SQUARE;
            spec->sizeModeParam      = 0;
            spec->minSecondarySize   = 0;
            spec->secondaryAlignment = sa;
            return spec;
        }
    };

private:
    Axis primaryAxis;
    grUiUnitSizeI gap;

    struct Pass0Data;

    void pass(grUiWidgetLayout *parent, int biasedSize, int passIndex, Pass0Data &p0d) const;
    void doLayout(grUiWidgetLayout *parent, int passIndex) const;

protected:
    uint32_t get_flags() override;
    grUiEnumContentBias get_contentBias(grUiWidgetLayout *parent) override;

public:
    GTL_RTTI_DECLARE();

    explicit grUiLayoutLinear(Axis primaryAxis) : primaryAxis(primaryAxis), gap(0) {}
    grUiLayoutLinear(Axis primaryAxis, grUiUnitSizeI gap) : primaryAxis(primaryAxis), gap(gap) {}

protected:
    grDimension initialMeasure(grUiWidgetLayout *parent, int biasedSize) override;

    void layout(grUiWidgetLayout *parent) override {
        doLayout(parent, 1);
    }

public:
    gnaPointer<gtlRcObject> createLayoutDataFromString(const gtl::AString &string) const override;
};
