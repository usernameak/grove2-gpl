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

#include "DataFilesPane.h"

#include <grUi/Widget/WidgetText.h>
#include <grUi/Widget/WidgetButton.h>
#include <grUi/Layout/LayoutLinear.h>

#include <ged/UI/Panes/MainPane.h>

#include <nxfResource/FlatFileResourceManager.h>
#include <nxfResource/RMEx/ExtendedResourceManager.h>

gedDataFilesPane::gedDataFilesPane() : grUiFrame() {
    set_title(GTXT("Data files"));

    auto lwMain        = gnaNew<grUiWidgetLayout>();
    lwMain->background = gnaNew<grUiBackground>(0xFF2D2D30_grColor);

    lwMain->layout = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_Y);

    gnaPointer<grUiWidgetText> lblLoadResourcePackage = gnaNew<grUiWidgetText>(GTXT("Load resource package"));
    lblLoadResourcePackage->set_padding({ 5 });
    lwMain->add(lblLoadResourcePackage);

    m_inpResourcePath = gnaNew<grUiWidgetTextField>();
    m_inpResourcePath->eventSink_textFieldConfirm.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onConfirm));
    lwMain->add(m_inpResourcePath);

    gnaPointer<grUiWidgetButton> btnOk = gnaNew<grUiWidgetButton>(GTXT("OK"));
    btnOk->eventSink_performAction.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onConfirm));
    lwMain->add(btnOk);

    set_contentWidget(lwMain);
}

bool gedDataFilesPane::onConfirm(const grUiEventPerformAction &ev) {
    get_parent()->remove(this);

    auto *rm = dynamic_cast<nxfResource::ExtendedResourceManager *>(nxf_getRM());
    rm->clearNamespace(nxfResource::ExtendedResourceManager::NS_GAME);
    auto *arch = gtlNew nxfFlatFileResourceManager(m_inpResourcePath->get_text());
    rm->addArchiveToNamespace(nxfResource::ExtendedResourceManager::NS_GAME, arch);
    rm->m_editResourceManager = arch;

    ged_gMainPane->m_projectExplorerPane->refresh();

    return true;
}
