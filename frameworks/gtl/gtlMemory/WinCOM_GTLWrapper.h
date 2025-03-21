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

#include <comdef.h>
#include <gtlMemory/RcObject.h>

namespace gtlMemory {
    class WinCOM_GTLWrapper final : public IUnknown {
        gtlRcObject *m_rcobj;

    public:
        WinCOM_GTLWrapper(gtlRcObject *rcobj) : m_rcobj(rcobj) {
            rcobj->addRef();
        }

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) {
            IUnknown *punk = NULL;
            if (riid == IID_IUnknown) {
                punk = static_cast<IUnknown *>(this);
            }
            *ppvObject = punk;
            if (punk) {
                punk->AddRef();
                return S_OK;
            } else {
                return E_NOINTERFACE;
            }
        }

        virtual ULONG STDMETHODCALLTYPE AddRef() {
            return m_rcobj->addRef();
        }

        virtual ULONG STDMETHODCALLTYPE Release() {
            ULONG rc = m_rcobj->release();
            if (rc == 0) {
                gtlDelete this;
            }
            return rc;
        }
    };
}