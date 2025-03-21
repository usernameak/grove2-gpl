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

#include "UiManager.h"

#include <grUi/Widget/Window/RootWindowManager.h>
#include <Windows.h>
#include <grUiNative/Device/NativePlatformDeviceImpl.h>

grUiManager *gr_gUiManager;

grUiManager::grUiManager() {
    m_device = gtlNew grUiNativePlatformDeviceImpl;
}

grUiManager::~grUiManager() {
    gtlDelete m_device;
}

void grUiManager::init() {
    if (!SUCCEEDED(OleInitialize(NULL))) {
        GR_FATAL(GTXT("OleInitialize Failed"));
    }
    rootWidget = grUi_gRootWindowManager = gnaNew<grUiRootWindowManager>(m_device);
    rootWidget->update();
}

void grUiManager::deinit() {
    rootWidget = grUi_gRootWindowManager = nullptr;
    OleUninitialize();
}
