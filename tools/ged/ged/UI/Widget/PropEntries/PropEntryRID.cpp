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

#include "PropEntryRID.h"

#include <grUi/Layout/LayoutLinear.h>
#include <ged/Editor/Editor.h>

using namespace ged::ui;

WidgetPropEntryRID::WidgetPropEntryRID() {
    static nxfRID iconsSRID = { GTXT("/textures/ui/icons/outlinericons.png") };

    background = gnaNew<grUiBackground>(grColor{ 0xFF202020 });
    layout     = gnaNew<grUiLayoutLinear>(grUiLayoutLinear::AXIS_X);

    btnDeleteResource = gnaNew<grUiWidgetButton>();
    btnDeleteResource->set_icon(grUiSprite::createTexModalRect(iconsSRID, 16, 16, 16, 16, 64, 64));
    btnDeleteResource->eventSink_performAction.addHandler([this](auto &ev) {
        EventUpdateRID ev1;
        ev1.newValue = {};
        eventSink_updateRID.emit(ev1);

        return true;
    });

    lblResourcePath            = gnaNew<grUiWidgetText>();
    lblResourcePath->alignment = (grUiTextAlignment)(GR_TEXT_ALIGN_CENTER | GR_TEXT_ALIGN_MIDDLE);
    auto pathLytSpec = grUiLayoutLinear::ElementSpec::createGrow();
    pathLytSpec->minSecondarySize = btnDeleteResource->initialMeasure(0).height;
    lblResourcePath->set_layoutData(pathLytSpec);
    add(lblResourcePath);

    nxfRID rref;
    if (m_fnDataSource) {
        rref = m_fnDataSource();
    }
    if (rref) {
        lblResourcePath->set_text(rref.toDisplayPathString());
        // add(btnEditResource);
        add(btnDeleteResource);
    } else {
        lblResourcePath->set_text(GTXT("(None, drag here to import)"));
    }

    lastRref = rref;

    lblResourcePath->eventSink_objectDrop.addHandler([this](const grUiEventObjectDrop &ev) {
        auto dragObj = ev.object.rttiCast2<grUiResourceIDDragObject>();
        if (dragObj) {
            EventUpdateRID ev1;
            ev1.newValue = dragObj->m_rid;
            eventSink_updateRID.emit(ev1);
            update();
        }

        return true;
    });
}

void WidgetPropEntryRID::setDataSource(std::function<nxfRID()> fnDataSource) {
    m_fnDataSource = std::move(fnDataSource);
}

void WidgetPropEntryRID::setDefaultDataSource(nxfRID *pRref) {
    setDataSource([pRref]() { return *pRref; });
    eventSink_updateRID.addHandler([pRref](EventUpdateRID &ev) {
        *pRref = ev.newValue;
        return true;
    });
}

void WidgetPropEntryRID::update() {
    nxfRID rref;
    if (m_fnDataSource) {
        rref = m_fnDataSource();
    }
    if (rref != lastRref) {
        if (rref) {
            lblResourcePath->set_text(rref.toDisplayPathString());
            add(btnDeleteResource);
        } else {
            lblResourcePath->set_text(GTXT("(None, drag here to import)"));
            remove(btnDeleteResource, true);
        }
        lastRref = rref;
    }

    grUiWidgetLayout::update();
}
