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

#include "ModuleLoader.h"

#include <cassert>
#include <gtlUtil/Logging.h>
#include <windows.h>

GNA_SINGLETON_IMPLEMENT(gtlModuleLoader);

// TODO: proper module unloading

void gtlModuleLoader::loadModule(const gtlModuleInfo *moduleInfo) {
    if (m_loadedModules.contains(moduleInfo)) return;
    m_loadedModules.insert(moduleInfo);

    if (moduleInfo->moduleDependencies) {
        for (const gtlModuleDependency *dep = moduleInfo->moduleDependencies;
             dep->moduleInfo || dep->moduleName;
             dep++) {
            if (dep->moduleInfo) {
                loadModule(dep->moduleInfo);
            } else if (dep->moduleName) {
                GR_FATAL(GTXT("Dynamic named module lookup not implemented yet"));
            } else {
                assert(false);
            }
        }
    }

    if (moduleInfo->staticInit) moduleInfo->staticInit();
}

const gtlModuleInfo *gtlModuleLoader::loadModuleDLL(gtl::String path) {
    HMODULE hmod = LoadLibraryW(path.toCString());
    if (!hmod) return nullptr;

    auto ppDllModuleInfo = (const gtlModuleInfo *const *)GetProcAddress(hmod, "GROVE2_DLL_MODULE_INFO");
    if (!ppDllModuleInfo) return nullptr;

    loadModule(*ppDllModuleInfo);

    return *ppDllModuleInfo;
}
