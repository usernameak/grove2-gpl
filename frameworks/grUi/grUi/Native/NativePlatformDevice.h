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

#include "grUi/Widget/WidgetLayout.h"

class GR_UI_DLLIMPEXP grUiNativePlatformDevice {
public:
    GTL_RTTI_DECLARE();

    virtual ~grUiNativePlatformDevice() = default;

    virtual grUiNativeFramePlatform *createFramePlatform(gnaWeakPointer<grUiWidget> widget) = 0;
    virtual grUiRenderer *createRenderer(gnaWeakPointer<grUiWidget> widget) = 0;

    virtual void nativeWidgetDraw(gnaWeakPointer<grUiWidget> widget) = 0;
    virtual void nativeWidgetPreDraw(gnaWeakPointer<grUiWidget> widget, float deltaTime) = 0;
    
    virtual bool isDesktopWidget(gnaWeakPointer<grUiWidgetLayout> parent) const = 0;
    virtual bool shouldHaveOwnRenderer(gnaWeakPointer<grUiWidget> widget, gnaWeakPointer<grUiWidgetLayout> parent) const = 0;
    virtual grRectangle get_displayBounds() const = 0;

    virtual void set_globalMousePointer(gtl::PooledAString pointerID) const = 0;

    virtual void openURI(const gtl::String &uri) = 0;

    virtual unsigned int get_doubleClickDelayMs() const = 0;

    virtual bool useNativeWindowManagerInputMechanism() const {
        return true;
    }
};
