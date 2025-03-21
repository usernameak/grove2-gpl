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

#include <ged/Editor/Common/Base3DEditorView.h>
#include "gtlMath2/Transform/Transform.h"

namespace grScene {
    class SceneObject;
    namespace Render {
        class RenderPassScene;
    }
}

namespace ged {
    namespace SceneEditor {
        class SceneEditor;

        class SceneEditorView : public CommonEditor::Base3DEditorView {
            SceneEditor *m_pEditor;

            class SceneEditorDragContext : public grUiDragContext {
                gnaWeakPointer<SceneEditorView> m_view;
                gtlMath2::LocalTransform m_initialLocalTransform;
                gtlMath2::Transform m_initialGlobalTransform;
                gtlMath2::Vector2f m_initialScreenPosition;

            public:
                SceneEditorDragContext(
                    int mouseButton,
                    gnaWeakPointer<SceneEditorView> view,
                    const gtlMath2::LocalTransform &initialLocalTransform,
                    const gtlMath2::Transform &initialGlobalTransform,
                    const gtlMath2::Vector2f &initialScreenPosition
                );

                void dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) override;
            };

            enum : uint8_t {
                AXIS_KEY_X_BIT = GTL_BIT(0),
                AXIS_KEY_Y_BIT = GTL_BIT(1),
                AXIS_KEY_Z_BIT = GTL_BIT(2)
            };

            uint8_t m_axisKeyBits;
            bool m_snapToGrid : 1;

        public:
            SceneEditorView(SceneEditor *pEditor);
            virtual ~SceneEditorView() override;

            void onObjectSelected(gnaWeakPointer<grScene::SceneObject> obj);

            void on3DAction(gtlMath2::Vector2f position) override;

            void tick(float deltaTime) override;

        private:
            bool onKeyEvent(grUiEventKeyPress &ev);
        };
    }
}
