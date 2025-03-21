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

#include <d3d11.h>
#include <wrl/client.h>

namespace grDX11 {
    class DX11RenderInterface;

    class RasterizerStateCache {
        using ID3D11RasterizerStatePtr = Microsoft::WRL::ComPtr<ID3D11RasterizerState>;

        DX11RenderInterface *m_renderInterface;

        struct CacheEntry {
            ID3D11RasterizerStatePtr rs;
            gnaStatus cachedError;
        };

        std::unordered_map<RasterizerStateInfo, CacheEntry> m_cachedStates;

    public:
        explicit RasterizerStateCache(DX11RenderInterface *mRenderInterface);

        gnaStatus findRasterizerState(const RasterizerStateInfo &info, ID3D11RasterizerStatePtr &rpState);
    };
}
