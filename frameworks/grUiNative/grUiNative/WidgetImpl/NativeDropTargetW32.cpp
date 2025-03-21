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

#include "NativeDropTargetW32.h"

#include "NativeFramePlatformW32.h"

grUiNativeDropTargetPlatformWin::grUiNativeDropTargetPlatformWin(grUiNativeFramePlatformImpl *nfPlatform)
    : m_refCount(1),
      m_nfPlatform(nfPlatform) {}

grUiNativeDropTargetPlatformWin::~grUiNativeDropTargetPlatformWin() = default;

HRESULT grUiNativeDropTargetPlatformWin::QueryInterface(const IID &riid, void **ppvObject) {
    IUnknown *punk = NULL;
    if (riid == IID_IUnknown) {
        punk = static_cast<IUnknown *>(this);
    } else if (riid == IID_IDropTarget) {
        punk = static_cast<IDropTarget *>(this);
    }

    *ppvObject = punk;
    if (punk) {
        punk->AddRef();
        return S_OK;
    } else {
        return E_NOINTERFACE;
    }
}

ULONG grUiNativeDropTargetPlatformWin::AddRef() {
    return ++m_refCount;
}

ULONG grUiNativeDropTargetPlatformWin::Release() {
    ULONG cRef = --m_refCount;
    if (cRef == 0)
        gtlDelete this;
    return cRef;
}

HRESULT grUiNativeDropTargetPlatformWin::DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) {
    POINT ptc = { pt.x, pt.y };
    ScreenToClient(m_nfPlatform->m_hwnd, &ptc);
    m_nfPlatform->emitMouseMoveEvent(ptc.x, ptc.y);

    *pdwEffect = DROPEFFECT_COPY;

    return S_OK;
}

HRESULT grUiNativeDropTargetPlatformWin::DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) {
    POINT ptc = { pt.x, pt.y };
    ScreenToClient(m_nfPlatform->m_hwnd, &ptc);
    m_nfPlatform->emitMouseMoveEvent(ptc.x, ptc.y);

    *pdwEffect = DROPEFFECT_COPY;

    return S_OK;
}

HRESULT grUiNativeDropTargetPlatformWin::DragLeave() {
    m_nfPlatform->emitMouseLeaveEvent();

    return S_OK;
}

HRESULT grUiNativeDropTargetPlatformWin::Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) {
    POINT ptc = { pt.x, pt.y };
    ScreenToClient(m_nfPlatform->m_hwnd, &ptc);
    m_nfPlatform->emitMouseMoveEvent(ptc.x, ptc.y);

    FORMATETC fe;
    fe.cfFormat = CF_PRIVATEFIRST;
    fe.dwAspect = DVASPECT_CONTENT;
    fe.lindex   = 0;
    fe.tymed    = TYMED_HGLOBAL;
    fe.ptd      = NULL;

    STGMEDIUM stgm;

    HRESULT hres = pDataObj->GetData(&fe, &stgm);
    if (FAILED(hres)) {
        *pdwEffect = DROPEFFECT_NONE;
        return hres;
    }

    grUiDragObject **p = (grUiDragObject **)GlobalLock(stgm.hGlobal);
    (*p)->addRef();
    if (stgm.pUnkForRelease) {
        stgm.pUnkForRelease->Release();
    }
    gnaPointer gpDragObject(*p);
    GlobalUnlock(stgm.hGlobal);
    GlobalFree(stgm.hGlobal);

    m_nfPlatform->emitObjectDropEvent(gpDragObject);

    *pdwEffect = DROPEFFECT_COPY;

    return S_OK;
}
