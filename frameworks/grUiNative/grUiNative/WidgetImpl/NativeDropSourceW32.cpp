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

#include "NativeDropSourceW32.h"

#include <grUi/Widget/Window/RootWindowManager.h>

grUiNativeDropSourcePlatformWin::grUiNativeDropSourcePlatformWin()
    : m_refCount(1),
      m_ctx(nullptr) {}

grUiNativeDropSourcePlatformWin::~grUiNativeDropSourcePlatformWin() = default;

HRESULT grUiNativeDropSourcePlatformWin::QueryInterface(const IID &riid, void **ppvObject) {
    IUnknown *punk = NULL;
    if (riid == IID_IUnknown) {
        punk = static_cast<IUnknown *>(this);
    } else if (riid == IID_IDropSource) {
        punk = static_cast<IDropSource *>(this);
    }

    *ppvObject = punk;
    if (punk) {
        punk->AddRef();
        return S_OK;
    } else {
        return E_NOINTERFACE;
    }
}

ULONG grUiNativeDropSourcePlatformWin::AddRef() {
    return ++m_refCount;
}

ULONG grUiNativeDropSourcePlatformWin::Release() {
    ULONG cRef = --m_refCount;
    if (cRef == 0)
        gtlDelete this;
    return cRef;
}

HRESULT grUiNativeDropSourcePlatformWin::QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState) {
    HRESULT hres = S_OK;

    if (fEscapePressed) {
        hres = DRAGDROP_S_CANCEL;
    } else {
        DWORD mouseButtonCvt = 0;
        switch (m_ctx->mouseButton) {
        case 0:
            mouseButtonCvt = MK_LBUTTON;
            break;
        case 1:
            mouseButtonCvt = MK_RBUTTON;
            break;
        case 2:
            mouseButtonCvt = MK_MBUTTON;
            break;
        case 3:
            mouseButtonCvt = MK_XBUTTON1;
            break;
        case 4:
            mouseButtonCvt = MK_XBUTTON2;
            break;
        }
        if (!(grfKeyState & mouseButtonCvt)) {
            hres = DRAGDROP_S_DROP;
        }
    }

    return hres;
}

HRESULT grUiNativeDropSourcePlatformWin::GiveFeedback(DWORD dwEffect) {
    return DRAGDROP_S_USEDEFAULTCURSORS;
}

void grUiNativeDropSourcePlatformWin::set_dragContext(gnaPointer<grUiObjectDragContext> ctx) {
    m_ctx = std::move(ctx);
}
