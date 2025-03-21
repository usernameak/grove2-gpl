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

#include <gtlModule/ModuleInfo.h>

#ifdef GROVE2_IMPORT_MODULE_grDX11
#ifdef GROVE2_IMPORT_DLL_MODULE_grDX11
GROVE2_IMPORT_DLL_MODULE(grDX11);
#else
GROVE2_IMPORT_STATIC_MODULE(grDX11);
#endif
#endif
