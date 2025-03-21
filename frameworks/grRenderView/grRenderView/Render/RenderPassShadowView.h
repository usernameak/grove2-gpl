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

#include "RenderPassView.h"

namespace grRenderView::Render {
    class RenderPassShadowView : public RenderPassView {
        gnaPointer<grScene::Light> m_light;
        gtlMath2::AABB m_bbox;

    public:
        explicit RenderPassShadowView(
            RenderPassView *parent,
            gnaPointer<grScene::Light> light);

        void update(float deltaTime) override;

        bool bindPipelineFromInstKey(gnaWeakPointer<grRenderCore::CmdListEmitter> cmdList, const InstancingKey &key) override;
        void setupCameraPerspective() override;
    };
}