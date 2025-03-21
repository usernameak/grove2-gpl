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

#include <gr2DCoords.h>
#include <gtlMemory/RcObject.h>
#include <gtlUtil/Misc.h>

#include <grUiNative/Widget/Widget3DView.h>

namespace grScene {
    class SceneObject;
    namespace Render {
        class RenderPassScene;
    }
}

namespace ged {
    namespace MaterialEditor {
        class MaterialEditor;

        class MaterialEditorView : public grUiWidget3DView {
            MaterialEditor *m_pEditor;

        public:
            MaterialEditorView(MaterialEditor *pEditor);

            void update() override;

            grRenderCore::RenderPass *get_renderPass() override;

            virtual ~MaterialEditorView() override;
        };
    }
}
