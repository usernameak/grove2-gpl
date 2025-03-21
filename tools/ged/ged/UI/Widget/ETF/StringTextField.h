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

#include <grUi/Widget/WidgetLayout.h>
#include <grUi/Widget/WidgetText.h>
#include <grUi/Widget/WidgetTextField.h>
#include <grUi/Widget/Window/RootWindowManager.h>

namespace ged {
    namespace ui {
        class StringTextField : public grUiWidgetLayout {
            gnaPointer<grUiWidgetTextField> m_textField;
            gnaPointer<grUiWidgetText> m_widgetTextValue;

            gtl::String *const valuePtr;
            gtl::String oldValue{};

            enum InputState {
                STATE_IDLE,
                STATE_HOLD,
                STATE_DRAG,
                STATE_EDIT
            } m_state = STATE_IDLE;

        public:
            StringTextField(gtl::String *valuePtr);

            void update() override;

        private:
            void updateText();
            gtl::String getValueText() const;

            void enterEditState();
            void enterIdleState();

            void confirmField();

            bool onMouseDown(grUiEventMouseDown &ev);
            bool onFieldDefocus(grUiEventDefocus &ev);
            bool onFieldConfirm(grUiEventPerformAction &ev);
        };
    }
}
