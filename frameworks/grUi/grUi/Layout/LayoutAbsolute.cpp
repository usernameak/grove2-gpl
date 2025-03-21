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

#include "LayoutAbsolute.h"

#include <grUi/Widget/WidgetLayout.h>

GTL_RTTI_DEFINE(grUiLayoutAbsolute, GTL_RTTI_INHERITS(grUiLayoutManager));
GTL_RTTI_DEFINE(grUiLayoutAbsolute::ElementSpec, GTL_RTTI_INHERITS(gtlRcObject));

grUiLayoutAbsolute::grUiLayoutAbsolute(grUiUnitSizeI width, grUiUnitSizeI height)
    : m_width(width),
      m_height(height) {
}

grDimension grUiLayoutAbsolute::initialMeasure(grUiWidgetLayout *parent, int biasedSize) {
    auto mc = parent->get_metricContext();
    return { m_width.toPixels(mc), m_height.toPixels(mc) };
}

void grUiLayoutAbsolute::layout(grUiWidgetLayout *parent) {
    auto mc = parent->get_metricContext();
    for (gnaWeakPointer<grUiWidget> child : *parent) {
        auto layoutData = child->get_layoutData().rttiCast2<ElementSpec>();
        if (layoutData) {
            child->set_bounds(
                layoutData->m_x.toPixels(mc),
                layoutData->m_y.toPixels(mc),
                layoutData->m_width.toPixels(mc),
                layoutData->m_height.toPixels(mc));
        }
    }
}
