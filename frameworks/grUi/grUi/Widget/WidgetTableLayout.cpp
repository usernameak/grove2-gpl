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

#include "WidgetTableLayout.h"

GTL_RTTI_DEFINE(grUiWidgetTableLayout, GTL_RTTI_INHERITS(grUiWidgetLayout));

class grUiWidgetTableLayout::TableLayoutManager : public grUiLayoutManager {
public:
protected:
    grDimension initialMeasure(grUiWidgetLayout *parent, int biasedSize) override {
        grUiWidgetTableLayout *tl = static_cast<grUiWidgetTableLayout *>(parent);

        grDimension finalDimension{ 0, 0 };

        {
            int totalHeight = 0;
            for (const auto &[name, columnInfo] : tl->m_columns) {
                grDimension d = columnInfo.titleWidget->measure();
                int width     = columnInfo.width > d.width ? columnInfo.width : d.width;
                finalDimension.width += width;
                if (d.height > totalHeight) totalHeight = d.height;
            }
            finalDimension.height += totalHeight;
        }

        for (const auto &rowInfo : tl->m_rows) {
            int totalHeight = 0;
            for (size_t i = 0; i < rowInfo.numCells; i++) {
                if (!rowInfo.cellWidgets[i]) continue;

                grDimension d = rowInfo.cellWidgets[i]->measure();
                if (d.height > totalHeight) totalHeight = d.height;
            }
            finalDimension.height += totalHeight;
        }

        return parent->get_baseInsets().outsetDimension(finalDimension);
    }

    void layout(grUiWidgetLayout *parent) override {
        grRectangle rc = parent->get_baseInsets().insetDimensionToRect(parent->get_size());

        assert(dynamic_cast<grUiWidgetTableLayout *>(parent));
        grUiWidgetTableLayout *tl = static_cast<grUiWidgetTableLayout *>(parent);

        int *widths = new int[tl->m_columns.size()];

        int x = rc.x;
        int y = rc.y;
        {
            int i           = 0;
            int totalHeight = 0;
            for (const auto &[name, columnInfo] : tl->m_columns) {
                grDimension d = columnInfo.titleWidget->measure();

                int width = columnInfo.width > d.width ? columnInfo.width : d.width;
                widths[i] = width;

                if (d.height > totalHeight) totalHeight = d.height;

                i++;
            }
            i = 0;
            for (const auto &[name, columnInfo] : tl->m_columns) {
                int width = widths[i];
                columnInfo.titleWidget->set_bounds(x, y, width, totalHeight);
                x += width;
                i++;
            }
            y += totalHeight;
        }

        for (const auto &rowInfo : tl->m_rows) {
            int totalHeight = 0;

            x = rc.x;
            for (size_t i = 0; i < rowInfo.numCells; i++) {
                if (!rowInfo.cellWidgets[i]) continue;

                grDimension d = rowInfo.cellWidgets[i]->measure();
                rowInfo.cellWidgets[i]->set_bounds(x, y, widths[i], d.height);

                x += widths[i];

                if (d.height > totalHeight) totalHeight = d.height;
            }
            y += totalHeight;
        }

        delete[] widths;
    }
};

grUiWidgetTableLayout::grUiWidgetTableLayout() {
    layout = gnaNew<TableLayoutManager>();
}

void grUiWidgetTableLayout::addColumn(gtl::Name name, gnaPointer<grUiWidget> titleWidget) {
    assert(m_rows.empty());

    auto [it, success] = m_columns.try_emplace(name);
    assert(success);

    auto &columnInfo = it.value();

    columnInfo.titleWidget = titleWidget;
    columnInfo.width       = 100;

    add(titleWidget);
}

grUiWidgetTableLayout::Row grUiWidgetTableLayout::addRow() {
    auto &rowInfo = m_rows.emplace_back(m_columns.size());
    return { gnaWeakPointer(this), rowInfo };
}

void grUiWidgetTableLayout::Row::setColumn(gtl::Name name, gnaPointer<grUiWidget> widget) {
    auto it = m_tableLayout->m_columns.find(name);
    assert(it != m_tableLayout->m_columns.end());

    size_t index = it - m_tableLayout->m_columns.begin();

    auto oldWidget = m_rowInfo.cellWidgets[index];
    if (m_rowInfo.cellWidgets[index]) {
        m_tableLayout->remove(oldWidget);
    }

    m_rowInfo.cellWidgets[index] = widget;
    m_tableLayout->add(widget);
}
