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
#include <nxfResource/RID.h>
#include <grUi/Widget/WidgetButton.h>
#include <grUi/Widget/WidgetText.h>

namespace ged {
    namespace ui {
        class WidgetPropEntryRID : public grUiWidgetLayout {
            nxfRID lastRref;

            gnaPointer<grUiWidgetText> lblResourcePath;
            gnaPointer<grUiWidgetButton> btnDeleteResource;

            std::function<nxfRID()> m_fnDataSource;

        public:
            struct EventUpdateRID {
                nxfRID newValue;
            };

            WidgetPropEntryRID();

            void setDataSource(std::function<nxfRID()> fnDataSource);
            [[deprecated]] void setDefaultDataSource(nxfRID *pRref);
            void update() override;

            gnaEventSink<EventUpdateRID> eventSink_updateRID;
        };
    }
}