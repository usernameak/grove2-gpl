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

#include "Frame.h"

#include "FrameBorderInterface.h"
#include "FrameCaptionInterface.h"

#include <grUi/Style/Border/BorderNative.h>
#include <grUi/Widget/Native/NativeFramePlatform.h>
#include <grUi/Widget/Window/RootWindowManager.h>
#include <grUi/Layout/LayoutLinear.h>

grUiFrame::grUiFrame() : m_captionInterface(nullptr) {
    layout = nullptr;

    set_border(gnaNew<grUiBorderNative>());

    eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown), gnaEventPriority::PRIORITY_MONITOR);
    eventSink_mouseUp.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseUp), gnaEventPriority::PRIORITY_MONITOR);
}

grUiFrame::~grUiFrame() {
}

void grUiFrame::set_title(gtl::String title) {
    if (m_captionInterface) {
        m_captionInterface->set_title(title);
    }
    m_title = std::move(title);
}

gtl::String grUiFrame::get_title() {
    return m_title;
}

void grUiFrame::closeFrame() {
    if (get_parent()) {
        get_parent()->remove(this);
    }
}

void grUiFrame::set_contentWidget(gnaPointer<grUiWidget> widget) {
    if (contentWidget) {
        remove(contentWidget);
    }

    contentWidget = widget;
    if (m_captionWidget) {
        insertBefore(widget, m_captionWidget);
    } else {
        add(widget);
    }
}

grDimension grUiFrame::initialMeasure(int biasedSize) {
    grDimension contentDims = contentWidget ? contentWidget->measure() : grDimension{ 0, 0 };
    return get_insets(INSET_BORDER).outsetDimension(contentDims);
}

void grUiFrame::update() {
    if (m_autoPack && needsLayout()) {
        grUiWindowLayoutData::pack(this);
    }

    if (contentWidget && (!m_platform || !m_platform->usesExternalWindowManager())) {
        contentWidget->set_bounds(get_insets(INSET_BORDER).insetDimensionToRect(get_size()));
    }

    if (m_needsCaptionRefresh) {
        m_needsCaptionRefresh = false;
        updateCaptionDimensions();
    }

    grUiWidgetLayout::update();
}

void grUiFrame::onBoundsChanged() {
    grUiWidgetLayout::onBoundsChanged();

    m_needsCaptionRefresh = true;
}

void grUiFrame::widgetBorderChanged() {
    grUiWidget::widgetBorderChanged();

    auto border = get_border();
    auto fbi    = dynamic_cast<grUiFrameBorderInterface *>(&*border);

    if (m_captionWidget) {
        remove(m_captionWidget);
    }

    if (m_captionInterface) {
        m_captionInterface->set_frame(nullptr);
    }

    m_captionWidget    = fbi ? fbi->createCaptionWidget() : nullptr;
    m_captionInterface = dynamic_cast<grUiFrameCaptionInterface *>(&*m_captionWidget);

    if (m_captionWidget) {
        add(m_captionWidget);
    }

    if (m_captionInterface) {
        m_captionInterface->set_frame(gnaWeakPointer(this));
        m_captionInterface->set_title(get_title());
    }
    updateCaptionDimensions();
}

void grUiFrame::updateCaptionDimensions() {
    if (m_captionWidget) {
        grInsets marginInsets = get_insets(INSET_MARGIN);
        grRectangle rc        = marginInsets.insetDimensionToRect(get_size());
        rc.height             = m_captionWidget->measure().height;
        m_captionWidget->set_bounds(rc);
    }
}

void grUiFrame::displayPopup(gnaWeakPointer<grUiWidgetLayout> windowManager, uint32_t flags) {
    if (get_parent() != windowManager) {
        windowManager->add(gnaWeakPointer(this));
    }

    if (!(flags & POPF_NOPACK)) {
        grUiWindowLayoutData::pack(this);
    }
    if (!(flags & POPF_NOCENTER)) {
        grUiWindowLayoutData::center(this, windowManager);
    }
    set_focused(true);
}

void grUiFrame::togglePopup(gnaWeakPointer<grUiWidgetLayout> windowManager, uint32_t flags) {
    if (get_parent()) {
        assert(get_parent() == windowManager);

        closeFrame();
    } else {
        displayPopup(windowManager, flags);
    }
}

void grUiFrame::bringToFront() {
    auto sib = nextSibling();
    if (sib && gtlIsKindOf<grUiFrame>(sib)) {
        gnaPointer<grUiFrame> ptr(gnaWeakPointer(this));
        gnaWeakPointer<grUiWidgetLayout> parent = get_parent();
        parent->remove(ptr, PFLAG_NO_EVENTS);
        parent->add(ptr, PFLAG_NO_EVENTS);
    }
}

bool grUiFrame::onMouseDown(const grUiEventMouseDown &ev) {
    if ((!m_platform || !m_platform->usesExternalWindowManager()) && ev.button == 0) {
        bringToFront();

        grUi_gRootWindowManager->startDragAndDrop(
            gnaNew<grUiFrameDragContext>(
                gnaWeakPointer(this), // do not replace to just `this`. it won't increase refcount in that case
                grPoint{ -ev.x, -ev.y },
                ev.button));
    }

    return false;
}

bool grUiFrame::onMouseUp(const grUiEventMouseUp &ev) {
    return false;
}

void grUiFrame::handleParentChanged(gnaWeakPointer<grUiWidgetLayout> parent) {
    grUiWidget::handleParentChanged(parent);

    if (parent) {
        grUiEventPerformAction ev{};
        eventSink_windowOpen.emit(ev);
    }
}

void grUiFrame::onLostParent() {
    grUiWidgetLayout::onLostParent();

    grUiEventPerformAction ev{};
    eventSink_windowClose.emit(ev);
}

GTL_RTTI_DEFINE(grUiFrame, GTL_RTTI_INHERITS(grUiWidgetLayout));

// --- //

grUiFrame::grUiFrameDragContext::grUiFrameDragContext(gnaPointer<grUiFrame> frame, grPoint startOffset, int button)
    : grUiDragContext(frame, button),
      m_startOffset(startOffset),
      m_frame(frame) {}

void grUiFrame::grUiFrameDragContext::dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) {
    int resultX = x + m_startOffset.x;
    int resultY = y + m_startOffset.y;
    m_frame->set_position(resultX, resultY);
}

void grUiFrame::grUiFrameDragContext::dragRelease(gnaWeakPointer<grUiRootWindowManager> root) {
}
