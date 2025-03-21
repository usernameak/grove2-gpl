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

#include "Widget3DView.h"

#include <grUi/Render/UiRenderer.h>

#include <grUiNative/Render/UiRendererImpl.h>

GTL_RTTI_DEFINE(grUiWidget3DView, GTL_RTTI_INHERITS(grUiWidget));

grUiWidget3DView::grUiWidget3DView() : lastRenderPass(nullptr), lastParentRenderPass(nullptr) {}

void grUiWidget3DView::preDraw(grUiRenderer *render, const grRectangle &clipRect) {
    grUiWidget::preDraw(render, clipRect);

    grRenderCore::RenderPass *renderPass = get_renderPass();

    auto dim = get_size();

    grRenderCore::RenderPass *parentRenderPass = dynamic_cast<grUiRendererImpl *>(render);

    if (lastRenderPass != renderPass || lastParentRenderPass != parentRenderPass) {
        // TODO: theoretically, it's possible that lastParentRenderPass will point to an invalid render pass
        releaseRenderPass(lastParentRenderPass, lastRenderPass);
        if (renderPass) {
            acquireRenderPass(parentRenderPass, renderPass);
            lastParentRenderPass = parentRenderPass;
            lastRenderPass       = renderPass;

            renderPass->resize(dim.width, dim.height);
            lastSize = dim;

            renderPass->update(0.0f);
        }
    } else if (renderPass) {
        assert(renderPass->m_rts);

        if (lastSize != dim) {
            lastSize = dim;
            if (lastSize.width > 0 && lastSize.height > 0) {
                renderPass->resize(lastSize.width, lastSize.height);
            }
        }
    }
}

void grUiWidget3DView::draw(grUiRenderer *render) {
    grUiWidget::draw(render);

    grRenderCore::RenderPass *renderPass = get_renderPass();

    auto dim = get_size();

    if (dim.width > 0 && dim.height > 0) {
        // TODO: will it always be attachment zero?
        grUiSprite spr{ renderPass->m_rts->getColorImage(0), 0.0f, 0.0f, 1.0f, 1.0f, (float)dim.width, (float)dim.height };

        render->drawSprite(0, 0, spr);
    }
}

void grUiWidget3DView::releaseLastRenderPass() {
    releaseRenderPass(lastParentRenderPass, lastRenderPass);
}

void grUiWidget3DView::acquireRenderPass(grRenderCore::RenderPass *parentPass, grRenderCore::RenderPass *pass) {
    if (!parentPass || !pass)
        return;

    auto &rdeps = parentPass->dependencies;
    rdeps.push_back(pass);
}

void grUiWidget3DView::releaseRenderPass(grRenderCore::RenderPass *parentPass, grRenderCore::RenderPass *pass) {
    if (!parentPass || !pass)
        return;

    grRenderCore::RenderPass *rootRenderPass = parentPass;

    auto &rdeps = rootRenderPass->dependencies;
    auto it     = std::find(rdeps.begin(), rdeps.end(), pass);
    if (it != rdeps.end()) {
        rdeps.erase(it);
    }
}

grDimension grUiWidget3DView::initialMeasure(int biasedSize) {
    return { 0, 0 };
}
