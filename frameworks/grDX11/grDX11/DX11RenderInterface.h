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

#include <grRenderCore/RenderInterface.h>

#include <d3d11.h>
#include <wrl/client.h>

#include "VideoOutputManager.h"
#include "ConstBuffer.h"
#include "StateCaches.h"

#include <grRenderCore/Pipeline/PipelineLibrary.h>

namespace grDX11 {
    class PipelineObject;

    class DX11RenderInterface : public grRenderCore::RenderInterface {
        gnaPointer<grRenderCore::PipelineLibrary> m_pipelineLibrary;
        std::vector<gnaWeakPointer<PipelineObject>> m_loadedPipelines;
        HMODULE m_dxgiLib, m_d3d11Lib;

        VideoOutputManager m_videoOutputManager;
        std::unordered_map<grRenderCore::SamplerProperties, gnaPointer<grRenderCore::Sampler>> m_samplerCache;

    public:
        Microsoft::WRL::ComPtr<IDXGIFactory1> m_dxgiFactory;
        Microsoft::WRL::ComPtr<ID3D11Device> m_device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_immediateContext;

        DX11RenderInterface();
        ~DX11RenderInterface() override;

        void initialize() override;
        void destroy() override;

        gnaWeakPointer<grRenderCore::PipelineLibrary> get_pipelineLibrary() override;

        void registerTexture(gnaPointer<grImg::Image> image) override;
        void registerOrUpdateConstantBuffer(gnaPointer<grRenderCore::ConstantBuffer> cb) override;
        void registerOrUpdateMesh(gnaPointer<grRenderCore::Mesh> mesh, uint32_t flags = 0) override;
        void registerOrUpdateInstancedMesh(gnaPointer<grRenderCore::InstancedMesh> mesh, uint32_t flags = 0) override;

        gnaPointer<grRenderCore::CmdListEmitter> createCmdListEmitter() override;
        gnaPointer<grRenderCore::RenderTargetSetBuilder> createRTSBuilder() override;

        void executeRenderPass(gnaWeakPointer<grRenderCore::CmdList> cmdList) override;

        grRenderCore::VideoOutputManager *get_videoOutputManager() override;
        gtlMath2::Matrix4x4f convertProjectionMatrix(const gtlMath2::Matrix4x4f &matrix, bool isForTexture) override;
        gnaPointer<grRenderCore::Sampler> findSampler(const grRenderCore::SamplerProperties &properties) override;

        ConstBufferPool m_constBufferPool;
        RasterizerStateCache m_rasterizerStateCache;

    private:
        void loadPipelines();
        void loadPipeline(gnaWeakPointer<PipelineObject> pipeline);
    };
}