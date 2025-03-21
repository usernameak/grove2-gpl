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

#include "BindingSupport.h"

grBindingReleaseGchType grBindingGlobal_releaseGch;

extern "C" GR_BINDING_THUNK_EXPORT gtl::ASCIICHAR *GR_BINDING_THUNK_CALLCONV grBindingAllocString(const gtl::ASCIICHAR *pstr);
extern "C" GR_BINDING_THUNK_EXPORT gtl::WIDECHAR *GR_BINDING_THUNK_CALLCONV grBindingAllocWString(const gtl::WIDECHAR *pstr);
extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBindingFreeString(const gtl::ASCIICHAR *pstr);
extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBindingFreeWString(const gtl::WIDECHAR *pstr);

extern "C" GR_BINDING_THUNK_EXPORT void *GR_BINDING_THUNK_CALLCONV grBindingAllocMem(size_t size);
extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBindingFreeMem(void *ptr);

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBindingAddRef(gtlRcObject *obj);
extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBindingRelease(gtlRcObject *obj);
extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBindingDeleteRcObject(gtlRcObject *obj);
extern "C" GR_BINDING_THUNK_EXPORT const gtlRTTI *GR_BINDING_THUNK_CALLCONV grBindingRcObjectGetRTTIDynamic(gtlRcObject *obj);
extern "C" GR_BINDING_THUNK_EXPORT const gtlRTTI *GR_BINDING_THUNK_CALLCONV grBindingRcObjectGetRTTIStatic();

extern "C" GR_BINDING_THUNK_EXPORT const gtlRTTI *GR_BINDING_THUNK_CALLCONV grBindingRttiBaseClass(const gtlRTTI *);
extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBindingSetCommonFuncs(grBindingReleaseGchType releaseDelegate);
extern "C" GR_BINDING_THUNK_EXPORT void *GR_BINDING_THUNK_CALLCONV grBindingRttiCheckNETGch(const unsigned char *ptr, const gtlRTTI *rtti);

gtl::ASCIICHAR* grBindingAllocString(const gtl::ASCIICHAR* pstr) {
    size_t size = gtl::StrLen(pstr) + 1;
    gtl::ASCIICHAR *chars = gtlNew gtl::ASCIICHAR[size];
    memcpy(chars, pstr, size * sizeof(*pstr));
    return chars;
}

gtl::WIDECHAR* grBindingAllocWString(const gtl::WIDECHAR* pstr) {
    size_t size = gtl::StrLen(pstr) + 1;
    gtl::WIDECHAR *chars = gtlNew gtl::WIDECHAR[size];
    memcpy(chars, pstr, size * sizeof(*pstr));
    return chars;
}

void grBindingFreeString(const gtl::ASCIICHAR *pstr) {
    gtlDeleteArray pstr;
}

void grBindingFreeWString(const gtl::WIDECHAR *pstr) {
    gtlDeleteArray pstr;
}

void *grBindingAllocMem(size_t size) {
    return gtlMalloc(size);
}

void grBindingFreeMem(void *ptr) {
    gtlFree(ptr);
}

void grBindingAddRef(gtlRcObject *obj) {
    obj->addRef();
}

void grBindingRelease(gtlRcObject *obj) {
    obj->release();
}

void grBindingDeleteRcObject(gtlRcObject *obj) {
    gtlDelete obj;
}

const gtlRTTI *grBindingRcObjectGetRTTIDynamic(gtlRcObject *obj) {
    return obj->get_rtti();
}

const gtlRTTI *grBindingRcObjectGetRTTIStatic() {
    return &gtlRcObject::st_rtti;
}

const gtlRTTI *grBindingRttiBaseClass(const gtlRTTI *rtti) {
    return rtti->get_baseClass();
}

void *grBindingRttiCheckNETGch(const unsigned char *ptr, const gtlRTTI *rtti) {
    if (rtti->get_bindingType() == GNA_FOURCC('.NET')) {
        return *(void **)(ptr + rtti->get_bindingOffset());
    }
    return nullptr;
}

void grBindingSetCommonFuncs(grBindingReleaseGchType releaseGch) {
    grBindingGlobal_releaseGch = releaseGch;
}

GTL_RTTI_DEFINE(grBindingGCHandleHolder, GTL_RTTI_INHERITS(gtlRcObject));

grBindingGCHandleHolder::grBindingGCHandleHolder(void *gch) : m_gch(gch) {}
grBindingGCHandleHolder::~grBindingGCHandleHolder() {
    if (m_gch != nullptr) {
        grBindingGlobal_releaseGch(m_gch);
    }
}
