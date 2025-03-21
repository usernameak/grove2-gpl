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

#include "NativeDropDataObjectW32.h"

#include <shlobj.h>
#include <gtlMemory/WinCOM_GTLWrapper.h>

grUiNativeDropDataObjectW32::grUiNativeDropDataObjectW32(gnaPointer<grUiObjectDragContext> ctx)
    : m_refCount(1),
      m_ctx(std::move(ctx)) {
    if (m_ctx->m_dragObject->get_type() == grUiDragObject::TYPE_SPECIAL) {
        m_formatetc.cfFormat = CF_PRIVATEFIRST;
        m_formatetc.ptd      = NULL;
        m_formatetc.dwAspect = DVASPECT_CONTENT;
        m_formatetc.lindex   = 0;
        m_formatetc.tymed    = TYMED_HGLOBAL;

        m_numFormatEtc = 1;
    } else {
        m_numFormatEtc = 0;
    }
}

grUiNativeDropDataObjectW32::~grUiNativeDropDataObjectW32() = default;

HRESULT grUiNativeDropDataObjectW32::QueryInterface(const IID &riid, void **ppvObject) {
    IUnknown *punk = NULL;
    if (riid == IID_IUnknown) {
        punk = static_cast<IUnknown *>(this);
    } else if (riid == IID_IDataObject) {
        punk = static_cast<IDataObject *>(this);
    }
    *ppvObject = punk;
    if (punk) {
        punk->AddRef();
        return S_OK;
    } else {
        return E_NOINTERFACE;
    }
}

ULONG grUiNativeDropDataObjectW32::AddRef() {
    return ++m_refCount;
}

ULONG grUiNativeDropDataObjectW32::Release() {
    ULONG cRef = --m_refCount;
    if (cRef == 0)
        gtlDelete this;
    return cRef;
}

HRESULT grUiNativeDropDataObjectW32::GetData(FORMATETC *pfeIn, STGMEDIUM *pmedium) {
    if (m_numFormatEtc == 0)
        return DV_E_FORMATETC;
    if (pfeIn->cfFormat == CF_PRIVATEFIRST) {
        if (pfeIn->dwAspect != DVASPECT_CONTENT)
            return DV_E_FORMATETC;
        if (!(pfeIn->tymed & TYMED_HGLOBAL))
            return DV_E_FORMATETC;
        if (pfeIn->lindex != 0)
            return DV_E_FORMATETC;

        if (m_ctx->m_dragObject->get_type() != grUiDragObject::TYPE_SPECIAL)
            return DV_E_FORMATETC;

        HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, sizeof(void *));
        if (!hg) {
            return E_OUTOFMEMORY;
        }
        void **ppObject = (void **)GlobalLock(hg);
        if (!ppObject) {
            GlobalFree(hg);
            return E_OUTOFMEMORY;
        }
        *ppObject = &*(m_ctx->m_dragObject);
        GlobalUnlock(hg);

        pmedium->tymed          = TYMED_HGLOBAL;
        pmedium->hGlobal        = hg;
        pmedium->pUnkForRelease = gtlNew gtlMemory::WinCOM_GTLWrapper(&*m_ctx->m_dragObject);
        return S_OK;
    }
    return DV_E_FORMATETC;
}

HRESULT grUiNativeDropDataObjectW32::GetDataHere(FORMATETC *pformatetc, STGMEDIUM *pmedium) {
    return E_NOTIMPL;
}

HRESULT grUiNativeDropDataObjectW32::QueryGetData(FORMATETC *pfeIn) {
    if (pfeIn->cfFormat == CF_PRIVATEFIRST) {
        if (pfeIn->dwAspect != DVASPECT_CONTENT)
            return S_FALSE;
        if (!(pfeIn->tymed & TYMED_HGLOBAL))
            return S_FALSE;
        if (pfeIn->lindex != 0)
            return S_FALSE;

        if (m_ctx->m_dragObject->get_type() != grUiDragObject::TYPE_SPECIAL)
            return S_FALSE;

        return S_OK;
    }
    return S_FALSE;
}

HRESULT grUiNativeDropDataObjectW32::GetCanonicalFormatEtc(FORMATETC *pfeIn, FORMATETC *pfeOut) {
    *pfeOut     = *pfeIn;
    pfeOut->ptd = NULL;
    return DATA_S_SAMEFORMATETC;
}

HRESULT grUiNativeDropDataObjectW32::SetData(FORMATETC *pformatetc, STGMEDIUM *pmedium, BOOL fRelease) {
    return E_NOTIMPL;
}

HRESULT grUiNativeDropDataObjectW32::EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC **ppefe) {
    if (dwDirection == DATADIR_GET) {
        if (m_ctx->m_dragObject->get_type() == grUiDragObject::TYPE_SPECIAL) {
            return SHCreateStdEnumFmtEtc(1, &m_formatetc, ppefe);
        } else {
            return SHCreateStdEnumFmtEtc(0, NULL, ppefe);
        }
    }
    *ppefe = NULL;
    return E_NOTIMPL;
}

HRESULT grUiNativeDropDataObjectW32::DAdvise(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink, DWORD *pdwConnection) {
    return OLE_E_ADVISENOTSUPPORTED;
}

HRESULT grUiNativeDropDataObjectW32::DUnadvise(DWORD dwConnection) {
    return OLE_E_ADVISENOTSUPPORTED;
}

HRESULT grUiNativeDropDataObjectW32::EnumDAdvise(IEnumSTATDATA **ppenumAdvise) {
    return OLE_E_ADVISENOTSUPPORTED;
}
