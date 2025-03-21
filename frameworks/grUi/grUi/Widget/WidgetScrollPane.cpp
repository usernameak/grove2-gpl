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

#include "WidgetScrollPane.h"

#include "WidgetScrollBar.h"

class grUiWidgetScrollPane::ScrollLayout : public grUiLayoutManager {
protected:
    grDimension initialMeasure(grUiWidgetLayout *parent, int biasedSize) override {
        assert(dynamic_cast<grUiWidgetScrollPane *>(parent) != nullptr);
        auto scrollPane = static_cast<grUiWidgetScrollPane *>(parent);

        auto contentWidget   = scrollPane->contentWidget;
        auto scrollbarWidget = scrollPane->scrollbarWidget;

        grDimension contentDim   = contentWidget ? contentWidget->measure() : grDimension{ 0, 0 };
        grDimension scrollbarDim = scrollbarWidget ? scrollbarWidget->measure() : grDimension{ 0, 0 };

        int width = contentDim.width + scrollbarDim.width;

        return parent->get_baseInsets().outsetDimension({ width, scrollbarDim.height });
    }

    void layout(grUiWidgetLayout *parent) override {
        assert(dynamic_cast<grUiWidgetScrollPane *>(parent) != nullptr);
        auto scrollPane = static_cast<grUiWidgetScrollPane *>(parent);

        grRectangle insetRect = parent->get_baseInsets().insetDimensionToRect(parent->get_size());

        auto contentWidget   = scrollPane->contentWidget;
        auto scrollbarWidget = scrollPane->scrollbarWidget;

        grDimension scrollbarDim = scrollbarWidget ? scrollbarWidget->measure() : grDimension{ 0, 0 };

        int contentWidth = insetRect.width - scrollbarDim.width;
        int paneHeight   = insetRect.height;

        if (contentWidget) {
            int biasedSize = 0;
            if (contentWidget->get_contentBias() == grUiEnumContentBias::CONTENT_BIAS_HORIZONTAL) {
                biasedSize = insetRect.width - scrollbarDim.width;
            }
            grDimension contentDim = contentWidget->measure(biasedSize);

            int offset;
            if (scrollPane->m_scrollFlags & SCROLL_FLAG_INVERT_OFFSET) {
                offset = -(std::max(contentDim.height, paneHeight) - paneHeight - scrollPane->scrollOffset);
            } else {
                offset = -scrollPane->scrollOffset;
            }

            contentWidget->set_bounds(
                insetRect.x, insetRect.y + offset,
                contentWidth, std::max(contentDim.height, paneHeight));
        }
        if (scrollbarWidget) {
            scrollbarWidget->set_bounds(
                insetRect.x + contentWidth, insetRect.y,
                scrollbarDim.width, paneHeight);
        }
    }
};

grUiWidgetScrollPane::grUiWidgetScrollPane()
    : scrollOffset(0),
      m_scrollFlags(0) {

    layout = gnaNew<ScrollLayout>();

    this->eventSink_mouseWheel.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseWheel));
    this->eventSink_mouseMove.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseMove), gnaEventPriority::PRIORITY_HIGHEST);
    this->eventSink_mouseLeave.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseLeave), gnaEventPriority::PRIORITY_HIGHEST);

    clipToBounds = true;

    auto scrollbar = gnaNew<grUiWidgetScrollBar>();
    set_scrollbarWidget(scrollbar);
}

void grUiWidgetScrollPane::set_contentWidget(gnaWeakPointer<grUiWidget> widget) {
    if (contentWidget) {
        remove(contentWidget);
    }
    if (widget) {
        add(widget);
    }
    contentWidget = widget;
}

void grUiWidgetScrollPane::set_scrollbarWidget(gnaWeakPointer<grUiWidget> widget) {
    if (scrollbarWidget) {
        remove(scrollbarWidget);
    }
    if (widget) {
        add(widget);
    }
    scrollbarWidget = widget;
}

void grUiWidgetScrollPane::scrollToTop() {
    scrollOffset = 0;
    forceLayout();

    forceUpdateMouse();
}

void grUiWidgetScrollPane::scrollToEnd() {
    forceLayout();

    grRectangle insetRect = get_baseInsets().insetDimensionToRect(get_size());

    const int contentHeight = contentWidget->get_size().height;
    const int parentHeight  = insetRect.height;
    scrollOffset = contentHeight - parentHeight;

    forceLayout();

    forceUpdateMouse();
}

bool grUiWidgetScrollPane::onMouseWheel(const grUiEventMouseWheel &ev) {
    int delta = ev.delta * 54 / 120; // TODO: use system settings
    scrollOffset += (m_scrollFlags & SCROLL_FLAG_INVERT_OFFSET) ? delta : -delta;

    grRectangle insetRect = get_baseInsets().insetDimensionToRect(get_size());

    if (contentWidget) {
        const int contentHeight = contentWidget->get_size().height;
        const int parentHeight  = insetRect.height;

        if (scrollOffset > contentHeight - parentHeight)
            scrollOffset = contentHeight - parentHeight;
    }
    if (scrollOffset < 0)
        scrollOffset = 0;

    if (contentWidget) {
        const int contentHeight = contentWidget->get_size().height;
        const int parentHeight  = insetRect.height;
        int offset;
        if (m_scrollFlags & SCROLL_FLAG_INVERT_OFFSET) {
            offset = -(contentHeight - parentHeight - scrollOffset);
        } else {
            offset = -scrollOffset;
        }
        contentWidget->set_position(insetRect.x, insetRect.y + offset);
    }

    forceUpdateMouse();

    return true;
}

void grUiWidgetScrollPane::forceUpdateMouse() {
    if (lastMouseX != INT_MAX && lastMouseY != INT_MAX) {
        grUiEventMouseMove mmev;
        mmev.dx = 0;
        mmev.dy = 0;
        mmev.x  = lastMouseX;
        mmev.y  = lastMouseY;
        eventSink_mouseMove.emit(mmev);
    }
}

bool grUiWidgetScrollPane::onMouseMove(grUiEventMouseMove &ev) {
    lastMouseX = ev.x;
    lastMouseY = ev.y;

    return true;
}

bool grUiWidgetScrollPane::onMouseLeave(grUiEventMouseLeave &ev) {
    lastMouseX = INT_MAX;
    lastMouseY = INT_MAX;

    return true;
}

GTL_RTTI_DEFINE(grUiWidgetScrollPane, GTL_RTTI_INHERITS(grUiWidgetLayout));
