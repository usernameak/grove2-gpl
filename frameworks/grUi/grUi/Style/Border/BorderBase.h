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

#include <gtlMemory/RcObject.h>
#include <gr2DCoords.h>

#include <grUi/Render/UiRenderer.h>
#include <grUi/UiDLL.h>
#include <grUi/Style/Background/BackgroundBase.h>
#include <grUi/Utils/UnitSize.h>

class grUiWidget;

class GR_UI_DLLIMPEXP grUiBorderBase : public gtlRcObject {
public:
    GTL_RTTI_DECLARE();

    [[deprecated]] grUiUnitInsets get_insets() {
        return getInsetsWithBackground(nullptr);
    }

    virtual grUiUnitInsets getInsetsWithBackground(gnaWeakPointer<grUiBackgroundBase> background) = 0;

    virtual void draw(gnaWeakPointer<grUiWidget> widget, grUiRenderer *render, int x, int y, int width, int height) = 0;
};
