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

#include "RenderPass.h"

#include <grRenderCore/RenderInterface.h>

void grRenderCore::RenderPass::prepare(float deltaTime) {
    for (auto dep : dependencies) {
        dep->prepare(deltaTime);
    }

    m_commandList = prepareCommandList(deltaTime);
}

void grRenderCore::RenderPass::draw() {
    if (!m_rts->isValid()) return;

    for (auto dep : dependencies) {
        dep->draw();
    }

    m_renderInterface->executeRenderPass(m_commandList);
    m_commandList = nullptr;
}

void grRenderCore::RenderPass::invalidateFB() {
    if (m_rts) {
        m_rts->invalidate();
    }
}
