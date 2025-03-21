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

#include "TextAlign.h"

GTL_RTTI_DEFINE(grUiGSSTextAlignPropVal, GTL_RTTI_INHERITS(grUiGSSPropVal));

bool grUiGSSTextAlignPropVal::Parser::stringToEnum(const gtl::PooledAString &str, TextAlign &value) const {
    if (str == "left") {
        value = TEXT_ALIGN_LEFT;
    } else if (str == "center") {
        value = TEXT_ALIGN_CENTER;
    } else if (str == "right") {
        value = TEXT_ALIGN_RIGHT;
    } else {
        return false;
    }
    return true;
}

GTL_RTTI_DEFINE(grUiGSSVerticalAlignPropVal, GTL_RTTI_INHERITS(grUiGSSPropVal));

bool grUiGSSVerticalAlignPropVal::Parser::stringToEnum(const gtl::PooledAString &str, VerticalAlign &value) const {
    if (str == "top") {
        value = VERTICAL_ALIGN_TOP;
    } else if (str == "middle") {
        value = VERTICAL_ALIGN_MIDDLE;
    } else if (str == "bottom") {
        value = VERTICAL_ALIGN_BOTTOM;
    } else {
        return false;
    }
    return true;
}
