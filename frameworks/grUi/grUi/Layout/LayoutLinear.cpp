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

#include "LayoutLinear.h"

#include <grUi/Widget/WidgetLayout.h>
#include <gtlUtil/Logging.h>

GTL_RTTI_DEFINE(grUiLayoutLinear, GTL_RTTI_INHERITS(grUiLayoutManager));
GTL_RTTI_DEFINE(grUiLayoutLinear::ElementSpec, GTL_RTTI_INHERITS(gtlRcObject));

struct grUiLayoutLinear::Pass0Data {
    gnaPointer<ElementSpec> *elementSpecs;
    grDimension *childBaseDimensions;
    grInsets parentInsets;
    grRectangle rcParentInset;
    int *childComputedSizes;
    grInsets *childMarginInsets;
    int fixedSizeSum;
    int weightSum;
    int crossMinSize;
};

void grUiLayoutLinear::pass(grUiWidgetLayout *parent, int biasedSize, int passIndex, Pass0Data &p0d) const {
    int numChildren = parent->numChildren();

    p0d.parentInsets  = parent->get_baseInsets();
    p0d.rcParentInset = p0d.parentInsets.insetDimensionToRect(parent->get_size());

    p0d.elementSpecs        = gtlNew gnaPointer<ElementSpec>[numChildren];
    p0d.childBaseDimensions = gtlNew grDimension[numChildren];
    p0d.childComputedSizes  = gtlNew int[numChildren];
    p0d.childMarginInsets   = gtlNew grInsets[numChildren];

    int primInset = primaryAxis == AXIS_X ? (p0d.parentInsets.left + p0d.parentInsets.right) : (p0d.parentInsets.top + p0d.parentInsets.bottom);
    int secInset  = primaryAxis == AXIS_X ? (p0d.parentInsets.top + p0d.parentInsets.bottom) : (p0d.parentInsets.left + p0d.parentInsets.right);

    p0d.crossMinSize = secInset;

    static gnaPointer<ElementSpec> dummySpec = ElementSpec::createMin();

    auto child = parent->firstChild();
    for (int i = 0; child; child = child->nextSibling(), i++) {
        if (child->get_visibility() == grUiWidget::VISIBILITY_GONE) {
            p0d.elementSpecs[i]        = dummySpec;
            p0d.childBaseDimensions[i] = { 0, 0 };
            p0d.childMarginInsets[i]   = { 0, 0, 0, 0 };
        } else {
            p0d.elementSpecs[i] = child->get_layoutData().rttiCast2<ElementSpec>();

            p0d.childMarginInsets[i] = child->get_insets(grUiWidget::INSET_MARGIN);
            auto contentBias         = child->get_contentBias();
            bool validContentBias    = contentBias == (primaryAxis == AXIS_X ? grUiEnumContentBias::CONTENT_BIAS_VERTICAL : grUiEnumContentBias::CONTENT_BIAS_HORIZONTAL);
            if (!validContentBias ||
                passIndex != 0) {
                if (p0d.elementSpecs[i] && p0d.elementSpecs[i]->secondaryAlignment != SA_FILL) {
                    p0d.childBaseDimensions[i] = child->measure(0);
                } else {
                    p0d.childBaseDimensions[i] = child->measure(validContentBias ? biasedSize - secInset : 0);
                }
            } else {
                p0d.childBaseDimensions[i] = { 0, 0 };
            }
        }
    }

    for (int i = 0; i < numChildren; i++) {
        grDimension dim = p0d.childBaseDimensions[i];
        auto spec       = p0d.elementSpecs[i];

        int elCrossSz = 0;
        if (primaryAxis == AXIS_X) {
            elCrossSz = dim.height;
        } else if (primaryAxis == AXIS_Y) {
            elCrossSz = dim.width;
        }
        elCrossSz += secInset;
        if (int mss = spec ? spec->minSecondarySize.toPixels(parent->get_metricContext()) : 0;
            spec && elCrossSz < mss) {
            elCrossSz = mss;
        }
        if (p0d.crossMinSize < elCrossSz) {
            p0d.crossMinSize = elCrossSz;
        }
    }

    p0d.fixedSizeSum = primInset;
    p0d.weightSum    = 0;

    for (int i = 0; i < numChildren; i++) {
        if (p0d.elementSpecs[i] != dummySpec && i != 0) {
            p0d.fixedSizeSum += gap.toPixels(parent->get_metricContext());
        }
        grDimension dim = p0d.childBaseDimensions[i];
        auto spec       = p0d.elementSpecs[i];
        if (!spec || spec->sizeMode == SIZEMODE_MIN) {
            int sz   = spec ? spec->sizeModeParam : 0;
            int elSz = 0;
            if (primaryAxis == AXIS_X) {
                elSz = dim.width;
            } else if (primaryAxis == AXIS_Y) {
                elSz = dim.height;
            }
            if (sz < elSz) {
                sz = elSz;
            }
            p0d.fixedSizeSum += sz;
            p0d.childComputedSizes[i] = sz;
        } else if (spec->sizeMode == SIZEMODE_FIXED) {
            p0d.fixedSizeSum += spec->sizeModeParam;
            p0d.childComputedSizes[i] = spec->sizeModeParam;
        } else if (spec->sizeMode == SIZEMODE_GROW) {
            p0d.weightSum += spec->sizeModeParam;
            int elSz = 0;
            if (primaryAxis == AXIS_X) {
                elSz = dim.width;
            } else if (primaryAxis == AXIS_Y) {
                elSz = dim.height;
            }
            p0d.fixedSizeSum += elSz;
            p0d.childComputedSizes[i] = elSz;
        } else if (spec->sizeMode == SIZEMODE_SQUARE) {
            if (passIndex == 1) {
                int ins = primaryAxis == AXIS_X ? p0d.childMarginInsets[i].left + p0d.childMarginInsets[i].right
                                                : p0d.childMarginInsets[i].top + p0d.childMarginInsets[i].bottom;

                p0d.fixedSizeSum += biasedSize - secInset + ins;
                p0d.childComputedSizes[i] = biasedSize - secInset + ins;
            } else {
                p0d.fixedSizeSum += p0d.crossMinSize;
                p0d.childComputedSizes[i] = p0d.crossMinSize;
            }
        } else {
            GR_FATAL(GTXT("grUiLayoutLinear: invalid sizeMode"));
        }
    }
}

