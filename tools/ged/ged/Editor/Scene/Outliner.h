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

class gedTreeList;
class gedEventTreeListPopulateSublist;

namespace grScene {
    class SceneObject;
    class Node;
}

namespace ged {
    namespace SceneEditor {
        class SceneEditor;

        class SceneEditorOutliner : public grUiWidgetLayout {
            SceneEditor *m_pEditor;
            gnaPointer<gedTreeList> m_treeList;

        public:
            GTL_RTTI_DECLARE();

            SceneEditorOutliner(SceneEditor *pEditor);

            void populateSingleSceneObj(gnaPointer<grScene::SceneObject> subnode, gedEventTreeListPopulateSublist &ev);
            bool populateNodeSubtree(gnaPointer<grScene::Node> node, gedEventTreeListPopulateSublist &ev);
            bool selectObject(gnaWeakPointer<grScene::SceneObject> obj);
            void updateNodeList();

            virtual ~SceneEditorOutliner() override;
        };
    }
}
