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

#include "GUI_Module.h"

#include <grUi/Style/GSS/Parser.h>
#include <gtlModule/ModuleInfo.h>
#include <grImg/ImgModule.h>

static void grUiStaticInit() {
    grUiGSSPropertyValueParserRegistry::staticInit();
}

static void grUiStaticRelease() {
    grUiGSSPropertyValueParserRegistry::staticRelease();
}

static const gtlModuleDependency grUiDeps[] = {
    &GROVE2_NAMED_MODULE_INFO_grImg,
    {}
};

GROVE2_DECLARE_MODULE(grUi){
    .moduleName         = "grUi",
    .moduleDescription  = GTXT("Grove2 UI Engine"),
    .moduleDependencies = grUiDeps,
    .staticInit         = &grUiStaticInit,
    .staticRelease      = &grUiStaticRelease,
    .provideService     = nullptr
};
