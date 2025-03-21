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

#include "PipelineRenderObject.h"

#include "DX11RenderInterface.h"
#include <nxfUtil/BinaryResource.h>

grDX11::PipelineRenderObject::PipelineRenderObject(DX11RenderInterface *renderInterface)
    : m_renderInterface(renderInterface) {}

grDX11::PipelineRenderObject::~PipelineRenderObject() = default;

gnaStatus grDX11::PipelineRenderObject::initialize(gnaWeakPointer<PipelineObject> pipelineObject) {
    m_pipelineObject = pipelineObject;

    HRESULT hres;

    // vertex shader

    auto vsBinary = m_pipelineObject->get_vertexShaderBinary();
    hres          = m_renderInterface->m_device->CreateVertexShader(vsBinary->data, vsBinary->size, nullptr, &m_vertexShader);
    if (FAILED(hres)) {
        GR_WARNING(GTXT("dx11 Vertex Shader compile failed with 0x%08x"), hres);
        return GNA_E_FAILED;
    }

    // pixel shader

    auto psBinary = m_pipelineObject->get_pixelShaderBinary();
    if (psBinary) {
        hres = m_renderInterface->m_device->CreatePixelShader(psBinary->data, psBinary->size, nullptr, &m_pixelShader);
        if (FAILED(hres)) {
            GR_WARNING(GTXT("dx11 Pixel Shader compile failed with 0x%08x"), hres);
            return GNA_E_FAILED;
        }
    } else {
        m_pixelShader = nullptr;
    }

    // blend state

    D3D11_BLEND_DESC blendDesc{};
    blendDesc.AlphaToCoverageEnable  = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;
    switch (m_pipelineObject->get_blendMode()) {
    case grRenderCore::BLEND_MODE_NORMAL:
        blendDesc.RenderTarget[0].BlendEnable           = FALSE;
        blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_ONE;
        blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_ZERO;
        blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
        blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
        blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        break;
    case grRenderCore::BLEND_MODE_TRANSLUCENT:
        blendDesc.RenderTarget[0].BlendEnable           = TRUE;
        blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
        blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
        blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_SRC_ALPHA;
        blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_INV_SRC_ALPHA;
        blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        break;
    default:
        GR_FATAL(GTXT("Pipeline contains an unsupported blending mode"));
    }

    hres = m_renderInterface->m_device->CreateBlendState(&blendDesc, &m_blendState);
    if (FAILED(hres)) {
        GR_WARNING(GTXT("dx11 BlendState compile failed with 0x%08x"), hres);
        return GNA_E_FAILED;
    }

    // depth/stencil state

    D3D11_DEPTH_STENCIL_DESC dsDesc{};
    dsDesc.DepthEnable    = m_pipelineObject->get_depthTest() ? TRUE : FALSE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc      = D3D11_COMPARISON_LESS_EQUAL;
    dsDesc.StencilEnable  = FALSE;

    hres = m_renderInterface->m_device->CreateDepthStencilState(&dsDesc, &m_depthStencilState);
    if (FAILED(hres)) {
        GR_WARNING(GTXT("dx11 DepthStencilState compile failed with 0x%08x"), hres);
        return GNA_E_FAILED;
    }

    // input layout

    auto vertexFormat = m_pipelineObject->get_vertexFormat();
    if (vertexFormat == 0) {
        m_inputLayout = nullptr;
    } else {
        grRenderCore::VertexFormatInfo info(vertexFormat);
        grRenderCore::InstanceVertexFormatInfo instanceInfo(vertexFormat);
        D3D11_INPUT_ELEMENT_DESC inputElements[16];
        unsigned int i = 0;
        if (vertexFormat & grRenderCore::VFF_POSITION) {
            inputElements[i].SemanticName         = "POSITION";
            inputElements[i].SemanticIndex        = 0;
            inputElements[i].Format               = DXGI_FORMAT_R32G32B32_FLOAT;
            inputElements[i].InputSlot            = 0;
            inputElements[i].AlignedByteOffset    = info.m_offsets[grRenderCore::VFA_POSITION];
            inputElements[i].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            inputElements[i].InstanceDataStepRate = 0;
            i++;
        }
        if (vertexFormat & grRenderCore::VFF_TEXCOORD) {
            inputElements[i].SemanticName         = "TEXCOORD";
            inputElements[i].SemanticIndex        = 0;
            inputElements[i].Format               = DXGI_FORMAT_R32G32_FLOAT;
            inputElements[i].InputSlot            = 0;
            inputElements[i].AlignedByteOffset    = info.m_offsets[grRenderCore::VFA_TEXCOORD];
            inputElements[i].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            inputElements[i].InstanceDataStepRate = 0;
            i++;
        }
        if (vertexFormat & grRenderCore::VFF_NORMAL) {
            inputElements[i].SemanticName         = "NORMAL";
            inputElements[i].SemanticIndex        = 0;
            inputElements[i].Format               = DXGI_FORMAT_R32G32B32_FLOAT;
            inputElements[i].InputSlot            = 0;
            inputElements[i].AlignedByteOffset    = info.m_offsets[grRenderCore::VFA_NORMAL];
            inputElements[i].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            inputElements[i].InstanceDataStepRate = 0;
            i++;
        }
        if (vertexFormat & grRenderCore::VFF_COLOR) {
            inputElements[i].SemanticName         = "COLOR";
            inputElements[i].SemanticIndex        = 0;
            inputElements[i].Format               = DXGI_FORMAT_R8G8B8A8_UNORM;
            inputElements[i].InputSlot            = 0;
            inputElements[i].AlignedByteOffset    = info.m_offsets[grRenderCore::VFA_COLOR];
            inputElements[i].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            inputElements[i].InstanceDataStepRate = 0;
            i++;
        }
        if (vertexFormat & grRenderCore::VFF_TANGENT) {
            inputElements[i].SemanticName         = "TANGENT";
            inputElements[i].SemanticIndex        = 0;
            inputElements[i].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
            inputElements[i].InputSlot            = 0;
            inputElements[i].AlignedByteOffset    = info.m_offsets[grRenderCore::VFA_TANGENT];
            inputElements[i].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            inputElements[i].InstanceDataStepRate = 0;
            i++;
        }
        if (vertexFormat & grRenderCore::VFF_BLENDINDICES) {
            inputElements[i].SemanticName         = "BLENDINDICES";
            inputElements[i].SemanticIndex        = 0;
            inputElements[i].Format               = DXGI_FORMAT_R8G8B8A8_UINT;
            inputElements[i].InputSlot            = 0;
            inputElements[i].AlignedByteOffset    = info.m_offsets[grRenderCore::VFA_BLENDINDICES];
            inputElements[i].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            inputElements[i].InstanceDataStepRate = 0;
            i++;
        }
        if (vertexFormat & grRenderCore::VFF_BLENDWEIGHTS) {
            inputElements[i].SemanticName         = "BLENDWEIGHTS";
            inputElements[i].SemanticIndex        = 0;
            inputElements[i].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
            inputElements[i].InputSlot            = 0;
            inputElements[i].AlignedByteOffset    = info.m_offsets[grRenderCore::VFA_BLENDWEIGHTS];
            inputElements[i].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            inputElements[i].InstanceDataStepRate = 0;
            i++;
        }
        if (vertexFormat & grRenderCore::VFF_INSTANCE_TRANSFORM) {
            // oh my god...
            for (int j = 0; j < 3; j++) {
                inputElements[i].SemanticName         = "POSITION";
                inputElements[i].SemanticIndex        = j + 1;
                inputElements[i].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
                inputElements[i].InputSlot            = 1;
                inputElements[i].AlignedByteOffset    = instanceInfo.m_offsets[grRenderCore::VFA_INSTANCE_TRANSFORM] + 4 * sizeof(float) * j;
                inputElements[i].InputSlotClass       = D3D11_INPUT_PER_INSTANCE_DATA;
                inputElements[i].InstanceDataStepRate = 1;
                i++;
            }
        }
        hres = m_renderInterface->m_device->CreateInputLayout(
            inputElements, i,
            vsBinary->data, vsBinary->size,
            &m_inputLayout);
        if (FAILED(hres)) {
            GR_WARNING(GTXT("dx11 InputLayout compile failed with 0x%08x"), hres);
            return GNA_E_FAILED;
        }
    }

    return GNA_E_OK;
}

void grDX11::PipelineRenderObject::bind(ID3D11DeviceContext *ctx) {
    ctx->VSSetShader(m_vertexShader.Get(), nullptr, 0);
    ctx->PSSetShader(m_pixelShader.Get(), nullptr, 0);
    ctx->OMSetBlendState(m_blendState.Get(), nullptr, 0xffffffff);
    ctx->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
    ctx->IASetInputLayout(m_inputLayout.Get());
}

grDX11::RasterizerStateInfo grDX11::PipelineRenderObject::getDefaultRasterizerStateInfo() {
    RasterizerStateInfo info = {
        .primitiveMode       = m_pipelineObject->get_primitiveMode(),
        .cullMode            = m_pipelineObject->get_cullMode(),
        .depthBias           = 0,
        .depthBiasClamp      = 0,
        .depthBiasSlopeScale = 0,
        .scissorTestEnable   = m_pipelineObject->get_scissorTest()
    };

    return info;
}
