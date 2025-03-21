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

#include <type_traits>
#include <gr2DCoords.h>
#include <gtlUtil/Hash.h>

struct grUiMetricContext {
    int dpiScaleFactor;

    grUiMetricContext() : dpiScaleFactor(100) {}
    explicit grUiMetricContext(int dpiScaleFactor) : dpiScaleFactor(dpiScaleFactor) {}
};

template <typename T>
struct grUiUnitSize {
    enum Unit {
        UNIT_PX,
        UNIT_DP
    } unit;

    static_assert(std::is_arithmetic_v<T>);

    T value;

    grUiUnitSize() : unit(UNIT_DP) {}
    grUiUnitSize(Unit unit, T value) : unit(unit), value(value) {}
    grUiUnitSize(T value) : unit(UNIT_DP), value(value) {}

    T toPixels(const grUiMetricContext &context) const {
        if (unit == UNIT_DP) {
            return value * context.dpiScaleFactor / 100;
        }
        return value;
    }

    void setWithPixels(T newValue, const grUiMetricContext &context) {
        if (unit == UNIT_DP) {
            this->value = newValue * 100 / context.dpiScaleFactor;
        }
        this->value = newValue;
    }

    bool operator==(const grUiUnitSize &other) const {
        return unit == other.unit && value == other.value;
    }

    bool operator!=(const grUiUnitSize &other) const {
        return unit != other.unit || value != other.value;
    }
};

using grUiUnitSizeF = grUiUnitSize<float>;
using grUiUnitSizeI = grUiUnitSize<int>;

struct grUiUnitDimension {
    grUiUnitSizeI width, height;

    grDimension toPixels(const grUiMetricContext &context) const {
        return {
            width.toPixels(context),
            height.toPixels(context)
        };
    }

    void setWithPixels(const grUiMetricContext &context, grDimension dimension) {
        width.setWithPixels(dimension.width, context);
        height.setWithPixels(dimension.height, context);
    }

    bool operator==(const grUiUnitDimension &other) const {
        return width == other.width && height == other.height;
    }

    bool operator!=(const grUiUnitDimension &other) const {
        return width != other.width || height != other.height;
    }
};

struct grUiUnitInsets {
    grUiUnitSizeI left, top, right, bottom;

    grUiUnitInsets() = default;

    grUiUnitInsets(grUiUnitSizeI left, grUiUnitSizeI top, grUiUnitSizeI right, grUiUnitSizeI bottom)
        : left(left),
          top(top),
          right(right),
          bottom(bottom) {}

    grUiUnitInsets(grUiUnitSizeI all) : grUiUnitInsets(all, all, all, all) {}

    grInsets toPxInsets(const grUiMetricContext &context) const {
        return {
            left.toPixels(context),
            top.toPixels(context),
            right.toPixels(context),
            bottom.toPixels(context)
        };
    }

    static grUiUnitInsets fromPxInsets(const grInsets &insets) {
        return {
            { grUiUnitSizeI::UNIT_PX, insets.left },
            { grUiUnitSizeI::UNIT_PX, insets.top },
            { grUiUnitSizeI::UNIT_PX, insets.right },
            { grUiUnitSizeI::UNIT_PX, insets.bottom }
        };
    }

    void setWithPixels(const grUiMetricContext &context, const grInsets &insets) {
        left.setWithPixels(insets.left, context);
        top.setWithPixels(insets.top, context);
        right.setWithPixels(insets.right, context);
        bottom.setWithPixels(insets.bottom, context);
    }

    bool operator==(const grUiUnitInsets &other) const {
        return left == other.left && right == other.right && top == other.top && bottom == other.bottom;
    }

    bool operator!=(const grUiUnitInsets &other) const {
        return left != other.left || right != other.right || top != other.top || bottom != other.bottom;
    }
};

namespace std {
    template <typename T>
    struct hash<grUiUnitSize<T>> {
        std::size_t operator()(grUiUnitSize<T> const &s) const noexcept {
            std::size_t seed = 0;
            gutlHashCombine(seed, s.unit);
            gutlHashCombine(seed, s.value);

            return seed;
        }
    };
}
