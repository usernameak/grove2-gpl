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

#include <gtlString/CString.h>

struct gtlModuleInfo;

struct GTL_DLLIMPEXP gtlModuleDependency {
    const gtl::ASCIICHAR *moduleName;
    const gtlModuleInfo *moduleInfo;

    constexpr gtlModuleDependency() : moduleName(nullptr), moduleInfo(nullptr) {}
    constexpr gtlModuleDependency(const gtl::ASCIICHAR *moduleName) : moduleName(moduleName), moduleInfo(nullptr) {}

    // this constructor is non-inline/constexpr
    // and defined in the cpp due to MSVC being
    // unable to reference dllimport globals
    // in a constant-initialized context
    gtlModuleDependency(const gtlModuleInfo *moduleInfo);
};

struct gtlModuleInfo {
    const gtl::ASCIICHAR *moduleName;
    const gtl::WIDECHAR *moduleDescription;
    const gtlModuleDependency *moduleDependencies;

    void (*staticInit)();
    void (*staticRelease)();

    void *(*provideService)(const gtl::ASCIICHAR *serviceName);
};

#ifdef GROVE2_BUILDING_MODULE_AS_DLL
#define GROVE2_MODULE_DLLEXPORT __declspec(dllexport)
#define GROVE2_MODULE_DECLARE_AS_DLL \
    extern "C" extern GROVE2_MODULE_DLLEXPORT constinit const gtlModuleInfo *const GROVE2_DLL_MODULE_INFO;
#define GROVE2_MODULE_DEFINE_AS_DLL(moduleName) \
    constinit const gtlModuleInfo *const GROVE2_DLL_MODULE_INFO = &GROVE2_NAMED_MODULE_INFO_##moduleName;
#else
#define GROVE2_MODULE_DLLEXPORT
#define GROVE2_MODULE_DECLARE_AS_DLL
#define GROVE2_MODULE_DEFINE_AS_DLL(moduleName)
#endif

#define GROVE2_DECLARE_MODULE(moduleName)                                                                         \
    GROVE2_MODULE_DECLARE_AS_DLL                                                                                  \
    extern "C" extern GROVE2_MODULE_DLLEXPORT constinit const gtlModuleInfo GROVE2_NAMED_MODULE_INFO_##moduleName; \
    GROVE2_MODULE_DEFINE_AS_DLL(moduleName)                                                                       \
    constinit const gtlModuleInfo GROVE2_NAMED_MODULE_INFO_##moduleName =

#define GROVE2_IMPORT_DLL_MODULE(moduleName) \
    extern "C" extern __declspec(dllimport) const gtlModuleInfo GROVE2_NAMED_MODULE_INFO_##moduleName;

#define GROVE2_IMPORT_STATIC_MODULE(moduleName) \
    extern "C" extern const gtlModuleInfo GROVE2_NAMED_MODULE_INFO_##moduleName;

#define GROVE2_MODULE_INFO(moduleName) GROVE2_NAMED_MODULE_INFO_##moduleName
