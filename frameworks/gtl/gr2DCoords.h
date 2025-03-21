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

#include <algorithm>
#include <type_traits>

template <typename T>
struct grDimensionBase;

template <typename T>
struct grPointBase {
    T x, y;

    grPointBase() = default;
    grPointBase(T x, T y) : x(x), y(y) {}

    template <typename U, std::enable_if_t<std::is_convertible_v<U, T>, nullptr_t> = nullptr>
    explicit grPointBase(grPointBase<U> pt)
        : x(static_cast<T>(pt.x)),
          y(static_cast<T>(pt.y)) {}

    grPointBase operator+(grPointBase other) const {
        return { x + other.x, y + other.y };
    }

    grPointBase operator-(grPointBase other) const {
        return { x - other.x, y - other.y };
    }

    grPointBase operator-() const {
        return { -x, -y };
    }

    grPointBase operator*(grDimensionBase<T> dim) const {
        return { x * dim.width, y * dim.height };
    }

    grPointBase operator/(grDimensionBase<T> dim) const {
        return { x / dim.width, y / dim.height };
    }
};

template <typename T>
struct grDimensionBase {
    int width, height;

    grDimensionBase() = default;
    grDimensionBase(T width, T height) : width(width), height(height) {}

    template <typename U, std::enable_if_t<std::is_convertible_v<U, T>, nullptr_t> = nullptr>
    explicit grDimensionBase(grDimensionBase<U> dim)
        : width(static_cast<T>(dim.width)),
          height(static_cast<T>(dim.height)) {}

    bool operator==(const grDimensionBase other) const {
        return width == other.width && height == other.height;
    }

    bool operator!=(const grDimensionBase other) const {
        return !operator==(other);
    }

    grDimensionBase operator+(grDimensionBase other) const {
        return { width + other.width, height + other.height };
    }

    grDimensionBase operator-(grDimensionBase other) const {
        return { width - other.width, height - other.height };
    }
};

using grPoint  = grPointBase<int>;
using grPointF = grPointBase<float>;

using grDimension  = grDimensionBase<int>;
using grDimensionF = grDimensionBase<float>;

struct grRectangle {
    int x, y, width, height;

    bool operator==(const grRectangle &other) const {
        return x == other.x && y == other.y && width == other.width && height == other.height;
    }

    bool operator!=(const grRectangle &other) const {
        return !operator==(other);
    }

    grRectangle intersect(const grRectangle &other) const {
        grRectangle rc;
        rc.x      = (std::max)(other.x, x);
        rc.y      = (std::max)(other.y, y);
        rc.width  = (std::min)(other.x + other.width, x + width) - rc.x;
        rc.height = (std::min)(other.y + other.height, y + height) - rc.y;

        if (rc.width < 0) {
            rc.width = 0;
        }
        if (rc.height < 0) {
            rc.height = 0;
        }

        return rc;
    }

    bool intersects(const grRectangle &other) const {
        return other.x < x + width && other.x + other.width >= x && other.y < y + height && other.y + other.height >= y;
    }

    bool contains(const grPoint &pt) const {
        return pt.x >= x && pt.y >= y && pt.x < x + width && pt.y < y + height;
    }
};

struct grInsets {
    int left, top, right, bottom;

    grInsets() = default;
    grInsets(int left, int top, int right, int bottom) : left(left), top(top), right(right), bottom(bottom) {}
    grInsets(int all) : grInsets(all, all, all, all) {}

    grInsets expand(int padding) const {
        return { left + padding, top + padding, right + padding, bottom + padding };
    }

    grRectangle insetRectToRect(grRectangle rect) const {
        return { left + rect.x, top + rect.y, rect.width - right - left, rect.height - bottom - top };
    }

    grRectangle insetDimensionToRect(grDimension dim) const {
        return { left, top, dim.width - right - left, dim.height - bottom - top };
    }

    grDimension outsetDimension(grDimension dimension) const {
        return { dimension.width + left + right, dimension.height + top + bottom };
    }

    grPoint insetPoint(grPoint point) const {
        return { point.x - left, point.y - top };
    }

    grPoint outsetPoint(grPoint point) const {
        return { point.x + left, point.y + top };
    }

    bool operator==(const grInsets &other) const {
        return left == other.left && right == other.right && top == other.top && bottom == other.bottom;
    }

    bool operator!=(const grInsets &other) const {
        return !operator==(other);
    }

    grInsets operator+(const grInsets &other) const {
        return { left + other.left, top + other.top, right + other.right, bottom + other.bottom };
    }

    grInsets &operator+=(const grInsets &other) {
        left += other.left;
        top += other.top;
        right += other.right;
        bottom += other.bottom;
        return *this;
    }
};
