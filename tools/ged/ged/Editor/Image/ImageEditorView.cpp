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

#include "ImageEditorView.h"

#include <grUi/Widget/Window/RootWindowManager.h>

GTL_RTTI_DEFINE(ged::ImageEditor::ImageEditorView, GTL_RTTI_INHERITS(grUiWidget));

ged::ImageEditor::ImageEditorView::ImageEditorView(gnaPointer<grImg::Image> image)
    : m_image(std::move(image)),
      m_zoom(1),
      m_panning(0, 0) {
    this->eventSink_mouseWheel.addHandlerV(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseWheel));
    this->eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
}

ged::ImageEditor::ImageEditorView::~ImageEditorView() = default;

grDimension ged::ImageEditor::ImageEditorView::initialMeasure(int biasedSize) {
    return get_baseInsets().outsetDimension({ 0, 0 });
}

void ged::ImageEditor::ImageEditorView::draw(grUiRenderer *render) {
    grUiWidget::draw(render);

    grRectangle rc = get_baseInsets().insetDimensionToRect(get_size());

    render->pushClip(rc);

    grUiSprite sprite(m_image);
    sprite.dstWidth *= m_zoom;
    sprite.dstHeight *= m_zoom;

    render->drawSprite(
        rc.x + (rc.width - sprite.dstWidth) * .5f + m_panning.x * m_zoom,
        rc.y + (rc.height - sprite.dstHeight) * .5f + m_panning.y * m_zoom,
        sprite);

    render->popClip();
}

void ged::ImageEditor::ImageEditorView::onMouseWheel(grUiEventMouseWheel &ev) {
    grRectangle rc = get_baseInsets().insetDimensionToRect(get_size());

    float newZoom = m_zoom * pow(2.0f, ev.delta / 120.0f);

    gtlMath2::Vector2f c = {
        ev.x - rc.x - rc.width * .5f,
        ev.y - rc.y - rc.height * .5f
    };

    m_panning += c / newZoom - c / m_zoom;

    m_zoom = newZoom;
}

bool ged::ImageEditor::ImageEditorView::onMouseDown(grUiEventMouseDown &ev) {
    if (ev.button == 0) {
        grUi_gRootWindowManager->startDragAndDrop(
            gnaNew<DragContext>(
                gnaWeakPointer(this), // do not replace to just `this`. it won't increase refcount in that case
                ev.button));
    }

    return false;
}

// --- //

GTL_RTTI_DEFINE(ged::ImageEditor::ImageEditorView::DragContext, GTL_RTTI_INHERITS(grUiDragContext));

ged::ImageEditor::ImageEditorView::DragContext::DragContext(gnaPointer<ImageEditorView> editorView, int button)
    : grUiDragContext(editorView, button),
      m_editorView(std::move(editorView)) {}

void ged::ImageEditor::ImageEditorView::DragContext::dragMove(
    gnaWeakPointer<grUiRootWindowManager> root,
    int x, int y,
    int dx, int dy) {

    m_editorView->m_panning.x += dx / m_editorView->m_zoom;
    m_editorView->m_panning.y += dy / m_editorView->m_zoom;
}
