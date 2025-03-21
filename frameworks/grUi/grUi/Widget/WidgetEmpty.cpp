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

#include "WidgetEmpty.h"
#include "grUi/Layout/LayoutLinear.h"

GTL_RTTI_DEFINE(grUiWidgetEmpty, GTL_RTTI_INHERITS(grUiWidget));

gnaPointer<grUiWidgetEmpty> grUiWidgetEmpty::createLinearGrowPlaceholder() {
    auto empty = gnaNew<grUiWidgetEmpty>();
    empty->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow(100));
    return empty;
}
