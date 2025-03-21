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

#include "LayoutGrid.h"

#include <grUi/Widget/WidgetLayout.h>

GTL_RTTI_DEFINE(grUiLayoutGrid, GTL_RTTI_INHERITS(grUiLayoutManager));
GTL_RTTI_DEFINE(grUiLayoutGrid::ElementSpec, GTL_RTTI_INHERITS(gtlRcObject));

static auto defaultLayoutData     = gnaNew<grUiLayoutGrid::ElementSpec>();
static auto defaultAxisConstraint = grUiLayoutGrid::AxisConstraint();

grUiLayoutGrid::grUiLayoutGrid(
    std::initializer_list<AxisConstraint> columnConstraints,
    std::initializer_list<AxisConstraint> rowConstraints,
    int columns,
    int rows,
    uint32_t alignment)
    : m_columns(columns),
      m_rows(rows),
      m_alignment(alignment) {
    m_numColumnConstraints = (int)columnConstraints.size();
    m_numRowConstraints    = (int)rowConstraints.size();

    m_columnConstraints = gtlNew AxisConstraint[m_numColumnConstraints];
    m_rowConstraints    = gtlNew AxisConstraint[m_numRowConstraints];

    std::copy(columnConstraints.begin(), columnConstraints.end(), m_columnConstraints);
    std::copy(rowConstraints.begin(), rowConstraints.end(), m_rowConstraints);
}

grUiLayoutGrid::grUiLayoutGrid(
    gtlFixedArrayView<AxisConstraint> columnConstraints,
    gtlFixedArrayView<AxisConstraint> rowConstraints,
    int columns, int rows,
    uint32_t alignment)
    : m_columns(columns),
      m_rows(rows),
      m_alignment(alignment),
      m_numColumnConstraints((int)columnConstraints.size()),
      m_numRowConstraints((int)rowConstraints.size()) {
    m_columnConstraints = gtlNew AxisConstraint[m_numColumnConstraints];
    m_rowConstraints    = gtlNew AxisConstraint[m_numRowConstraints];

    std::copy(columnConstraints.begin(), columnConstraints.end(), m_columnConstraints);
    std::copy(rowConstraints.begin(), rowConstraints.end(), m_rowConstraints);
}

grUiLayoutGrid::~grUiLayoutGrid() {
    gtlDeleteArray m_columnConstraints;
    gtlDeleteArray m_rowConstraints;
}

static grUiLayoutGrid::AxisConstraint &lookupConstraint(int index, grUiLayoutGrid::AxisConstraint *constraints, int size) {
    int constraintIdx = index;
    if (constraintIdx >= size) {
        if (size == 0) {
            constraintIdx = -1;
        } else {
            constraintIdx = size - 1;
        }
    }
    return constraintIdx == -1 ? defaultAxisConstraint : constraints[constraintIdx];
}

