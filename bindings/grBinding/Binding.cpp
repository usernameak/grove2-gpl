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

#include <grBinding/BindingSupport.h>

#include <gtlObject/Object.h>
#include <gtlObject/Cloneable.h>
#include <nxfIO/FileInputStream.h>
#include <nxfResource/FlatFileResourceManager.h>
#include <nxfResource/Asset/AssetManager.h>
#include <nxfResource/RMEx/ExtendedResourceManager.h>
#include <nxfResource/Archive/GPKArchive.h>

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18nxfResourceManagerr() {
    return &nxfResourceManager::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18nxfResourceManagerd(void *self) {
    if (!self) return nullptr;
    return static_cast<nxfResourceManager*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18nxfResourceManagerx(void *self) {
    return gtlDelete static_cast<nxfResourceManager*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18nxfResourceManagerm15initializeIndex_1t1_4boolv(void * grBindingSelfRaw, bool grBindingArgRaw_reinitialize) {
    auto grBindingSelf = static_cast<nxfResourceManager *>(grBindingSelfRaw);
    auto grBindingArg_reinitialize = grBindingArgRaw_reinitialize;
    grBindingSelf->initializeIndex(grBindingArg_reinitialize);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c18nxfResourceManagerm24getGlobalResourceManager_0() {
    auto grBindingReturnValue = nxfResourceManager::getGlobalResourceManager();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18nxfResourceManagerm24setGlobalResourceManager_1t1_18nxfResourceManager(void * grBindingArgRaw_rm) {
    auto grBindingArg_rm = static_cast<nxfResourceManager *>(grBindingArgRaw_rm);
    nxfResourceManager::setGlobalResourceManager(grBindingArg_rm);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14nxfInputStreamr() {
    return &nxfInputStream::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14nxfInputStreamd(void *self) {
    if (!self) return nullptr;
    return static_cast<nxfInputStream*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14nxfInputStreamx(void *self) {
    return gtlDelete static_cast<nxfInputStream*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void *GR_BINDING_THUNK_CALLCONV grBinding_c15nxfAssetManagers() {
    return gnaSingleton<nxfAssetManager>();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15nxfAssetManagerx(void *self) {
    return gtlDelete static_cast<nxfAssetManager*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c15nxfAssetManagern0_0() {
    auto grBindingReturnValue = gtlNew nxfAssetManager();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15nxfAssetManagerm10dropCaches_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<nxfAssetManager *>(grBindingSelfRaw);
    grBindingSelf->nxfAssetManager::dropCaches();
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c15nxfAssetManagerm14loadOrGetAsset_4t2_3gtl12PooledStringt1_11RuntimeTypet1_9gtlObjectt1_8uint32_t(void * grBindingSelfRaw, const gtl::WIDECHAR * grBindingArgRaw_filename, const gtlRTTI * grBindingArgRaw_objectType, void * & grBindingArgRaw_obj, uint32_t grBindingArgRaw_loadFlags) {
    auto grBindingSelf = static_cast<nxfAssetManager *>(grBindingSelfRaw);
    auto grBindingArg_filename = static_cast<gtl::PooledString>(grBindingArgRaw_filename);
    auto grBindingArg_objectType = grBindingArgRaw_objectType;
    gnaPointer<gtlObject> grBindingArg_obj;
    auto grBindingArg_loadFlags = grBindingArgRaw_loadFlags;
    auto grBindingReturnValue = grBindingSelf->nxfAssetManager::loadOrGetAsset(grBindingArg_filename, grBindingArg_objectType, grBindingArg_obj, grBindingArg_loadFlags);
    if (grBindingArg_obj) grBindingArg_obj->addRef();
    grBindingArgRaw_obj = &*grBindingArg_obj;
    return (grBindingReturnValue).errorCode;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c9gtlObjectr() {
    return &gtlObject::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c9gtlObjectd(void *self) {
    if (!self) return nullptr;
    return static_cast<gtlObject*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c9gtlObject {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
} static grBindingProxyInfoInstance_grBinding_c9gtlObject;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9gtlObjectp(const grBindingProxyInfo_grBinding_c9gtlObject *info) {
    grBindingProxyInfoInstance_grBinding_c9gtlObject = *info;
}

class grBindingProxyClass_grBinding_c9gtlObject : public gtlObject {
public:
    GTL_RTTI_DECLARE();

    using gtlObject::gtlObject;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c9gtlObject() override {
        grBindingProxyInfoInstance_grBinding_c9gtlObject.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c9gtlObject, GTL_RTTI_INHERITS(gtlObject), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c9gtlObject, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9gtlObjectg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c9gtlObject*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9gtlObjectx(void *self) {
    return gtlDelete static_cast<gtlObject*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c26nxfFlatFileResourceManagerr() {
    return &nxfFlatFileResourceManager::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c26nxfFlatFileResourceManagerd(void *self) {
    if (!self) return nullptr;
    return static_cast<nxfFlatFileResourceManager*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c26nxfFlatFileResourceManagerx(void *self) {
    return gtlDelete static_cast<nxfFlatFileResourceManager*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c26nxfFlatFileResourceManagern0_1t2_3gtl6String(const gtl::WIDECHAR * grBindingArgRaw_resourceDirectory) {
    auto grBindingArg_resourceDirectory = static_cast<gtl::String>(grBindingArgRaw_resourceDirectory);
    auto grBindingReturnValue = gtlNew nxfFlatFileResourceManager(grBindingArg_resourceDirectory);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c26nxfFlatFileResourceManagerm15initializeIndex_1t1_4boolv(void * grBindingSelfRaw, bool grBindingArgRaw_reinitialize) {
    auto grBindingSelf = static_cast<nxfFlatFileResourceManager *>(grBindingSelfRaw);
    auto grBindingArg_reinitialize = grBindingArgRaw_reinitialize;
    grBindingSelf->initializeIndex(grBindingArg_reinitialize);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c25nxfMutableResourceManagerr() {
    return &nxfMutableResourceManager::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c25nxfMutableResourceManagerd(void *self) {
    if (!self) return nullptr;
    return static_cast<nxfMutableResourceManager*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c25nxfMutableResourceManagerx(void *self) {
    return gtlDelete static_cast<nxfMutableResourceManager*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec23ExtendedResourceManagerr() {
    return &nxfResource::ExtendedResourceManager::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec23ExtendedResourceManagerd(void *self) {
    if (!self) return nullptr;
    return static_cast<nxfResource::ExtendedResourceManager*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec23ExtendedResourceManagerx(void *self) {
    return gtlDelete static_cast<nxfResource::ExtendedResourceManager*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec23ExtendedResourceManagern0_0() {
    auto grBindingReturnValue = gtlNew nxfResource::ExtendedResourceManager();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec23ExtendedResourceManagerm15initializeIndex_1t1_4boolv(void * grBindingSelfRaw, bool grBindingArgRaw_reinitialize) {
    auto grBindingSelf = static_cast<nxfResource::ExtendedResourceManager *>(grBindingSelfRaw);
    auto grBindingArg_reinitialize = grBindingArgRaw_reinitialize;
    grBindingSelf->initializeIndex(grBindingArg_reinitialize);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec23ExtendedResourceManagerm21addArchiveToNamespace_2t3_11nxfResource23ExtendedResourceManager14OrderNamespacet1_18nxfResourceManager(void * grBindingSelfRaw, int grBindingArgRaw_ns, void * grBindingArgRaw_arch) {
    auto grBindingSelf = static_cast<nxfResource::ExtendedResourceManager *>(grBindingSelfRaw);
    auto grBindingArg_ns = static_cast<nxfResource::ExtendedResourceManager::OrderNamespace>(grBindingArgRaw_ns);
    auto grBindingArg_arch = static_cast<nxfResourceManager *>(grBindingArgRaw_arch);
    grBindingSelf->nxfResource::ExtendedResourceManager::addArchiveToNamespace(grBindingArg_ns, grBindingArg_arch);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec23ExtendedResourceManagerm14clearNamespace_1t3_11nxfResource23ExtendedResourceManager14OrderNamespace(void * grBindingSelfRaw, int grBindingArgRaw_ns) {
    auto grBindingSelf = static_cast<nxfResource::ExtendedResourceManager *>(grBindingSelfRaw);
    auto grBindingArg_ns = static_cast<nxfResource::ExtendedResourceManager::OrderNamespace>(grBindingArgRaw_ns);
    grBindingSelf->nxfResource::ExtendedResourceManager::clearNamespace(grBindingArg_ns);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec10GPKArchiver() {
    return &nxfResource::GPKArchive::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec10GPKArchived(void *self) {
    if (!self) return nullptr;
    return static_cast<nxfResource::GPKArchive*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec10GPKArchivex(void *self) {
    return gtlDelete static_cast<nxfResource::GPKArchive*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec10GPKArchiven0_1t1_14nxfInputStream(void * grBindingArgRaw_stream) {
    auto grBindingArg_stream = grBindingExpandWeakPtr<nxfInputStream>(grBindingArgRaw_stream);
    auto grBindingReturnValue = gtlNew nxfResource::GPKArchive(grBindingArg_stream);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n11nxfResourcec10GPKArchivem15initializeIndex_1t1_4boolv(void * grBindingSelfRaw, bool grBindingArgRaw_reinitialize) {
    auto grBindingSelf = static_cast<nxfResource::GPKArchive *>(grBindingSelfRaw);
    auto grBindingArg_reinitialize = grBindingArgRaw_reinitialize;
    grBindingSelf->initializeIndex(grBindingArg_reinitialize);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c11gtlRcObjectx(void *self) {
    return gtlDelete static_cast<gtlRcObject*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c12gtlCloneabler() {
    return &gtlCloneable::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c12gtlCloneabled(void *self) {
    if (!self) return nullptr;
    return static_cast<gtlCloneable*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c12gtlCloneable {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
} static grBindingProxyInfoInstance_grBinding_c12gtlCloneable;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12gtlCloneablep(const grBindingProxyInfo_grBinding_c12gtlCloneable *info) {
    grBindingProxyInfoInstance_grBinding_c12gtlCloneable = *info;
}

class grBindingProxyClass_grBinding_c12gtlCloneable : public gtlCloneable {
public:
    GTL_RTTI_DECLARE();

    using gtlCloneable::gtlCloneable;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c12gtlCloneable() override {
        grBindingProxyInfoInstance_grBinding_c12gtlCloneable.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c12gtlCloneable, GTL_RTTI_INHERITS(gtlCloneable), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c12gtlCloneable, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12gtlCloneableg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c12gtlCloneable*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12gtlCloneablex(void *self) {
    return gtlDelete static_cast<gtlCloneable*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18nxfFileInputStreamr() {
    return &nxfFileInputStream::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18nxfFileInputStreamd(void *self) {
    if (!self) return nullptr;
    return static_cast<nxfFileInputStream*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18nxfFileInputStreamx(void *self) {
    return gtlDelete static_cast<nxfFileInputStream*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c18nxfFileInputStreamn0_0() {
    auto grBindingReturnValue = gtlNew nxfFileInputStream();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c18nxfFileInputStreamm4open_1t2_3gtl6String(void * grBindingSelfRaw, const gtl::WIDECHAR * grBindingArgRaw_filename) {
    auto grBindingSelf = static_cast<nxfFileInputStream *>(grBindingSelfRaw);
    auto grBindingArg_filename = static_cast<gtl::String>(grBindingArgRaw_filename);
    auto grBindingReturnValue = grBindingSelf->nxfFileInputStream::open(grBindingArg_filename);
    return (grBindingReturnValue).errorCode;
}

