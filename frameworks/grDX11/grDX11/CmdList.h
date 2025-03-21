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

#include "PipelineRenderObject.h"


#include <grRenderCore/CmdList/CmdList.h>
#include <grRenderCore/CmdList/CmdListEmitter.h>
#include <grRenderCore/RenderTarget/RenderTargetSet.h>
#include <wrl/client.h>
#include <d3d11.h>

namespace grDX11 {
    class DX11RenderInterface;

    class CmdListEmitter : public grRenderCore::CmdListEmitter {
        DX11RenderInterface *m_renderInterface;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;
        gnaPointer<grRenderCore::PipelineObject> m_currentPipeline;

        RasterizerStateInfo m_currentRasterizerStateInfo;
        Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_currentRasterizerState;

        gnaPointer<grRenderCore::RenderTargetSet> m_currentRTS;
        std::vector<gnaPointer<gtlRcObject>> m_heldReferences;

    public:
        explicit CmdListEmitter(DX11RenderInterface *renderInterface);

        void begin() override;
        gnaPointer<grRenderCore::CmdList> end() override;

        void cmdClear(std::underlying_type_t<grRenderCore::ClearFlags> flags, grRenderCore::RGBAColor clearColor, float clearDepth, uint32_t clearStencil) override;
        void cmdBindRenderTargetSet(gnaWeakPointer<grRenderCore::RenderTargetSet> rts) override;
        void cmdViewport(int x, int y, int width, int height) override;
        void cmdSetClipRect(int x, int y, int width, int height) override;
        void cmdSetDepthBias(int32_t depthBias, float depthBiasClamp, float depthBiasSlopeScale) override;
        void cmdBindPipeline(gnaWeakPointer<grRenderCore::PipelineObject> pipeline) override;
        void cmdBindTexture(uint8_t slot, gnaWeakPointer<grImg::Image> image) override;
        void cmdBindSampler(uint8_t slot, gnaWeakPointer<grRenderCore::Sampler> sampler) override;
        void cmdBindConstantBuffer(uint8_t slot, gnaWeakPointer<grRenderCore::ConstantBuffer> cb) override;
        void cmdDrawMesh(grRenderCore::MeshRegion meshRegion) override;
        void cmdDrawInstancedMesh(
            gnaWeakPointer<grRenderCore::Mesh> mesh,
            gnaWeakPointer<grRenderCore::InstancedMesh> instancedMesh,
            uint32_t startInstance,
            uint32_t numInstances) override;

    private:
        void preDraw();
    };

    class CmdList : public grRenderCore::CmdList {
        DX11RenderInterface *m_renderInterface;
        Microsoft::WRL::ComPtr<ID3D11CommandList> m_cmdList;
        std::vector<gnaPointer<gtlRcObject>> m_heldReferences;

    public:
        CmdList(
            DX11RenderInterface *renderInterface,
            Microsoft::WRL::ComPtr<ID3D11CommandList> cmdList,
            std::vector<gnaPointer<gtlRcObject>> &&heldReferences);
        void execute() override;
    };
}