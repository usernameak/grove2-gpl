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

#include <grImg/Image.h>
#include <grRenderCore/RenderCoreDLL.h>
#include <grRenderCore/CmdList/CmdList.h>
#include <grRenderCore/RenderTarget/RenderTargetSet.h>

namespace grRenderCore {
    class RenderInterface;
    class GR_RENDERCORE_DLLIMPEXP RenderPass {

        gnaPointer<CmdList> m_commandList;

    protected:
        RenderInterface *m_renderInterface;

    public:
        std::vector<RenderPass *> dependencies;

        RenderPass(RenderInterface *renderInterface) : m_renderInterface(renderInterface) {}

        virtual void update(float deltaTime) {
            for (auto dep : dependencies) {
                dep->update(deltaTime);
            }
        }
        void prepare(float deltaTime);
        virtual gnaPointer<grRenderCore::CmdList> prepareCommandList(float deltaTime) = 0;
        void draw();
        void invalidateFB();
        virtual void resize(int width, int height) {}

        virtual ~RenderPass() = default;

        gnaPointer<RenderTargetSet> m_rts;
    };
}