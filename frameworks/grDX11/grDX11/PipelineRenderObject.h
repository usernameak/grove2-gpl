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

#include "PipelineObject.h"

#include <d3d11.h>
#include <wrl/client.h>

namespace grDX11 {
    struct RasterizerStateInfo {
        PipelineObject::PrimitiveMode primitiveMode;
        PipelineObject::CullMode cullMode;

        int32_t depthBias;
        float depthBiasClamp;
        float depthBiasSlopeScale;

        bool scissorTestEnable;

        bool operator==(const RasterizerStateInfo &other) const noexcept {
            return primitiveMode == other.primitiveMode &&
                   cullMode == other.cullMode &&
                   depthBias == other.depthBias &&
                   depthBiasClamp == other.depthBiasClamp &&
                   depthBiasSlopeScale == other.depthBiasSlopeScale &&
                   scissorTestEnable == other.scissorTestEnable;
        }

        bool operator!=(const RasterizerStateInfo &other) const noexcept {
            return !operator==(other);
        }
    };
}

template <>
struct std::hash<grDX11::RasterizerStateInfo> {
    size_t operator()(const grDX11::RasterizerStateInfo &info) const noexcept;
};

namespace grDX11 {
    class DX11RenderInterface;

    class PipelineRenderObject {
        DX11RenderInterface *m_renderInterface;
        gnaWeakPointer<PipelineObject> m_pipelineObject;

        Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
        Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
        Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
        Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

    public:
        explicit PipelineRenderObject(DX11RenderInterface *renderInterface);
        ~PipelineRenderObject();

        gnaStatus initialize(gnaWeakPointer<PipelineObject> pipelineObject);
        void bind(ID3D11DeviceContext *ctx);

        RasterizerStateInfo getDefaultRasterizerStateInfo();
    };
}