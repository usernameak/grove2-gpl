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

#include "SceneEditorPane.h"

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/WidgetButton.h>

#include <ged/Editor/Scene/Outliner.h>
#include <ged/Editor/Scene/SceneEditorView.h>

using namespace ged::SceneEditor;

SceneEditorPane::SceneEditorPane(SceneEditor *pEditor) : m_pEditor(pEditor) {
    layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);

    {
        auto toolbarLayout = gnaNew<grUiWidgetLayout>(gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X, 4));
        add(toolbarLayout);

        auto dupObjectIconSprite = grUiSprite::createTexModalRect(
            nxfRID{ GTXT("/textures/ui/icons/toolbaricons.png") },
            0, 0,
            24, 24,
            256, 256);

        auto dupObjectButton = gnaNew<grUiWidgetButton>(GTXT("Duplicate Object"));
        dupObjectButton->set_icon(dupObjectIconSprite);
        dupObjectButton->set_layoutData(grUiLayoutLinear::ElementSpec::createMin(0));
        dupObjectButton->eventSink_performAction.addHandlerV([this](auto &ev) {
            m_pEditor->duplicateSelectedObject();
        });
        toolbarLayout->add(dupObjectButton);
    }

    {
        auto subLayout    = gnaNew<grUiWidgetLayout>();
        subLayout->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);

        m_sceneEditorView = gnaNew<SceneEditorView>(m_pEditor);
        m_sceneEditorView->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());
        subLayout->add(m_sceneEditorView);

        m_outliner = gnaNew<SceneEditorOutliner>(m_pEditor);
        m_outliner->set_layoutData(grUiLayoutLinear::ElementSpec::createFixed(300));
        subLayout->add(m_outliner);

        subLayout->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());
        add(subLayout);
    }
}

SceneEditorPane::~SceneEditorPane() = default;

void SceneEditorPane::onObjectSelected(gnaWeakPointer<grScene::SceneObject> obj) {
    m_sceneEditorView->onObjectSelected(obj);
}

void SceneEditorPane::updateNodeList() {
    m_outliner->updateNodeList();
}
