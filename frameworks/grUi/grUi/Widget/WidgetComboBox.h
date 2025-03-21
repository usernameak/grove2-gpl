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

#include "WidgetText.h"
#include "DropDownMenu.h"


class grUiWidgetComboBox : public grUiWidgetText {
    GTL_RTTI_DECLARE();

private:
    struct ComboBoxItem {
        gtl::String label;
        uint32_t key;
    };

    ComboBoxItem *m_currentItemData;
    std::vector<ComboBoxItem> m_items;
    gnaPointer<grUi::DropDownMenu> list = gnaNew<grUi::DropDownMenu>();
    gtl::String m_emptyText;

    uint32_t m_currentItem;
public:
    struct EventSelectItem {
        uint32_t itemKey;
    };

    grUiWidgetComboBox();

    void addItem(gtl::String label, uint32_t key);
    void removeAllItems();

    void set_currentItem(uint32_t key);
    void setEmptyText(gtl::String text) {
        m_emptyText = text;
    }
    uint32_t get_currentItem();
    gtl::String getCurrentItemName();

    grDimension initialMeasure(int biasedSize) override;

    gnaEventSink<EventSelectItem> eventSink_selectItem;
private:
    bool onMouseDown(const grUiEventMouseDown &ev);

    bool onMouseEnter(const grUiEventMouseEnter& ev);

    bool onMouseLeave(const grUiEventMouseLeave& ev);
};
