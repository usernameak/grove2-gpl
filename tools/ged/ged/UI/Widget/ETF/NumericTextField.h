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

#include "ged/Property/EditableProperty.h"


#include <grUi/Widget/WidgetLayout.h>
#include <grUi/Widget/WidgetText.h>
#include <grUi/Widget/WidgetTextField.h>
#include <grUi/Widget/Window/RootWindowManager.h>
#include <gtlObject/Object.h>

#include <ged/Action/ActionExecutor.h>

namespace ged {
    namespace ui {
        template <typename T>
        class NumericTextField : public grUiWidgetLayout {
            gnaPointer<grUiWidgetTextField> m_textField;
            gnaPointer<grUiWidgetText> m_widgetTextValue;

            action::ActionExecutor *m_actionExecutor;
            property::EditableProperty<T> m_property;

            T oldValue = 0;

            enum InputState {
                STATE_IDLE,
                STATE_HOLD,
                STATE_DRAG,
                STATE_EDIT
            } m_state = STATE_IDLE;

            class FieldDnDContext : public grUiDragContext {
                gnaWeakPointer<NumericTextField> m_field;

            public:
                FieldDnDContext(const int mouseButton, gnaWeakPointer<NumericTextField> field);

                void dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) override;

                void dragRelease(gnaWeakPointer<grUiRootWindowManager> root) override;
            };

        public:
            NumericTextField(
                action::ActionExecutor *actionExecutor,
                property::EditableProperty<T> property);

            void update() override;

            virtual T getValueMultiplier() const {
                return T(1);
            }

            virtual T getDragStep() const {
                return T(.01);
            }

            void modifyValue(T value) const;

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

        template <typename T>
        class AngleNumericTextField : public NumericTextField<T> {
        public:
            using NumericTextField<T>::NumericTextField;

            T getValueMultiplier() const override {
                return T(180) / gtlMath2::pi<T>;
            }

            T getDragStep() const override {
                return T(.5);
            }
        };
    }
}
