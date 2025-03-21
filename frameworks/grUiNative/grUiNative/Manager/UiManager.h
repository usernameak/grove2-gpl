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
#include <grUiNative/UiNativeDLL.h>

class GR_UI_NATIVE_DLLIMPEXP grUiManager {
    grUiNativePlatformDevice *m_device;
public:
    grUiManager();
    ~grUiManager();

    void init();
    void deinit();

    gnaPointer<grUiWidgetLayout> rootWidget;
};

extern GR_UI_NATIVE_DLLIMPEXP grUiManager *gr_gUiManager;
