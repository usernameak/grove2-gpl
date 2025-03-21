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
#include "NumericTextField.h"

namespace ged {
    namespace ui {
        template <typename T, int N, template <typename> typename NumericFieldType = NumericTextField>
        class VectorEditField : public grUiWidgetLayout {
        public:
            VectorEditField(
                action::ActionExecutor *actionExecutor,
                property::EditableProperty<gtlMath2::SizedVector<T, N>> property);
        };

        template <typename T, int N>
        using EulerVectorEditField = VectorEditField<T, N, AngleNumericTextField>;
    }
}
