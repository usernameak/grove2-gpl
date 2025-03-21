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

#include "Sampler.h"

#include "DX11RenderInterface.h"
#include <gtlUtil/Logging.h>

grDX11::Sampler::Sampler(
    grDX11::DX11RenderInterface *renderInterface,
    const grRenderCore::SamplerProperties &props)
    : m_renderInterface(renderInterface) {

    D3D11_SAMPLER_DESC sampDesc{};
    sampDesc.Filter         = (D3D11_FILTER)props.filteringMode;
    sampDesc.AddressU       = (D3D11_TEXTURE_ADDRESS_MODE)props.addrModeU;
    sampDesc.AddressV       = (D3D11_TEXTURE_ADDRESS_MODE)props.addrModeV;
    sampDesc.AddressW       = (D3D11_TEXTURE_ADDRESS_MODE)props.addrModeW;
    sampDesc.MipLODBias     = props.lodBias;
    sampDesc.MaxAnisotropy  = props.maxAnisotropy;
    sampDesc.ComparisonFunc = (D3D11_COMPARISON_FUNC)props.cmpFunc;
    sampDesc.BorderColor[0] = props.borderColor.r;
    sampDesc.BorderColor[1] = props.borderColor.g;
    sampDesc.BorderColor[2] = props.borderColor.b;
    sampDesc.BorderColor[3] = props.borderColor.a;
    sampDesc.MinLOD         = props.minLOD;
    sampDesc.MaxLOD         = props.maxLOD;

    HRESULT hres = m_renderInterface->m_device->CreateSamplerState(&sampDesc, &m_samplerState);
    if (FAILED(hres)) {
        GR_FATAL(GTXT("Could not create sampler state: error 0x%08x"), hres);
    }
}
