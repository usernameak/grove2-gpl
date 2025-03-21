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

#include "WidgetComboBox.h"

#include "Window/RootWindowManager.h"
#include "DropDownMenu.h"
#include <grUi/Text/TextRenderer.h>

GTL_RTTI_DEFINE(grUiWidgetComboBox, GTL_RTTI_INHERITS(grUiWidgetText));

grUiWidgetComboBox::grUiWidgetComboBox()
    : m_currentItemData(nullptr),
      m_currentItem(UINT32_MAX) {
    this->eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
    this->eventSink_mouseEnter.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseEnter));
    this->eventSink_mouseLeave.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseLeave));
}

void grUiWidgetComboBox::addItem(gtl::String label, uint32_t key) {
    m_items.push_back({ label, key });
    set_layoutDirty(true);
}

void grUiWidgetComboBox::removeAllItems() {
    m_currentItemData = nullptr;
    m_currentItem     = UINT32_MAX;
    set_text(m_emptyText);

    m_items.clear();
    set_layoutDirty(true);
}

void grUiWidgetComboBox::set_currentItem(uint32_t key) {
    if (key != m_currentItem) {
        m_currentItemData = nullptr;
        for (auto &item : m_items) {
            if (item.key == key) {
                m_currentItemData = &item;
                set_text(m_currentItemData->label);
            }
        }
        if (!m_currentItemData) {
            GR_FATAL(GTXT("Invalid combobox item key %u"), key);
        }
    }

    m_currentItem = key;
}

uint32_t grUiWidgetComboBox::get_currentItem() {
    return m_currentItem;
}

gtl::String grUiWidgetComboBox::getCurrentItemName() {
    if (!m_currentItemData)
        GR_FATAL(GTXT("No combo box item selected"));
    return m_currentItemData->label;
}

grDimension grUiWidgetComboBox::initialMeasure(int biasedSize) {
    grDimension dim{ 0, 0 };

    grUiFontKey fontKey = get_font();
    auto fontRenderer   = gnaSingleton<grUiFontCache>()->get_font(fontKey);

    grInsets textInsets = get_insets(INSET_TEXT);

    grUiTextRenderer tr(get_metricContext(), fontKey);

    if (!fontRenderer) {
        dim = { 0, 0 };
    } else {
        for (auto &item : m_items) {
            int newWidth = (int)ceil(tr.get_width(item.label));
            if (newWidth > dim.width) {
                dim.width = newWidth;
            }
        }
        
        dim.height = static_cast<int>(ceil(tr.get_lineHeight()));
    }

    return textInsets.outsetDimension(dim);
}

bool grUiWidgetComboBox::onMouseDown(const grUiEventMouseDown &ev) {
    if (ev.button == 0) {
        // todo hiding old list
        list->removeAll();

        // displaying new list
        for (const auto &itemData : m_items) {
            auto item = gnaNew<grUi::DropDownMenuEntry>(itemData.label);
            item->eventSink_performAction.addHandler([this, idx = itemData.key](const auto &ev) {
                set_currentItem(idx);

                EventSelectItem ev1{};
                ev1.itemKey = idx;
                eventSink_selectItem.emit(ev1);

                return true;
            });

            list->add(item);
        }

        grUi_gRootWindowManager->add(list);
        grUiWindowLayoutData::pack(list);

        auto position = computeRelativePosition(grUi_gRootWindowManager);
        auto insets   = get_insets(INSET_MARGIN);
        list->set_focused(true);

        int pos_x, pos_y;
        // displaying on top of combo box
        if (position.y + get_size().height + list->get_size().height >= grUi_gRootWindowManager->get_size().height) {
            pos_x = position.x + insets.left;
            pos_y = position.y - list->get_size().height + insets.top;
        }
        // displaying bellow combobox
        else {
            pos_x = position.x + get_size().width - list->get_size().width;
            pos_y = position.y + get_size().height;
        }

        list->set_position(pos_x, pos_y);
    }

    return false;
}

bool grUiWidgetComboBox::onMouseEnter(const grUiEventMouseEnter& ev) {
    set_styleStateBits(STSTBIT_HOVERED);
    return true;
}

bool grUiWidgetComboBox::onMouseLeave(const grUiEventMouseLeave& ev) {
    set_styleStateBits(0);
    return true;
}
