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

#include <grImg/ImgModule.h>
#include <grImg/Image.h>

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBindingLoadModule_grImg() {
    gnaSingleton<gtlModuleLoader>()->loadModule(&GROVE2_MODULE_INFO(grImg));
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imager() {
    return &grImg::Image::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imaged(void *self) {
    if (!self) return nullptr;
    return static_cast<grImg::Image*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_n5grImgc5Image {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
} static grBindingProxyInfoInstance_grBinding_n5grImgc5Image;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagep(const grBindingProxyInfo_grBinding_n5grImgc5Image *info) {
    grBindingProxyInfoInstance_grBinding_n5grImgc5Image = *info;
}

class grBindingProxyClass_grBinding_n5grImgc5Image : public grImg::Image {
public:
    GTL_RTTI_DECLARE();

    using grImg::Image::Image;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_n5grImgc5Image() override {
        grBindingProxyInfoInstance_grBinding_n5grImgc5Image.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_n5grImgc5Image, GTL_RTTI_INHERITS(grImg::Image), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_n5grImgc5Image, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imageg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_n5grImgc5Image*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagex(void *self) {
    return gtlDelete static_cast<grImg::Image*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagec12RendererDatar() {
    return &grImg::Image::RendererData::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagec12RendererDatad(void *self) {
    if (!self) return nullptr;
    return static_cast<grImg::Image::RendererData*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_n5grImgc5Imagec12RendererData {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_n5grImgc5Imagec12RendererDatam6resize_2t1_8uint32_tt1_8uint32_t)(void * grBindingGchRaw, uint32_t grBindingArgRaw_width, uint32_t grBindingArgRaw_height);
} static grBindingProxyInfoInstance_grBinding_n5grImgc5Imagec12RendererData;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagec12RendererDatap(const grBindingProxyInfo_grBinding_n5grImgc5Imagec12RendererData *info) {
    grBindingProxyInfoInstance_grBinding_n5grImgc5Imagec12RendererData = *info;
}

class grBindingProxyClass_grBinding_n5grImgc5Imagec12RendererData : public grImg::Image::RendererData {
public:
    GTL_RTTI_DECLARE();

    using grImg::Image::RendererData::RendererData;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_n5grImgc5Imagec12RendererData() override {
        grBindingProxyInfoInstance_grBinding_n5grImgc5Imagec12RendererData.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual void resize(uint32_t grBindingArg_width, uint32_t grBindingArg_height) override {
        grBindingProxyInfoInstance_grBinding_n5grImgc5Imagec12RendererData.grBinding_n5grImgc5Imagec12RendererDatam6resize_2t1_8uint32_tt1_8uint32_t(grBindingGch, grBindingTypeUtils<uint32_t>::translateArgFromNativeToManaged(grBindingArg_width), grBindingTypeUtils<uint32_t>::translateArgFromNativeToManaged(grBindingArg_height));
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_n5grImgc5Imagec12RendererData, GTL_RTTI_INHERITS(grImg::Image::RendererData), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_n5grImgc5Imagec12RendererData, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagec12RendererDatag(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_n5grImgc5Imagec12RendererData*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagec12RendererDatax(void *self) {
    return gtlDelete static_cast<grImg::Image::RendererData*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagec12RendererDatan0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_n5grImgc5Imagec12RendererData();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagec12RendererDatam6resize_2t1_8uint32_tt1_8uint32_tv(void * grBindingSelfRaw, uint32_t grBindingArgRaw_width, uint32_t grBindingArgRaw_height) {
    auto grBindingSelf = static_cast<grImg::Image::RendererData *>(grBindingSelfRaw);
    auto grBindingArg_width = grBindingArgRaw_width;
    auto grBindingArg_height = grBindingArgRaw_height;
    grBindingSelf->resize(grBindingArg_width, grBindingArg_height);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagef14m_samplingModeg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grImg::Image::m_samplingMode;
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagef14m_samplingModes(void * grBindingSelfRaw, int grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grImg::Image::SamplingMode>(grBindingArgRaw_val);
    grBindingSelf->grImg::Image::m_samplingMode = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagen0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_n5grImgc5Image();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagen0_0() {
    auto grBindingReturnValue = gtlNew grImg::Image();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem9get_width_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grImg::Image::get_width();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem10get_height_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grImg::Image::get_height();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem8get_size_0(grDimension * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grImg::Image::get_size();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem8get_type_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grImg::Image::get_type();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const void * GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem14get_bitmapData_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_mipLevel) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_mipLevel = grBindingArgRaw_mipLevel;
    auto grBindingReturnValue = grBindingSelf->grImg::Image::get_bitmapData(grBindingArg_mipLevel);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem10get_format_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grImg::Image::get_format();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem14get_numMipMaps_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grImg::Image::get_numMipMaps();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem22get_implementationData_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grImg::Image::get_implementationData();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem18loadBitmapDataSlow_6t1_8uint32_tt1_8uint32_tt2_5grImg11ImageFormatt1_7CIntPtrt1_6size_tt1_3int(void * grBindingSelfRaw, uint32_t grBindingArgRaw_width, uint32_t grBindingArgRaw_height, int grBindingArgRaw_fmt, const void * grBindingArgRaw_bitmapData, size_t grBindingArgRaw_bitmapDataSize, int32_t grBindingArgRaw_numMipMaps) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_width = grBindingArgRaw_width;
    auto grBindingArg_height = grBindingArgRaw_height;
    auto grBindingArg_fmt = static_cast<grImg::ImageFormat>(grBindingArgRaw_fmt);
    auto grBindingArg_bitmapData = grBindingArgRaw_bitmapData;
    auto grBindingArg_bitmapDataSize = grBindingArgRaw_bitmapDataSize;
    auto grBindingArg_numMipMaps = grBindingArgRaw_numMipMaps;
    grBindingSelf->grImg::Image::loadBitmapDataSlow(grBindingArg_width, grBindingArg_height, grBindingArg_fmt, grBindingArg_bitmapData, grBindingArg_bitmapDataSize, grBindingArg_numMipMaps);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem11loadSurface_4t1_8uint32_tt1_8uint32_tt2_5grImg11ImageFormatt1_6IntPtr(void * grBindingSelfRaw, uint32_t grBindingArgRaw_width, uint32_t grBindingArgRaw_height, int grBindingArgRaw_fmt, void * grBindingArgRaw_externalSurface) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_width = grBindingArgRaw_width;
    auto grBindingArg_height = grBindingArgRaw_height;
    auto grBindingArg_fmt = static_cast<grImg::ImageFormat>(grBindingArgRaw_fmt);
    auto grBindingArg_externalSurface = grBindingArgRaw_externalSurface;
    grBindingSelf->grImg::Image::loadSurface(grBindingArg_width, grBindingArg_height, grBindingArg_fmt, grBindingArg_externalSurface);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem22loadImplementationData_5t1_8uint32_tt1_8uint32_tt2_5grImg11ImageFormatt1_6IntPtrt1_3int(void * grBindingSelfRaw, uint32_t grBindingArgRaw_width, uint32_t grBindingArgRaw_height, int grBindingArgRaw_fmt, void * grBindingArgRaw_externalSurface, int32_t grBindingArgRaw_numMipMaps) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_width = grBindingArgRaw_width;
    auto grBindingArg_height = grBindingArgRaw_height;
    auto grBindingArg_fmt = static_cast<grImg::ImageFormat>(grBindingArgRaw_fmt);
    auto grBindingArg_externalSurface = grBindingArgRaw_externalSurface;
    auto grBindingArg_numMipMaps = grBindingArgRaw_numMipMaps;
    grBindingSelf->grImg::Image::loadImplementationData(grBindingArg_width, grBindingArg_height, grBindingArg_fmt, grBindingArg_externalSurface, grBindingArg_numMipMaps);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem6resize_2t1_8uint32_tt1_8uint32_t(void * grBindingSelfRaw, uint32_t grBindingArgRaw_width, uint32_t grBindingArgRaw_height) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_width = grBindingArgRaw_width;
    auto grBindingArg_height = grBindingArgRaw_height;
    grBindingSelf->grImg::Image::resize(grBindingArg_width, grBindingArg_height);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem17calculateMipWidth_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_mipLevel) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_mipLevel = grBindingArgRaw_mipLevel;
    auto grBindingReturnValue = grBindingSelf->grImg::Image::calculateMipWidth(grBindingArg_mipLevel);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem18calculateMipHeight_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_mipLevel) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_mipLevel = grBindingArgRaw_mipLevel;
    auto grBindingReturnValue = grBindingSelf->grImg::Image::calculateMipHeight(grBindingArg_mipLevel);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT size_t GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem17calculateByteSize_4t2_5grImg11ImageFormatt1_8uint32_tt1_8uint32_tt1_3int(int grBindingArgRaw_format, uint32_t grBindingArgRaw_width, uint32_t grBindingArgRaw_height, int32_t grBindingArgRaw_mipLevel) {
    auto grBindingArg_format = static_cast<grImg::ImageFormat>(grBindingArgRaw_format);
    auto grBindingArg_width = grBindingArgRaw_width;
    auto grBindingArg_height = grBindingArgRaw_height;
    auto grBindingArg_mipLevel = grBindingArgRaw_mipLevel;
    auto grBindingReturnValue = grImg::Image::calculateByteSize(grBindingArg_format, grBindingArg_width, grBindingArg_height, grBindingArg_mipLevel);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT size_t GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem20calculateMipByteSize_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_mipLevel) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_mipLevel = grBindingArgRaw_mipLevel;
    auto grBindingReturnValue = grBindingSelf->grImg::Image::calculateMipByteSize(grBindingArg_mipLevel);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT size_t GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem24calculateTotalBitmapSize_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grImg::Image::calculateTotalBitmapSize();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT size_t GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem18calculateMipOffset_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_mipLevel) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_mipLevel = grBindingArgRaw_mipLevel;
    auto grBindingReturnValue = grBindingSelf->grImg::Image::calculateMipOffset(grBindingArg_mipLevel);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT size_t GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagem19get_bitmapRowStride_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_mipLevel) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_mipLevel = grBindingArgRaw_mipLevel;
    auto grBindingReturnValue = grBindingSelf->grImg::Image::get_bitmapRowStride(grBindingArg_mipLevel);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagef14m_rendererDatag(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grImg::Image::m_rendererData;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_n5grImgc5Imagef14m_rendererDatas(void * grBindingSelfRaw, void * grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grImg::Image *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grImg::Image::RendererData *>(grBindingArgRaw_val);
    grBindingSelf->grImg::Image::m_rendererData = grBindingArg_val;
}

