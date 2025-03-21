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

#include "NumericTextField.h"

#include <grUi/Layout/LayoutLinear.h>
#include <ged/Action/ActionModifyProperty.h>

namespace ged::ui {
    template <typename T>
    NumericTextField<T>::NumericTextField(
        action::ActionExecutor *actionExecutor,
        property::EditableProperty<T> property)
        : m_actionExecutor(actionExecutor),
          m_property(std::move(property)) {

        background = gnaNew<grUiBackground>(grColor{ 0xFF1E1E1D });

        layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);

        m_widgetTextValue = gnaNew<grUiWidgetText>();
        m_widgetTextValue->add_styleClass("WidgetTextValue");
        m_widgetTextValue->set_text(GTXT("0"));

        m_textField = gnaNew<grUiWidgetTextField>();

        gnaPointer<grUiLayoutLinear::ElementSpec> espec = grUiLayoutLinear::ElementSpec::createGrow();
        espec->minSecondarySize                         = m_textField->initialMeasure(0).height;
        m_widgetTextValue->set_layoutData(espec);
        add(m_widgetTextValue);

        m_textField->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());

        eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
        m_textField->eventSink_parentDefocus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onFieldDefocus));
        m_textField->eventSink_defocus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onFieldDefocus));
        m_textField->eventSink_textFieldConfirm.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onFieldConfirm));
    }

    template <typename T>
    void NumericTextField<T>::update() {
        grUiWidgetLayout::update();

        if (m_state != STATE_EDIT) {
            if (oldValue != m_property.get()) {
                updateText();
            }
        }
    }

    template <typename T>
    void NumericTextField<T>::updateText() {
        m_widgetTextValue->set_text(getValueText());
        oldValue = m_property.get();
    }

    template <typename T>
    void NumericTextField<T>::modifyValue(T value) const {
        if (m_actionExecutor) {
            m_actionExecutor->executeAction(gnaNew<action::ActionModifyProperty<T>>(m_property, value));
        } else {
            m_property.set(value);
        }
    }

    template <>
    gtl::String NumericTextField<float>::getValueText() const {
        return gtl::String::format(GTXT("%.4g"), m_property.get() * getValueMultiplier());
    }

    template <>
    gtl::String NumericTextField<double>::getValueText() const {
        return gtl::String::format(GTXT("%.4lg"), m_property.get() * getValueMultiplier());
    }

    template <typename T>
    void NumericTextField<T>::enterEditState() {
        if (m_state == STATE_EDIT) {
            return;
        }
        m_state = STATE_EDIT;
        remove(m_widgetTextValue);
        add(m_textField);
        m_textField->set_text(getValueText());
        m_textField->selectAll();
        m_textField->set_focused(true);
    }

    template <typename T>
    void NumericTextField<T>::enterIdleState() {
        if (m_state == STATE_EDIT) {
            remove(m_textField);
            add(m_widgetTextValue);
        }
        m_state = STATE_IDLE;
    }

    template <typename T>
    void NumericTextField<T>::confirmField() {
        errno = 0;

        const gtl::WIDECHAR *wc = m_textField->get_text().toCString();
        gtl::WIDECHAR *end;
        double val = gtl::StrToD(wc, &end);
        if (val != 0 || (errno == 0 && end != wc)) {
            modifyValue((T)val / getValueMultiplier());
        }

        enterIdleState();
    }

    template <typename T>
    bool NumericTextField<T>::onMouseDown(grUiEventMouseDown &ev) {
        if (ev.button == 0) {
            if (m_state == STATE_IDLE) {
                m_state     = STATE_HOLD;
                auto dndctx = gnaNew<FieldDnDContext>(ev.button, this);
                grUi_gRootWindowManager->startDragAndDrop(dndctx);
            }
        }

        return true;
    }

    template <typename T>
    bool NumericTextField<T>::onFieldDefocus(grUiEventDefocus &ev) {
        confirmField();

        return true;
    }

    template <typename T>
    bool NumericTextField<T>::onFieldConfirm(grUiEventPerformAction &ev) {
        confirmField();

        return true;
    }

    template <typename T>
    NumericTextField<T>::FieldDnDContext::FieldDnDContext(
        const int mouseButton,
        gnaWeakPointer<NumericTextField> field) : grUiDragContext(field, mouseButton),
                                                  m_field(field) {
    }

    template <typename T>
    void NumericTextField<T>::FieldDnDContext::dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) {
        if (dx == 0 && dy == 0)
            return;

        if (m_field->m_state == STATE_HOLD || m_field->m_state == STATE_DRAG) {
            T newValue = m_field->m_property.get() + static_cast<T>(dx) / m_field->getValueMultiplier() * m_field->getDragStep();
            m_field->modifyValue(newValue);

            m_field->m_state = STATE_DRAG;
        }
    }

    template <typename T>
    void NumericTextField<T>::FieldDnDContext::dragRelease(gnaWeakPointer<grUiRootWindowManager> root) {
        if (m_field->m_state == STATE_HOLD) {
            m_field->enterEditState();
        } else if (m_field->m_state == STATE_DRAG) {
            m_field->enterIdleState();
        }
    }

    template class NumericTextField<float>;
    template class NumericTextField<double>;
}
