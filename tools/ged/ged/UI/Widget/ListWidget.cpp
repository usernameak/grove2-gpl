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

#include "ListWidget.h"

#include <grUi/Text/TextRenderer.h>

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/Window/RootWindowManager.h>

#include <grUi/Utils/DragOrClick.h>

using namespace ged::ui;

ListWidget::ListWidget() {
    set_padding({ 5 });

    layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);
}

void ListWidget::updateList() {
    removeAll();
    EventListPopulate ev;
    eventSink_populate.emit(ev);
    for (gnaWeakPointer<grUiWidget> w : ev.list) {
        add(w);
    }
}


ListEntry::ListEntry(gtl::String text) : eventSink_doubleClick(this), name(text) {
    eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(this->eventSink_doubleClick, onMouseDown));
    eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
    eventSink_doubleClick.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onDoubleClick));
    eventSink_keyEvent.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onKeyPress));
    eventSink_focus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onFocus));
}

grDimension ListEntry::initialMeasure(int biasedSize) {
    grInsets ins = get_baseInsets();

    grUiTextRenderer tr(get_metricContext(), font);
    float entryHeight = std::max(tr.get_lineHeight(), 16.0f);

    return ins.outsetDimension({ 0, (int)std::ceil(entryHeight) });
}

void ListEntry::draw(grUiRenderer *uiRenderer) {
    grUiWidget::draw(uiRenderer);

    int nestingLevel = 0;

    grInsets ins   = get_baseInsets();
    grRectangle rc = ins.insetDimensionToRect(get_size());

    grUiTextRenderer tr(get_metricContext(), font);
    //  auto fontRenderer = gnaSingleton<grUiFontCache>()->get_fontRenderer(font);

    float entryHeight = std::max(tr.get_lineHeight(), 16.0f);

    int x     = rc.x + nestingLevel * 16;
    int y     = rc.y;
    int width = rc.width - nestingLevel * 16;

    if (get_focused()) {
        if (get_fullyFocused()) {
            uiRenderer->drawRectf(x, y, width, entryHeight, 0xFF007ACC);
        } else {
            uiRenderer->drawRectf(x, y, width, entryHeight, 0xFF3F3F46);
        }
    }
    const grUiSprite &icon = this->icon.withDstSize(16, 16);
    uiRenderer->drawSprite(x, y, icon);
    tr.setOrigin(x + icon.dstWidth + 4, y + tr.get_ascender());
    tr.render(uiRenderer, name);
}

bool ListEntry::onMouseDown(const grUiEventMouseDown &ev) {
    if (ev.button == 0) {
        if (m_dragObject) {
            auto dragCtx = gnaNew<grUiObjectDragContext>(this, ev.button, m_dragObject);

            auto ctx = grUiStartDragOrClick(this, dragCtx);
            ctx->eventSink_performAction.addHandler([this](auto &ev1) {
                set_focused(true);
                return true;
            });
        } else {
            set_focused(true);
        }
    } else if (ev.button == 1) {
        set_focused(true);

        auto dropDownMenu = gnaNew<grUi::DropDownMenu>();

        gedEventTreeListContextMenu ev1;
        ev1.dropDown = dropDownMenu;
        eventSink_contextMenu.emit(ev1);

        grPoint relPos = computeRelativePosition(grUi_gRootWindowManager);

        // TODO: this is wrong way to do this
        int x = relPos.x + ev.x;
        x -= dropDownMenu->get_size().width;
        if (x < 0) {
            x = 0;
        }
        int y = relPos.y + ev.y;

        if (dropDownMenu->numChildren() > 0) {
            dropDownMenu->showAt(x, y);
        }
    }

    return true;
}

bool ListEntry::onKeyPress(const grUiEventKeyPress &ev) {
    if (ev.action == GR_ACTION_KEY_PRESSED) {
        if (ev.keycode == grKeycode::GR_KEY_RETURN) {
            gedEventTreeListOpenEntry ev1;
            eventSink_openEntry.emit(ev1);
        }
    }

    return true;
}

bool ListEntry::onDoubleClick(const grUiEventDoubleClick &ev) {
    set_focused(true);

    gedEventTreeListOpenEntry ev1;
    eventSink_openEntry.emit(ev1);

    return true;
}

bool ListEntry::onFocus(const grUiEventFocus &ev) {
    gedEventTreeListSelectEntry ev1;
    eventSink_selectEntry.emit(ev1);
    return true;
}
