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

#include <grUi/Drag/DragContext.h>
#include <grImg/Image.h>
#include <grUi/Widget/Widget.h>
#include <gtlMemory/RcObject.h>

namespace ged {
    namespace ImageEditor {
        class ImageEditorView : public grUiWidget {
            gnaPointer<grImg::Image> m_image;

            float m_zoom;
            gtlMath2::Vector2f m_panning;

            class DragContext : public grUiDragContext {
                gnaPointer<ImageEditorView> m_editorView;

            public:
                GTL_RTTI_DECLARE();

                DragContext(gnaPointer<ImageEditorView> editorView, int button);

                void dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) override;
            };

        public:
            GTL_RTTI_DECLARE();

            explicit ImageEditorView(gnaPointer<grImg::Image> image);

            ~ImageEditorView() override;

            grDimension initialMeasure(int biasedSize) override;
            void draw(grUiRenderer *render) override;

        private:
            void onMouseWheel(grUiEventMouseWheel &ev);
            bool onMouseDown(grUiEventMouseDown &ev);
        };
    }
}
