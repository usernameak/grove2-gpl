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

#include "StateCaches.h"

#include "DX11RenderInterface.h"

#include "gtlUtil/Hash.h"

grDX11::RasterizerStateCache::RasterizerStateCache(DX11RenderInterface *mRenderInterface)
    : m_renderInterface(mRenderInterface) {}

gnaStatus grDX11::RasterizerStateCache::findRasterizerState(
    const RasterizerStateInfo &info,
    ID3D11RasterizerStatePtr &rpState) {

    auto it = m_cachedStates.find(info);
    if (it == m_cachedStates.end()) {
        D3D11_RASTERIZER_DESC rasterDesc{};
        switch (info.primitiveMode) {
        case PipelineObject::PRIMITIVE_MODE_SOLID:
            rasterDesc.FillMode = D3D11_FILL_SOLID;
            break;
        case PipelineObject::PRIMITIVE_MODE_WIREFRAME:
            rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
            break;
        default:
            GR_FATAL(GTXT("Pipeline contains an unsupported fill mode"));
        }
        switch (info.cullMode) {
        case PipelineObject::CULL_MODE_BACK:
            rasterDesc.CullMode = D3D11_CULL_BACK;
            break;
        case PipelineObject::CULL_MODE_FRONT:
            rasterDesc.CullMode = D3D11_CULL_FRONT;
            break;
        case PipelineObject::CULL_MODE_NONE:
            rasterDesc.CullMode = D3D11_CULL_NONE;
            break;
        default:
            GR_FATAL(GTXT("Pipeline contains an unsupported cull mode"));
        }
        rasterDesc.FrontCounterClockwise = TRUE;
        rasterDesc.DepthBias             = info.depthBias;
        rasterDesc.DepthBiasClamp        = info.depthBiasClamp;
        rasterDesc.SlopeScaledDepthBias  = info.depthBiasSlopeScale;
        rasterDesc.DepthClipEnable       = TRUE;
        rasterDesc.ScissorEnable         = info.scissorTestEnable;
        rasterDesc.MultisampleEnable     = FALSE;
        rasterDesc.AntialiasedLineEnable = FALSE;

        auto &entry = m_cachedStates[info];

        HRESULT hres = m_renderInterface->m_device->CreateRasterizerState(&rasterDesc, &entry.rs);
        if (FAILED(hres)) {
            GR_WARNING(GTXT("dx11 RasterizerState compile failed with 0x%08x"), hres);
            entry.cachedError = GNA_E_FAILED;

            return entry.cachedError;
        }

        rpState           = entry.rs;
        entry.cachedError = GNA_E_OK;
        return entry.cachedError;
    }

    auto &entry = it->second;

    rpState = entry.rs;
    return entry.cachedError;
}

size_t
std::hash<grDX11::RasterizerStateInfo>::operator()(
    const grDX11::RasterizerStateInfo &info) const noexcept {

    std::size_t hash = 0;
    gutlHashCombine(hash, info.primitiveMode);
    gutlHashCombine(hash, info.cullMode);
    gutlHashCombine(hash, info.depthBias);
    gutlHashCombine(hash, info.depthBiasClamp);
    gutlHashCombine(hash, info.depthBiasSlopeScale);
    gutlHashCombine(hash, info.scissorTestEnable);
    return hash;
}