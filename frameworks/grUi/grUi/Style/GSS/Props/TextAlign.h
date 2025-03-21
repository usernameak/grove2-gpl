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

#include "PropVal.h"
#include "Helpers.h"

struct GR_UI_DLLIMPEXP grUiGSSTextAlignPropVal : public grUiGSSPropVal {
    GTL_RTTI_DECLARE();

    enum TextAlign {
        TEXT_ALIGN_LEFT,
        TEXT_ALIGN_CENTER,
        TEXT_ALIGN_RIGHT,
    } textAlign;

    class Parser : public grUiGSSEnumPropValParser<grUiGSSTextAlignPropVal, TextAlign> {
    public:
        bool stringToEnum(const gtl::PooledAString &str, TextAlign &value) const override;
    };

    grUiGSSTextAlignPropVal() = default;
    explicit grUiGSSTextAlignPropVal(TextAlign textAlign) : textAlign(textAlign) {}
};

struct GR_UI_DLLIMPEXP grUiGSSVerticalAlignPropVal : public grUiGSSPropVal {
    GTL_RTTI_DECLARE();

    enum VerticalAlign {
        VERTICAL_ALIGN_TOP,
        VERTICAL_ALIGN_MIDDLE,
        VERTICAL_ALIGN_BOTTOM,
    } verticalAlign;

    class Parser : public grUiGSSEnumPropValParser<grUiGSSVerticalAlignPropVal, VerticalAlign> {
    public:
        bool stringToEnum(const gtl::PooledAString &str, VerticalAlign &value) const override;
    };

    grUiGSSVerticalAlignPropVal() = default;
    explicit grUiGSSVerticalAlignPropVal(VerticalAlign verticalAlign) : verticalAlign(verticalAlign) {}
};

