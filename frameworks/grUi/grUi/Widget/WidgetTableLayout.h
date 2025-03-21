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

#include "WidgetLayout.h"
#include <tsl/ordered_map.h>

class GR_UI_DLLIMPEXP grUiWidgetTableLayout : public grUiWidgetLayout {
public:
    GTL_RTTI_DECLARE();

private:
    class TableLayoutManager;

    struct ColumnInfo {
        gnaPointer<grUiWidget> titleWidget;
        unsigned int width;
    };

    struct RowInfo {
        uint32_t numCells;
        gnaWeakPointer<grUiWidget> *cellWidgets;

        explicit RowInfo(size_t numCells) : numCells(numCells) {
            cellWidgets = gtlNew gnaWeakPointer<grUiWidget>[numCells];
        }

        RowInfo(const RowInfo &other) = delete;
        RowInfo(RowInfo &&other)      = default;

        RowInfo &operator=(const RowInfo &other) = delete;
        RowInfo &operator=(RowInfo &&other)      = default;

        ~RowInfo() {
            gtlDeleteArray cellWidgets;
        }
    };

    tsl::ordered_map<gtl::Name, ColumnInfo> m_columns;
    std::vector<RowInfo> m_rows;

public:
    class GR_UI_DLLIMPEXP Row {
        gnaWeakPointer<grUiWidgetTableLayout> m_tableLayout;
        RowInfo &m_rowInfo;

    public:
        Row(
            gnaWeakPointer<grUiWidgetTableLayout> tableLayout,
            RowInfo &rowInfo)
            : m_tableLayout(tableLayout),
              m_rowInfo(rowInfo) {}

        void setColumn(gtl::Name name, gnaPointer<grUiWidget> widget);
    };

    grUiWidgetTableLayout();

    void addColumn(gtl::Name name, gnaPointer<grUiWidget> titleWidget);
    Row addRow();
};
