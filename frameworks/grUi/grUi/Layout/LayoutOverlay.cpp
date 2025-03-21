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

#include "LayoutOverlay.h"

#include <grUi/Widget/Widget.h>
#include <grUi/Widget/WidgetLayout.h>

GTL_RTTI_DEFINE(grUiLayoutOverlay, GTL_RTTI_INHERITS(grUiLayoutManager));
GTL_RTTI_DEFINE(grUiLayoutOverlay::ElementSpec, GTL_RTTI_INHERITS(gtlRcObject));

grDimension grUiLayoutOverlay::initialMeasure(grUiWidgetLayout *parent, int biasedSize) {
    grUiMetricContext metricContext = parent->get_metricContext();

    grDimension dim{0, 0};
    for(gnaWeakPointer<grUiWidget> widget : *parent) {
        grDimension childDim = widget->measure();

        static gnaPointer<ElementSpec> DEFAULT_SPEC = gnaNew<ElementSpec>();
        gnaWeakPointer<ElementSpec> spec = widget->get_layoutData().rttiCast2<ElementSpec>();

        if (!spec) spec = DEFAULT_SPEC;

        if (!spec) continue;

        if (childDim.width + std::abs(spec->offsetX.toPixels(metricContext)) > dim.width) {
            dim.width = childDim.width;
        }
        if (childDim.height + std::abs(spec->offsetY.toPixels(metricContext)) >= dim.height) {
            dim.height = childDim.height;
        }
    }
    return parent->get_baseInsets().outsetDimension(dim);
}

void grUiLayoutOverlay::layout(grUiWidgetLayout *parent) {
    grUiMetricContext metricContext = parent->get_metricContext();

    grRectangle rc = parent->get_baseInsets().insetDimensionToRect(parent->get_size());
    for(gnaWeakPointer<grUiWidget> widget : *parent) {
        grDimension childDim = widget->measure();

        static gnaPointer<ElementSpec> DEFAULT_SPEC = gnaNew<ElementSpec>();
        gnaWeakPointer<ElementSpec> spec = widget->get_layoutData().rttiCast2<ElementSpec>();

        if (!spec) spec = DEFAULT_SPEC;

        int childX = 0;
        if (spec->relativePositionX != ElementSpec::FILL_PARENT) {
            childX = rc.x + static_cast<int>((rc.width - childDim.width) * spec->relativePositionX) + spec->offsetX.toPixels(metricContext);
        }
        int childY = 0;
        if (spec->relativePositionY != ElementSpec::FILL_PARENT) {
            childY = rc.y + static_cast<int>((rc.height - childDim.height) * spec->relativePositionY) + spec->offsetY.toPixels(metricContext);
        }
        int childWidth = childDim.width;
        if (spec->relativePositionX == ElementSpec::FILL_PARENT) {
            childWidth = rc.width;
        }
        int childHeight = childDim.height;
        if (spec->relativePositionY == ElementSpec::FILL_PARENT) {
            childHeight = rc.height;
        }

        widget->set_bounds(childX, childY, childWidth, childHeight);
    }
}
