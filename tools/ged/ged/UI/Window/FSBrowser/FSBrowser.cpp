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

#include "FSBrowser.h"

#include <grUi/Layout/LayoutLinear.h>
#include <ged/UI/Widget/ListWidget.h>
#include <algorithm>

using namespace ged::ui;

FSBrowser::FSBrowser() : currentPath(GTXT("")) {
    set_title(GTXT("File browser"));
    set_size(800, 600);

    auto lwMain        = gnaNew<grUiWidgetLayout>();
    lwMain->background = gnaNew<grUiBackground>(0xFF2D2D30_grColor);
    lwMain->layout     = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);

    {
        auto lwToolbar    = gnaNew<grUiWidgetLayout>();
        lwToolbar->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);

        auto btnUp = gnaNew<grUiWidgetButton>(GTXT("Up a level"));
        btnUp->eventSink_performAction.addHandler([this](auto &ev) {
            enterSubfolder(GTXT(".."));
            return true;
        });
        lwToolbar->add(btnUp);

        auto btnRefresh = gnaNew<grUiWidgetButton>(GTXT("Refresh"));
        btnRefresh->eventSink_performAction.addHandler([this](auto &ev) {
            refresh();
            return true;
        });
        lwToolbar->add(btnRefresh);

        m_currentPathWidget = gnaNew<grUiWidgetText>();
        m_currentPathWidget->set_padding({ 5, 0, 5, 0 });
        lwToolbar->add(m_currentPathWidget);

        lwMain->add(lwToolbar);
    }

    {
        m_listWidget = gnaNew<ListWidget>();
        m_listWidget->eventSink_populate.addHandler([this](auto &ev) {
            static nxfRID iconsSRID = { GTXT("/textures/ui/icons/groupicons.png") };
            grUiSprite folderIcon   = grUiSprite::createTexModalRect(iconsSRID, 32, 16, 16, 16, 64, 64);
            grUiSprite fileIcon     = grUiSprite::createTexModalRect(iconsSRID, 48, 16, 16, 16, 64, 64);

            std::unordered_set<grFsPlatform::ListFilesEntry> filesUnsorted;
            grFsPlatform::listFiles(currentPath, filesUnsorted);

            std::vector<grFsPlatform::ListFilesEntry> files(filesUnsorted.begin(), filesUnsorted.end());
            std::sort(files.begin(), files.end(), [](const auto &a, const auto &b) {
                if (a.type == b.type) {
                    return a.filename < b.filename;
                }
                return a.type == grFsPlatform::FileEntryType::DIRECTORY;
            });

            for (auto &entry : files) {
                auto w            = gnaNew<ListEntry>(entry.filename);
                w->icon           = entry.type == grFsPlatform::FileEntryType::DIRECTORY ? folderIcon : fileIcon;
                gtl::String fname = entry.filename;
                if (entry.type == grFsPlatform::FileEntryType::DIRECTORY) {
                    w->eventSink_openEntry.addHandler([this, fname](auto &ev) {
                        enterSubfolder(fname);
                        return true;
                    });
                } else {
                    w->eventSink_openEntry.addHandler([this, fname](auto &ev) {
                        EventSelectFile esf;
                        esf.filePath = grFsPlatform::combinePaths(currentPath, fname);
                        if (eventSink_selectFile.emit(esf)) {
                            closeFrame();
                        }
                        return true;
                    });
                }
                ev.list.push_back(w);
            }

            return true;
        });

        m_scrollPane             = gnaNew<grUiWidgetScrollPane>();
        m_scrollPane->background = gnaNew<grUiBackground>(grColor{ 0xFF252526 });
        m_scrollPane->set_border(gnaNew<grUiBorder>(1, grColor{ 0xFF3F3F46 }));
        m_scrollPane->set_contentWidget(m_listWidget);
        m_scrollPane->set_layoutData(grUiLayoutLinear::ElementSpec::createGrow());

        lwMain->add(m_scrollPane);
    }

    refresh();

    set_contentWidget(lwMain);
}

FSBrowser::~FSBrowser() = default;

void FSBrowser::refresh() {
    m_scrollPane->scrollToTop();
    m_currentPathWidget->set_text(currentPath);
    m_listWidget->updateList();
}

void FSBrowser::enterSubfolder(gtl::String subfolder) {
    currentPath = grFsPlatform::combinePaths(currentPath, subfolder);
    refresh();
}