grDimension grUiLayoutLinear::initialMeasure(grUiWidgetLayout *parent, int biasedSize) {
    Pass0Data p0d;
    pass(parent, 0, 0, p0d);

    gtlDeleteArray p0d.childBaseDimensions;
    gtlDeleteArray p0d.elementSpecs;
    gtlDeleteArray p0d.childComputedSizes;
    gtlDeleteArray p0d.childMarginInsets;

    Pass0Data p1d;
    pass(parent, std::max(biasedSize, p0d.crossMinSize), 1, p1d);

    gtlDeleteArray p1d.childBaseDimensions;
    gtlDeleteArray p1d.elementSpecs;
    gtlDeleteArray p1d.childComputedSizes;
    gtlDeleteArray p1d.childMarginInsets;

    grDimension dim;
    if (primaryAxis == AXIS_X) {
        dim = { p1d.fixedSizeSum, p1d.crossMinSize };
    } else if (primaryAxis == AXIS_Y) {
        dim = { p1d.crossMinSize, p1d.fixedSizeSum };
    } else {
        GR_FATAL(GTXT("grUiLayoutLinear: invalid primary axis"));
    }

    grDimension parentMinSize = parent->get_minimumSize().toPixels(parent->get_metricContext());
    if (dim.width < parentMinSize.width)
        dim.width = parentMinSize.width;
    if (dim.height < parentMinSize.height)
        dim.height = parentMinSize.height;
    return dim;
}

