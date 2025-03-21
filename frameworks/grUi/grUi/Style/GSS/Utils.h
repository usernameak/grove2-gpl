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

#include <nxfResource/RID.h>
#include <gnaStatus.h>
#include <grUi/UiDLL.h>

namespace grUiGSSUtils {
    gnaStatus GR_UI_DLLIMPEXP convertUrlToRID(const gtl::AString &url, nxfRID &rid);

    inline bool isHexDigit(int32_t c) {
        return (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9');
    }

    inline uint32_t decodeHexDigit(int32_t c) {
        if (c >= 'A' && c <= 'F') {
            return c - 'A' + 0xA;
        } else if (c >= 'a' && c <= 'f') {
            return c - 'a' + 0xA;
        } else if (c >= '0' && c <= '9') {
            return c - '0';
        } else {
            assert(false);
            return 0;
        }
    }
}
