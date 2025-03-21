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

#include "DX11Module.h"

#include "DX11RenderInterface.h"
#include "PipelineObject.h"
#include "nxfSerialization/SerializationTypeRegistry.h"

#include <gtlModule/ModuleInfo.h>
#include <grRenderCore/RenderCoreModule.h>

static void *grDX11ProvideService(const gtl::ASCIICHAR *name) {
    if (gtl::StrCmp(name, "RenderInterface") == 0) {
        return gtlNew grDX11::DX11RenderInterface;
    }
    return nullptr;
}

namespace grDX11 {
    static void staticInit() {
        gnaSingleton<nxfSerialization::SerializationTypeRegistry>()->registerType<PipelineObject>("grDX11::PipelineObject");
    }

    static void staticRelease() {
        gnaSingleton<nxfSerialization::SerializationTypeRegistry>()->unregisterType("grDX11::PipelineObject");
    }
}

static const gtlModuleDependency grDX11Deps[] = {
    &GROVE2_MODULE_INFO(grRenderCore),
    {}
};

GROVE2_DECLARE_MODULE(grDX11){
    .moduleName         = "grDX11",
    .moduleDescription  = GTXT("Grove2 Direct3D 11 Renderer"),
    .moduleDependencies = grDX11Deps,

    .staticInit = &grDX11::staticInit,
    .staticRelease = &grDX11::staticRelease,

    .provideService     = &grDX11ProvideService,

};
