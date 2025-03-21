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

#include <gtlString/String.h>
#include <cstdint>
#include <gtlMemory/RcObject.h>

enum : uint32_t {
    GNA_E_OK              = 0x00000000,
    GNA_E_DATA_NOT_CACHED = 0x00000001,
    GNA_E_END_OF_DATA     = 0x00000002,

    GNA_E_FAILED                         = 0x80000001,
    GNA_E_OUT_OF_MEMORY                  = 0x80000002,
    GNA_E_INVALID_STATE                  = 0x80000003,
    GNA_E_CLS_NOT_FOUND                  = 0x80000004,
    GNA_E_INCOMPATIBLE_CLS               = 0x80000005,
    GNA_E_INVALID_ARGUMENT               = 0x80000006,
    GNA_E_CACHE_INVALID_INDEX            = 0x80000007,
    GNA_E_FILE_NOT_FOUND                 = 0x80000008,
    GNA_E_IS_A_DIR                       = 0x80000009,
    GNA_E_INVALID_CONFIG                 = 0x8000000A,
    GNA_E_BUFFER_TOO_BIG                 = 0x8000000B,
    GNA_E_PROP_NOT_FOUND                 = 0x8000000D,
    GNA_E_PARSE_WRONG_START_TOKEN        = 0x8000000E,
    GNA_E_INVALID_DATA_FORMAT            = 0x8000000F,
    GNA_E_BAD_FILE_FORMAT [[deprecated]] = GNA_E_INVALID_DATA_FORMAT,
    GNA_E_UNSUPPORTED                    = 0x80000010,
    GNA_E_OUT_OF_BOUNDS                  = 0x80000011,
};

class gnaStatus {
public:
    uint32_t errorCode;

    gnaStatus() : errorCode(GNA_E_OK) {}

    gnaStatus(uint32_t errorCode) : errorCode(errorCode) {}

    // FIXME: error message is currently discarded
    gnaStatus(uint32_t errorCode, gtl::String errorMessage) : errorCode(errorCode) {}

    inline gnaStatus &operator=(uint32_t errorCode) {
        this->errorCode = errorCode;
        return *this;
    }

    explicit operator bool() const {
        return get_success();
    }

    gtl::String get_errorMessage() const {
        return gtl::String::format(GTXT("Error 0x%08x"), errorCode);
    }

    bool get_success() const {
        return !(errorCode & 0x80000000);
    }
};

#define GNA_CHECK_STATUS(...)              \
    do {                                   \
        gnaStatus _gna_st = (__VA_ARGS__); \
        if (!_gna_st)                      \
            return _gna_st;                \
    } while (false)
