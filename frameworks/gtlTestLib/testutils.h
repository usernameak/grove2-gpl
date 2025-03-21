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

#include <gtlUtil/Logging.h>
#include <gnaStatus.h>

#define testCheck(value)                                                                               \
    do {                                                                                               \
        if (!(value)) {                                                                                \
            GR_FATAL(GTXT("test check (%ls) failed, %ls:%d"), GTXT(#value), GTXT(__FILE__), __LINE__); \
        }                                                                                              \
    } while (false)

#define testCheckStatus(...)                                       \
    do {                                                           \
        gnaStatus _gna_st = (__VA_ARGS__);                         \
        if (!_gna_st)                                              \
            GR_FATAL(GTXT("test check (%ls) failed: %ls, %ls:%d"), \
                GTXT(#__VA_ARGS__),                                \
                _gna_st.get_errorMessage().toCString(),            \
                GTXT(__FILE__), __LINE__);                         \
    } while (false)
