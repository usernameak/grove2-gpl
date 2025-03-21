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

#include <cstdint>
#include <gtlUtil/Misc.h>

#define GTL_COLOR_RED(argb) ((argb >> 16) & 0xFF)
#define GTL_COLOR_GREEN(argb) ((argb >> 8) & 0xFF)
#define GTL_COLOR_BLUE(argb) (argb & 0xFF)
#define GTL_COLOR_ALPHA(argb) (argb >> 24)

struct GTL_PASS_BY_VALUE grColor {
    uint32_t argb;

    inline uint8_t get_red() const {
        return GTL_COLOR_RED(argb);
    }

    inline uint8_t get_green() const {
        return GTL_COLOR_GREEN(argb);
    }

    inline uint8_t get_blue() const {
        return GTL_COLOR_BLUE(argb);
    }

    inline uint8_t getAlpha() const {
        return GTL_COLOR_ALPHA(argb);
    }

    inline void set_red(uint8_t red) {
        argb = (argb & 0xFF00FFFF) | (red << 16);
    }

    inline void set_green(uint8_t green) {
        argb = (argb & 0xFFFF00FF) | (green << 8);
    }

    inline void set_blue(uint8_t blue) {
        argb = (argb & 0xFFFFFF00) | blue;
    }

    inline void set_alpha(uint8_t alpha) {
        argb = (argb & 0x00FFFFFF) | (alpha << 24);
    }

    grColor &operator=(grColor other) {
        argb = other.argb;
        return *this;
    }

    GTL_DLLIMPEXP static const grColor C_TRANSPARENT;
    GTL_DLLIMPEXP static const grColor C_BLACK;
    GTL_DLLIMPEXP static const grColor WHITE;
};

inline grColor operator"" _grColor(unsigned long long color) {
    return grColor{ (uint32_t)color };
}
