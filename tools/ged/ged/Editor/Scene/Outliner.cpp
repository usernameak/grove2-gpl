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

#include "Outliner.h"

#include <grScene/SceneObject.h>
#include <grScene/SceneNode.h>

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/WidgetScrollPane.h>
#include <grUi/Widget/DropDownMenu.h>
#include <ged/UI/Widget/TreeList.h>

#include <ged/Editor/Scene/SceneEditor.h>

using namespace ged::SceneEditor;

GTL_RTTI_DEFINE(ged::SceneEditor::SceneEditorOutliner, GTL_RTTI_INHERITS(grUiWidgetLayout));

SceneEditorOutliner::SceneEditorOutliner(SceneEditor *pEditor) : grUiWidgetLayout(), m_pEditor(pEditor) {
    layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);

    m_treeList = gnaNew<gedTreeList>();

    m_treeList->eventSink_populateSublist.addHandler([this](auto &ev) {
        populateSingleSceneObj(m_pEditor->m_editedScene->m_rootNode, ev);
        return true;
    });
    m_treeList->updateList();

    auto listScroll = gnaNew<grUiWidgetScrollPane>();
    listScroll->set_contentWidget(m_treeList);
    listScroll->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());

    add(listScroll);
}

SceneEditorOutliner::~SceneEditorOutliner() = default;

void SceneEditorOutliner::populateSingleSceneObj(gnaPointer<grScene::SceneObject> subnode, gedEventTreeListPopulateSublist &ev) {
    nxfRID iconsSRID = { GTXT("/textures/ui/icons/outlinericons.png") };
    grUiSprite icon  = grUiSprite::createTexModalRect(iconsSRID, 0, 0, 16, 16, 64, 64);

    gtl::String name = static_cast<gtl::String>(subnode->name);
    name += GTXT(" [");
    name += subnode->get_rtti()->get_className();
    name += GTXT(']');

    auto entry  = gnaNew<gedTreeListEntryWidget>();
    entry->icon = icon;
    entry->name = name;
    entry->key  = &*subnode;
    if (subnode == m_pEditor->m_selectedObject) {
        entry->set_focused(true);
    }
    entry->eventSink_selectEntry.addHandler([this, subnode](auto &ev) {
        m_pEditor->selectObject(subnode);
        return true;
    });
    entry->eventSink_contextMenu.addHandler([this, subnode](auto &ev) {
        if (m_pEditor->canDeleteNode(subnode)) {
            auto entDelete = gnaNew<grUi::DropDownMenuEntry>(GTXT("Delete"));
            entDelete->eventSink_performAction.addHandler([this, subnode](auto &ev) {
                m_pEditor->deleteNode(subnode);
                return true;
            });
            ev.dropDown->add(entDelete);
        }
        return true;
    });
    entry->eventSink_keyEvent.addHandler([this, subnode](auto &ev) {
        if (ev.action == GR_ACTION_KEY_PRESSED) {
            if (ev.keycode == grKeycode::GR_KEY_DELETE) {
                m_pEditor->deleteNode(subnode);
                return true;
            }
        }
        return true;
    });

    gnaPointer<grScene::Node> subnodeN = subnode.rttiCast2<grScene::Node>();
    if (subnodeN) {
        entry->isExpandable = true;
        entry->eventSink_populateSublist.addHandler([this, subnodeN](auto &ev) {
            return populateNodeSubtree(subnodeN, ev);
        });
    }
    ev.addEntry(entry);
}

bool SceneEditorOutliner::populateNodeSubtree(gnaPointer<grScene::Node> node, gedEventTreeListPopulateSublist &ev) {
    for (gnaWeakPointer<grScene::SceneObject> subnode = node->firstChild(); subnode; subnode = subnode->nextSibling()) {
        populateSingleSceneObj(subnode, ev);
    }
    return true;
}

bool SceneEditorOutliner::selectObject(gnaWeakPointer<grScene::SceneObject> obj) {
    for (gnaWeakPointer<grUiWidget> w : *m_treeList) {
        gnaWeakPointer wnode = static_cast<grScene::SceneObject *>(w->key);

        if (wnode == obj) {
            w->set_focused(true, true);
            return true;
        }
    }
    m_treeList->releaseFocusFromChildren(true);
    return false;
}

void SceneEditorOutliner::updateNodeList() {
    m_treeList->updateList();
}
