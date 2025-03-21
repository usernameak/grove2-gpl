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

#include "ObjEditor.h"

#include <ged/Editor/Editor.h>
#include <ged/UI/Widget/ETF/TransformEditField.h>
#include <gtlMath2/Transform/Transform.h>

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/WidgetLayout.h>
#include <grUi/Widget/WidgetText.h>

namespace ged {
    void ObjEditor::populatePropertyGui(Editor *editor, gnaWeakPointer<gtlObject> obj, gnaWeakPointer<grUiWidgetLayout> container) {
        gnaPointer<grUiWidgetLayout> lw = gnaNew<grUiWidgetLayout>(gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y, 8));

        gtlProperty::enumerateProperties(obj, [obj, editor, lw](const gtlProperty &prop) {
            auto lblTitle = gnaNew<grUiWidgetText>(prop.m_name);
            lblTitle->add_styleClass("GED_PropertyTitle");
            lw->add(lblTitle);
            if (prop.m_typeInfo == gtlTypeInfo::of<gtlMath2::LocalTransform>()) {
                lw->add(gnaNew<ui::LocalTransformEditField>(
                    editor,
                    property::EditableProperty<gtlMath2::LocalTransform>::fromProperty(obj, &prop)
                ));
            }
        });

        container->add(lw);
    }

    void ObjEditorRegistry::registerEditor(const gtlRTTI *rtti, gnaPointer<ObjEditor> factory) {
        assert(!m_registeredEditors.contains(rtti));
        m_registeredEditors.emplace(rtti, std::move(factory));
    }

    gnaWeakPointer<ObjEditor> ObjEditorRegistry::findEditor(const gtlRTTI *rtti) {
        do {
            auto it = m_registeredEditors.find(rtti);
            if (it == m_registeredEditors.end()) continue;
            return it->second;
        } while ((rtti = rtti->get_baseClass()));

        return nullptr;
    }

    void ObjEditorRegistry::registerDefaultEditors() {
        registerEditor(&gtlObject::st_rtti, gnaNew<ObjEditor>());
        /*
        registerEditor(&grScene::SceneObject::st_rtti, gnaNew<PGFSceneObject>());
        registerEditor(&grScene::Geometry::st_rtti, gnaNew<PGFSceneGeom>());
        registerEditor(&grScene::DirectionalLight::st_rtti, gnaNew<PGFSceneDirectionalLight>());
        registerEditor(&grScene::MaterialInstance::st_rtti, gnaNew<PGFMaterial>());
        */
    }
}

GNA_SINGLETON_IMPLEMENT(ged::ObjEditorRegistry);