void grUiLayoutGrid::prepass(grUiWidgetLayout *parent, grUiLayoutGrid::PrepassData &data) const {
    grUiMetricContext metricContext = parent->get_metricContext();

    data.totalColumns = m_columns < 0 ? 0 : m_columns;
    data.totalRows    = m_rows < 0 ? 0 : m_rows;

    data.numChildren = parent->numChildren();
    data.childInfos  = gtlNew PrepassData::ChildInfo[data.numChildren];
    int currentCol = 0, currentRow = 0;
    int index = 0;
    for (gnaWeakPointer<grUiWidget> child : *parent) {
        auto layoutData = child->get_layoutData().rttiCast2<ElementSpec>();
        if (!layoutData) layoutData = defaultLayoutData;

        int column = layoutData->cellX;
        int row    = layoutData->cellY;
        if (column == VAL_DEFAULT || column == VAL_END_OF_ROW) {
            column = currentCol;
        }

        if (row == VAL_DEFAULT) {
            row = currentRow;
        }

        data.childInfos[index].widget  = child;
        data.childInfos[index].column  = column;
        data.childInfos[index].row     = row;
        data.childInfos[index].colspan = layoutData->spanX;
        data.childInfos[index].rowspan = layoutData->spanY;

        if (child->get_visibility() != grUiWidget::VISIBILITY_GONE) {
            if (column + layoutData->spanX > data.totalColumns) {
                data.totalColumns = column + layoutData->spanX;
            }
            if (row + layoutData->spanY >= data.totalRows) {
                data.totalRows = row + layoutData->spanY;
            }
            currentCol = column + layoutData->spanX;
            currentRow = row;

            if (layoutData->cellX == VAL_END_OF_ROW) {
                currentCol = 0;
                currentRow++;
            }

            if (m_columns >= 0) {
                if (currentCol >= m_columns) {
                    currentCol = 0;
                    currentRow++;
                }
            }
        }

        index++;
    }

    data.columnMetrics = gtlNew PrepassData::AxisMetric[data.totalColumns]{};
    data.rowMetrics    = gtlNew PrepassData::AxisMetric[data.totalRows]{};

    for (int i = 0; i < data.totalColumns; i++) {
        const auto &cons = lookupConstraint(i, m_columnConstraints, m_numColumnConstraints);

        if (cons.sizeMode == SIZE_FIXED || cons.sizeMode == SIZE_MIN) {
            data.columnMetrics[i].size = cons.sizeConstraint.toPixels(metricContext);
        }
        data.columnMetrics[i].gapAfter = cons.gapNext.toPixels(metricContext);
    }

    for (int i = 0; i < data.totalRows; i++) {
        const auto &cons = lookupConstraint(i, m_rowConstraints, m_numRowConstraints);

        if (cons.sizeMode == SIZE_FIXED || cons.sizeMode == SIZE_MIN) {
            data.rowMetrics[i].size = cons.sizeConstraint.toPixels(metricContext);
        }
        data.rowMetrics[i].gapAfter = cons.gapNext.toPixels(metricContext);
    }

    for (size_t i = 0; i < data.numChildren; i++) {
        PrepassData::ChildInfo &ci = data.childInfos[i];

        const auto &ccons = lookupConstraint(ci.column, m_columnConstraints, m_numColumnConstraints);
        const auto &rcons = lookupConstraint(ci.row, m_rowConstraints, m_numRowConstraints);

        if (ccons.sizeMode == SIZE_FIXED && rcons.sizeMode == SIZE_FIXED) continue;
        if (ci.widget->get_visibility() == grUiWidget::VISIBILITY_GONE) continue;

        grDimension childDim = ci.widget->measure();

        if (ccons.sizeMode != SIZE_FIXED && ci.colspan == 1) {
            if (childDim.width > data.columnMetrics[ci.column].size) {
                data.columnMetrics[ci.column].size = childDim.width;
            }
        }
        if (rcons.sizeMode != SIZE_FIXED && ci.rowspan == 1) {
            if (childDim.height > data.rowMetrics[ci.row].size) {
                data.rowMetrics[ci.row].size = childDim.height;
            }
        }
    }

    for (int i = 0; i < data.totalColumns; i++) {
        data.totalFixedWidth += data.columnMetrics[i].size;
        if (i != data.totalColumns - 1) {
            data.totalFixedWidth += data.columnMetrics[i].gapAfter;
        }
    }

    for (int i = 0; i < data.totalRows; i++) {
        data.totalFixedHeight += data.rowMetrics[i].size;
        if (i != data.totalRows - 1) {
            data.totalFixedHeight += data.rowMetrics[i].gapAfter;
        }
    }
}

grDimension grUiLayoutGrid::initialMeasure(grUiWidgetLayout *parent, int biasedSize) {
    PrepassData data{};
    prepass(parent, data);

    gtlDeleteArray data.columnMetrics;
    gtlDeleteArray data.rowMetrics;
    gtlDeleteArray data.childInfos;

    return parent->get_baseInsets().outsetDimension({ data.totalFixedWidth, data.totalFixedHeight });
}

