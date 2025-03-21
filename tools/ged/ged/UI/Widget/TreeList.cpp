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

#include "TreeList.h"
#include "grUi/Text/TextRenderer.h"

#include <algorithm>

#include <grUi/Render/UiRenderer.h>
#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/Window/WindowManager.h>
#include <grUi/Widget/DropDownMenu.h>
#include <grUi/Widget/Window/RootWindowManager.h>

#include <grUi/Utils/DragOrClick.h>

GTL_RTTI_DEFINE(gedTreeList, GTL_RTTI_INHERITS(grUiWidgetLayout));

static constexpr int PLUS_ICON_WIDTH = 16;

gedTreeList::gedTreeList() {
    set_padding({ 5 });

    layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);
    eventSink_keyEvent.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onKeyPress));
}

void gedTreeList::updateList() {
    gedEventTreeListPopulateSublist ev;
    eventSink_populateSublist.emit(ev);

    removeAll();

    for (gedEventTreeListPopulateSublist::Entry entry : ev.sublist) {
        auto widget                             = entry.widget;
        gedTreeListEntryInterface *subInterface = entry.entry;

        subInterface->parentEntry  = nullptr;
        subInterface->nestingLevel = 0;

        add(widget);
    }
}

// TODO: expanding and collapsing are highly unoptimized, optimize!

void gedTreeList::expandEntry(gedTreeListEntryInterface *entryInterface) {
    gedEventTreeListPopulateSublist ev;
    entryInterface->eventSink_populateSublist.emit(ev);

    gnaWeakPointer<grUiWidget> entryWidget = entryInterface->get_widget();

    gnaPointer<grUiWidget> before = entryWidget;

    for (gedEventTreeListPopulateSublist::Entry entry : ev.sublist) {
        auto widget                             = entry.widget;
        gedTreeListEntryInterface *subInterface = entry.entry;

        subInterface->parentEntry  = entryWidget;
        subInterface->nestingLevel = entryInterface->nestingLevel + 1;

        insertAfter(widget, before);
        before = widget;
    }
}

void gedTreeList::collapseEntry(gedTreeListEntryInterface *entryInterface) {
    std::vector<gnaWeakPointer<grUiWidget>> removalList;
    std::vector<gnaWeakPointer<grUiWidget>> parentList;
    bool foundEntry = false;

    gnaWeakPointer<grUiWidget> entryWidget = entryInterface->get_widget();

    for (auto widget : *this) {
        gedTreeListEntryInterface *ifc = dynamic_cast<gedTreeListEntryInterface *>(&*widget);
        if (!foundEntry) {
            if (widget == entryWidget) {
                foundEntry = true;
                parentList.push_back(widget);
            }
        } else {
            while (ifc->parentEntry != parentList.back()) {
                parentList.pop_back();
                if (parentList.empty()) {
                    goto quitLabel;
                }
            }
            removalList.push_back(widget);
            if (ifc->expanded) {
                parentList.push_back(widget);
            }
        }
    }
quitLabel:

    for (auto widget : removalList) {
        remove(widget);
    }
}

bool gedTreeList::onKeyPress(const grUiEventKeyPress &ev) {
    if (ev.action == GR_ACTION_KEY_PRESSED || ev.action == GR_ACTION_KEY_REPEATED) {
        if (ev.keycode == grKeycode::GR_KEY_UP) {
            /*auto &children = get_children();
            for (int i = 0; i < children.size(); i++) {
                if (children[i]->get_focused()) {
                    if (i - 1 < 0) {
                        break;
                    }
                    children[i - 1]->set_focused(true);
                    break;
                }
            }*/
        } else if (ev.keycode == grKeycode::GR_KEY_DOWN) {
            /*auto &children = get_children();
            for (int i = 0; i < children.size(); i++) {
                if (children[i]->get_focused()) {
                    if (i + 1 >= children.size()) {
                        break;
                    }
                    children[i + 1]->set_focused(true);
                    break;
                }
            }*/
            // TODO: fix arrow controls
        }
    }
    return true;
}

/////

gedTreeListEntryWidget::gedTreeListEntryWidget() : eventSink_doubleClick(this) {
    extensionData = static_cast<gedTreeListEntryInterface *>(this);

    eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(this->eventSink_doubleClick, onMouseDown));
    eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
    eventSink_doubleClick.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onDoubleClick));
    eventSink_keyEvent.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onKeyPress));
    eventSink_focus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onFocus));
}

