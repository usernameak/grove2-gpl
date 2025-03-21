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

#include "ModuleInfo.h"

#include <unordered_set>
#include <gtlString/String.h>
#include <gtlUtil/Singleton.h>

class GTL_DLLIMPEXP gtlModuleLoader {
    std::unordered_set<const gtlModuleInfo *> m_loadedModules;

public:
    void loadModule(const gtlModuleInfo *moduleInfo);
    const gtlModuleInfo *loadModuleDLL(gtl::String path);
};

GNA_SINGLETON_EXPORTED_DECLARE(GTL_DLLIMPEXP, gtlModuleLoader);
