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

#include "grUi/Utils/UnitSize.h"


#include <grUi/Layout/Layout.h>
#include <grUi/UiDLL.h>
#include <gtlString/String.h>
#include <gtlCollections/FixedArray.h>

class GR_UI_DLLIMPEXP grUiLayoutGrid : public grUiLayoutManager {
public:
    enum SpecialValue : int {
        VAL_DEFAULT    = -1,
        VAL_END_OF_ROW = -2
    };

    enum SizeMode {
        SIZE_MIN   = 0,
        SIZE_FIXED = 1
    };

    enum GlobalAlignmnentFlags : uint32_t {
        GA_LEFT   = 1,
        GA_RIGHT  = 2,
        GA_CENTER = GA_LEFT | GA_RIGHT,

        GA_TOP    = 4,
        GA_BOTTOM = 8,
        GA_MIDDLE = GA_TOP | GA_BOTTOM,
    };

    struct GR_UI_DLLIMPEXP ElementSpec : gtlRcObject {
        GTL_RTTI_DECLARE();

        int cellX, cellY;
        int spanX, spanY;

        ElementSpec(
            int cellX = VAL_DEFAULT, int cellY = VAL_DEFAULT,
            int spanX = 1, int spanY = 1)
            : cellX(cellX),
              cellY(cellY),
              spanX(spanX),
              spanY(spanY) {}
    };

    struct AxisConstraint {
        grUiUnitSizeI sizeConstraint = 0;
        SizeMode sizeMode            = SIZE_MIN;
        int growFactor               = 0;
        grUiUnitSizeI gapNext        = 0;

        AxisConstraint &withGrowFactor(int gf) {
            growFactor = gf;
            return *this;
        }

        AxisConstraint &withSize(SizeMode sm, int sc = 0) {
            sizeMode       = sm;
            sizeConstraint = sc;
            return *this;
        }

        AxisConstraint &withSizeConstraint(grUiUnitSizeI sc) {
            sizeConstraint = sc;
            return *this;
        }

        AxisConstraint &withGapNext(int gap) {
            gapNext = gap;
            return *this;
        }
    };

private:
    int m_columns, m_rows;
    uint32_t m_alignment;

    AxisConstraint *m_columnConstraints;
    int m_numColumnConstraints;

    AxisConstraint *m_rowConstraints;
    int m_numRowConstraints;

    struct PrepassData {
        struct AxisMetric {
            int size     = 0;
            int gapAfter = 0;
        };

        int totalColumns;
        int totalRows;
        AxisMetric *columnMetrics;
        AxisMetric *rowMetrics;

        size_t numChildren;
        struct ChildInfo {
            gnaWeakPointer<grUiWidget> widget;
            int column, row;
            int colspan, rowspan;
        } *childInfos;

        int totalFixedWidth, totalFixedHeight;
    };

    void prepass(grUiWidgetLayout *parent, PrepassData &data) const;

public:
    GTL_RTTI_DECLARE();

    grUiLayoutGrid(
        std::initializer_list<AxisConstraint> columnConstraints = {},
        std::initializer_list<AxisConstraint> rowConstraints    = {},
        int columns                                             = VAL_DEFAULT,
        int rows                                                = VAL_DEFAULT,
        uint32_t alignment                                      = GA_CENTER | GA_MIDDLE);

    grUiLayoutGrid(
        gtlFixedArrayView<AxisConstraint> columnConstraints,
        gtlFixedArrayView<AxisConstraint> rowConstraints,
        int columns        = VAL_DEFAULT,
        int rows           = VAL_DEFAULT,
        uint32_t alignment = GA_CENTER | GA_MIDDLE);

    ~grUiLayoutGrid() override;

protected:
    grDimension initialMeasure(grUiWidgetLayout *parent, int biasedSize) override;

    void layout(grUiWidgetLayout *parent) override;
};
