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

#include "ProjectExplorerPane.h"

#include <ged/Document/Document.h>
#include <ged/Editor/Editor.h>
#include <ged/Tools/ImportGLTF/nxftGltfImporter.h>
#include <ged/UI/Widget/TreeList.h>
#include <ged/UI/Window/FSBrowser/FSBrowser.h>
#include <ged/UI/Window/ErrorWindow.h>

#include <nxfResource/Asset/AssetManager.h>

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/Window/RootWindowManager.h>
#include <grUi/Widget/WidgetScrollPane.h>

gedProjectExplorerPane::gedProjectExplorerPane() {
    layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);

    {
        auto toolbar        = gnaNew<grUiWidgetLayout>();
        toolbar->background = gnaNew<grUiBackground>(grColor{ 0xFF2D2D30 });
        toolbar->layout     = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);

        add(toolbar);
    }

    background = gnaNew<grUiBackground>(grColor{ 0xFF252526 });
    set_border(gnaNew<grUiBorder>(1, grColor{ 0xFF3F3F46 }));

    auto scrollPane = gnaNew<grUiWidgetScrollPane>();

    m_treeList = gnaNew<gedTreeList>();
    m_treeList->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());

    m_treeList->eventSink_populateSublist.addHandlerV(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, buildList));
    m_treeList->updateList();

    scrollPane->set_contentWidget(m_treeList);
    scrollPane->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());
    add(scrollPane);
}

void gedProjectExplorerPane::refresh() {
    m_treeList->updateList();
}

void gedProjectExplorerPane::buildList(gedEventTreeListPopulateSublist &ev) {
    buildFolderListing(ev, GTXT("/"));
}

void gedProjectExplorerPane::buildFolderListing(gedEventTreeListPopulateSublist &ev, gtl::String basePath) {
    if (!nxf_getRM()) {
        return;
    }

    nxfRID iconsSRID      = { GTXT("/textures/ui/icons/groupicons.png") };
    grUiSprite folderIcon = grUiSprite::createTexModalRect(iconsSRID, 32, 16, 16, 16, 64, 64);
    grUiSprite fileIcon   = grUiSprite::createTexModalRect(iconsSRID, 48, 16, 16, 16, 64, 64);

    std::vector<grFsPlatform::ListFilesEntry> filenames;

    if (!nxf_getRM()->listFiles(basePath, filenames)) {
        return;
    }

    for (const auto &entry : filenames) {
        gtl::String filename = basePath + entry.filename;
        if (entry.type == grFsPlatform::FileEntryType::DIRECTORY) {
            filename += GTXT('/');
        }
        gtl::String displayName = entry.filename;
        grUiSprite icon         = entry.type == grFsPlatform::FileEntryType::DIRECTORY ? folderIcon : fileIcon;

        gnaPointer<gedTreeListEntryWidget> lentry = gnaNew<gedTreeListEntryWidget>();

        lentry->icon = icon;
        lentry->name = displayName;
        if (entry.type == grFsPlatform::FileEntryType::DIRECTORY) {
            lentry->isExpandable = true;
            lentry->eventSink_populateSublist.addHandlerV([this, filename](auto &ev) {
                buildFolderListing(ev, filename);
            });
            lentry->eventSink_contextMenu.addHandlerV([this, filename](auto &ev) {
                auto eImportGLTF = gnaNew<grUi::DropDownMenuEntry>(GTXT("Import GLTF..."));
                eImportGLTF->eventSink_performAction.addHandler([this, filename](auto &ev) {
                    auto fsb = gnaNew<ged::ui::FSBrowser>();
                    fsb->set_title(GTXT("Import GLTF"));
                    fsb->eventSink_selectFile.addHandler([this, filename](auto &esf) {
                        nxftGltfImporter imp;
                        gnaStatus sta = imp.importFile(esf.filePath);
                        if (!sta) {
                            gnaPointer<gedErrorWindow> wError = gnaNew<gedErrorWindow>(sta.get_errorMessage());
                            grUi_gRootWindowManager->displayCenteredDialog(wError);
                        } else {
                            imp.importDefaultScene();
                            gnaSingleton<nxfAssetManager>()->saveAsset(filename + GTXT("/imported.nxf"), imp.getScene());
                        }

                        return true;
                    });
                    grUiWindowLayoutData::center(fsb, grUi_gRootWindowManager);
                    fsb->set_focused(true);

                    grUi_gRootWindowManager->add(fsb);
                    return true;
                });
                ev.dropDown->add(eImportGLTF);
            });
        }
        if (entry.type == grFsPlatform::FileEntryType::FILE) {
            lentry->eventSink_openEntry.addHandlerV([this, filename](auto &ev) {
                gnaSingleton<ged::EditorManager>()->openDocument(gtlNew ged::document::Document(filename));
            });
            lentry->m_dragObject = gnaNew<grUiResourceIDDragObject>(filename);
        }
        ev.addEntry(lentry);
    }
}
