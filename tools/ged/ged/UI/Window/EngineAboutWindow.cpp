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

#include "EngineAboutWindow.h"

#include <gtlLicenseInfo.h>

#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Widget/WidgetText.h>

static const grUiEngineAboutEntry *aboutEntryLists[] = {
    gtl_gAboutEntries,
    nullptr
};

gedEngineAboutWindow::gedEngineAboutWindow() {
    set_title(GTXT("About"));

    auto engineAboutPanel = gnaNew<grUiWidgetLayout>(gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y, 10));
    engineAboutPanel->set_padding({ 8, 8, 8, 8 });

    const grUiEngineAboutEntry **currentEntryList = aboutEntryLists;
    while(*currentEntryList) {
        const grUiEngineAboutEntry *currentEntry = *currentEntryList;
        while (currentEntry->name) {
            auto box = gnaNew<grUiWidgetLayout>(gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y));

            auto textEngineName = gnaNew<grUiWidgetText>(currentEntry->name);
            textEngineName->set_font(grUiFontKey{ "Default", 18.0f });
            textEngineName->set_margin({ 0, 0, 0, 6 });
            box->add(textEngineName);

            if (currentEntry->license) {
                auto licenseInfo = gnaNew<grUiWidgetText>(currentEntry->license);
                licenseInfo->set_stylingEnabled(false);
                licenseInfo->color = grColor{ 0x80FFFFFF };
                licenseInfo->set_margin({ 0, 0, 0, 6 });
                box->add(licenseInfo);
            }

            if (currentEntry->authors) {
                const gtl::WIDECHAR *const *currentAuthor = currentEntry->authors;
                while (*currentAuthor) {
                    auto row       = gnaNew<grUiWidgetText>(*currentAuthor);
                    row->alignment = GR_TEXT_ALIGN_LEFT | GR_TEXT_ALIGN_MIDDLE;
                    box->add(row);
                    currentAuthor++;
                }
            }

            engineAboutPanel->add(box);

            currentEntry++;
        }
        currentEntryList++;
    }

    set_contentWidget(engineAboutPanel);
}
