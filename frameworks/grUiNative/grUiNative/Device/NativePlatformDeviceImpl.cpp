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

#include "NativePlatformDeviceImpl.h"

#include <grUi/Widget/Window/RootWindowManager.h>
#include <grUiNative/WidgetImpl/NativeFramePlatformW32.h>

#include <grRenderCore/RenderInterface.h>

#include <grUiNative/Render/UiRendererImpl.h>
#include <shellapi.h>

bool grUiNativePlatformDeviceImpl::isDesktopWidget(gnaWeakPointer<grUiWidgetLayout> parent) const {
    return parent && parent == grUi_gRootWindowManager;
}

grUiNativeFramePlatform *grUiNativePlatformDeviceImpl::createFramePlatform(gnaWeakPointer<grUiWidget> widget) {
    return gtlNew grUiNativeFramePlatformImpl(widget);
}

grUiRenderer *grUiNativePlatformDeviceImpl::createRenderer(gnaWeakPointer<grUiWidget> widget) {
    return gtlNew grUiRendererImpl();
}

void grUiNativePlatformDeviceImpl::nativeWidgetDraw(gnaWeakPointer<grUiWidget> widget) {
    if (widget == grUi_gRootWindowManager) {
        return;
    }
    grUiNativeFramePlatformShared *platform = static_cast<grUiNativeFramePlatformShared *>(widget->get_nativeFrame());

    grUiRendererImpl *renderer = static_cast<grUiRendererImpl *>(widget->get_windowRenderer());
    if (platform && renderer) {
        platform->get_videoOutput()->prepareBackbuffers();
        renderer->m_rts = platform->get_videoOutput()->getBackbufferRenderTargetSet();

        grRectangle vp = platform->get_windowViewport();
        renderer->resize(vp.width, vp.height);
        renderer->prepare(0.0f);
        renderer->draw();
    }
}

void grUiNativePlatformDeviceImpl::nativeWidgetPreDraw(gnaWeakPointer<grUiWidget> widget, float deltaTime) {
    if (widget == grUi_gRootWindowManager) {
        return;
    }
    grUiNativeFramePlatformShared *platform = static_cast<grUiNativeFramePlatformShared *>(widget->get_nativeFrame());

    grUiRendererImpl *renderer = static_cast<grUiRendererImpl *>(widget->get_windowRenderer());
    if (platform && renderer) {
        renderer->m_rts = nullptr;

        renderer->set_renderWidget(widget->get_nativeViewportWidget());

        grDimension size = widget->get_size();
        widget->preDraw(renderer, { 0, 0, size.width, size.height });

        renderer->update(deltaTime);
    }
}

unsigned int grUiNativePlatformDeviceImpl::get_doubleClickDelayMs() const {
    return GetDoubleClickTime();
}

grRectangle grUiNativePlatformDeviceImpl::get_displayBounds() const {
    return {
        GetSystemMetrics(SM_XVIRTUALSCREEN), GetSystemMetrics(SM_YVIRTUALSCREEN),
        GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN)
    };
}

bool grUiNativePlatformDeviceImpl::shouldHaveOwnRenderer(gnaWeakPointer<grUiWidget> widget, gnaWeakPointer<grUiWidgetLayout> parent) const {
    return isDesktopWidget(parent);
}

void grUiNativePlatformDeviceImpl::openURI(const gtl::String &uri) {
    ShellExecuteW(NULL, L"open", uri.toCString(), NULL, NULL, SW_SHOW);
}

void grUiNativePlatformDeviceImpl::set_globalMousePointer(gtl::PooledAString pointerID) const {
}
