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

#include "RenderCoreModule.h"

#include "Mesh/InstancedMesh.h"
#include "Mesh/Mesh.h"
#include "Pipeline/PipelineLibrary.h"
#include "nxfSerialization/SerializationTypeRegistry.h"
#include <gtlModule/ModuleInfo.h>

namespace grRenderCore {
    static void staticInit() {
        using nxfSerialization::SerializationTypeRegistry;

        auto *registry = gnaSingleton<SerializationTypeRegistry>();
        registry->registerType<PipelineLibrary>("grRenderCore::PipelineLibrary");
        registry->registerType<Mesh>("grRenderCore::Mesh");
        registry->registerType<InstancedMesh>("grRenderCore::InstancedMesh");
    }

    static void staticRelease() {
        using nxfSerialization::SerializationTypeRegistry;

        auto *registry = gnaSingleton<SerializationTypeRegistry>();
        registry->unregisterType("grRenderCore::PipelineLibrary");
        registry->unregisterType("grRenderCore::Mesh");
        registry->unregisterType("grRenderCore::InstancedMesh");
    }
}

GROVE2_DECLARE_MODULE(grRenderCore){
    .moduleName        = "grRenderCore",
    .moduleDescription = GTXT("Grove2 Render Core"),
    .staticInit        = &grRenderCore::staticInit,
    .staticRelease     = &grRenderCore::staticRelease
};
