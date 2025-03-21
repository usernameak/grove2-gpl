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

#include "TransformEditField.h"

#include "VectorEditField.h"

#include <grUi/Layout/LayoutLinear.h>

GTL_RTTI_DEFINE(ged::ui::LocalTransformEditField, GTL_RTTI_INHERITS(grUiWidgetLayout));

ged::ui::LocalTransformEditField::LocalTransformEditField(
    action::ActionExecutor *actionExecutor,
    property::EditableProperty<gtlMath2::LocalTransform> property
) {
    this->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y, 8);

    {
        auto box = gnaNew<grUiWidgetLayout>(gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y, 2));

        auto lblTitle = gnaNew<grUiWidgetText>(GTXT("Translation"));
        lblTitle->add_styleClass("GED_SubPropertyTitle");
        box->add(lblTitle);

        auto valueWidget = gnaNew<VectorEditField<float, 3>>(
            actionExecutor,
            property::EditableProperty<gtlMath2::Vector3f>(
                "Translation",
                property.undoKey,
                [property]() -> const gtlMath2::Vector3f & {
                    return property.get().translation;
                },
                [property](const gtlMath2::Vector3f &translation) {
                    gtlMath2::LocalTransform transform = property.get();
                    transform.translation              = translation;
                    property.set(transform);
                }
            )
        );
        box->add(valueWidget);

        add(box);
    }

    {
        auto box = gnaNew<grUiWidgetLayout>(gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y, 2));

        auto lblTitle = gnaNew<grUiWidgetText>(GTXT("Rotation"));
        lblTitle->add_styleClass("GED_SubPropertyTitle");
        box->add(lblTitle);

        auto valueWidget = gnaNew<EulerVectorEditField<float, 3>>(
            actionExecutor,
            property::EditableProperty<gtlMath2::Vector3f>(
                "Rotation",
                property.undoKey,
                [property]() -> const gtlMath2::Vector3f & {
                    return property.get().rotation;
                },
                [property](const gtlMath2::Vector3f &rotation) {
                    gtlMath2::LocalTransform transform = property.get();
                    transform.rotation                 = rotation;
                    property.set(transform);
                }
            )
        );
        box->add(valueWidget);

        add(box);
    }

    {
        auto box = gnaNew<grUiWidgetLayout>(gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y, 2));

        auto lblTitle = gnaNew<grUiWidgetText>(GTXT("Scale"));
        lblTitle->add_styleClass("GED_SubPropertyTitle");
        box->add(lblTitle);

        auto valueWidget = gnaNew<NumericTextField<float>>(
            actionExecutor,
            property::EditableProperty<float>(
                "Scale",
                property.undoKey,
                [property]() -> float {
                    return property.get().scale;
                },
                [property](float scale) {
                    gtlMath2::LocalTransform transform = property.get();
                    transform.scale                    = scale;
                    property.set(transform);
                }
            )
        );
        box->add(valueWidget);

        add(box);
    }
}
