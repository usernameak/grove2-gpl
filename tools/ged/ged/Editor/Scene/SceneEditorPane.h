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
#include <ged/Editor/Scene/SceneEditor.h>
#include <ged/Editor/Scene/Outliner.h>
#include <ged/Editor/Scene/SceneEditorView.h>

class grUiWidgetScrollPane;

namespace ged {
    namespace SceneEditor {
        class SceneEditorPane : public grUiWidgetLayout {
            SceneEditor *m_pEditor;

        public:
            explicit SceneEditorPane(SceneEditor *pEditor);

            ~SceneEditorPane() override;

            void onObjectSelected(gnaWeakPointer<grScene::SceneObject> obj);
            void updateNodeList();

            gnaPointer<SceneEditorView> m_sceneEditorView;
            gnaPointer<SceneEditorOutliner> m_outliner;
        };
    }
}
