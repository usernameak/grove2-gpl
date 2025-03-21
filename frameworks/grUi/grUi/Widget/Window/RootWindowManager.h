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

#include "WindowManager.h"
#include <grUi/Drag/DragContext.h>
#include <grUi/UiDLL.h>

class grUiRootWindowManager;

GR_UI_DLLIMPEXP extern gnaPointer<grUiRootWindowManager> grUi_gRootWindowManager;

class GR_UI_DLLIMPEXP grUiRootWindowManager : public grUiWindowManager {
    gnaPointer<grUiDragContext> m_dragAndDropContext;

public:
    grUiRootWindowManager(grUiNativePlatformDevice *device);
    virtual ~grUiRootWindowManager() override;

    void startDragAndDrop(gnaPointer<grUiDragContext> context);
    gnaWeakPointer<grUiDragContext> get_dragContext() {
        return m_dragAndDropContext;
    }
    void nativeWidgetDraw() override;
    void nativeWidgetPreDraw(float deltaTime) override;
    void nativeWidgetPresent() override;
    bool usesNativeChildEventBehavior() override;
    void update() override;
    void endDragAndDrop();

    static gnaWeakPointer<grUiRootWindowManager> getRootWindowManager() {
        return grUi_gRootWindowManager;
    }

    static void setRootWindowManager(gnaPointer<grUiRootWindowManager> wm) {
        grUi_gRootWindowManager = std::move(wm);
    }

private:
    bool onMouseMove(grUiEventMouseMove &ev);
    bool onMouseUp(grUiEventMouseUp &ev);

public:
    GTL_RTTI_DECLARE();
};
