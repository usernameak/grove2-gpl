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

#include "VectorEditField.h"

#include <grUi/Layout/LayoutLinear.h>

namespace ged::ui {
    template <typename T, int N, template <typename> typename NumericFieldType>
    VectorEditField<T, N, NumericFieldType>::VectorEditField(
        action::ActionExecutor *actionExecutor,
        property::EditableProperty<gtlMath2::SizedVector<T, N>> property
    ) {
        this->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y, 2);

        for (int i = 0; i < N; i++) {
            auto tf = gnaNew<NumericFieldType<T>>(
                actionExecutor,
                property::EditableProperty<T>(
                    "Value",
                    property.undoKey,
                    [property, i]() -> T {
                        return property.get()[i];
                    },
                    [property, i](T value) {
                        gtlMath2::SizedVector<T, N> vec = property.get();

                        vec[i] = value;
                        property.set(vec);
                    }
                )
            );
            add(tf);
        }
    }

    template class VectorEditField<float, 3>;
    template class VectorEditField<double, 3>;

    template class VectorEditField<float, 3, AngleNumericTextField>;
    template class VectorEditField<double, 3, AngleNumericTextField>;
}
