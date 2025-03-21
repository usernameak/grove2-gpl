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

#include <gtlMemory/RcObject.h>
#include <gtlUtil/Misc.h>

#include <grUiNative/Widget/Widget3DView.h>
#include <grUi/Widget/Window/RootWindowManager.h>

namespace grRenderView {
    namespace Render {
        class RenderPassView;
    }
}

namespace grScene {
    class Node;
    class Camera;
}

namespace ged {
    namespace CommonEditor {
        class Base3DEditorView : public grUiWidget3DView {
            bool rotatingCamera = false;
            enum : uint16_t {
                MKEY_FORWARD = GTL_BIT(0),
                MKEY_BACK    = GTL_BIT(1),
                MKEY_LEFT    = GTL_BIT(2),
                MKEY_RIGHT   = GTL_BIT(3),
                MKEY_FAST    = GTL_BIT(4)
            };
            uint16_t movementKeys = 0;
            float yaw        = 0.0f;
            float pitch      = 0.0f;

            class SceneDnDContext : public grUiDragContext {
                gnaWeakPointer<Base3DEditorView> m_view;

            public:
                SceneDnDContext(const int mouseButton, gnaWeakPointer<Base3DEditorView> view);

                void dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) override;

                void dragRelease(gnaWeakPointer<grUiRootWindowManager> root) override;
            };

        protected:
            grRenderView::Render::RenderPassView *m_renderPass;
            gnaPointer<grScene::Camera> m_camera;

        public:
            Base3DEditorView(gnaPointer<grScene::Camera> camera);
            virtual ~Base3DEditorView() override;

            void update() override;
            void tick(float deltaTime) override;

            grRenderCore::RenderPass *get_renderPass() override;

        protected:
            virtual void on3DAction(gtlMath2::Vector2f position);

            // Window space to Screen space
            gtlMath2::Vector2f convertWindowSpaceToScreenSpace(int x, int y) const;

            gtlMath2::Vector2f windowSpaceDeltaToScreenSpace(int dx, int dy) const;

        private:
            bool onKeyPress(const grUiEventKeyPress &ev);
            bool onMouseDown(const grUiEventMouseDown &ev);
            bool onMouseUp(const grUiEventMouseUp &ev);
        };

    }
}