grDimension gedTreeListEntryWidget::initialMeasure(int biasedSize) {
    grInsets ins = get_baseInsets();

    grUiTextRenderer tr(get_metricContext(), font);
    float entryHeight = std::max(tr.get_lineHeight(), 16.0f);

    return ins.outsetDimension({ 0, (int)std::ceil(entryHeight) });
}

void gedTreeListEntryWidget::draw(grUiRenderer *uiRenderer) {
    grUiWidget::draw(uiRenderer);

    grUiTextRenderer tr(get_metricContext(), font);

    grInsets ins   = get_baseInsets();
    grRectangle rc = ins.insetDimensionToRect(get_size());

    float entryHeight = std::max(tr.get_lineHeight(), 16.0f);

    nxfRID iconsSRID     = { GTXT("/textures/ui/icons/groupicons.png") };
    grUiSprite plusIcon  = grUiSprite::createTexModalRect(iconsSRID, 0, 16, 16, 16, 64, 64);
    grUiSprite minusIcon = grUiSprite::createTexModalRect(iconsSRID, 16, 16, 16, 16, 64, 64);

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
    grUiSprite icon = this->icon.withDstSize(16, 16);
    if (isExpandable) {
        const grUiSprite &expandIcon = expanded ? minusIcon : plusIcon;
        uiRenderer->drawSprite(x, y + std::round((entryHeight - expandIcon.dstHeight) / 2), expandIcon);
    }
    uiRenderer->drawSprite(x + plusIcon.dstWidth, y + std::round((entryHeight - icon.dstHeight) / 2), icon);
    tr.setOrigin(x + plusIcon.dstWidth + icon.dstWidth + 4, y + tr.get_ascender());
    tr.render(uiRenderer, name);
}

void gedTreeListEntryWidget::flipExpand() {
    assert(get_parent().rttiCast2<gedTreeList>().hasValue());
    gnaWeakPointer<gedTreeList> list = get_parent().cast<gedTreeList>();
    if (!expanded) {
        list->expandEntry(this);
    } else {
        list->collapseEntry(this);
    }
    expanded = !expanded;
}

bool gedTreeListEntryWidget::onMouseDown(const grUiEventMouseDown &ev) {
    grInsets ins   = get_baseInsets();
    grRectangle rc = ins.insetDimensionToRect(get_size());
    int x          = rc.x + nestingLevel * 16;

    if (ev.button == 0 && isExpandable && ev.x >= x && ev.x < x + PLUS_ICON_WIDTH) {
        flipExpand();
    } else if (ev.button == 0) {
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

bool gedTreeListEntryWidget::onKeyPress(const grUiEventKeyPress &ev) {
    if (ev.action == GR_ACTION_KEY_PRESSED) {
        if (ev.keycode == grKeycode::GR_KEY_RETURN) {
            gedEventTreeListOpenEntry ev1;
            eventSink_openEntry.emit(ev1);
        } else if (ev.keycode == grKeycode::GR_KEY_SPACE) {
            if (isExpandable) {
                flipExpand();
            }
        } else if (ev.keycode == grKeycode::GR_KEY_RIGHT) {
            if (isExpandable && !expanded) {
                flipExpand();
            }
        } else if (ev.keycode == grKeycode::GR_KEY_LEFT) {
            if (isExpandable && expanded) {
                flipExpand();
            }
        }
    }

    return true;
}

bool gedTreeListEntryWidget::onDoubleClick(const grUiEventDoubleClick &ev) {
    grInsets ins   = get_baseInsets();
    grRectangle rc = ins.insetDimensionToRect(get_size());

    set_focused(true);

    int x = rc.x + nestingLevel * 16;

    if (isExpandable && ev.x >= x && ev.x < x + PLUS_ICON_WIDTH) {
        flipExpand();
    } else {
        set_focused(true);

        gedEventTreeListOpenEntry ev1;
        eventSink_openEntry.emit(ev1);
    }
    return true;
}

bool gedTreeListEntryWidget::onFocus(const grUiEventFocus &ev) {
    gedEventTreeListSelectEntry ev1;
    eventSink_selectEntry.emit(ev1);
    return true;
}
