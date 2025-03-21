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

#include <grUi/Native/NativePlatformDevice.h>

class grUiNativePlatformDeviceImpl : public grUiNativePlatformDevice {
public:
    bool isDesktopWidget(gnaWeakPointer<grUiWidgetLayout> parent) const override;
    grUiNativeFramePlatform *createFramePlatform(gnaWeakPointer<grUiWidget> widget) override;
    grUiRenderer *createRenderer(gnaWeakPointer<grUiWidget> widget) override;

    void nativeWidgetDraw(gnaWeakPointer<grUiWidget> widget) override;
    void nativeWidgetPreDraw(gnaWeakPointer<grUiWidget> widget, float deltaTime) override;

    unsigned int get_doubleClickDelayMs() const override;

    grRectangle get_displayBounds() const override;
    bool shouldHaveOwnRenderer(gnaWeakPointer<grUiWidget> widget, gnaWeakPointer<grUiWidgetLayout> parent) const override;
    void openURI(const gtl::String &uri) override;
    void set_globalMousePointer(gtl::PooledAString pointerID) const override;
};
