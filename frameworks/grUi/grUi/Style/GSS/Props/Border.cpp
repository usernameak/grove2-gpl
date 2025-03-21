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

#include "Border.h"

GTL_RTTI_DEFINE(grUiGSSBorderTypePropVal, GTL_RTTI_INHERITS(grUiGSSPropVal));

bool grUiGSSBorderTypePropVal::Parser::stringToEnum(const gtl::PooledAString &str, BorderType &value) const {
    if (str == "-gr-multipatch") {
        value = BORDER_TYPE_MULTIPATCH;
    } else if (str == "-gr-native") {
        value = BORDER_TYPE_NATIVE;
    } else if (str == "solid") {
        value = BORDER_TYPE_NORMAL;
    } else if (str == "none") {
        value = BORDER_TYPE_NONE;
    } else {
        return false;
    }
    return true;
}
