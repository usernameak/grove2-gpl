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

#include <stdint.h>

typedef uint32_t gnaFOURCC;

#define GNA_FOURCC(fcc) (                  \
    ((((gnaFOURCC)fcc) & 0xFF) << 24) |    \
    ((((gnaFOURCC)fcc) & 0xFF00) << 8) |   \
    ((((gnaFOURCC)fcc) & 0xFF0000) >> 8) | \
    ((((gnaFOURCC)fcc) & 0xFF000000) >> 24))
