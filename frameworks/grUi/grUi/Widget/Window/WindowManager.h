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
#include <grUi/UiDLL.h>

namespace grUiWindowLayoutData {
    GR_UI_DLLIMPEXP void pack(gnaWeakPointer<grUiWidget> window, grDimension minSize = { 0, 0 });

    GR_UI_DLLIMPEXP void center(gnaWeakPointer<grUiWidget> window, gnaWeakPointer<grUiWidget> parent);
}

class GR_UI_DLLIMPEXP grUiWindowManager : public grUiWidgetLayout {
public:
    grUiWindowManager();

    void displayCenteredDialog(gnaWeakPointer<grUiWidget> win);

    void displayProportionalDialog(gnaWeakPointer<grUiWidget> win, float x, float y);

    GTL_RTTI_DECLARE();
};
