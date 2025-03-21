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

#include <windows.h>
#include <ole2.h>
#include <grUi/Drag/DragContext.h>

class grUiNativeDropDataObjectW32 final : public IDataObject {
    ULONG m_refCount;
    gnaPointer<grUiObjectDragContext> m_ctx;
    FORMATETC m_formatetc;
    int m_numFormatEtc;

public:
    grUiNativeDropDataObjectW32(gnaPointer<grUiObjectDragContext> ctx);
    ~grUiNativeDropDataObjectW32();

    STDMETHODIMP QueryInterface(const IID &riid, void **ppvObject) override;
    STDMETHODIMP_(ULONG) AddRef() override;
    STDMETHODIMP_(ULONG) Release() override;
    STDMETHODIMP GetData(FORMATETC *pformatetcIn, STGMEDIUM *pmedium) override;
    STDMETHODIMP GetDataHere(FORMATETC *pformatetc, STGMEDIUM *pmedium) override;
    STDMETHODIMP QueryGetData(FORMATETC *pformatetc) override;
    STDMETHODIMP GetCanonicalFormatEtc(FORMATETC *pformatectIn, FORMATETC *pformatetcOut) override;
    STDMETHODIMP SetData(FORMATETC *pformatetc, STGMEDIUM *pmedium, BOOL fRelease) override;
    STDMETHODIMP EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC **ppenumFormatEtc) override;
    STDMETHODIMP DAdvise(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink, DWORD *pdwConnection) override;
    STDMETHODIMP DUnadvise(DWORD dwConnection) override;
    STDMETHODIMP EnumDAdvise(IEnumSTATDATA **ppenumAdvise) override;
};
