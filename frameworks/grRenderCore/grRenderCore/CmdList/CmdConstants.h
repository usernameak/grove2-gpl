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

namespace grRenderCore {
    enum ClearFlags : uint8_t {
        CLEAR_FLAG_COLOR = GTL_BIT(0),
        CLEAR_FLAG_DEPTH = GTL_BIT(1),
        CLEAR_FLAG_STENCIL = GTL_BIT(2)
    };
}
