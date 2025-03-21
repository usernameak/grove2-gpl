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

#include <gtlMemory/RcObject.h>
#include <gtlString/String.h>
#include <gtlMath2/Matrix/Matrix4x4.h>
#include "RenderCoreDLL.h"
#include "CmdList/CmdListEmitter.h"
#include "Stats/RenderStats.h"
#include "Sampler/SamplerProperties.h"

namespace grImg {
    class Image;
}

namespace grRenderCore {
    class InstancedMesh;
    class Mesh;
    class VideoOutputManager;
    class PipelineLibrary;
    class ConstantBuffer;
    class RenderTargetSetBuilder;
    class RenderPass;
    class Sampler;

    class GR_RENDERCORE_DLLIMPEXP RenderInterface {
    public:
        /** Flags for registerOrUpdateMesh */
        enum MeshRegisterFlags : uint32_t {
            /** Allocate memory and prepare for adding draw calls
             * into a command list. Don't upload the actual data. */
            MESH_REGISTER_FLAG_ONLY_ALLOCATE = GTL_BIT(0),
        };

        virtual ~RenderInterface() = default;

        virtual void initialize() {}
        virtual void destroy() = 0;

        virtual gnaWeakPointer<PipelineLibrary> get_pipelineLibrary() = 0;

        virtual void registerTexture(gnaPointer<grImg::Image> image)                               = 0;
        virtual void registerOrUpdateConstantBuffer(gnaPointer<grRenderCore::ConstantBuffer> cb)   = 0;

        /**
         * Prepares a mesh for rendering
         * @param mesh - the mesh to upload
         * @param flags - flags, bitfield from MeshRegisterFlags
         */
        virtual void registerOrUpdateMesh(gnaPointer<grRenderCore::Mesh> mesh, uint32_t flags = 0) = 0;

        /**
         * Prepares an instanced mesh for rendering
         * @param mesh - the mesh to upload
         * @param flags - flags, bitfield from MeshRegisterFlags
         */
        virtual void registerOrUpdateInstancedMesh(gnaPointer<grRenderCore::InstancedMesh> mesh, uint32_t flags = 0) = 0;

        virtual gnaPointer<CmdListEmitter> createCmdListEmitter()     = 0;
        virtual gnaPointer<RenderTargetSetBuilder> createRTSBuilder() = 0;

        virtual void executeRenderPass(gnaWeakPointer<CmdList> cmdList) = 0;

        virtual VideoOutputManager *get_videoOutputManager() = 0;

        virtual gtlMath2::Matrix4x4f convertProjectionMatrix(const gtlMath2::Matrix4x4f &matrix, bool isForTexture = false) {
            return matrix;
        }

        virtual gnaPointer<Sampler> findSampler(const SamplerProperties &properties) = 0;

        static RenderInterface *createRenderInterface(const gtl::String &rendererName);

        grRenderCore::RenderStats m_renderStats;
    };

    GR_RENDERCORE_DLLIMPEXP extern RenderInterface *g_renderInterface;
}
