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

#include "WidgetScrollBar.h"

grDimension grUiWidgetScrollBar::initialMeasure(int biasedSize) {
    return get_baseInsets().outsetDimension({ 0, 0 });
}

void grUiWidgetScrollBar::set_scrollContentSize(int size) {
}

void grUiWidgetScrollBar::set_scrollPosition(int offset) {
}

GTL_RTTI_DEFINE(grUiWidgetScrollBar, GTL_RTTI_INHERITS(grUiWidget));