void grUiLayoutLinear::doLayout(grUiWidgetLayout *parent, int passIndex) const {
    Pass0Data p0d;

    pass(parent, primaryAxis == AXIS_Y ? parent->get_size().width : parent->get_size().height, passIndex, p0d);

    int numChildren = parent->numChildren();

    int remainingSize    = (primaryAxis == AXIS_X ? parent->get_size().width : parent->get_size().height) - p0d.fixedSizeSum;
    int totalGrowingSize = remainingSize;

    for (int i = 0; i < numChildren; i++) {
        auto spec = p0d.elementSpecs[i];
        if (spec && spec->sizeMode == SIZEMODE_GROW) {
            totalGrowingSize += p0d.childComputedSizes[i];
        }
    }

    int *tempSizes = gtlNew int[numChildren];

    for (int i = 0; i < numChildren; i++) {
        auto spec = p0d.elementSpecs[i];
        if (spec && spec->sizeMode == SIZEMODE_GROW) {
            tempSizes[i] = totalGrowingSize * spec->sizeModeParam / p0d.weightSum;
        }
    }

    uint32_t shrinkValue           = 0;
    uint32_t numShrinkableElements = 0;
    for (int i = 0; i < numChildren; i++) {
        auto spec = p0d.elementSpecs[i];
        if (spec && spec->sizeMode == SIZEMODE_GROW) {
            if (p0d.childComputedSizes[i] > tempSizes[i]) {
                shrinkValue += p0d.childComputedSizes[i] - tempSizes[i];
            } else {
                numShrinkableElements++;
            }
        }
    }

    for (int i = 0; i < numChildren; i++) {
        auto spec = p0d.elementSpecs[i];
        if (spec && spec->sizeMode == SIZEMODE_GROW) {
            if (p0d.childComputedSizes[i] <= tempSizes[i]) {
                int growValue = tempSizes[i] - p0d.childComputedSizes[i] - shrinkValue / numShrinkableElements;

                p0d.childComputedSizes[i] += growValue;
            }
        }
    }

    gtlDeleteArray tempSizes;

    int pos    = 0;
    auto child = parent->firstChild();
    for (int i = 0; child; child = child->nextSibling(), i++) {
        if (child->get_visibility() != grUiWidget::VISIBILITY_GONE && i != 0) {
            pos += gap.toPixels(parent->get_metricContext());
        }

        grRectangle rc;
        if (primaryAxis == AXIS_X) {
            rc.x     = pos;
            rc.width = p0d.childComputedSizes[i];
            pos += rc.width;

            if (!p0d.elementSpecs[i] || p0d.elementSpecs[i]->secondaryAlignment == SA_FILL) {
                rc.y      = 0;
                rc.height = p0d.rcParentInset.height;
            } else {
                rc.height = p0d.childBaseDimensions[i].height;

                auto sa = p0d.elementSpecs[i]->secondaryAlignment;
                if (sa == SA_START) {
                    rc.y = 0;
                } else if (sa == SA_MIDDLE) {
                    rc.y = (p0d.rcParentInset.height - rc.height) / 2;
                } else if (sa == SA_END) {
                    rc.y = p0d.rcParentInset.height - rc.height;
                }
            }
        } else if (primaryAxis == AXIS_Y) {
            rc.y      = pos;
            rc.height = p0d.childComputedSizes[i];
            pos += rc.height;

            if (!p0d.elementSpecs[i] || p0d.elementSpecs[i]->secondaryAlignment == SA_FILL) {
                rc.x     = 0;
                rc.width = p0d.rcParentInset.width;
            } else {
                auto sa  = p0d.elementSpecs[i]->secondaryAlignment;
                rc.width = p0d.childBaseDimensions[i].width;
                if (sa == SA_START) {
                    rc.x = 0;
                } else if (sa == SA_MIDDLE) {
                    rc.x = (p0d.rcParentInset.width - rc.width) / 2;
                } else if (sa == SA_END) {
                    rc.x = p0d.rcParentInset.width - rc.width;
                }
            }
        } else {
            GR_FATAL(GTXT("grUiLayoutLinear: invalid primary axis"));
        }

        grPoint p = { rc.x, rc.y };
        p         = p0d.parentInsets.outsetPoint(p);

        child->set_bounds(p.x, p.y, rc.width, rc.height);
    }

    gtlDeleteArray p0d.childBaseDimensions;
    gtlDeleteArray p0d.elementSpecs;
    gtlDeleteArray p0d.childComputedSizes;
}

gnaPointer<gtlRcObject> grUiLayoutLinear::createLayoutDataFromString(const gtl::AString &string) const {
    auto spec = gnaNew<ElementSpec>();

    if (string.startsWith("grow ")) {
        spec->sizeMode = SIZEMODE_GROW;

        const gtl::ASCIICHAR *startPtr = string.toCString() + 5;
        gtl::ASCIICHAR *endPtr;
        unsigned long val = gtl::StrToUL(startPtr, &endPtr, 10);
        if (endPtr == string.toCString() + string.size()) {
            if (val != ULONG_MAX || errno != ERANGE) {
                spec->sizeModeParam = (int)val;
            }
        }
    }

    return spec;
}

grUiEnumContentBias grUiLayoutLinear::get_contentBias(grUiWidgetLayout *parent) {
    gnaWeakPointer<grUiWidget> widget = parent->firstChild();
    while (widget) {
        auto spec = widget->get_layoutData().rttiCast2<ElementSpec>();

        if (primaryAxis == AXIS_X &&
            ((spec && spec->sizeMode == SIZEMODE_SQUARE) ||
                widget->get_contentBias() == grUiEnumContentBias::CONTENT_BIAS_VERTICAL)) {
            return grUiEnumContentBias::CONTENT_BIAS_VERTICAL;
        }

        if (primaryAxis == AXIS_Y &&
            ((spec && spec->sizeMode == SIZEMODE_SQUARE) ||
                widget->get_contentBias() == grUiEnumContentBias::CONTENT_BIAS_HORIZONTAL)) {
            return grUiEnumContentBias::CONTENT_BIAS_HORIZONTAL;
        }

        widget = widget->nextSibling();
    }

    return grUiLayoutManager::get_contentBias(parent);
}

uint32_t grUiLayoutLinear::get_flags() {
    return grUiLayoutFlags::FLAG_RESPECTS_MINIMUM_SIZE;
}
