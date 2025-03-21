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

#include <gtlUtil/Misc.h>

enum class grUiEnumContentBias {
    CONTENT_BIAS_NONE       = 0,
    CONTENT_BIAS_HORIZONTAL = 1,
    CONTENT_BIAS_VERTICAL   = 2,
};

namespace grUiLayoutFlags {
    enum : uint32_t {
        FLAG_RESPECTS_MINIMUM_SIZE = GTL_BIT(0)
    };
}
