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

#include <grUi/Widget/Widget.h>
#include <grRenderCore/RenderPass/RenderPass.h>
#include <grUiNative/UiNativeDLL.h>

class GR_UI_NATIVE_DLLIMPEXP grUiWidget3DView : public grUiWidget {
    grRenderCore::RenderPass *lastRenderPass;
    grRenderCore::RenderPass *lastParentRenderPass;
    grDimension lastSize{ -1, -1 };

public:
    GTL_RTTI_DECLARE();

    grUiWidget3DView();

    void preDraw(grUiRenderer *render, const grRectangle &clipRect) override;
    void draw(grUiRenderer *) override;

    virtual grRenderCore::RenderPass *get_renderPass() = 0;

    grDimension initialMeasure(int biasedSize) override;

    void releaseLastRenderPass();

private:
    void acquireRenderPass(grRenderCore::RenderPass *parentPass, grRenderCore::RenderPass *pass);
    void releaseRenderPass(grRenderCore::RenderPass *parentPass, grRenderCore::RenderPass *pass);
};