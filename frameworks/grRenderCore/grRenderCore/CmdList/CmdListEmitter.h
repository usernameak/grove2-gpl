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
#include <grRenderCore/CmdList/CmdConstants.h>
#include <grRenderCore/RenderTypes.h>

namespace grImg {
    class Image;
}

namespace grRenderCore {
    class CmdList;
    class Sampler;
    struct MeshRegion;
    class PipelineObject;
    class ConstantBuffer;
    class RenderTargetSet;
    class InstancedMesh;
    class Mesh;

    class CmdListEmitter : public gtlRcObject {
    public:
        virtual ~CmdListEmitter() = default;

        virtual void begin() = 0;
        virtual gnaPointer<CmdList> end() = 0;

        virtual void cmdClear(
            std::underlying_type_t<grRenderCore::ClearFlags> flags,
            grRenderCore::RGBAColor clearColor = 0xFF000000,
            float clearDepth                   = 1.0f,
            uint32_t clearStencil              = 0) = 0;
        virtual void cmdBindRenderTargetSet(gnaWeakPointer<RenderTargetSet> rts) = 0;
        virtual void cmdViewport(int x, int y, int width, int height) = 0;
        virtual void cmdSetClipRect(int x, int y, int width, int height) = 0;
        virtual void cmdSetDepthBias(int32_t depthBias, float depthBiasClamp, float depthBiasSlopeScale) = 0;
        virtual void cmdBindPipeline(gnaWeakPointer<grRenderCore::PipelineObject> pipeline) = 0;
        virtual void cmdBindTexture(uint8_t slot, gnaWeakPointer<grImg::Image> image) = 0;
        virtual void cmdBindSampler(uint8_t slot, gnaWeakPointer<grRenderCore::Sampler> sampler) = 0;
        virtual void cmdBindConstantBuffer(uint8_t slot, gnaWeakPointer<grRenderCore::ConstantBuffer> cb) = 0;
        virtual void cmdDrawMesh(grRenderCore::MeshRegion meshRegion) = 0;
        virtual void cmdDrawInstancedMesh(
            gnaWeakPointer<grRenderCore::Mesh> mesh,
            gnaWeakPointer<grRenderCore::InstancedMesh> instancedMesh,
            uint32_t startInstance,
            uint32_t numInstances) = 0;
    };
}