void grUiLayoutGrid::layout(grUiWidgetLayout *parent) {
    PrepassData data{};
    prepass(parent, data);

    grInsets insets = parent->get_baseInsets();

    grDimension apparentInsetSize = parent->get_size();
    apparentInsetSize.width -= insets.left + insets.right;
    apparentInsetSize.height -= insets.top + insets.bottom;

    int remainingWidth  = apparentInsetSize.width - data.totalFixedWidth;
    int remainingHeight = apparentInsetSize.height - data.totalFixedHeight;

    int totalColumnGrowFactor = 0;
    int totalGrowingWidth     = remainingWidth;
    int totalRowGrowFactor    = 0;
    int totalGrowingHeight    = remainingHeight;

    for (int i = 0; i < data.totalColumns; i++) {
        const auto &cons = lookupConstraint(i, m_columnConstraints, m_numColumnConstraints);

        totalColumnGrowFactor += cons.growFactor;
        if (cons.growFactor != 0) {
            totalGrowingWidth += data.columnMetrics[i].size;
        }
    }

    for (int i = 0; i < data.totalRows; i++) {
        const auto &cons = lookupConstraint(i, m_rowConstraints, m_numRowConstraints);

        totalRowGrowFactor += cons.growFactor;
        if (cons.growFactor != 0) {
            totalGrowingHeight += data.rowMetrics[i].size;
        }
    }

    int curColOffset = 0;
    int curRowOffset = 0;

    if (totalColumnGrowFactor != 0) {
        int *tempSizes = gtlNew int[data.totalColumns];

        for (int i = 0; i < data.totalColumns; i++) {
            const auto &cons = lookupConstraint(i, m_columnConstraints, m_numColumnConstraints);
            if (cons.growFactor != 0) {
                tempSizes[i] = totalGrowingWidth * cons.growFactor / totalColumnGrowFactor;
            }
        }

        uint32_t shrinkValue           = 0;
        uint32_t numShrinkableElements = 0;
        for (int i = 0; i < data.totalColumns; i++) {
            const auto &cons = lookupConstraint(i, m_columnConstraints, m_numColumnConstraints);
            if (cons.growFactor != 0) {
                if (data.columnMetrics[i].size > tempSizes[i]) {
                    shrinkValue += data.columnMetrics[i].size - tempSizes[i];
                } else {
                    numShrinkableElements++;
                }
            }
        }

        for (int i = 0; i < data.totalColumns; i++) {
            const auto &cons = lookupConstraint(i, m_columnConstraints, m_numColumnConstraints);
            if (cons.growFactor != 0) {
                if (data.columnMetrics[i].size <= tempSizes[i]) {
                    int growValue = tempSizes[i] - data.columnMetrics[i].size - shrinkValue / numShrinkableElements;

                    data.columnMetrics[i].size += growValue;
                }
            }
        }

        gtlDeleteArray tempSizes;
    } else if ((m_alignment & GA_CENTER) == GA_CENTER) {
        curColOffset = (apparentInsetSize.width - data.totalFixedWidth) / 2;
    } else if ((m_alignment & GA_LEFT) == GA_LEFT) {
        curColOffset = 0;
    } else if ((m_alignment & GA_RIGHT) == GA_RIGHT) {
        curColOffset = apparentInsetSize.width - data.totalFixedWidth;
    }

    if (totalRowGrowFactor != 0) {
        int *tempSizes = gtlNew int[data.totalRows];

        for (int i = 0; i < data.totalRows; i++) {
            const auto &cons = lookupConstraint(i, m_rowConstraints, m_numRowConstraints);
            if (cons.growFactor != 0) {
                tempSizes[i] = totalGrowingHeight * cons.growFactor / totalRowGrowFactor;
            }
        }

        uint32_t shrinkValue           = 0;
        uint32_t numShrinkableElements = 0;
        for (int i = 0; i < data.totalRows; i++) {
            const auto &cons = lookupConstraint(i, m_rowConstraints, m_numRowConstraints);
            if (cons.growFactor != 0) {
                if (data.rowMetrics[i].size > tempSizes[i]) {
                    shrinkValue += data.rowMetrics[i].size - tempSizes[i];
                } else {
                    numShrinkableElements++;
                }
            }
        }

        for (int i = 0; i < data.totalRows; i++) {
            const auto &cons = lookupConstraint(i, m_rowConstraints, m_numRowConstraints);
            if (cons.growFactor != 0) {
                if (data.rowMetrics[i].size <= tempSizes[i]) {
                    int growValue = tempSizes[i] - data.rowMetrics[i].size - shrinkValue / numShrinkableElements;

                    data.rowMetrics[i].size += growValue;
                }
            }
        }

        gtlDeleteArray tempSizes;
    } else if ((m_alignment & GA_MIDDLE) == GA_MIDDLE) {
        curRowOffset = (apparentInsetSize.height - data.totalFixedHeight) / 2;
    } else if ((m_alignment & GA_TOP) == GA_TOP) {
        curRowOffset = 0;
    } else if ((m_alignment & GA_BOTTOM) == GA_BOTTOM) {
        curRowOffset = apparentInsetSize.height - data.totalFixedHeight;
    }

    int *columnOffsets = gtlNew int[data.totalColumns]{};
    int *rowOffsets    = gtlNew int[data.totalRows]{};

    for (int i = 0; i < data.totalColumns; i++) {
        columnOffsets[i] = curColOffset;
        curColOffset += data.columnMetrics[i].size;
        if (i != data.totalColumns - 1) {
            curColOffset += data.columnMetrics[i].gapAfter;
        }
    }
    for (int i = 0; i < data.totalRows; i++) {
        rowOffsets[i] = curRowOffset;
        curRowOffset += data.rowMetrics[i].size;
        if (i != data.totalRows - 1) {
            curRowOffset += data.rowMetrics[i].gapAfter;
        }
    }

    for (size_t i = 0; i < data.numChildren; i++) {
        PrepassData::ChildInfo &ci = data.childInfos[i];

        int x      = columnOffsets[ci.column];
        int y      = rowOffsets[ci.row];
        int width  = columnOffsets[ci.column + ci.colspan - 1] - x + data.columnMetrics[ci.column + ci.colspan - 1].size;
        int height = rowOffsets[ci.row + ci.rowspan - 1] - y + data.rowMetrics[ci.row + ci.rowspan - 1].size;

        grRectangle rc{ x, y, width, height };

        ci.widget->set_bounds(insets.left + rc.x, insets.top + rc.y, rc.width, rc.height);
    }

    gtlDeleteArray columnOffsets;
    gtlDeleteArray rowOffsets;

    gtlDeleteArray data.columnMetrics;
    gtlDeleteArray data.rowMetrics;
    gtlDeleteArray data.childInfos;
}
