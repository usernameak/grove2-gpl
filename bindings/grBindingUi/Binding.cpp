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

#include <grUi/GUI_Module.h>
#include <grUi/Widget/Widget.h>
#include <grUi/Widget/WidgetLayout.h>
#include <grUi/Widget/WidgetEmpty.h>
#include <grUi/Widget/WidgetButton.h>
#include <grUi/Widget/WidgetTooltip.h>
#include <grUi/Widget/WidgetScrollPane.h>
#include <grUi/Widget/WidgetImage.h>
#include <grUi/Widget/Window/RootWindowManager.h>
#include <grUi/Widget/Window/Frame.h>
#include <grUi/Layout/LayoutLinear.h>
#include <grUi/Layout/LayoutGrid.h>
#include <grUi/Layout/LayoutOverlay.h>
#include <grUi/Layout/LayoutAbsolute.h>
#include <grUi/Style/StyleManager.h>
#include <grUi/Style/GSS/StyleSheet.h>
#include <grUi/Native/NativePlatformDevice.h>
#include <grUi/Widget/Native/NativeFramePlatform.h>
#include <grUi/Drag/DragContext.h>
#include <grUi/Drag/DragObject.h>
#include <grUi/Utils/MultipatchImageCache.h>
#include <grUi/Text/TextRenderer.h>

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBindingLoadModule_grUi() {
    gnaSingleton<gtlModuleLoader>()->loadModule(&GROVE2_MODULE_INFO(grUi));
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonr() {
    return &grUiWidgetButton::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtond(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiWidgetButton*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c16grUiWidgetButton {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetButtonm22updateVisualsFromState_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm15get_contentBias_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutDirty_0)(void * grBindingGchRaw);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15onBoundsChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonp(const grBindingProxyInfo_grBinding_c16grUiWidgetButton *info) {
    grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton = *info;
}

class grBindingProxyClass_grBinding_c16grUiWidgetButton : public grUiWidgetButton {
public:
    GTL_RTTI_DECLARE();

    using grUiWidgetButton::grUiWidgetButton;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c16grUiWidgetButton() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual void updateVisualsFromState() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c16grUiWidgetButtonm22updateVisualsFromState_0(grBindingGch);
    }

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c14grUiWidgetTextm14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c14grUiWidgetTextm15get_contentBias_0(grBindingGch));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c14grUiWidgetTextm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c14grUiWidgetTextm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm15get_layoutFlags_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm6update_0(grBindingGch);
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm15get_layoutDirty_0(grBindingGch));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm20updateStyleHierarchy_0(grBindingGch);
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidget::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidget::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetButton.grBinding_c10grUiWidgetm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidget::onBoundsChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c16grUiWidgetButton, GTL_RTTI_INHERITS(grUiWidgetButton), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c16grUiWidgetButton, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtong(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c16grUiWidgetButton*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonx(void *self) {
    return gtlDelete static_cast<grUiWidgetButton*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonn0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c16grUiWidgetButton();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonn0_0() {
    auto grBindingReturnValue = gtlNew grUiWidgetButton();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonn0_1t2_3gtl6Stringv(const gtl::WIDECHAR * grBindingArgRaw_label) {
    auto grBindingArg_label = static_cast<gtl::String>(grBindingArgRaw_label);
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c16grUiWidgetButton(grBindingArg_label);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonn0_1t2_3gtl6String(const gtl::WIDECHAR * grBindingArgRaw_label) {
    auto grBindingArg_label = static_cast<gtl::String>(grBindingArgRaw_label);
    auto grBindingReturnValue = gtlNew grUiWidgetButton(grBindingArg_label);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtone23eventSink_performAction_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventPerformAction&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidgetButton *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_performAction.addHandler(grBindingHandlerWrapper<grUiEventPerformAction>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtone23eventSink_performAction_emit(void * grBindingSelfRaw, grUiEventPerformAction &ev) {
    auto grBindingSelf = static_cast<grUiWidgetButton *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_performAction.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtone23eventSink_performAction_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidgetButton *>(grBindingSelfRaw);
    grBindingSelf->eventSink_performAction.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm11clickButton_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetButton *>(grBindingSelfRaw);
    grBindingSelf->grUiWidgetButton::clickButton();
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm15get_buttonState_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetButton *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetButton::get_buttonState();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm12set_disabled_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_disabled) {
    auto grBindingSelf = static_cast<grUiWidgetButton *>(grBindingSelfRaw);
    auto grBindingArg_disabled = grBindingArgRaw_disabled;
    grBindingSelf->grUiWidgetButton::set_disabled(grBindingArg_disabled);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm12get_disabled_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetButton *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetButton::get_disabled();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm22updateVisualsFromState_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetButton *>(grBindingSelfRaw);
    grBindingSelf->updateVisualsFromState();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm22updateVisualsFromState_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetButton *>(grBindingSelfRaw);
    grBindingSelf->grUiWidgetButton::updateVisualsFromState();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetButton *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetButton *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetButton *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetButton *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetButton *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetButtonm15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetButton *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformr() {
    return &grUiNativeFramePlatform::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiNativeFramePlatform*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c23grUiNativeFramePlatform {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm15set_windowTitle_1t2_3gtl6String)(void * grBindingGchRaw, const gtl::WIDECHAR * grBindingArgRaw_title);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm17set_windowVisible_1t1_4bool)(void * grBindingGchRaw, bool grBindingArgRaw_value);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm18get_windowViewport_0)(grRectangle * grBindingReturnPtr, void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm17set_mouseCaptured_1t1_4bool)(void * grBindingGchRaw, bool grBindingArgRaw_value);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm17outsetFrameBounds_1t1_11grRectangle)(grRectangle * grBindingReturnPtr, void * grBindingGchRaw, grRectangle grBindingArgRaw_bounds);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm13startDragging_1t1_21grUiObjectDragContext)(void * grBindingGchRaw, void * grBindingArgRaw_ctx);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm18emitMouseMoveEvent_2t1_3intt1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm19emitMouseLeaveEvent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm19emitObjectDropEvent_1t1_14grUiDragObject)(void * grBindingGchRaw, void * grBindingArgRaw_ctx);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm6update_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm24updateNativeBorderInsets_1t1_16grUiBorderNative)(void * grBindingGchRaw, void * grBindingArgRaw_ctx);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    int32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm15get_scaleFactor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c23grUiNativeFramePlatformm25usesExternalWindowManager_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformp(const grBindingProxyInfo_grBinding_c23grUiNativeFramePlatform *info) {
    grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform = *info;
}

class grBindingProxyClass_grBinding_c23grUiNativeFramePlatform : public grUiNativeFramePlatform {
public:
    GTL_RTTI_DECLARE();

    using grUiNativeFramePlatform::grUiNativeFramePlatform;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c23grUiNativeFramePlatform() override {
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    gnaWeakPointer<grUiWidget> & grBindingMemberAccessor_m_frame() {
        return this->m_frame;
    }

    virtual void set_windowTitle(const gtl::String & grBindingArg_title) override {
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm15set_windowTitle_1t2_3gtl6String(grBindingGch, grBindingTypeUtils<const gtl::String &>::translateArgFromNativeToManaged(grBindingArg_title));
    }

    virtual void set_windowVisible(bool grBindingArg_value) override {
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm17set_windowVisible_1t1_4bool(grBindingGch, grBindingTypeUtils<bool>::translateArgFromNativeToManaged(grBindingArg_value));
    }

    virtual grRectangle get_windowViewport() override {
        grRectangle grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm18get_windowViewport_0(&grBindingReturnValue, grBindingGch);
        return grBindingReturnValue;
    }

    virtual void set_mouseCaptured(bool grBindingArg_value) override {
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm17set_mouseCaptured_1t1_4bool(grBindingGch, grBindingTypeUtils<bool>::translateArgFromNativeToManaged(grBindingArg_value));
    }

    virtual grRectangle outsetFrameBounds(const grRectangle & grBindingArg_bounds) override {
        grRectangle grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm17outsetFrameBounds_1t1_11grRectangle(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_bounds));
        return grBindingReturnValue;
    }

    virtual void startDragging(gnaPointer<grUiObjectDragContext> grBindingArg_ctx) override {
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm13startDragging_1t1_21grUiObjectDragContext(grBindingGch, grBindingTypeUtils<gnaPointer<grUiObjectDragContext>>::translateArgFromNativeToManagedCls(grBindingArg_ctx));
    }

    virtual void emitMouseMoveEvent(int32_t grBindingArg_x, int32_t grBindingArg_y) override {
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm18emitMouseMoveEvent_2t1_3intt1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_x), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_y));
    }

    virtual void emitMouseLeaveEvent() override {
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm19emitMouseLeaveEvent_0(grBindingGch);
    }

    virtual void emitObjectDropEvent(gnaPointer<grUiDragObject> grBindingArg_ctx) override {
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm19emitObjectDropEvent_1t1_14grUiDragObject(grBindingGch, grBindingTypeUtils<gnaPointer<grUiDragObject>>::translateArgFromNativeToManagedCls(grBindingArg_ctx));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm6update_0(grBindingGch);
    }

    virtual bool updateNativeBorderInsets(gnaWeakPointer<grUiBorderNative> grBindingArg_ctx) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm24updateNativeBorderInsets_1t1_16grUiBorderNative(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiBorderNative>>::translateArgFromNativeToManagedCls(grBindingArg_ctx)));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual int32_t get_scaleFactor() override {
        return grBindingTypeUtils<int32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm15get_scaleFactor_0(grBindingGch));
    }

    virtual bool usesExternalWindowManager() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c23grUiNativeFramePlatform.grBinding_c23grUiNativeFramePlatformm25usesExternalWindowManager_0(grBindingGch));
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c23grUiNativeFramePlatform, GTL_RTTI_INHERITS(grUiNativeFramePlatform), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c23grUiNativeFramePlatform, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c23grUiNativeFramePlatform*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformx(void *self) {
    return gtlDelete static_cast<grUiNativeFramePlatform*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformf7m_frameg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c23grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grBindingMemberAccessor_m_frame();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformf7m_frames(void * grBindingSelfRaw, void * grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c23grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_val);
    grBindingSelf->grBindingMemberAccessor_m_frame() = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformn0_1t1_10grUiWidgetv(void * grBindingArgRaw_frame) {
    auto grBindingArg_frame = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_frame);
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c23grUiNativeFramePlatform(grBindingArg_frame);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm15set_windowTitle_1t2_3gtl6Stringv(void * grBindingSelfRaw, const gtl::WIDECHAR * grBindingArgRaw_title) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingArg_title = static_cast<gtl::String>(grBindingArgRaw_title);
    grBindingSelf->set_windowTitle(grBindingArg_title);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm17set_windowVisible_1t1_4boolv(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->set_windowVisible(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm18get_windowViewport_0v(grRectangle * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_windowViewport();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm17set_mouseCaptured_1t1_4boolv(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->set_mouseCaptured(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm17outsetFrameBounds_1t1_11grRectanglev(grRectangle * grBindingReturnPtr, void * grBindingSelfRaw, grRectangle grBindingArgRaw_bounds) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingArg_bounds = static_cast<grRectangle>(grBindingArgRaw_bounds);
    auto grBindingReturnValue = grBindingSelf->outsetFrameBounds(grBindingArg_bounds);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm9get_frame_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiNativeFramePlatform::get_frame();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm13startDragging_1t1_21grUiObjectDragContextv(void * grBindingSelfRaw, void * grBindingArgRaw_ctx) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingArg_ctx = grBindingExpandWeakPtr<grUiObjectDragContext>(grBindingArgRaw_ctx);
    grBindingSelf->startDragging(grBindingArg_ctx);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm18emitMouseMoveEvent_2t1_3intt1_3intv(void * grBindingSelfRaw, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    grBindingSelf->emitMouseMoveEvent(grBindingArg_x, grBindingArg_y);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm19emitMouseLeaveEvent_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    grBindingSelf->emitMouseLeaveEvent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm19emitObjectDropEvent_1t1_14grUiDragObjectv(void * grBindingSelfRaw, void * grBindingArgRaw_ctx) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingArg_ctx = grBindingExpandWeakPtr<grUiDragObject>(grBindingArgRaw_ctx);
    grBindingSelf->emitObjectDropEvent(grBindingArg_ctx);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm6update_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    grBindingSelf->update();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm6update_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    grBindingSelf->grUiNativeFramePlatform::update();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm24updateNativeBorderInsets_1t1_16grUiBorderNativev(void * grBindingSelfRaw, void * grBindingArgRaw_ctx) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingArg_ctx = grBindingExpandWeakPtr<grUiBorderNative>(grBindingArgRaw_ctx);
    auto grBindingReturnValue = grBindingSelf->updateNativeBorderInsets(grBindingArg_ctx);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm24updateNativeBorderInsets_1t1_16grUiBorderNative(void * grBindingSelfRaw, void * grBindingArgRaw_ctx) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingArg_ctx = grBindingExpandWeakPtr<grUiBorderNative>(grBindingArgRaw_ctx);
    auto grBindingReturnValue = grBindingSelf->grUiNativeFramePlatform::updateNativeBorderInsets(grBindingArg_ctx);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm19nativeWidgetPresent_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    grBindingSelf->nativeWidgetPresent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm19nativeWidgetPresent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    grBindingSelf->grUiNativeFramePlatform::nativeWidgetPresent();
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm15get_scaleFactor_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_scaleFactor();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm15get_scaleFactor_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiNativeFramePlatform::get_scaleFactor();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm25usesExternalWindowManager_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->usesExternalWindowManager();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c23grUiNativeFramePlatformm25usesExternalWindowManager_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativeFramePlatform *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiNativeFramePlatform::usesExternalWindowManager();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImager() {
    return &grUiWidgetImage::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImaged(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiWidgetImage*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c15grUiWidgetImage {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiWidgetImagem14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiWidgetImagem4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_contentBias_0)(void * grBindingGchRaw);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutDirty_0)(void * grBindingGchRaw);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15onBoundsChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagep(const grBindingProxyInfo_grBinding_c15grUiWidgetImage *info) {
    grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage = *info;
}

class grBindingProxyClass_grBinding_c15grUiWidgetImage : public grUiWidgetImage {
public:
    GTL_RTTI_DECLARE();

    using grUiWidgetImage::grUiWidgetImage;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c15grUiWidgetImage() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c15grUiWidgetImagem14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c15grUiWidgetImagem4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm15get_contentBias_0(grBindingGch));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm15get_layoutFlags_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm6update_0(grBindingGch);
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm15get_layoutDirty_0(grBindingGch));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm20updateStyleHierarchy_0(grBindingGch);
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidget::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidget::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetImage.grBinding_c10grUiWidgetm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidget::onBoundsChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c15grUiWidgetImage, GTL_RTTI_INHERITS(grUiWidgetImage), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c15grUiWidgetImage, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImageg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c15grUiWidgetImage*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagex(void *self) {
    return gtlDelete static_cast<grUiWidgetImage*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagen0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c15grUiWidgetImage();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagen0_0() {
    auto grBindingReturnValue = gtlNew grUiWidgetImage();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagen0_1t1_10grUiSpritev(void * grBindingArgRaw_sprite) {
    auto grBindingArg_sprite = *static_cast<grUiSprite *>(grBindingArgRaw_sprite);
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c15grUiWidgetImage(grBindingArg_sprite);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagen0_1t1_10grUiSprite(void * grBindingArgRaw_sprite) {
    auto grBindingArg_sprite = *static_cast<grUiSprite *>(grBindingArgRaw_sprite);
    auto grBindingReturnValue = gtlNew grUiWidgetImage(grBindingArg_sprite);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem14initialMeasure_1t1_3intv(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem14initialMeasure_1t1_3int(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->grUiWidgetImage::initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem4draw_1t1_12grUiRendererv(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->draw(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem4draw_1t1_12grUiRenderer(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->grUiWidgetImage::draw(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem9get_image_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetImage::get_image();
    return gtlNew grUiSprite(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem9set_image_1t1_10grUiSprite(void * grBindingSelfRaw, void * grBindingArgRaw_image) {
    auto grBindingSelf = static_cast<grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingArg_image = *static_cast<grUiSprite *>(grBindingArgRaw_image);
    grBindingSelf->grUiWidgetImage::set_image(grBindingArg_image);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem17get_dpiScaleImage_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetImage::get_dpiScaleImage();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem17set_dpiScaleImage_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grUiWidgetImage::set_dpiScaleImage(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT float GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem14get_imageScale_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetImage::get_imageScale();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem14set_imageScale_1t1_5float(void * grBindingSelfRaw, float grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grUiWidgetImage::set_imageScale(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetImage *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetImage *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetImage *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetImagem15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetImage *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutManagerr() {
    return &grUiLayoutManager::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutManagerd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiLayoutManager*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c17grUiLayoutManager {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c17grUiLayoutManagerm14initialMeasure_2t1_16grUiWidgetLayoutt1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, void * grBindingArgRaw_parent, int32_t grBindingArgRaw_biasedSize);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c17grUiLayoutManagerm6layout_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c17grUiLayoutManagerm15get_contentBias_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c17grUiLayoutManagerm9get_flags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c17grUiLayoutManagerm9drawDebug_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c17grUiLayoutManager;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutManagerp(const grBindingProxyInfo_grBinding_c17grUiLayoutManager *info) {
    grBindingProxyInfoInstance_grBinding_c17grUiLayoutManager = *info;
}

class grBindingProxyClass_grBinding_c17grUiLayoutManager : public grUiLayoutManager {
public:
    GTL_RTTI_DECLARE();

    using grUiLayoutManager::grUiLayoutManager;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c17grUiLayoutManager() override {
        grBindingProxyInfoInstance_grBinding_c17grUiLayoutManager.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(grUiWidgetLayout * grBindingArg_parent, int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c17grUiLayoutManager.grBinding_c17grUiLayoutManagerm14initialMeasure_2t1_16grUiWidgetLayoutt1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidgetLayout *>::translateArgFromNativeToManagedCls(grBindingArg_parent), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    grDimension grBindingMemberAccessor_initialMeasure(grUiWidgetLayout * grBindingArg_parent, int32_t grBindingArg_biasedSize) {
        return grUiLayoutManager::initialMeasure(grBindingArg_parent, grBindingArg_biasedSize);
    }

    virtual void layout(grUiWidgetLayout * grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c17grUiLayoutManager.grBinding_c17grUiLayoutManagerm6layout_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<grUiWidgetLayout *>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    void grBindingMemberAccessor_layout(grUiWidgetLayout * grBindingArg_parent) {
        grUiLayoutManager::layout(grBindingArg_parent);
    }

    virtual grUiEnumContentBias get_contentBias(grUiWidgetLayout * grBindingArg_parent) override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiLayoutManager.grBinding_c17grUiLayoutManagerm15get_contentBias_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<grUiWidgetLayout *>::translateArgFromNativeToManagedCls(grBindingArg_parent)));
    }

    grUiEnumContentBias grBindingMemberAccessor_get_contentBias(grUiWidgetLayout * grBindingArg_parent) {
        return grUiLayoutManager::get_contentBias(grBindingArg_parent);
    }

    virtual uint32_t get_flags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiLayoutManager.grBinding_c17grUiLayoutManagerm9get_flags_0(grBindingGch));
    }

    uint32_t grBindingMemberAccessor_get_flags() {
        return grUiLayoutManager::get_flags();
    }

    virtual void drawDebug() override {
        grBindingProxyInfoInstance_grBinding_c17grUiLayoutManager.grBinding_c17grUiLayoutManagerm9drawDebug_0(grBindingGch);
    }

    void grBindingMemberAccessor_drawDebug() {
        grUiLayoutManager::drawDebug();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c17grUiLayoutManager, GTL_RTTI_INHERITS(grUiLayoutManager), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c17grUiLayoutManager, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutManagerg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c17grUiLayoutManager*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutManagerx(void *self) {
    return gtlDelete static_cast<grUiLayoutManager*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutManagern0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c17grUiLayoutManager();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutManagerm15get_contentBias_1t1_16grUiWidgetLayout(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiLayoutManager *>(grBindingSelfRaw);
    auto grBindingArg_parent = static_cast<grUiWidgetLayout *>(grBindingArgRaw_parent);
    auto grBindingReturnValue = grBindingSelf->grBindingMemberAccessor_get_contentBias(grBindingArg_parent);
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutManagerm9get_flags_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiLayoutManager *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grBindingMemberAccessor_get_flags();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutManagerm9drawDebug_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiLayoutManager *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_drawDebug();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearr() {
    return &grUiLayoutLinear::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLineard(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiLayoutLinear*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c16grUiLayoutLinear {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiLayoutLinearm14initialMeasure_2t1_16grUiWidgetLayoutt1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, void * grBindingArgRaw_parent, int32_t grBindingArgRaw_biasedSize);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiLayoutLinearm6layout_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiLayoutLinearm15get_contentBias_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiLayoutLinearm9get_flags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c17grUiLayoutManagerm9drawDebug_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c16grUiLayoutLinear;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearp(const grBindingProxyInfo_grBinding_c16grUiLayoutLinear *info) {
    grBindingProxyInfoInstance_grBinding_c16grUiLayoutLinear = *info;
}

class grBindingProxyClass_grBinding_c16grUiLayoutLinear : public grUiLayoutLinear {
public:
    GTL_RTTI_DECLARE();

    using grUiLayoutLinear::grUiLayoutLinear;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c16grUiLayoutLinear() override {
        grBindingProxyInfoInstance_grBinding_c16grUiLayoutLinear.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(grUiWidgetLayout * grBindingArg_parent, int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c16grUiLayoutLinear.grBinding_c16grUiLayoutLinearm14initialMeasure_2t1_16grUiWidgetLayoutt1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidgetLayout *>::translateArgFromNativeToManagedCls(grBindingArg_parent), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    grDimension grBindingMemberAccessor_initialMeasure(grUiWidgetLayout * grBindingArg_parent, int32_t grBindingArg_biasedSize) {
        return grUiLayoutLinear::initialMeasure(grBindingArg_parent, grBindingArg_biasedSize);
    }

    virtual void layout(grUiWidgetLayout * grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c16grUiLayoutLinear.grBinding_c16grUiLayoutLinearm6layout_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<grUiWidgetLayout *>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    void grBindingMemberAccessor_layout(grUiWidgetLayout * grBindingArg_parent) {
        grUiLayoutLinear::layout(grBindingArg_parent);
    }

    virtual grUiEnumContentBias get_contentBias(grUiWidgetLayout * grBindingArg_parent) override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiLayoutLinear.grBinding_c16grUiLayoutLinearm15get_contentBias_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<grUiWidgetLayout *>::translateArgFromNativeToManagedCls(grBindingArg_parent)));
    }

    grUiEnumContentBias grBindingMemberAccessor_get_contentBias(grUiWidgetLayout * grBindingArg_parent) {
        return grUiLayoutLinear::get_contentBias(grBindingArg_parent);
    }

    virtual uint32_t get_flags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiLayoutLinear.grBinding_c16grUiLayoutLinearm9get_flags_0(grBindingGch));
    }

    uint32_t grBindingMemberAccessor_get_flags() {
        return grUiLayoutLinear::get_flags();
    }

    virtual void drawDebug() override {
        grBindingProxyInfoInstance_grBinding_c16grUiLayoutLinear.grBinding_c17grUiLayoutManagerm9drawDebug_0(grBindingGch);
    }

    void grBindingMemberAccessor_drawDebug() {
        grUiLayoutManager::drawDebug();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c16grUiLayoutLinear, GTL_RTTI_INHERITS(grUiLayoutLinear), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c16grUiLayoutLinear, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c16grUiLayoutLinear*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearx(void *self) {
    return gtlDelete static_cast<grUiLayoutLinear*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecr() {
    return &grUiLayoutLinear::ElementSpec::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiLayoutLinear::ElementSpec*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecx(void *self) {
    return gtlDelete static_cast<grUiLayoutLinear::ElementSpec*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecf8sizeModeg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutLinear::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutLinear::ElementSpec::sizeMode;
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecf8sizeModes(void * grBindingSelfRaw, int grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutLinear::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiLayoutLinear::SizeMode>(grBindingArgRaw_val);
    grBindingSelf->grUiLayoutLinear::ElementSpec::sizeMode = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecf13sizeModeParamg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutLinear::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutLinear::ElementSpec::sizeModeParam;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecf13sizeModeParams(void * grBindingSelfRaw, int32_t grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutLinear::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiLayoutLinear::ElementSpec::sizeModeParam = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecf16minSecondarySizeg(grUiUnitSizeI * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutLinear::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutLinear::ElementSpec::minSecondarySize;
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecf16minSecondarySizes(void * grBindingSelfRaw, grUiUnitSizeI grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutLinear::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiUnitSizeI>(grBindingArgRaw_val);
    grBindingSelf->grUiLayoutLinear::ElementSpec::minSecondarySize = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecf18secondaryAlignmentg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutLinear::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutLinear::ElementSpec::secondaryAlignment;
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecf18secondaryAlignments(void * grBindingSelfRaw, int grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutLinear::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiLayoutLinear::SecondaryAlignment>(grBindingArgRaw_val);
    grBindingSelf->grUiLayoutLinear::ElementSpec::secondaryAlignment = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecn0_0() {
    auto grBindingReturnValue = gtlNew grUiLayoutLinear::ElementSpec();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecm9createMin_2t1_3intt2_16grUiLayoutLinear18SecondaryAlignment(int32_t grBindingArgRaw_size, int grBindingArgRaw_secondaryAlignment) {
    auto grBindingArg_size = grBindingArgRaw_size;
    auto grBindingArg_secondaryAlignment = static_cast<grUiLayoutLinear::SecondaryAlignment>(grBindingArgRaw_secondaryAlignment);
    auto grBindingReturnValue = grUiLayoutLinear::ElementSpec::createMin(grBindingArg_size, grBindingArg_secondaryAlignment);
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecm11createFixed_2t1_3intt2_16grUiLayoutLinear18SecondaryAlignment(int32_t grBindingArgRaw_size, int grBindingArgRaw_secondaryAlignment) {
    auto grBindingArg_size = grBindingArgRaw_size;
    auto grBindingArg_secondaryAlignment = static_cast<grUiLayoutLinear::SecondaryAlignment>(grBindingArgRaw_secondaryAlignment);
    auto grBindingReturnValue = grUiLayoutLinear::ElementSpec::createFixed(grBindingArg_size, grBindingArg_secondaryAlignment);
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecm10createGrow_2t1_3intt2_16grUiLayoutLinear18SecondaryAlignment(int32_t grBindingArgRaw_weight, int grBindingArgRaw_secondaryAlignment) {
    auto grBindingArg_weight = grBindingArgRaw_weight;
    auto grBindingArg_secondaryAlignment = static_cast<grUiLayoutLinear::SecondaryAlignment>(grBindingArgRaw_secondaryAlignment);
    auto grBindingReturnValue = grUiLayoutLinear::ElementSpec::createGrow(grBindingArg_weight, grBindingArg_secondaryAlignment);
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearc11ElementSpecm12createSquare_1t2_16grUiLayoutLinear18SecondaryAlignment(int grBindingArgRaw_secondaryAlignment) {
    auto grBindingArg_secondaryAlignment = static_cast<grUiLayoutLinear::SecondaryAlignment>(grBindingArgRaw_secondaryAlignment);
    auto grBindingReturnValue = grUiLayoutLinear::ElementSpec::createSquare(grBindingArg_secondaryAlignment);
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearn0_1t2_16grUiLayoutLinear4Axisv(int grBindingArgRaw_primaryAxis) {
    auto grBindingArg_primaryAxis = static_cast<grUiLayoutLinear::Axis>(grBindingArgRaw_primaryAxis);
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c16grUiLayoutLinear(grBindingArg_primaryAxis);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearn0_1t2_16grUiLayoutLinear4Axis(int grBindingArgRaw_primaryAxis) {
    auto grBindingArg_primaryAxis = static_cast<grUiLayoutLinear::Axis>(grBindingArgRaw_primaryAxis);
    auto grBindingReturnValue = gtlNew grUiLayoutLinear(grBindingArg_primaryAxis);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearn0_2t2_16grUiLayoutLinear4Axist1_13grUiUnitSizeIv(int grBindingArgRaw_primaryAxis, grUiUnitSizeI grBindingArgRaw_gap) {
    auto grBindingArg_primaryAxis = static_cast<grUiLayoutLinear::Axis>(grBindingArgRaw_primaryAxis);
    auto grBindingArg_gap = static_cast<grUiUnitSizeI>(grBindingArgRaw_gap);
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c16grUiLayoutLinear(grBindingArg_primaryAxis, grBindingArg_gap);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearn0_2t2_16grUiLayoutLinear4Axist1_13grUiUnitSizeI(int grBindingArgRaw_primaryAxis, grUiUnitSizeI grBindingArgRaw_gap) {
    auto grBindingArg_primaryAxis = static_cast<grUiLayoutLinear::Axis>(grBindingArgRaw_primaryAxis);
    auto grBindingArg_gap = static_cast<grUiUnitSizeI>(grBindingArgRaw_gap);
    auto grBindingReturnValue = gtlNew grUiLayoutLinear(grBindingArg_primaryAxis, grBindingArg_gap);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearm14initialMeasure_2t1_16grUiWidgetLayoutt1_3int(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, void * grBindingArgRaw_parent, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiLayoutLinear *>(grBindingSelfRaw);
    auto grBindingArg_parent = static_cast<grUiWidgetLayout *>(grBindingArgRaw_parent);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->grBindingMemberAccessor_initialMeasure(grBindingArg_parent, grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearm6layout_1t1_16grUiWidgetLayout(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiLayoutLinear *>(grBindingSelfRaw);
    auto grBindingArg_parent = static_cast<grUiWidgetLayout *>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_layout(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearm15get_contentBias_1t1_16grUiWidgetLayout(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiLayoutLinear *>(grBindingSelfRaw);
    auto grBindingArg_parent = static_cast<grUiWidgetLayout *>(grBindingArgRaw_parent);
    auto grBindingReturnValue = grBindingSelf->grBindingMemberAccessor_get_contentBias(grBindingArg_parent);
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearm9get_flags_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiLayoutLinear *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grBindingMemberAccessor_get_flags();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiLayoutLinearm9drawDebug_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiLayoutLinear *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_drawDebug();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiTextRendererx(void *self) {
    return gtlDelete static_cast<grUiTextRenderer*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiTextRendererm19set_enableDebugDraw_1t1_4bool(bool grBindingArgRaw_debugDraw) {
    auto grBindingArg_debugDraw = grBindingArgRaw_debugDraw;
    grUiTextRenderer::set_enableDebugDraw(grBindingArg_debugDraw);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutr() {
    return &grUiWidgetLayout::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiWidgetLayout*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c16grUiWidgetLayout {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_contentBias_0)(void * grBindingGchRaw);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutp(const grBindingProxyInfo_grBinding_c16grUiWidgetLayout *info) {
    grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout = *info;
}

class grBindingProxyClass_grBinding_c16grUiWidgetLayout : public grUiWidgetLayout {
public:
    GTL_RTTI_DECLARE();

    using grUiWidgetLayout::grUiWidgetLayout;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c16grUiWidgetLayout() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm15get_contentBias_0(grBindingGch));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm6update_0(grBindingGch);
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0(grBindingGch));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0(grBindingGch);
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidgetLayout::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidgetLayout::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidgetLayout::onBoundsChanged();
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c16grUiWidgetLayout.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c16grUiWidgetLayout, GTL_RTTI_INHERITS(grUiWidgetLayout), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c16grUiWidgetLayout, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c16grUiWidgetLayout*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutx(void *self) {
    return gtlDelete static_cast<grUiWidgetLayout*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutn0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c16grUiWidgetLayout();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutn0_0() {
    auto grBindingReturnValue = gtlNew grUiWidgetLayout();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutn0_1t1_17grUiLayoutManagerv(void * grBindingArgRaw_layoutManager) {
    auto grBindingArg_layoutManager = grBindingExpandWeakPtr<grUiLayoutManager>(grBindingArgRaw_layoutManager);
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c16grUiWidgetLayout(grBindingArg_layoutManager);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutn0_1t1_17grUiLayoutManager(void * grBindingArgRaw_layoutManager) {
    auto grBindingArg_layoutManager = grBindingExpandWeakPtr<grUiLayoutManager>(grBindingArgRaw_layoutManager);
    auto grBindingReturnValue = gtlNew grUiWidgetLayout(grBindingArg_layoutManager);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3intv(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm15get_contentBias_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_contentBias();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm15get_contentBias_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::get_contentBias();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_layoutFlags();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::get_layoutFlags();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm11insertAfter_3t1_10grUiWidgett1_10grUiWidgett1_8uint32_t(void * grBindingSelfRaw, void * grBindingArgRaw_child, void * grBindingArgRaw_after, uint32_t grBindingArgRaw_pflags) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_child = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_child);
    auto grBindingArg_after = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_after);
    auto grBindingArg_pflags = grBindingArgRaw_pflags;
    grBindingSelf->grUiWidgetLayout::insertAfter(grBindingArg_child, grBindingArg_after, grBindingArg_pflags);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm12insertBefore_3t1_10grUiWidgett1_10grUiWidgett1_8uint32_t(void * grBindingSelfRaw, void * grBindingArgRaw_child, void * grBindingArgRaw_before, uint32_t grBindingArgRaw_pflags) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_child = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_child);
    auto grBindingArg_before = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_before);
    auto grBindingArg_pflags = grBindingArgRaw_pflags;
    grBindingSelf->grUiWidgetLayout::insertBefore(grBindingArg_child, grBindingArg_before, grBindingArg_pflags);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm3add_2t1_10grUiWidgett1_8uint32_t(void * grBindingSelfRaw, void * grBindingArgRaw_child, uint32_t grBindingArgRaw_pflags) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_child = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_child);
    auto grBindingArg_pflags = grBindingArgRaw_pflags;
    grBindingSelf->grUiWidgetLayout::add(grBindingArg_child, grBindingArg_pflags);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm3add_3t1_10grUiWidgett1_11gtlRcObjectt1_8uint32_t(void * grBindingSelfRaw, void * grBindingArgRaw_child, void * grBindingArgRaw_layoutData, uint32_t grBindingArgRaw_pflags) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_child = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_child);
    auto grBindingArg_layoutData = grBindingExpandWeakPtr<gtlRcObject>(grBindingArgRaw_layoutData);
    auto grBindingArg_pflags = grBindingArgRaw_pflags;
    grBindingSelf->grUiWidgetLayout::add(grBindingArg_child, grBindingArg_layoutData, grBindingArg_pflags);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm6remove_2t1_10grUiWidgett1_8uint32_t(void * grBindingSelfRaw, void * grBindingArgRaw_child, uint32_t grBindingArgRaw_pflags) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_child = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_child);
    auto grBindingArg_pflags = grBindingArgRaw_pflags;
    grBindingSelf->grUiWidgetLayout::remove(grBindingArg_child, grBindingArg_pflags);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm9removeAll_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    grBindingSelf->grUiWidgetLayout::removeAll();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm6update_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    grBindingSelf->update();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm6update_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    grBindingSelf->grUiWidgetLayout::update();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm4tick_1t1_5floatv(void * grBindingSelfRaw, float grBindingArgRaw_deltaTime) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_deltaTime = grBindingArgRaw_deltaTime;
    grBindingSelf->tick(grBindingArg_deltaTime);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm4tick_1t1_5float(void * grBindingSelfRaw, float grBindingArgRaw_deltaTime) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_deltaTime = grBindingArgRaw_deltaTime;
    grBindingSelf->grUiWidgetLayout::tick(grBindingArg_deltaTime);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectanglev(void * grBindingSelfRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    auto grBindingArg_clipRect = static_cast<grRectangle>(grBindingArgRaw_clipRect);
    grBindingSelf->drawClipped(grBindingArg_render, grBindingArg_clipRect);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle(void * grBindingSelfRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    auto grBindingArg_clipRect = static_cast<grRectangle>(grBindingArgRaw_clipRect);
    grBindingSelf->grUiWidgetLayout::drawClipped(grBindingArg_render, grBindingArg_clipRect);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRendererv(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->draw(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->grUiWidgetLayout::draw(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectanglev(void * grBindingSelfRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    auto grBindingArg_clipRect = static_cast<grRectangle>(grBindingArgRaw_clipRect);
    grBindingSelf->preDraw(grBindingArg_render, grBindingArg_clipRect);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle(void * grBindingSelfRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    auto grBindingArg_clipRect = static_cast<grRectangle>(grBindingArgRaw_clipRect);
    grBindingSelf->grUiWidgetLayout::preDraw(grBindingArg_render, grBindingArg_clipRect);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRendererv(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->drawDebug(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->grUiWidgetLayout::drawDebug(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm11needsLayout_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::needsLayout();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm15markNeedsLayout_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    grBindingSelf->grUiWidgetLayout::markNeedsLayout();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_layoutDirty();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::get_layoutDirty();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm24releaseFocusFromChildren_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_suppressEvent) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_suppressEvent = grBindingArgRaw_suppressEvent;
    grBindingSelf->grUiWidgetLayout::releaseFocusFromChildren(grBindingArg_suppressEvent);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAStringv(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_id) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_id = static_cast<gtl::PooledAString>(grBindingArgRaw_id);
    auto grBindingReturnValue = grBindingSelf->findByID(grBindingArg_id);
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_id) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_id = static_cast<gtl::PooledAString>(grBindingArgRaw_id);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::findByID(grBindingArg_id);
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    grBindingSelf->updateStyleHierarchy();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    grBindingSelf->grUiWidgetLayout::updateStyleHierarchy();
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm10firstChild_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::firstChild();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm11numChildren_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::numChildren();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayoutv(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_parent);
    grBindingSelf->updateNativeDevice(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_parent);
    grBindingSelf->grUiWidgetLayout::updateNativeDevice(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm22set_transparentHitTest_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grUiWidgetLayout::set_transparentHitTest(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm21is_transparentHitTest_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::is_transparentHitTest();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const gtl::ASCIICHAR * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm16get_actualCursor_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_actualCursor();
    return grBindingAllocateString(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const gtl::ASCIICHAR * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm16get_actualCursor_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::get_actualCursor();
    return grBindingAllocateString(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPointv(void * grBindingSelfRaw, grPoint grBindingArgRaw_point) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_point = static_cast<grPoint>(grBindingArgRaw_point);
    auto grBindingReturnValue = grBindingSelf->hitTest(grBindingArg_point);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint(void * grBindingSelfRaw, grPoint grBindingArgRaw_point) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_point = static_cast<grPoint>(grBindingArgRaw_point);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::hitTest(grBindingArg_point);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutf6layoutg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetLayout::layout;
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutf6layouts(void * grBindingSelfRaw, void * grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingExpandWeakPtr<grUiLayoutManager>(grBindingArgRaw_val);
    grBindingSelf->grUiWidgetLayout::layout = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm11forceLayout_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_ignoreCheck) {
    auto grBindingSelf = static_cast<grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_ignoreCheck = grBindingArgRaw_ignoreCheck;
    grBindingSelf->grUiWidgetLayout::forceLayout(grBindingArg_ignoreCheck);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetLayout *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetLayout *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetLayout *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiWidgetLayoutm19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c16grUiWidgetLayout *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiSpannedTextx(void *self) {
    return gtlDelete static_cast<grUiSpannedText*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiSpannedTextm5clear_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiSpannedText *>(grBindingSelfRaw);
    grBindingSelf->grUiSpannedText::clear();
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c15grUiSpannedTextm4size_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiSpannedText *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiSpannedText::size();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c15grUiSpannedTextm5empty_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiSpannedText *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiSpannedText::empty();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiSpannedTextm11addTextSpan_1t2_3gtl6String(void * grBindingSelfRaw, const gtl::WIDECHAR * grBindingArgRaw_str) {
    auto grBindingSelf = static_cast<grUiSpannedText *>(grBindingSelfRaw);
    auto grBindingArg_str = static_cast<gtl::String>(grBindingArgRaw_str);
    grBindingSelf->grUiSpannedText::addTextSpan(grBindingArg_str);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiSpannedTextm11addTextSpan_2t2_3gtl6Stringt1_7grColor(void * grBindingSelfRaw, const gtl::WIDECHAR * grBindingArgRaw_str, grColor grBindingArgRaw_color) {
    auto grBindingSelf = static_cast<grUiSpannedText *>(grBindingSelfRaw);
    auto grBindingArg_str = static_cast<gtl::String>(grBindingArgRaw_str);
    auto grBindingArg_color = static_cast<grColor>(grBindingArgRaw_color);
    grBindingSelf->grUiSpannedText::addTextSpan(grBindingArg_str, grBindingArg_color);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiSpannedTextm12addImageSpan_1t2_3gtl12PooledString(void * grBindingSelfRaw, const gtl::WIDECHAR * grBindingArgRaw_path) {
    auto grBindingSelf = static_cast<grUiSpannedText *>(grBindingSelfRaw);
    auto grBindingArg_path = static_cast<gtl::PooledString>(grBindingArgRaw_path);
    grBindingSelf->grUiSpannedText::addImageSpan(grBindingArg_path);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetr() {
    return &grUiWidget::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiWidget*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c10grUiWidget {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_contentBias_0)(void * grBindingGchRaw);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutDirty_0)(void * grBindingGchRaw);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15onBoundsChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c10grUiWidget;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetp(const grBindingProxyInfo_grBinding_c10grUiWidget *info) {
    grBindingProxyInfoInstance_grBinding_c10grUiWidget = *info;
}

class grBindingProxyClass_grBinding_c10grUiWidget : public grUiWidget {
public:
    GTL_RTTI_DECLARE();

    using grUiWidget::grUiWidget;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c10grUiWidget() override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm15get_contentBias_0(grBindingGch));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm15get_layoutFlags_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm6update_0(grBindingGch);
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm15get_layoutDirty_0(grBindingGch));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm20updateStyleHierarchy_0(grBindingGch);
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidget::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidget::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c10grUiWidget.grBinding_c10grUiWidgetm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidget::onBoundsChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c10grUiWidget, GTL_RTTI_INHERITS(grUiWidget), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c10grUiWidget, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c10grUiWidget*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetx(void *self) {
    return gtlDelete static_cast<grUiWidget*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetn0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c10grUiWidget();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm14initialMeasure_1t1_3intv(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15get_contentBias_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_contentBias();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15get_contentBias_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_contentBias();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15get_layoutFlags_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_layoutFlags();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15get_layoutFlags_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_layoutFlags();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm7measure_1t1_3int(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->grUiWidget::measure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm6update_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->update();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm6update_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->grUiWidget::update();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm4tick_1t1_5floatv(void * grBindingSelfRaw, float grBindingArgRaw_deltaTime) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_deltaTime = grBindingArgRaw_deltaTime;
    grBindingSelf->tick(grBindingArg_deltaTime);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm4tick_1t1_5float(void * grBindingSelfRaw, float grBindingArgRaw_deltaTime) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_deltaTime = grBindingArgRaw_deltaTime;
    grBindingSelf->grUiWidget::tick(grBindingArg_deltaTime);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm16findNativeWindow_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->findNativeWindow();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm16findNativeWindow_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::findNativeWindow();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18get_windowRenderer_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_windowRenderer();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectanglev(void * grBindingSelfRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    auto grBindingArg_clipRect = static_cast<grRectangle>(grBindingArgRaw_clipRect);
    grBindingSelf->preDraw(grBindingArg_render, grBindingArg_clipRect);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle(void * grBindingSelfRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    auto grBindingArg_clipRect = static_cast<grRectangle>(grBindingArgRaw_clipRect);
    grBindingSelf->grUiWidget::preDraw(grBindingArg_render, grBindingArg_clipRect);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectanglev(void * grBindingSelfRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    auto grBindingArg_clipRect = static_cast<grRectangle>(grBindingArgRaw_clipRect);
    grBindingSelf->drawClipped(grBindingArg_render, grBindingArg_clipRect);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle(void * grBindingSelfRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    auto grBindingArg_clipRect = static_cast<grRectangle>(grBindingArgRaw_clipRect);
    grBindingSelf->grUiWidget::drawClipped(grBindingArg_render, grBindingArg_clipRect);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm4draw_1t1_12grUiRendererv(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->draw(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm4draw_1t1_12grUiRenderer(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->grUiWidget::draw(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm16nativeWidgetDraw_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->nativeWidgetDraw();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm16nativeWidgetDraw_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->grUiWidget::nativeWidgetDraw();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5floatv(void * grBindingSelfRaw, float grBindingArgRaw_deltaTime) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_deltaTime = grBindingArgRaw_deltaTime;
    grBindingSelf->nativeWidgetPreDraw(grBindingArg_deltaTime);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(void * grBindingSelfRaw, float grBindingArgRaw_deltaTime) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_deltaTime = grBindingArgRaw_deltaTime;
    grBindingSelf->grUiWidget::nativeWidgetPreDraw(grBindingArg_deltaTime);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm19nativeWidgetPresent_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->nativeWidgetPresent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm19nativeWidgetPresent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->grUiWidget::nativeWidgetPresent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRendererv(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->drawDebug(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->grUiWidget::drawDebug(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm24get_nativeViewportWidget_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_nativeViewportWidget();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_nativeViewportWidget();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->usesNativeChildEventBehavior();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::usesNativeChildEventBehavior();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10get_insets_1t2_10grUiWidget13EnumInsetType(grInsets * grBindingReturnPtr, void * grBindingSelfRaw, int grBindingArgRaw_type) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_type = static_cast<grUiWidget::EnumInsetType>(grBindingArgRaw_type);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_insets(grBindingArg_type);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetTypev(grInsets * grBindingReturnPtr, void * grBindingSelfRaw, int grBindingArgRaw_type) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_type = static_cast<grUiWidget::EnumInsetType>(grBindingArgRaw_type);
    auto grBindingReturnValue = grBindingSelf->get_extendedInsets(grBindingArg_type);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(grInsets * grBindingReturnPtr, void * grBindingSelfRaw, int grBindingArgRaw_type) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_type = static_cast<grUiWidget::EnumInsetType>(grBindingArgRaw_type);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_extendedInsets(grBindingArg_type);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm14get_baseInsets_0(grInsets * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_baseInsets();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10get_parent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_parent();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10set_parent_2t1_16grUiWidgetLayoutt1_8uint32_t(void * grBindingSelfRaw, void * grBindingArgRaw_val, uint32_t grBindingArgRaw_pflag) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_val);
    auto grBindingArg_pflag = grBindingArgRaw_pflag;
    grBindingSelf->grUiWidget::set_parent(grBindingArg_val, grBindingArg_pflag);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm12isRootWidget_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::isRootWidget();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayoutv(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_parent);
    grBindingSelf->handleParentChanged(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_parent);
    grBindingSelf->grUiWidget::handleParentChanged(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayoutv(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_parent);
    grBindingSelf->updateNativeDevice(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_parent);
    grBindingSelf->grUiWidget::updateNativeDevice(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15get_layoutDirty_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_layoutDirty();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15get_layoutDirty_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_layoutDirty();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15set_layoutDirty_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiWidget::set_layoutDirty(grBindingArg_val);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm12get_position_0(grPoint * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_position();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm8get_size_0(grDimension * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_size();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm14get_layoutData_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_layoutData();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm14set_layoutData_1t1_11gtlRcObject(void * grBindingSelfRaw, void * grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingExpandWeakPtr<gtlRcObject>(grBindingArgRaw_val);
    grBindingSelf->grUiWidget::set_layoutData(grBindingArg_val);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10get_border_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_border();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10set_border_1t1_14grUiBorderBase(void * grBindingSelfRaw, void * grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingExpandWeakPtr<grUiBorderBase>(grBindingArgRaw_val);
    grBindingSelf->grUiWidget::set_border(grBindingArg_val);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm11get_padding_0(grUiUnitInsets * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_padding();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm11set_padding_1t1_14grUiUnitInsets(void * grBindingSelfRaw, grUiUnitInsets grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiUnitInsets>(grBindingArgRaw_val);
    grBindingSelf->grUiWidget::set_padding(grBindingArg_val);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15get_minimumSize_0(grUiUnitDimension * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_minimumSize();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15set_minimumSize_1t1_17grUiUnitDimension(void * grBindingSelfRaw, grUiUnitDimension grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiUnitDimension>(grBindingArgRaw_val);
    grBindingSelf->grUiWidget::set_minimumSize(grBindingArg_val);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10get_margin_0(grUiUnitInsets * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_margin();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10set_margin_1t1_14grUiUnitInsets(void * grBindingSelfRaw, grUiUnitInsets grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiUnitInsets>(grBindingArgRaw_val);
    grBindingSelf->grUiWidget::set_margin(grBindingArg_val);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10get_bounds_0(grRectangle * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_bounds();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10set_bounds_1t1_11grRectangle(void * grBindingSelfRaw, grRectangle grBindingArgRaw_bounds) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_bounds = static_cast<grRectangle>(grBindingArgRaw_bounds);
    grBindingSelf->grUiWidget::set_bounds(grBindingArg_bounds);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm8set_size_1t1_11grDimension(void * grBindingSelfRaw, grDimension grBindingArgRaw_size) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_size = static_cast<grDimension>(grBindingArgRaw_size);
    grBindingSelf->grUiWidget::set_size(grBindingArg_size);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm12set_position_1t1_7grPoint(void * grBindingSelfRaw, grPoint grBindingArgRaw_pos) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_pos = static_cast<grPoint>(grBindingArgRaw_pos);
    grBindingSelf->grUiWidget::set_position(grBindingArg_pos);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm14get_visibility_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_visibility();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm14set_visibility_1t2_10grUiWidget14EnumVisibility(void * grBindingSelfRaw, int grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiWidget::EnumVisibility>(grBindingArgRaw_val);
    grBindingSelf->grUiWidget::set_visibility(grBindingArg_val);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm11get_focused_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_focused();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm16get_fullyFocused_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_fullyFocused();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm11set_focused_2t1_4boolt1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_focused, bool grBindingArgRaw_suppressEvent) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_focused = grBindingArgRaw_focused;
    auto grBindingArg_suppressEvent = grBindingArgRaw_suppressEvent;
    grBindingSelf->grUiWidget::set_focused(grBindingArg_focused, grBindingArg_suppressEvent);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm16get_ignoresMouse_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_ignoresMouse();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm16set_ignoresMouse_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiWidget::set_ignoresMouse(grBindingArg_val);
}

extern "C" GR_BINDING_THUNK_EXPORT const gtl::ASCIICHAR * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10get_cursor_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_cursor();
    return grBindingAllocateString(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm10set_cursor_1t2_3gtl13PooledAString(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_cursor) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_cursor = static_cast<gtl::PooledAString>(grBindingArgRaw_cursor);
    grBindingSelf->grUiWidget::set_cursor(grBindingArg_cursor);
}

extern "C" GR_BINDING_THUNK_EXPORT const gtl::ASCIICHAR * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm16get_actualCursor_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_actualCursor();
    return grBindingAllocateString(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const gtl::ASCIICHAR * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm16get_actualCursor_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_actualCursor();
    return grBindingAllocateString(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm7hitTest_1t1_7grPointv(void * grBindingSelfRaw, grPoint grBindingArgRaw_point) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_point = static_cast<grPoint>(grBindingArgRaw_point);
    auto grBindingReturnValue = grBindingSelf->hitTest(grBindingArg_point);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint(void * grBindingSelfRaw, grPoint grBindingArgRaw_point) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_point = static_cast<grPoint>(grBindingArgRaw_point);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::hitTest(grBindingArg_point);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm23computeRelativePosition_1t1_10grUiWidget(grPoint * grBindingReturnPtr, void * grBindingSelfRaw, void * grBindingArgRaw_widget) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_widget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_widget);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::computeRelativePosition(grBindingArg_widget);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAStringv(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_id) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_id = static_cast<gtl::PooledAString>(grBindingArgRaw_id);
    auto grBindingReturnValue = grBindingSelf->findByID(grBindingArg_id);
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_id) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_id = static_cast<gtl::PooledAString>(grBindingArgRaw_id);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::findByID(grBindingArg_id);
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm6set_id_1t2_3gtl13PooledAString(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_id) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_id = static_cast<gtl::PooledAString>(grBindingArgRaw_id);
    grBindingSelf->grUiWidget::set_id(grBindingArg_id);
}

extern "C" GR_BINDING_THUNK_EXPORT const gtl::ASCIICHAR * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm6get_id_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_id();
    return grBindingAllocateString(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18set_styleStateBits_1t1_8uint64_t(void * grBindingSelfRaw, uint64_t grBindingArgRaw_styleStateBits) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_styleStateBits = grBindingArgRaw_styleStateBits;
    grBindingSelf->grUiWidget::set_styleStateBits(grBindingArg_styleStateBits);
}

extern "C" GR_BINDING_THUNK_EXPORT uint64_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18get_styleStateBits_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_styleStateBits();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18set_stylingEnabled_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_enabled) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_enabled = grBindingArgRaw_enabled;
    grBindingSelf->grUiWidget::set_stylingEnabled(grBindingArg_enabled);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm14set_styleSheet_1t1_17grUiGSSStyleSheet(void * grBindingSelfRaw, void * grBindingArgRaw_ns) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_ns = grBindingExpandWeakPtr<grUiGSSStyleSheet>(grBindingArgRaw_ns);
    grBindingSelf->grUiWidget::set_styleSheet(grBindingArg_ns);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropValv(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_name = static_cast<gtl::PooledAString>(grBindingArgRaw_name);
    auto grBindingArg_value = grBindingExpandWeakPtr<grUiGSSPropVal>(grBindingArgRaw_value);
    auto grBindingReturnValue = grBindingSelf->applyStyleProperty(grBindingArg_name, grBindingArg_value);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_name = static_cast<gtl::PooledAString>(grBindingArgRaw_name);
    auto grBindingArg_value = grBindingExpandWeakPtr<grUiGSSPropVal>(grBindingArgRaw_value);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::applyStyleProperty(grBindingArg_name, grBindingArg_value);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm11updateStyle_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->grUiWidget::updateStyle();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm20updateStyleHierarchy_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->updateStyleHierarchy();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm20updateStyleHierarchy_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->grUiWidget::updateStyleHierarchy();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm14add_styleClass_1t2_3gtl13PooledAString(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_name) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_name = static_cast<gtl::PooledAString>(grBindingArgRaw_name);
    grBindingSelf->grUiWidget::add_styleClass(grBindingArg_name);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm17remove_styleClass_1t2_3gtl13PooledAString(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_name) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_name = static_cast<gtl::PooledAString>(grBindingArgRaw_name);
    grBindingSelf->grUiWidget::remove_styleClass(grBindingArg_name);
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18get_dpiScaleFactor_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_dpiScaleFactor();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm20updateDpiScaleFactor_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->grUiWidget::updateDpiScaleFactor();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c10grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm17get_metricContext_0(grUiMetricContext * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::get_metricContext();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm11nextSibling_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::nextSibling();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15previousSibling_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::previousSibling();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm4pack_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->grUiWidget::pack();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm4pack_1t1_11grDimension(void * grBindingSelfRaw, grDimension grBindingArgRaw_minSize) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_minSize = static_cast<grDimension>(grBindingArgRaw_minSize);
    grBindingSelf->grUiWidget::pack(grBindingArg_minSize);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm6center_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grUiWidget::center(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetf10backgroundg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::background;
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetf10backgrounds(void * grBindingSelfRaw, void * grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingExpandWeakPtr<grUiBackgroundBase>(grBindingArgRaw_val);
    grBindingSelf->grUiWidget::background = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetf12clipToBoundsg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidget::clipToBounds;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetf12clipToBoundss(void * grBindingSelfRaw, bool grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiWidget::clipToBounds = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete19eventSink_mouseMove_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventMouseMove&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseMove.addHandler(grBindingHandlerWrapper<grUiEventMouseMove>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete19eventSink_mouseMove_emit(void * grBindingSelfRaw, grUiEventMouseMove &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseMove.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete19eventSink_mouseMove_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_mouseMove.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete19eventSink_mouseDown_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventMouseDown&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseDown.addHandler(grBindingHandlerWrapper<grUiEventMouseDown>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete19eventSink_mouseDown_emit(void * grBindingSelfRaw, grUiEventMouseDown &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseDown.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete19eventSink_mouseDown_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_mouseDown.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete17eventSink_mouseUp_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventMouseUp&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseUp.addHandler(grBindingHandlerWrapper<grUiEventMouseUp>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete17eventSink_mouseUp_emit(void * grBindingSelfRaw, grUiEventMouseUp &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseUp.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete17eventSink_mouseUp_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_mouseUp.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_mouseWheel_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventMouseWheel&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseWheel.addHandler(grBindingHandlerWrapper<grUiEventMouseWheel>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_mouseWheel_emit(void * grBindingSelfRaw, grUiEventMouseWheel &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseWheel.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_mouseWheel_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_mouseWheel.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_mouseLeave_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventMouseLeave&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseLeave.addHandler(grBindingHandlerWrapper<grUiEventMouseLeave>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_mouseLeave_emit(void * grBindingSelfRaw, grUiEventMouseLeave &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseLeave.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_mouseLeave_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_mouseLeave.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_mouseEnter_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventMouseEnter&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseEnter.addHandler(grBindingHandlerWrapper<grUiEventMouseEnter>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_mouseEnter_emit(void * grBindingSelfRaw, grUiEventMouseEnter &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_mouseEnter.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_mouseEnter_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_mouseEnter.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete15eventSink_focus_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventFocus&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_focus.addHandler(grBindingHandlerWrapper<grUiEventFocus>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete15eventSink_focus_emit(void * grBindingSelfRaw, grUiEventFocus &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_focus.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete15eventSink_focus_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_focus.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete17eventSink_defocus_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventDefocus&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_defocus.addHandler(grBindingHandlerWrapper<grUiEventDefocus>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete17eventSink_defocus_emit(void * grBindingSelfRaw, grUiEventDefocus &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_defocus.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete17eventSink_defocus_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_defocus.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete23eventSink_parentDefocus_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventDefocus&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_parentDefocus.addHandler(grBindingHandlerWrapper<grUiEventDefocus>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete23eventSink_parentDefocus_emit(void * grBindingSelfRaw, grUiEventDefocus &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_parentDefocus.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete23eventSink_parentDefocus_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_parentDefocus.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete18eventSink_keyEvent_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventKeyPress&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_keyEvent.addHandler(grBindingHandlerWrapper<grUiEventKeyPress>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete18eventSink_keyEvent_emit(void * grBindingSelfRaw, grUiEventKeyPress &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_keyEvent.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete18eventSink_keyEvent_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_keyEvent.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete19eventSink_textInput_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventTextInput&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_textInput.addHandler(grBindingHandlerWrapper<grUiEventTextInput>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete19eventSink_textInput_emit(void * grBindingSelfRaw, grUiEventTextInput &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_textInput.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete19eventSink_textInput_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_textInput.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_objectDrop_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventObjectDrop&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_objectDrop.addHandler(grBindingHandlerWrapper<grUiEventObjectDrop>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_objectDrop_emit(void * grBindingSelfRaw, grUiEventObjectDrop &ev) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_objectDrop.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgete20eventSink_objectDrop_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->eventSink_objectDrop.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c10grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c10grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c10grUiWidget *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c10grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiWidgetm15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c10grUiWidget *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextr() {
    return &grUiDragContext::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiDragContext*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c15grUiDragContext {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiDragContextm8dragMove_5t1_21grUiRootWindowManagert1_3intt1_3intt1_3intt1_3int)(void * grBindingGchRaw, void * grBindingArgRaw_root, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y, int32_t grBindingArgRaw_dx, int32_t grBindingArgRaw_dy);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiDragContextm11dragRelease_1t1_21grUiRootWindowManager)(void * grBindingGchRaw, void * grBindingArgRaw_root);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiDragContextm10showObject_3t1_21grUiRootWindowManagert1_3intt1_3int)(void * grBindingGchRaw, void * grBindingArgRaw_root, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiDragContextm10hideObject_1t1_21grUiRootWindowManager)(void * grBindingGchRaw, void * grBindingArgRaw_root);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiDragContextm9getCursor_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c15grUiDragContext;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextp(const grBindingProxyInfo_grBinding_c15grUiDragContext *info) {
    grBindingProxyInfoInstance_grBinding_c15grUiDragContext = *info;
}

class grBindingProxyClass_grBinding_c15grUiDragContext : public grUiDragContext {
public:
    GTL_RTTI_DECLARE();

    using grUiDragContext::grUiDragContext;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c15grUiDragContext() override {
        grBindingProxyInfoInstance_grBinding_c15grUiDragContext.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual void dragMove(gnaWeakPointer<grUiRootWindowManager> grBindingArg_root, int32_t grBindingArg_x, int32_t grBindingArg_y, int32_t grBindingArg_dx, int32_t grBindingArg_dy) override {
        grBindingProxyInfoInstance_grBinding_c15grUiDragContext.grBinding_c15grUiDragContextm8dragMove_5t1_21grUiRootWindowManagert1_3intt1_3intt1_3intt1_3int(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiRootWindowManager>>::translateArgFromNativeToManagedCls(grBindingArg_root), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_x), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_y), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dx), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dy));
    }

    virtual void dragRelease(gnaWeakPointer<grUiRootWindowManager> grBindingArg_root) override {
        grBindingProxyInfoInstance_grBinding_c15grUiDragContext.grBinding_c15grUiDragContextm11dragRelease_1t1_21grUiRootWindowManager(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiRootWindowManager>>::translateArgFromNativeToManagedCls(grBindingArg_root));
    }

    virtual void showObject(gnaWeakPointer<grUiRootWindowManager> grBindingArg_root, int32_t grBindingArg_x, int32_t grBindingArg_y) override {
        grBindingProxyInfoInstance_grBinding_c15grUiDragContext.grBinding_c15grUiDragContextm10showObject_3t1_21grUiRootWindowManagert1_3intt1_3int(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiRootWindowManager>>::translateArgFromNativeToManagedCls(grBindingArg_root), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_x), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_y));
    }

    virtual void hideObject(gnaWeakPointer<grUiRootWindowManager> grBindingArg_root) override {
        grBindingProxyInfoInstance_grBinding_c15grUiDragContext.grBinding_c15grUiDragContextm10hideObject_1t1_21grUiRootWindowManager(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiRootWindowManager>>::translateArgFromNativeToManagedCls(grBindingArg_root));
    }

    virtual gtl::PooledAString getCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiDragContext.grBinding_c15grUiDragContextm9getCursor_0(grBindingGch));
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c15grUiDragContext, GTL_RTTI_INHERITS(grUiDragContext), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c15grUiDragContext, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c15grUiDragContext*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextx(void *self) {
    return gtlDelete static_cast<grUiDragContext*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextf14m_holderWindowg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiDragContext::m_holderWindow;
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextf14m_holderWindows(void * grBindingSelfRaw, void * grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_val);
    grBindingSelf->grUiDragContext::m_holderWindow = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextf11mouseButtong(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiDragContext::mouseButton;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextn0_2t1_10grUiWidgett1_3intv(void * grBindingArgRaw_holderWidget, int32_t grBindingArgRaw_mouseButton) {
    auto grBindingArg_holderWidget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_holderWidget);
    auto grBindingArg_mouseButton = grBindingArgRaw_mouseButton;
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c15grUiDragContext(grBindingArg_holderWidget, grBindingArg_mouseButton);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextm8dragMove_5t1_21grUiRootWindowManagert1_3intt1_3intt1_3intt1_3intv(void * grBindingSelfRaw, void * grBindingArgRaw_root, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y, int32_t grBindingArgRaw_dx, int32_t grBindingArgRaw_dy) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingArg_root = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_root);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    auto grBindingArg_dx = grBindingArgRaw_dx;
    auto grBindingArg_dy = grBindingArgRaw_dy;
    grBindingSelf->dragMove(grBindingArg_root, grBindingArg_x, grBindingArg_y, grBindingArg_dx, grBindingArg_dy);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextm11dragRelease_1t1_21grUiRootWindowManagerv(void * grBindingSelfRaw, void * grBindingArgRaw_root) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingArg_root = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_root);
    grBindingSelf->dragRelease(grBindingArg_root);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextm10showObject_3t1_21grUiRootWindowManagert1_3intt1_3intv(void * grBindingSelfRaw, void * grBindingArgRaw_root, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingArg_root = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_root);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    grBindingSelf->showObject(grBindingArg_root, grBindingArg_x, grBindingArg_y);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextm10showObject_3t1_21grUiRootWindowManagert1_3intt1_3int(void * grBindingSelfRaw, void * grBindingArgRaw_root, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingArg_root = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_root);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    grBindingSelf->grUiDragContext::showObject(grBindingArg_root, grBindingArg_x, grBindingArg_y);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextm10hideObject_1t1_21grUiRootWindowManagerv(void * grBindingSelfRaw, void * grBindingArgRaw_root) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingArg_root = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_root);
    grBindingSelf->hideObject(grBindingArg_root);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextm10hideObject_1t1_21grUiRootWindowManager(void * grBindingSelfRaw, void * grBindingArgRaw_root) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingArg_root = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_root);
    grBindingSelf->grUiDragContext::hideObject(grBindingArg_root);
}

extern "C" GR_BINDING_THUNK_EXPORT const gtl::ASCIICHAR * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextm9getCursor_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->getCursor();
    return grBindingAllocateString(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const gtl::ASCIICHAR * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiDragContextm9getCursor_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiDragContext *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiDragContext::getCursor();
    return grBindingAllocateString(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerr() {
    return &grUiWindowManager::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiWindowManager*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c17grUiWindowManager {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_contentBias_0)(void * grBindingGchRaw);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c17grUiWindowManager;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerp(const grBindingProxyInfo_grBinding_c17grUiWindowManager *info) {
    grBindingProxyInfoInstance_grBinding_c17grUiWindowManager = *info;
}

class grBindingProxyClass_grBinding_c17grUiWindowManager : public grUiWindowManager {
public:
    GTL_RTTI_DECLARE();

    using grUiWindowManager::grUiWindowManager;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c17grUiWindowManager() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm15get_contentBias_0(grBindingGch));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm6update_0(grBindingGch);
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0(grBindingGch));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0(grBindingGch);
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidgetLayout::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidgetLayout::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidgetLayout::onBoundsChanged();
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWindowManager.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c17grUiWindowManager, GTL_RTTI_INHERITS(grUiWindowManager), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c17grUiWindowManager, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c17grUiWindowManager*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerx(void *self) {
    return gtlDelete static_cast<grUiWindowManager*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagern0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c17grUiWindowManager();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagern0_0() {
    auto grBindingReturnValue = gtlNew grUiWindowManager();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerm21displayCenteredDialog_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_win) {
    auto grBindingSelf = static_cast<grUiWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_win = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_win);
    grBindingSelf->grUiWindowManager::displayCenteredDialog(grBindingArg_win);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerm25displayProportionalDialog_3t1_10grUiWidgett1_5floatt1_5float(void * grBindingSelfRaw, void * grBindingArgRaw_win, float grBindingArgRaw_x, float grBindingArgRaw_y) {
    auto grBindingSelf = static_cast<grUiWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_win = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_win);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    grBindingSelf->grUiWindowManager::displayProportionalDialog(grBindingArg_win, grBindingArg_x, grBindingArg_y);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerm18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerm12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWindowManager *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerm15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWindowManager *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerm20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerm16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWindowManagerm19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWindowManager *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextr() {
    return &grUiWidgetText::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiWidgetText*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c14grUiWidgetText {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm15get_contentBias_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutDirty_0)(void * grBindingGchRaw);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15onBoundsChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c14grUiWidgetText;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextp(const grBindingProxyInfo_grBinding_c14grUiWidgetText *info) {
    grBindingProxyInfoInstance_grBinding_c14grUiWidgetText = *info;
}

class grBindingProxyClass_grBinding_c14grUiWidgetText : public grUiWidgetText {
public:
    GTL_RTTI_DECLARE();

    using grUiWidgetText::grUiWidgetText;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c14grUiWidgetText() override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c14grUiWidgetTextm14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c14grUiWidgetTextm15get_contentBias_0(grBindingGch));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c14grUiWidgetTextm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c14grUiWidgetTextm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm15get_layoutFlags_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm6update_0(grBindingGch);
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm15get_layoutDirty_0(grBindingGch));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm20updateStyleHierarchy_0(grBindingGch);
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidget::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidget::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c14grUiWidgetText.grBinding_c10grUiWidgetm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidget::onBoundsChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c14grUiWidgetText, GTL_RTTI_INHERITS(grUiWidgetText), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c14grUiWidgetText, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c14grUiWidgetText*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextx(void *self) {
    return gtlDelete static_cast<grUiWidgetText*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextn0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c14grUiWidgetText();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextn0_0() {
    auto grBindingReturnValue = gtlNew grUiWidgetText();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextn0_1t2_3gtl6Stringv(const gtl::WIDECHAR * grBindingArgRaw_text) {
    auto grBindingArg_text = static_cast<gtl::String>(grBindingArgRaw_text);
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c14grUiWidgetText(grBindingArg_text);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextn0_1t2_3gtl6String(const gtl::WIDECHAR * grBindingArgRaw_text) {
    auto grBindingArg_text = static_cast<gtl::String>(grBindingArgRaw_text);
    auto grBindingReturnValue = gtlNew grUiWidgetText(grBindingArg_text);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm14initialMeasure_1t1_3intv(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm14initialMeasure_1t1_3int(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->grUiWidgetText::initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm15get_contentBias_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_contentBias();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm15get_contentBias_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetText::get_contentBias();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm4draw_1t1_12grUiRendererv(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->draw(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm4draw_1t1_12grUiRenderer(void * grBindingSelfRaw, void * grBindingArgRaw_render) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_render = static_cast<grUiRenderer *>(grBindingArgRaw_render);
    grBindingSelf->grUiWidgetText::draw(grBindingArg_render);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm8set_text_1t2_3gtl6String(void * grBindingSelfRaw, const gtl::WIDECHAR * grBindingArgRaw_text) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_text = static_cast<gtl::String>(grBindingArgRaw_text);
    grBindingSelf->grUiWidgetText::set_text(grBindingArg_text);
}

extern "C" GR_BINDING_THUNK_EXPORT const gtl::WIDECHAR * GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm8get_text_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetText::get_text();
    return grBindingAllocateWString(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm15get_spannedText_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto & grBindingReturnValue = grBindingSelf->grUiWidgetText::get_spannedText();
    return &(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm12set_maxWidth_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_maxWidth) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_maxWidth = grBindingArgRaw_maxWidth;
    grBindingSelf->grUiWidgetText::set_maxWidth(grBindingArg_maxWidth);
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm12get_maxWidth_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetText::get_maxWidth();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm13set_multiline_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_multiline) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_multiline = grBindingArgRaw_multiline;
    grBindingSelf->grUiWidgetText::set_multiline(grBindingArg_multiline);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm13get_multiline_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetText::get_multiline();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm13set_ellipsize_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_ellipsize) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_ellipsize = grBindingArgRaw_ellipsize;
    grBindingSelf->grUiWidgetText::set_ellipsize(grBindingArg_ellipsize);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm13get_ellipsize_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetText::get_ellipsize();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropValv(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_name = static_cast<gtl::PooledAString>(grBindingArgRaw_name);
    auto grBindingArg_value = grBindingExpandWeakPtr<grUiGSSPropVal>(grBindingArgRaw_value);
    auto grBindingReturnValue = grBindingSelf->applyStyleProperty(grBindingArg_name, grBindingArg_value);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_name = static_cast<gtl::PooledAString>(grBindingArgRaw_name);
    auto grBindingArg_value = grBindingExpandWeakPtr<grUiGSSPropVal>(grBindingArgRaw_value);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetText::applyStyleProperty(grBindingArg_name, grBindingArg_value);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextf5colorg(grColor * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetText::color;
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextf5colors(void * grBindingSelfRaw, grColor grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grColor>(grBindingArgRaw_val);
    grBindingSelf->grUiWidgetText::color = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c14grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c14grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c14grUiWidgetText *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c14grUiWidgetText *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c14grUiWidgetText *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiWidgetTextm15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c14grUiWidgetText *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipr() {
    return &grUiWidgetTooltip::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiWidgetTooltip*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c17grUiWidgetTooltip {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_contentBias_0)(void * grBindingGchRaw);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipp(const grBindingProxyInfo_grBinding_c17grUiWidgetTooltip *info) {
    grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip = *info;
}

class grBindingProxyClass_grBinding_c17grUiWidgetTooltip : public grUiWidgetTooltip {
public:
    GTL_RTTI_DECLARE();

    using grUiWidgetTooltip::grUiWidgetTooltip;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c17grUiWidgetTooltip() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm15get_contentBias_0(grBindingGch));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm6update_0(grBindingGch);
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0(grBindingGch));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0(grBindingGch);
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidgetLayout::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidgetLayout::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidgetLayout::onBoundsChanged();
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c17grUiWidgetTooltip.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c17grUiWidgetTooltip, GTL_RTTI_INHERITS(grUiWidgetTooltip), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c17grUiWidgetTooltip, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c17grUiWidgetTooltip*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipx(void *self) {
    return gtlDelete static_cast<grUiWidgetTooltip*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipn0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c17grUiWidgetTooltip();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipn0_0() {
    auto grBindingReturnValue = gtlNew grUiWidgetTooltip();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipm10displayTip_3t1_17grUiWindowManagert1_3intt1_3int(void * grBindingSelfRaw, void * grBindingArgRaw_windowManager, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y) {
    auto grBindingSelf = static_cast<grUiWidgetTooltip *>(grBindingSelfRaw);
    auto grBindingArg_windowManager = grBindingExpandWeakPtr<grUiWindowManager>(grBindingArgRaw_windowManager);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    grBindingSelf->grUiWidgetTooltip::displayTip(grBindingArg_windowManager, grBindingArg_x, grBindingArg_y);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipm7hideTip_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetTooltip *>(grBindingSelfRaw);
    grBindingSelf->grUiWidgetTooltip::hideTip();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipm18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWidgetTooltip *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipm12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWidgetTooltip *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipm15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWidgetTooltip *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipm20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWidgetTooltip *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipm16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWidgetTooltip *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiWidgetTooltipm19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c17grUiWidgetTooltip *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramer() {
    return &grUiFrame::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramed(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiFrame*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c9grUiFrame {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c9grUiFramem6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c9grUiFramem14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c9grUiFramem24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c9grUiFramem19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c9grUiFramem19widgetBorderChanged_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c9grUiFramem12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c9grUiFramem15onBoundsChanged_0)(void * grBindingGchRaw);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_contentBias_0)(void * grBindingGchRaw);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
} static grBindingProxyInfoInstance_grBinding_c9grUiFrame;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramep(const grBindingProxyInfo_grBinding_c9grUiFrame *info) {
    grBindingProxyInfoInstance_grBinding_c9grUiFrame = *info;
}

class grBindingProxyClass_grBinding_c9grUiFrame : public grUiFrame {
public:
    GTL_RTTI_DECLARE();

    using grUiFrame::grUiFrame;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c9grUiFrame() override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c9grUiFramem6update_0(grBindingGch);
    }

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c9grUiFramem14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c9grUiFramem24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c9grUiFramem19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c9grUiFramem19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiFrame::widgetBorderChanged();
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c9grUiFramem12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiFrame::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c9grUiFramem15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiFrame::onBoundsChanged();
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm15get_contentBias_0(grBindingGch));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0(grBindingGch));
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0(grBindingGch));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0(grBindingGch);
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidgetLayout::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c9grUiFrame.grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c9grUiFrame, GTL_RTTI_INHERITS(grUiFrame), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c9grUiFrame, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFrameg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c9grUiFrame*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramex(void *self) {
    return gtlDelete static_cast<grUiFrame*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramen0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c9grUiFrame();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramen0_0() {
    auto grBindingReturnValue = gtlNew grUiFrame();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem6update_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    grBindingSelf->update();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem6update_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    grBindingSelf->grUiFrame::update();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem9set_title_1t2_3gtl6String(void * grBindingSelfRaw, const gtl::WIDECHAR * grBindingArgRaw_title) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_title = static_cast<gtl::String>(grBindingArgRaw_title);
    grBindingSelf->grUiFrame::set_title(grBindingArg_title);
}

extern "C" GR_BINDING_THUNK_EXPORT const gtl::WIDECHAR * GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem9get_title_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiFrame::get_title();
    return grBindingAllocateWString(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem10closeFrame_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    grBindingSelf->grUiFrame::closeFrame();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem17set_contentWidget_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_widget) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_widget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_widget);
    grBindingSelf->grUiFrame::set_contentWidget(grBindingArg_widget);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem14initialMeasure_1t1_3intv(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem14initialMeasure_1t1_3int(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->grUiFrame::initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem17get_contentWidget_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiFrame::get_contentWidget();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem24get_nativeViewportWidget_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_nativeViewportWidget();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem24get_nativeViewportWidget_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiFrame::get_nativeViewportWidget();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem19handleParentChanged_1t1_16grUiWidgetLayoutv(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_parent);
    grBindingSelf->handleParentChanged(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem19handleParentChanged_1t1_16grUiWidgetLayout(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_parent);
    grBindingSelf->grUiFrame::handleParentChanged(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem12displayPopup_2t1_16grUiWidgetLayoutt1_8uint32_t(void * grBindingSelfRaw, void * grBindingArgRaw_windowManager, uint32_t grBindingArgRaw_flags) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_windowManager = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_windowManager);
    auto grBindingArg_flags = grBindingArgRaw_flags;
    grBindingSelf->grUiFrame::displayPopup(grBindingArg_windowManager, grBindingArg_flags);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem11togglePopup_2t1_16grUiWidgetLayoutt1_8uint32_t(void * grBindingSelfRaw, void * grBindingArgRaw_windowManager, uint32_t grBindingArgRaw_flags) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_windowManager = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_windowManager);
    auto grBindingArg_flags = grBindingArgRaw_flags;
    grBindingSelf->grUiFrame::togglePopup(grBindingArg_windowManager, grBindingArg_flags);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem12bringToFront_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    grBindingSelf->grUiFrame::bringToFront();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem12set_autoPack_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_autoPack) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_autoPack = grBindingArgRaw_autoPack;
    grBindingSelf->grUiFrame::set_autoPack(grBindingArg_autoPack);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem12get_autoPack_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiFrame::get_autoPack();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramee21eventSink_windowClose_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventPerformAction&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_windowClose.addHandler(grBindingHandlerWrapper<grUiEventPerformAction>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramee21eventSink_windowClose_emit(void * grBindingSelfRaw, grUiEventPerformAction &ev) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_windowClose.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramee21eventSink_windowClose_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    grBindingSelf->eventSink_windowClose.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramee20eventSink_windowOpen_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(grUiEventPerformAction&), void *grBindingHandlerGch, gnaEventPriority priority) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_windowOpen.addHandler(grBindingHandlerWrapper<grUiEventPerformAction>{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramee20eventSink_windowOpen_emit(void * grBindingSelfRaw, grUiEventPerformAction &ev) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    return grBindingSelf->eventSink_windowOpen.emit(ev);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramee20eventSink_windowOpen_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {
    auto grBindingSelf = static_cast<grUiFrame *>(grBindingSelfRaw);
    grBindingSelf->eventSink_windowOpen.removeHandler(static_cast<gnaEventHandlerHandle>(handle));
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c9grUiFrame *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c9grUiFrame *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c9grUiFrame *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c9grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c9grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c9grUiFramem16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c9grUiFrame *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiBorderBaser() {
    return &grUiBorderBase::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiBorderBased(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiBorderBase*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c14grUiBorderBase {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
} static grBindingProxyInfoInstance_grBinding_c14grUiBorderBase;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiBorderBasep(const grBindingProxyInfo_grBinding_c14grUiBorderBase *info) {
    grBindingProxyInfoInstance_grBinding_c14grUiBorderBase = *info;
}

class grBindingProxyClass_grBinding_c14grUiBorderBase : public grUiBorderBase {
public:
    GTL_RTTI_DECLARE();

    using grUiBorderBase::grUiBorderBase;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c14grUiBorderBase() override {
        grBindingProxyInfoInstance_grBinding_c14grUiBorderBase.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c14grUiBorderBase, GTL_RTTI_INHERITS(grUiBorderBase), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c14grUiBorderBase, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiBorderBaseg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c14grUiBorderBase*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiBorderBasex(void *self) {
    return gtlDelete static_cast<grUiBorderBase*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerr() {
    return &grUiRootWindowManager::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiRootWindowManager*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c21grUiRootWindowManager {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c21grUiRootWindowManagerm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c21grUiRootWindowManagerm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c21grUiRootWindowManagerm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c21grUiRootWindowManagerm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c21grUiRootWindowManagerm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_contentBias_0)(void * grBindingGchRaw);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerp(const grBindingProxyInfo_grBinding_c21grUiRootWindowManager *info) {
    grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager = *info;
}

class grBindingProxyClass_grBinding_c21grUiRootWindowManager : public grUiRootWindowManager {
public:
    GTL_RTTI_DECLARE();

    using grUiRootWindowManager::grUiRootWindowManager;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c21grUiRootWindowManager() override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c21grUiRootWindowManagerm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c21grUiRootWindowManagerm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c21grUiRootWindowManagerm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c21grUiRootWindowManagerm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c21grUiRootWindowManagerm6update_0(grBindingGch);
    }

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm15get_contentBias_0(grBindingGch));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0(grBindingGch));
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0(grBindingGch));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0(grBindingGch);
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidgetLayout::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidgetLayout::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidgetLayout::onBoundsChanged();
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c21grUiRootWindowManager.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c21grUiRootWindowManager, GTL_RTTI_INHERITS(grUiRootWindowManager), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c21grUiRootWindowManager, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c21grUiRootWindowManager*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerx(void *self) {
    return gtlDelete static_cast<grUiRootWindowManager*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagern0_1t1_24grUiNativePlatformDevicev(void * grBindingArgRaw_device) {
    auto grBindingArg_device = static_cast<grUiNativePlatformDevice *>(grBindingArgRaw_device);
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c21grUiRootWindowManager(grBindingArg_device);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagern0_1t1_24grUiNativePlatformDevice(void * grBindingArgRaw_device) {
    auto grBindingArg_device = static_cast<grUiNativePlatformDevice *>(grBindingArgRaw_device);
    auto grBindingReturnValue = gtlNew grUiRootWindowManager(grBindingArg_device);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm16startDragAndDrop_1t1_15grUiDragContext(void * grBindingSelfRaw, void * grBindingArgRaw_ctx) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_ctx = grBindingExpandWeakPtr<grUiDragContext>(grBindingArgRaw_ctx);
    grBindingSelf->grUiRootWindowManager::startDragAndDrop(grBindingArg_ctx);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm15get_dragContext_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiRootWindowManager::get_dragContext();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm25displayProportionalDialog_3t1_10grUiWidgett1_5floatt1_5float(void * grBindingSelfRaw, void * grBindingArgRaw_win, float grBindingArgRaw_x, float grBindingArgRaw_y) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_win = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_win);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    grBindingSelf->grUiRootWindowManager::displayProportionalDialog(grBindingArg_win, grBindingArg_x, grBindingArg_y);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm16nativeWidgetDraw_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    grBindingSelf->nativeWidgetDraw();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm16nativeWidgetDraw_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    grBindingSelf->grUiRootWindowManager::nativeWidgetDraw();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm19nativeWidgetPreDraw_1t1_5floatv(void * grBindingSelfRaw, float grBindingArgRaw_deltaTime) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_deltaTime = grBindingArgRaw_deltaTime;
    grBindingSelf->nativeWidgetPreDraw(grBindingArg_deltaTime);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm19nativeWidgetPreDraw_1t1_5float(void * grBindingSelfRaw, float grBindingArgRaw_deltaTime) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_deltaTime = grBindingArgRaw_deltaTime;
    grBindingSelf->grUiRootWindowManager::nativeWidgetPreDraw(grBindingArg_deltaTime);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm19nativeWidgetPresent_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    grBindingSelf->nativeWidgetPresent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm19nativeWidgetPresent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    grBindingSelf->grUiRootWindowManager::nativeWidgetPresent();
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm28usesNativeChildEventBehavior_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->usesNativeChildEventBehavior();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm28usesNativeChildEventBehavior_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiRootWindowManager::usesNativeChildEventBehavior();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm6update_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    grBindingSelf->update();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm6update_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    grBindingSelf->grUiRootWindowManager::update();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm14endDragAndDrop_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRootWindowManager *>(grBindingSelfRaw);
    grBindingSelf->grUiRootWindowManager::endDragAndDrop();
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm20getRootWindowManager_0() {
    auto grBindingReturnValue = grUiRootWindowManager::getRootWindowManager();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm20setRootWindowManager_1t1_21grUiRootWindowManager(void * grBindingArgRaw_wm) {
    auto grBindingArg_wm = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_wm);
    grUiRootWindowManager::setRootWindowManager(grBindingArg_wm);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c21grUiRootWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c21grUiRootWindowManager *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c21grUiRootWindowManager *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c21grUiRootWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c21grUiRootWindowManager *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiRootWindowManagerm19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c21grUiRootWindowManager *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritex(void *self) {
    return gtlDelete static_cast<grUiSprite*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef9m_textureg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiSprite::m_texture;
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef9m_textures(void * grBindingSelfRaw, void * grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingExpandWeakPtr<grImg::Image>(grBindingArgRaw_val);
    grBindingSelf->grUiSprite::m_texture = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT float GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef4minUg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiSprite::minU;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef4minUs(void * grBindingSelfRaw, float grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiSprite::minU = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT float GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef4minVg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiSprite::minV;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef4minVs(void * grBindingSelfRaw, float grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiSprite::minV = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT float GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef4maxUg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiSprite::maxU;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef4maxUs(void * grBindingSelfRaw, float grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiSprite::maxU = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT float GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef4maxVg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiSprite::maxV;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef4maxVs(void * grBindingSelfRaw, float grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiSprite::maxV = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT float GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef8dstWidthg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiSprite::dstWidth;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef8dstWidths(void * grBindingSelfRaw, float grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiSprite::dstWidth = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT float GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef9dstHeightg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiSprite::dstHeight;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritef9dstHeights(void * grBindingSelfRaw, float grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiSprite::dstHeight = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpriten0_0() {
    auto grBindingReturnValue = gtlNew grUiSprite();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpriten0_1t2_3gtl12PooledString(const gtl::WIDECHAR * grBindingArgRaw_resource) {
    auto grBindingArg_resource = static_cast<gtl::PooledString>(grBindingArgRaw_resource);
    auto grBindingReturnValue = gtlNew grUiSprite(grBindingArg_resource);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpriten0_3t2_3gtl12PooledStringt1_5floatt1_5float(const gtl::WIDECHAR * grBindingArgRaw_resource, float grBindingArgRaw_dstWidth, float grBindingArgRaw_dstHeight) {
    auto grBindingArg_resource = static_cast<gtl::PooledString>(grBindingArgRaw_resource);
    auto grBindingArg_dstWidth = grBindingArgRaw_dstWidth;
    auto grBindingArg_dstHeight = grBindingArgRaw_dstHeight;
    auto grBindingReturnValue = gtlNew grUiSprite(grBindingArg_resource, grBindingArg_dstWidth, grBindingArg_dstHeight);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpriten0_7t2_3gtl12PooledStringt1_5floatt1_5floatt1_5floatt1_5floatt1_5floatt1_5float(const gtl::WIDECHAR * grBindingArgRaw_resource, float grBindingArgRaw_minU, float grBindingArgRaw_minV, float grBindingArgRaw_maxU, float grBindingArgRaw_maxV, float grBindingArgRaw_dstWidth, float grBindingArgRaw_dstHeight) {
    auto grBindingArg_resource = static_cast<gtl::PooledString>(grBindingArgRaw_resource);
    auto grBindingArg_minU = grBindingArgRaw_minU;
    auto grBindingArg_minV = grBindingArgRaw_minV;
    auto grBindingArg_maxU = grBindingArgRaw_maxU;
    auto grBindingArg_maxV = grBindingArgRaw_maxV;
    auto grBindingArg_dstWidth = grBindingArgRaw_dstWidth;
    auto grBindingArg_dstHeight = grBindingArgRaw_dstHeight;
    auto grBindingReturnValue = gtlNew grUiSprite(grBindingArg_resource, grBindingArg_minU, grBindingArg_minV, grBindingArg_maxU, grBindingArg_maxV, grBindingArg_dstWidth, grBindingArg_dstHeight);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpriten0_1t2_5grImg5Image(void * grBindingArgRaw_texturePtr) {
    auto grBindingArg_texturePtr = grBindingExpandWeakPtr<grImg::Image>(grBindingArgRaw_texturePtr);
    auto grBindingReturnValue = gtlNew grUiSprite(grBindingArg_texturePtr);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpriten0_3t2_5grImg5Imaget1_5floatt1_5float(void * grBindingArgRaw_texturePtr, float grBindingArgRaw_dstWidth, float grBindingArgRaw_dstHeight) {
    auto grBindingArg_texturePtr = grBindingExpandWeakPtr<grImg::Image>(grBindingArgRaw_texturePtr);
    auto grBindingArg_dstWidth = grBindingArgRaw_dstWidth;
    auto grBindingArg_dstHeight = grBindingArgRaw_dstHeight;
    auto grBindingReturnValue = gtlNew grUiSprite(grBindingArg_texturePtr, grBindingArg_dstWidth, grBindingArg_dstHeight);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpriten0_7t2_5grImg5Imaget1_5floatt1_5floatt1_5floatt1_5floatt1_5floatt1_5float(void * grBindingArgRaw_texturePtr, float grBindingArgRaw_minU, float grBindingArgRaw_minV, float grBindingArgRaw_maxU, float grBindingArgRaw_maxV, float grBindingArgRaw_dstWidth, float grBindingArgRaw_dstHeight) {
    auto grBindingArg_texturePtr = grBindingExpandWeakPtr<grImg::Image>(grBindingArgRaw_texturePtr);
    auto grBindingArg_minU = grBindingArgRaw_minU;
    auto grBindingArg_minV = grBindingArgRaw_minV;
    auto grBindingArg_maxU = grBindingArgRaw_maxU;
    auto grBindingArg_maxV = grBindingArgRaw_maxV;
    auto grBindingArg_dstWidth = grBindingArgRaw_dstWidth;
    auto grBindingArg_dstHeight = grBindingArgRaw_dstHeight;
    auto grBindingReturnValue = gtlNew grUiSprite(grBindingArg_texturePtr, grBindingArg_minU, grBindingArg_minV, grBindingArg_maxU, grBindingArg_maxV, grBindingArg_dstWidth, grBindingArg_dstHeight);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritem11withDstSize_2t1_5floatt1_5float(void * grBindingSelfRaw, float grBindingArgRaw_width, float grBindingArgRaw_height) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingArg_width = grBindingArgRaw_width;
    auto grBindingArg_height = grBindingArgRaw_height;
    auto grBindingReturnValue = grBindingSelf->grUiSprite::withDstSize(grBindingArg_width, grBindingArg_height);
    return gtlNew grUiSprite(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c10grUiSpritem4crop_4t1_5floatt1_5floatt1_5floatt1_5float(void * grBindingSelfRaw, float grBindingArgRaw_x, float grBindingArgRaw_y, float grBindingArgRaw_width, float grBindingArgRaw_height) {
    auto grBindingSelf = static_cast<grUiSprite *>(grBindingSelfRaw);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    auto grBindingArg_width = grBindingArgRaw_width;
    auto grBindingArg_height = grBindingArgRaw_height;
    auto grBindingReturnValue = grBindingSelf->grUiSprite::crop(grBindingArg_x, grBindingArg_y, grBindingArg_width, grBindingArg_height);
    return gtlNew grUiSprite(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicer() {
    return &grUiNativePlatformDevice::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDeviced(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiNativePlatformDevice*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c24grUiNativePlatformDevice {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem19createFramePlatform_1t1_10grUiWidget)(void * grBindingGchRaw, void * grBindingArgRaw_widget);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem14createRenderer_1t1_10grUiWidget)(void * grBindingGchRaw, void * grBindingArgRaw_widget);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem16nativeWidgetDraw_1t1_10grUiWidget)(void * grBindingGchRaw, void * grBindingArgRaw_widget);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem19nativeWidgetPreDraw_2t1_10grUiWidgett1_5float)(void * grBindingGchRaw, void * grBindingArgRaw_widget, float grBindingArgRaw_deltaTime);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem15isDesktopWidget_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem21shouldHaveOwnRenderer_2t1_10grUiWidgett1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_widget, void * grBindingArgRaw_parent);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem17get_displayBounds_0)(grRectangle * grBindingReturnPtr, void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem22set_globalMousePointer_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_pointerID);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem7openURI_1t2_3gtl6String)(void * grBindingGchRaw, const gtl::WIDECHAR * grBindingArgRaw_uri);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem22get_doubleClickDelayMs_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c24grUiNativePlatformDevicem36useNativeWindowManagerInputMechanism_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicep(const grBindingProxyInfo_grBinding_c24grUiNativePlatformDevice *info) {
    grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice = *info;
}

class grBindingProxyClass_grBinding_c24grUiNativePlatformDevice : public grUiNativePlatformDevice {
public:
    GTL_RTTI_DECLARE();

    using grUiNativePlatformDevice::grUiNativePlatformDevice;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c24grUiNativePlatformDevice() override {
        grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grUiNativeFramePlatform * createFramePlatform(gnaWeakPointer<grUiWidget> grBindingArg_widget) override {
        return grBindingTypeUtils<grUiNativeFramePlatform *>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem19createFramePlatform_1t1_10grUiWidget(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateArgFromNativeToManagedCls(grBindingArg_widget)));
    }

    virtual grUiRenderer * createRenderer(gnaWeakPointer<grUiWidget> grBindingArg_widget) override {
        return grBindingTypeUtils<grUiRenderer *>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem14createRenderer_1t1_10grUiWidget(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateArgFromNativeToManagedCls(grBindingArg_widget)));
    }

    virtual void nativeWidgetDraw(gnaWeakPointer<grUiWidget> grBindingArg_widget) override {
        grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem16nativeWidgetDraw_1t1_10grUiWidget(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateArgFromNativeToManagedCls(grBindingArg_widget));
    }

    virtual void nativeWidgetPreDraw(gnaWeakPointer<grUiWidget> grBindingArg_widget, float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem19nativeWidgetPreDraw_2t1_10grUiWidgett1_5float(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateArgFromNativeToManagedCls(grBindingArg_widget), grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual bool isDesktopWidget(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) const override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem15isDesktopWidget_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent)));
    }

    virtual bool shouldHaveOwnRenderer(gnaWeakPointer<grUiWidget> grBindingArg_widget, gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) const override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem21shouldHaveOwnRenderer_2t1_10grUiWidgett1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateArgFromNativeToManagedCls(grBindingArg_widget), grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent)));
    }

    virtual grRectangle get_displayBounds() const override {
        grRectangle grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem17get_displayBounds_0(&grBindingReturnValue, grBindingGch);
        return grBindingReturnValue;
    }

    virtual void set_globalMousePointer(gtl::PooledAString grBindingArg_pointerID) const override {
        grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem22set_globalMousePointer_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<gtl::PooledAString>::translateArgFromNativeToManaged(grBindingArg_pointerID));
    }

    virtual void openURI(const gtl::String & grBindingArg_uri) override {
        grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem7openURI_1t2_3gtl6String(grBindingGch, grBindingTypeUtils<const gtl::String &>::translateArgFromNativeToManaged(grBindingArg_uri));
    }

    virtual uint32_t get_doubleClickDelayMs() const override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem22get_doubleClickDelayMs_0(grBindingGch));
    }

    virtual bool useNativeWindowManagerInputMechanism() const override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c24grUiNativePlatformDevice.grBinding_c24grUiNativePlatformDevicem36useNativeWindowManagerInputMechanism_0(grBindingGch));
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c24grUiNativePlatformDevice, GTL_RTTI_INHERITS(grUiNativePlatformDevice), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c24grUiNativePlatformDevice, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDeviceg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c24grUiNativePlatformDevice*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicex(void *self) {
    return gtlDelete static_cast<grUiNativePlatformDevice*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicen0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c24grUiNativePlatformDevice();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem19createFramePlatform_1t1_10grUiWidgetv(void * grBindingSelfRaw, void * grBindingArgRaw_widget) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingArg_widget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_widget);
    auto grBindingReturnValue = grBindingSelf->createFramePlatform(grBindingArg_widget);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem14createRenderer_1t1_10grUiWidgetv(void * grBindingSelfRaw, void * grBindingArgRaw_widget) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingArg_widget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_widget);
    auto grBindingReturnValue = grBindingSelf->createRenderer(grBindingArg_widget);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem16nativeWidgetDraw_1t1_10grUiWidgetv(void * grBindingSelfRaw, void * grBindingArgRaw_widget) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingArg_widget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_widget);
    grBindingSelf->nativeWidgetDraw(grBindingArg_widget);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem19nativeWidgetPreDraw_2t1_10grUiWidgett1_5floatv(void * grBindingSelfRaw, void * grBindingArgRaw_widget, float grBindingArgRaw_deltaTime) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingArg_widget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_widget);
    auto grBindingArg_deltaTime = grBindingArgRaw_deltaTime;
    grBindingSelf->nativeWidgetPreDraw(grBindingArg_widget, grBindingArg_deltaTime);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem15isDesktopWidget_1t1_16grUiWidgetLayoutv(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_parent);
    auto grBindingReturnValue = grBindingSelf->isDesktopWidget(grBindingArg_parent);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem21shouldHaveOwnRenderer_2t1_10grUiWidgett1_16grUiWidgetLayoutv(void * grBindingSelfRaw, void * grBindingArgRaw_widget, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingArg_widget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_widget);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidgetLayout>(grBindingArgRaw_parent);
    auto grBindingReturnValue = grBindingSelf->shouldHaveOwnRenderer(grBindingArg_widget, grBindingArg_parent);
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem17get_displayBounds_0v(grRectangle * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_displayBounds();
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem22set_globalMousePointer_1t2_3gtl13PooledAStringv(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_pointerID) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingArg_pointerID = static_cast<gtl::PooledAString>(grBindingArgRaw_pointerID);
    grBindingSelf->set_globalMousePointer(grBindingArg_pointerID);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem7openURI_1t2_3gtl6Stringv(void * grBindingSelfRaw, const gtl::WIDECHAR * grBindingArgRaw_uri) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingArg_uri = static_cast<gtl::String>(grBindingArgRaw_uri);
    grBindingSelf->openURI(grBindingArg_uri);
}

extern "C" GR_BINDING_THUNK_EXPORT uint32_t GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem22get_doubleClickDelayMs_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_doubleClickDelayMs();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem36useNativeWindowManagerInputMechanism_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->useNativeWindowManagerInputMechanism();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV grBinding_c24grUiNativePlatformDevicem36useNativeWindowManagerInputMechanism_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiNativePlatformDevice *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiNativePlatformDevice::useNativeWindowManagerInputMechanism();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPaner() {
    return &grUiWidgetScrollPane::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPaned(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiWidgetScrollPane*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c20grUiWidgetScrollPane {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_contentBias_0)(void * grBindingGchRaw);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanep(const grBindingProxyInfo_grBinding_c20grUiWidgetScrollPane *info) {
    grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane = *info;
}

class grBindingProxyClass_grBinding_c20grUiWidgetScrollPane : public grUiWidgetScrollPane {
public:
    GTL_RTTI_DECLARE();

    using grUiWidgetScrollPane::grUiWidgetScrollPane;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c20grUiWidgetScrollPane() override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm15get_contentBias_0(grBindingGch));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm15get_layoutFlags_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm6update_0(grBindingGch);
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm15get_layoutDirty_0(grBindingGch));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm20updateStyleHierarchy_0(grBindingGch);
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidgetLayout::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidgetLayout::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c16grUiWidgetLayoutm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidgetLayout::onBoundsChanged();
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c20grUiWidgetScrollPane.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c20grUiWidgetScrollPane, GTL_RTTI_INHERITS(grUiWidgetScrollPane), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c20grUiWidgetScrollPane, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPaneg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c20grUiWidgetScrollPane*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanex(void *self) {
    return gtlDelete static_cast<grUiWidgetScrollPane*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanen0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c20grUiWidgetScrollPane();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanen0_0() {
    auto grBindingReturnValue = gtlNew grUiWidgetScrollPane();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem17set_contentWidget_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_widget) {
    auto grBindingSelf = static_cast<grUiWidgetScrollPane *>(grBindingSelfRaw);
    auto grBindingArg_widget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_widget);
    grBindingSelf->grUiWidgetScrollPane::set_contentWidget(grBindingArg_widget);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem17get_contentWidget_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetScrollPane *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetScrollPane::get_contentWidget();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem19set_scrollbarWidget_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_widget) {
    auto grBindingSelf = static_cast<grUiWidgetScrollPane *>(grBindingSelfRaw);
    auto grBindingArg_widget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_widget);
    grBindingSelf->grUiWidgetScrollPane::set_scrollbarWidget(grBindingArg_widget);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem19get_scrollbarWidget_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetScrollPane *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetScrollPane::get_scrollbarWidget();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem15set_scrollFlags_1t2_20grUiWidgetScrollPane11ScrollFlags(void * grBindingSelfRaw, int grBindingArgRaw_widget) {
    auto grBindingSelf = static_cast<grUiWidgetScrollPane *>(grBindingSelfRaw);
    auto grBindingArg_widget = static_cast<grUiWidgetScrollPane::ScrollFlags>(grBindingArgRaw_widget);
    grBindingSelf->grUiWidgetScrollPane::set_scrollFlags(grBindingArg_widget);
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem15get_scrollFlags_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetScrollPane *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiWidgetScrollPane::get_scrollFlags();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem11scrollToTop_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetScrollPane *>(grBindingSelfRaw);
    grBindingSelf->grUiWidgetScrollPane::scrollToTop();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem11scrollToEnd_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiWidgetScrollPane *>(grBindingSelfRaw);
    grBindingSelf->grUiWidgetScrollPane::scrollToEnd();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c20grUiWidgetScrollPane *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c20grUiWidgetScrollPane *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c20grUiWidgetScrollPane *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c20grUiWidgetScrollPane *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c20grUiWidgetScrollPane *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c20grUiWidgetScrollPanem19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c20grUiWidgetScrollPane *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18grUiBackgroundBaser() {
    return &grUiBackgroundBase::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18grUiBackgroundBased(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiBackgroundBase*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c18grUiBackgroundBase {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
} static grBindingProxyInfoInstance_grBinding_c18grUiBackgroundBase;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiBackgroundBasep(const grBindingProxyInfo_grBinding_c18grUiBackgroundBase *info) {
    grBindingProxyInfoInstance_grBinding_c18grUiBackgroundBase = *info;
}

class grBindingProxyClass_grBinding_c18grUiBackgroundBase : public grUiBackgroundBase {
public:
    GTL_RTTI_DECLARE();

    using grUiBackgroundBase::grUiBackgroundBase;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c18grUiBackgroundBase() override {
        grBindingProxyInfoInstance_grBinding_c18grUiBackgroundBase.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c18grUiBackgroundBase, GTL_RTTI_INHERITS(grUiBackgroundBase), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c18grUiBackgroundBase, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiBackgroundBaseg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c18grUiBackgroundBase*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiBackgroundBasex(void *self) {
    return gtlDelete static_cast<grUiBackgroundBase*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiGSSStyleSheetr() {
    return &grUiGSSStyleSheet::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiGSSStyleSheetd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiGSSStyleSheet*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c17grUiGSSStyleSheet {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
} static grBindingProxyInfoInstance_grBinding_c17grUiGSSStyleSheet;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiGSSStyleSheetp(const grBindingProxyInfo_grBinding_c17grUiGSSStyleSheet *info) {
    grBindingProxyInfoInstance_grBinding_c17grUiGSSStyleSheet = *info;
}

class grBindingProxyClass_grBinding_c17grUiGSSStyleSheet : public grUiGSSStyleSheet {
public:
    GTL_RTTI_DECLARE();

    using grUiGSSStyleSheet::grUiGSSStyleSheet;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c17grUiGSSStyleSheet() override {
        grBindingProxyInfoInstance_grBinding_c17grUiGSSStyleSheet.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c17grUiGSSStyleSheet, GTL_RTTI_INHERITS(grUiGSSStyleSheet), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c17grUiGSSStyleSheet, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiGSSStyleSheetg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c17grUiGSSStyleSheet*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiGSSStyleSheetx(void *self) {
    return gtlDelete static_cast<grUiGSSStyleSheet*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridr() {
    return &grUiLayoutGrid::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiLayoutGrid*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridx(void *self) {
    return gtlDelete static_cast<grUiLayoutGrid*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecr() {
    return &grUiLayoutGrid::ElementSpec::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiLayoutGrid::ElementSpec*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecx(void *self) {
    return gtlDelete static_cast<grUiLayoutGrid::ElementSpec*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecf5cellXg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutGrid::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutGrid::ElementSpec::cellX;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecf5cellXs(void * grBindingSelfRaw, int32_t grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutGrid::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiLayoutGrid::ElementSpec::cellX = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecf5cellYg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutGrid::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutGrid::ElementSpec::cellY;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecf5cellYs(void * grBindingSelfRaw, int32_t grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutGrid::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiLayoutGrid::ElementSpec::cellY = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecf5spanXg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutGrid::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutGrid::ElementSpec::spanX;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecf5spanXs(void * grBindingSelfRaw, int32_t grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutGrid::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiLayoutGrid::ElementSpec::spanX = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT int32_t GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecf5spanYg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutGrid::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutGrid::ElementSpec::spanY;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecf5spanYs(void * grBindingSelfRaw, int32_t grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutGrid::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiLayoutGrid::ElementSpec::spanY = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridc11ElementSpecn0_4t1_3intt1_3intt1_3intt1_3int(int32_t grBindingArgRaw_cellX, int32_t grBindingArgRaw_cellY, int32_t grBindingArgRaw_spanX, int32_t grBindingArgRaw_spanY) {
    auto grBindingArg_cellX = grBindingArgRaw_cellX;
    auto grBindingArg_cellY = grBindingArgRaw_cellY;
    auto grBindingArg_spanX = grBindingArgRaw_spanX;
    auto grBindingArg_spanY = grBindingArgRaw_spanY;
    auto grBindingReturnValue = gtlNew grUiLayoutGrid::ElementSpec(grBindingArg_cellX, grBindingArg_cellY, grBindingArg_spanX, grBindingArg_spanY);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c14grUiLayoutGridn0_5t2_14grUiLayoutGrid14AxisConstraintt2_14grUiLayoutGrid14AxisConstraintt1_3intt1_3intt1_8uint32_t(grBindingArray grBindingArgRaw_columnConstraints, grBindingArray grBindingArgRaw_rowConstraints, int32_t grBindingArgRaw_columns, int32_t grBindingArgRaw_rows, uint32_t grBindingArgRaw_alignment) {
    auto grBindingArg_columnConstraints = grBindingArgRaw_columnConstraints.toFixedArray();
    auto grBindingArg_rowConstraints = grBindingArgRaw_rowConstraints.toFixedArray();
    auto grBindingArg_columns = grBindingArgRaw_columns;
    auto grBindingArg_rows = grBindingArgRaw_rows;
    auto grBindingArg_alignment = grBindingArgRaw_alignment;
    auto grBindingReturnValue = gtlNew grUiLayoutGrid(grBindingArg_columnConstraints, grBindingArg_rowConstraints, grBindingArg_columns, grBindingArg_rows, grBindingArg_alignment);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextr() {
    return &grUiObjectDragContext::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiObjectDragContext*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c21grUiObjectDragContext {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c21grUiObjectDragContextm8dragMove_5t1_21grUiRootWindowManagert1_3intt1_3intt1_3intt1_3int)(void * grBindingGchRaw, void * grBindingArgRaw_root, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y, int32_t grBindingArgRaw_dx, int32_t grBindingArgRaw_dy);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c21grUiObjectDragContextm11dragRelease_1t1_21grUiRootWindowManager)(void * grBindingGchRaw, void * grBindingArgRaw_root);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c21grUiObjectDragContextm13objectDropped_1t1_4bool)(void * grBindingGchRaw, bool grBindingArgRaw_hasTarget);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiDragContextm10showObject_3t1_21grUiRootWindowManagert1_3intt1_3int)(void * grBindingGchRaw, void * grBindingArgRaw_root, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiDragContextm10hideObject_1t1_21grUiRootWindowManager)(void * grBindingGchRaw, void * grBindingArgRaw_root);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiDragContextm9getCursor_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c21grUiObjectDragContext;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextp(const grBindingProxyInfo_grBinding_c21grUiObjectDragContext *info) {
    grBindingProxyInfoInstance_grBinding_c21grUiObjectDragContext = *info;
}

class grBindingProxyClass_grBinding_c21grUiObjectDragContext : public grUiObjectDragContext {
public:
    GTL_RTTI_DECLARE();

    using grUiObjectDragContext::grUiObjectDragContext;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c21grUiObjectDragContext() override {
        grBindingProxyInfoInstance_grBinding_c21grUiObjectDragContext.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual void dragMove(gnaWeakPointer<grUiRootWindowManager> grBindingArg_root, int32_t grBindingArg_x, int32_t grBindingArg_y, int32_t grBindingArg_dx, int32_t grBindingArg_dy) override {
        grBindingProxyInfoInstance_grBinding_c21grUiObjectDragContext.grBinding_c21grUiObjectDragContextm8dragMove_5t1_21grUiRootWindowManagert1_3intt1_3intt1_3intt1_3int(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiRootWindowManager>>::translateArgFromNativeToManagedCls(grBindingArg_root), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_x), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_y), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dx), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dy));
    }

    virtual void dragRelease(gnaWeakPointer<grUiRootWindowManager> grBindingArg_root) override {
        grBindingProxyInfoInstance_grBinding_c21grUiObjectDragContext.grBinding_c21grUiObjectDragContextm11dragRelease_1t1_21grUiRootWindowManager(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiRootWindowManager>>::translateArgFromNativeToManagedCls(grBindingArg_root));
    }

    virtual void objectDropped(bool grBindingArg_hasTarget) override {
        grBindingProxyInfoInstance_grBinding_c21grUiObjectDragContext.grBinding_c21grUiObjectDragContextm13objectDropped_1t1_4bool(grBindingGch, grBindingTypeUtils<bool>::translateArgFromNativeToManaged(grBindingArg_hasTarget));
    }

    virtual void showObject(gnaWeakPointer<grUiRootWindowManager> grBindingArg_root, int32_t grBindingArg_x, int32_t grBindingArg_y) override {
        grBindingProxyInfoInstance_grBinding_c21grUiObjectDragContext.grBinding_c15grUiDragContextm10showObject_3t1_21grUiRootWindowManagert1_3intt1_3int(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiRootWindowManager>>::translateArgFromNativeToManagedCls(grBindingArg_root), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_x), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_y));
    }

    virtual void hideObject(gnaWeakPointer<grUiRootWindowManager> grBindingArg_root) override {
        grBindingProxyInfoInstance_grBinding_c21grUiObjectDragContext.grBinding_c15grUiDragContextm10hideObject_1t1_21grUiRootWindowManager(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiRootWindowManager>>::translateArgFromNativeToManagedCls(grBindingArg_root));
    }

    virtual gtl::PooledAString getCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c21grUiObjectDragContext.grBinding_c15grUiDragContextm9getCursor_0(grBindingGch));
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c21grUiObjectDragContext, GTL_RTTI_INHERITS(grUiObjectDragContext), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c21grUiObjectDragContext, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c21grUiObjectDragContext*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextx(void *self) {
    return gtlDelete static_cast<grUiObjectDragContext*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextf12m_dragObjectg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiObjectDragContext *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiObjectDragContext::m_dragObject;
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextf12m_dragObjects(void * grBindingSelfRaw, void * grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiObjectDragContext *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingExpandWeakPtr<grUiDragObject>(grBindingArgRaw_val);
    grBindingSelf->grUiObjectDragContext::m_dragObject = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextn0_3t1_10grUiWidgett1_3intt1_14grUiDragObjectv(void * grBindingArgRaw_holderWidget, int32_t grBindingArgRaw_mouseButton, void * grBindingArgRaw_dragObject) {
    auto grBindingArg_holderWidget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_holderWidget);
    auto grBindingArg_mouseButton = grBindingArgRaw_mouseButton;
    auto grBindingArg_dragObject = grBindingExpandWeakPtr<grUiDragObject>(grBindingArgRaw_dragObject);
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c21grUiObjectDragContext(grBindingArg_holderWidget, grBindingArg_mouseButton, grBindingArg_dragObject);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextn0_3t1_10grUiWidgett1_3intt1_14grUiDragObject(void * grBindingArgRaw_holderWidget, int32_t grBindingArgRaw_mouseButton, void * grBindingArgRaw_dragObject) {
    auto grBindingArg_holderWidget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_holderWidget);
    auto grBindingArg_mouseButton = grBindingArgRaw_mouseButton;
    auto grBindingArg_dragObject = grBindingExpandWeakPtr<grUiDragObject>(grBindingArgRaw_dragObject);
    auto grBindingReturnValue = gtlNew grUiObjectDragContext(grBindingArg_holderWidget, grBindingArg_mouseButton, grBindingArg_dragObject);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextm8dragMove_5t1_21grUiRootWindowManagert1_3intt1_3intt1_3intt1_3intv(void * grBindingSelfRaw, void * grBindingArgRaw_root, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y, int32_t grBindingArgRaw_dx, int32_t grBindingArgRaw_dy) {
    auto grBindingSelf = static_cast<grUiObjectDragContext *>(grBindingSelfRaw);
    auto grBindingArg_root = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_root);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    auto grBindingArg_dx = grBindingArgRaw_dx;
    auto grBindingArg_dy = grBindingArgRaw_dy;
    grBindingSelf->dragMove(grBindingArg_root, grBindingArg_x, grBindingArg_y, grBindingArg_dx, grBindingArg_dy);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextm8dragMove_5t1_21grUiRootWindowManagert1_3intt1_3intt1_3intt1_3int(void * grBindingSelfRaw, void * grBindingArgRaw_root, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y, int32_t grBindingArgRaw_dx, int32_t grBindingArgRaw_dy) {
    auto grBindingSelf = static_cast<grUiObjectDragContext *>(grBindingSelfRaw);
    auto grBindingArg_root = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_root);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    auto grBindingArg_dx = grBindingArgRaw_dx;
    auto grBindingArg_dy = grBindingArgRaw_dy;
    grBindingSelf->grUiObjectDragContext::dragMove(grBindingArg_root, grBindingArg_x, grBindingArg_y, grBindingArg_dx, grBindingArg_dy);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextm11dragRelease_1t1_21grUiRootWindowManagerv(void * grBindingSelfRaw, void * grBindingArgRaw_root) {
    auto grBindingSelf = static_cast<grUiObjectDragContext *>(grBindingSelfRaw);
    auto grBindingArg_root = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_root);
    grBindingSelf->dragRelease(grBindingArg_root);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextm11dragRelease_1t1_21grUiRootWindowManager(void * grBindingSelfRaw, void * grBindingArgRaw_root) {
    auto grBindingSelf = static_cast<grUiObjectDragContext *>(grBindingSelfRaw);
    auto grBindingArg_root = grBindingExpandWeakPtr<grUiRootWindowManager>(grBindingArgRaw_root);
    grBindingSelf->grUiObjectDragContext::dragRelease(grBindingArg_root);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextm13objectDropped_1t1_4boolv(void * grBindingSelfRaw, bool grBindingArgRaw_hasTarget) {
    auto grBindingSelf = static_cast<grUiObjectDragContext *>(grBindingSelfRaw);
    auto grBindingArg_hasTarget = grBindingArgRaw_hasTarget;
    grBindingSelf->objectDropped(grBindingArg_hasTarget);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c21grUiObjectDragContextm13objectDropped_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_hasTarget) {
    auto grBindingSelf = static_cast<grUiObjectDragContext *>(grBindingSelfRaw);
    auto grBindingArg_hasTarget = grBindingArgRaw_hasTarget;
    grBindingSelf->grUiObjectDragContext::objectDropped(grBindingArg_hasTarget);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextr() {
    return &grUiWidgetIconText::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiWidgetIconText*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c18grUiWidgetIconText {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm15get_contentBias_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiWidgetTextm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutDirty_0)(void * grBindingGchRaw);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15onBoundsChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextp(const grBindingProxyInfo_grBinding_c18grUiWidgetIconText *info) {
    grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText = *info;
}

class grBindingProxyClass_grBinding_c18grUiWidgetIconText : public grUiWidgetIconText {
public:
    GTL_RTTI_DECLARE();

    using grUiWidgetIconText::grUiWidgetIconText;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c18grUiWidgetIconText() override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c14grUiWidgetTextm14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c14grUiWidgetTextm15get_contentBias_0(grBindingGch));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c14grUiWidgetTextm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c14grUiWidgetTextm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm15get_layoutFlags_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm6update_0(grBindingGch);
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm15get_layoutDirty_0(grBindingGch));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm20updateStyleHierarchy_0(grBindingGch);
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidget::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidget::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c18grUiWidgetIconText.grBinding_c10grUiWidgetm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidget::onBoundsChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c18grUiWidgetIconText, GTL_RTTI_INHERITS(grUiWidgetIconText), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c18grUiWidgetIconText, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c18grUiWidgetIconText*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextx(void *self) {
    return gtlDelete static_cast<grUiWidgetIconText*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextm20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c18grUiWidgetIconText *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextm16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c18grUiWidgetIconText *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextm19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c18grUiWidgetIconText *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextm18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c18grUiWidgetIconText *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextm12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c18grUiWidgetIconText *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiWidgetIconTextm15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c18grUiWidgetIconText *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiGSSPropValr() {
    return &grUiGSSPropVal::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiGSSPropVald(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiGSSPropVal*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c14grUiGSSPropVal {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
} static grBindingProxyInfoInstance_grBinding_c14grUiGSSPropVal;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiGSSPropValp(const grBindingProxyInfo_grBinding_c14grUiGSSPropVal *info) {
    grBindingProxyInfoInstance_grBinding_c14grUiGSSPropVal = *info;
}

class grBindingProxyClass_grBinding_c14grUiGSSPropVal : public grUiGSSPropVal {
public:
    GTL_RTTI_DECLARE();

    using grUiGSSPropVal::grUiGSSPropVal;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c14grUiGSSPropVal() override {
        grBindingProxyInfoInstance_grBinding_c14grUiGSSPropVal.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c14grUiGSSPropVal, GTL_RTTI_INHERITS(grUiGSSPropVal), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c14grUiGSSPropVal, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiGSSPropValg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c14grUiGSSPropVal*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiGSSPropValx(void *self) {
    return gtlDelete static_cast<grUiGSSPropVal*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c14grUiGSSPropValn0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c14grUiGSSPropVal();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsoluter() {
    return &grUiLayoutAbsolute::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsoluted(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiLayoutAbsolute*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutex(void *self) {
    return gtlDelete static_cast<grUiLayoutAbsolute*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecr() {
    return &grUiLayoutAbsolute::ElementSpec::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiLayoutAbsolute::ElementSpec*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecx(void *self) {
    return gtlDelete static_cast<grUiLayoutAbsolute::ElementSpec*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecf3m_xg(grUiUnitSizeI * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutAbsolute::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutAbsolute::ElementSpec::m_x;
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecf3m_xs(void * grBindingSelfRaw, grUiUnitSizeI grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutAbsolute::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiUnitSizeI>(grBindingArgRaw_val);
    grBindingSelf->grUiLayoutAbsolute::ElementSpec::m_x = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecf3m_yg(grUiUnitSizeI * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutAbsolute::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutAbsolute::ElementSpec::m_y;
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecf3m_ys(void * grBindingSelfRaw, grUiUnitSizeI grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutAbsolute::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiUnitSizeI>(grBindingArgRaw_val);
    grBindingSelf->grUiLayoutAbsolute::ElementSpec::m_y = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecf7m_widthg(grUiUnitSizeI * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutAbsolute::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutAbsolute::ElementSpec::m_width;
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecf7m_widths(void * grBindingSelfRaw, grUiUnitSizeI grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutAbsolute::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiUnitSizeI>(grBindingArgRaw_val);
    grBindingSelf->grUiLayoutAbsolute::ElementSpec::m_width = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecf8m_heightg(grUiUnitSizeI * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutAbsolute::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutAbsolute::ElementSpec::m_height;
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecf8m_heights(void * grBindingSelfRaw, grUiUnitSizeI grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutAbsolute::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiUnitSizeI>(grBindingArgRaw_val);
    grBindingSelf->grUiLayoutAbsolute::ElementSpec::m_height = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsolutec11ElementSpecn0_4t1_13grUiUnitSizeIt1_13grUiUnitSizeIt1_13grUiUnitSizeIt1_13grUiUnitSizeI(grUiUnitSizeI grBindingArgRaw_x, grUiUnitSizeI grBindingArgRaw_y, grUiUnitSizeI grBindingArgRaw_width, grUiUnitSizeI grBindingArgRaw_height) {
    auto grBindingArg_x = static_cast<grUiUnitSizeI>(grBindingArgRaw_x);
    auto grBindingArg_y = static_cast<grUiUnitSizeI>(grBindingArgRaw_y);
    auto grBindingArg_width = static_cast<grUiUnitSizeI>(grBindingArgRaw_width);
    auto grBindingArg_height = static_cast<grUiUnitSizeI>(grBindingArgRaw_height);
    auto grBindingReturnValue = gtlNew grUiLayoutAbsolute::ElementSpec(grBindingArg_x, grBindingArg_y, grBindingArg_width, grBindingArg_height);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c18grUiLayoutAbsoluten0_2t1_13grUiUnitSizeIt1_13grUiUnitSizeI(grUiUnitSizeI grBindingArgRaw_width, grUiUnitSizeI grBindingArgRaw_height) {
    auto grBindingArg_width = static_cast<grUiUnitSizeI>(grBindingArgRaw_width);
    auto grBindingArg_height = static_cast<grUiUnitSizeI>(grBindingArgRaw_height);
    auto grBindingReturnValue = gtlNew grUiLayoutAbsolute(grBindingArg_width, grBindingArg_height);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiBorderNativer() {
    return &grUiBorderNative::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiBorderNatived(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiBorderNative*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c16grUiBorderNative {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
} static grBindingProxyInfoInstance_grBinding_c16grUiBorderNative;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiBorderNativep(const grBindingProxyInfo_grBinding_c16grUiBorderNative *info) {
    grBindingProxyInfoInstance_grBinding_c16grUiBorderNative = *info;
}

class grBindingProxyClass_grBinding_c16grUiBorderNative : public grUiBorderNative {
public:
    GTL_RTTI_DECLARE();

    using grUiBorderNative::grUiBorderNative;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c16grUiBorderNative() override {
        grBindingProxyInfoInstance_grBinding_c16grUiBorderNative.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c16grUiBorderNative, GTL_RTTI_INHERITS(grUiBorderNative), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c16grUiBorderNative, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiBorderNativeg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c16grUiBorderNative*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiBorderNativex(void *self) {
    return gtlDelete static_cast<grUiBorderNative*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void *GR_BINDING_THUNK_CALLCONV grBinding_c16grUiStyleManagers() {
    return gnaSingleton<grUiStyleManager>();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiStyleManagerx(void *self) {
    return gtlDelete static_cast<grUiStyleManager*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiStyleManagern0_0() {
    auto grBindingReturnValue = gtlNew grUiStyleManager();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c16grUiStyleManagerm14findStyleSheet_1t2_3gtl13PooledAString(void * grBindingSelfRaw, const gtl::ASCIICHAR * grBindingArgRaw_name) {
    auto grBindingSelf = static_cast<grUiStyleManager *>(grBindingSelfRaw);
    auto grBindingArg_name = static_cast<gtl::PooledAString>(grBindingArgRaw_name);
    auto grBindingReturnValue = grBindingSelf->grUiStyleManager::findStyleSheet(grBindingArg_name);
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c16grUiStyleManagerm10dropCaches_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiStyleManager *>(grBindingSelfRaw);
    grBindingSelf->grUiStyleManager::dropCaches();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptyr() {
    return &grUiWidgetEmpty::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptyd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiWidgetEmpty*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c15grUiWidgetEmpty {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c15grUiWidgetEmptym14initialMeasure_1t1_3int)(grDimension * grBindingReturnPtr, void * grBindingGchRaw, int32_t grBindingArgRaw_biasedSize);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_contentBias_0)(void * grBindingGchRaw);
    uint32_t (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutFlags_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm6update_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm4tick_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16findNativeWindow_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle)(void * grBindingGchRaw, void * grBindingArgRaw_render, grRectangle grBindingArgRaw_clipRect);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm4draw_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16nativeWidgetDraw_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float)(void * grBindingGchRaw, float grBindingArgRaw_deltaTime);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19nativeWidgetPresent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer)(void * grBindingGchRaw, void * grBindingArgRaw_render);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm24get_nativeViewportWidget_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType)(grInsets * grBindingReturnPtr, void * grBindingGchRaw, int grBindingArgRaw_type);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout)(void * grBindingGchRaw, void * grBindingArgRaw_parent);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15get_layoutDirty_0)(void * grBindingGchRaw);
    const gtl::ASCIICHAR * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm16get_actualCursor_0)(void * grBindingGchRaw);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint)(void * grBindingGchRaw, grPoint grBindingArgRaw_point);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_id);
    bool (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal)(void * grBindingGchRaw, const gtl::ASCIICHAR * grBindingArgRaw_name, void * grBindingArgRaw_value);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm20updateStyleHierarchy_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm19widgetBorderChanged_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_dpi);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm12onLostParent_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c10grUiWidgetm15onBoundsChanged_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptyp(const grBindingProxyInfo_grBinding_c15grUiWidgetEmpty *info) {
    grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty = *info;
}

class grBindingProxyClass_grBinding_c15grUiWidgetEmpty : public grUiWidgetEmpty {
public:
    GTL_RTTI_DECLARE();

    using grUiWidgetEmpty::grUiWidgetEmpty;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c15grUiWidgetEmpty() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grDimension initialMeasure(int32_t grBindingArg_biasedSize) override {
        grDimension grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c15grUiWidgetEmptym14initialMeasure_1t1_3int(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_biasedSize));
        return grBindingReturnValue;
    }

    virtual grUiEnumContentBias get_contentBias() override {
        return grBindingTypeUtils<grUiEnumContentBias>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm15get_contentBias_0(grBindingGch));
    }

    virtual uint32_t get_layoutFlags() override {
        return grBindingTypeUtils<uint32_t>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm15get_layoutFlags_0(grBindingGch));
    }

    virtual void update() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm6update_0(grBindingGch);
    }

    virtual void tick(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm4tick_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual gnaWeakPointer<grUiWidget> findNativeWindow() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm16findNativeWindow_0(grBindingGch));
    }

    virtual void preDraw(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm7preDraw_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void drawClipped(grUiRenderer * grBindingArg_render, const grRectangle & grBindingArg_clipRect) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm11drawClipped_2t1_12grUiRenderert1_11grRectangle(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render), grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_clipRect));
    }

    virtual void draw(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm4draw_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual void nativeWidgetDraw() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm16nativeWidgetDraw_0(grBindingGch);
    }

    virtual void nativeWidgetPreDraw(float grBindingArg_deltaTime) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm19nativeWidgetPreDraw_1t1_5float(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_deltaTime));
    }

    virtual void nativeWidgetPresent() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm19nativeWidgetPresent_0(grBindingGch);
    }

    virtual void drawDebug(grUiRenderer * grBindingArg_render) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm9drawDebug_1t1_12grUiRenderer(grBindingGch, grBindingTypeUtils<grUiRenderer *>::translateArgFromNativeToManagedCls(grBindingArg_render));
    }

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm24get_nativeViewportWidget_0(grBindingGch));
    }

    virtual bool usesNativeChildEventBehavior() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm28usesNativeChildEventBehavior_0(grBindingGch));
    }

    virtual grInsets get_extendedInsets(grUiWidget::EnumInsetType grBindingArg_type) override {
        grInsets grBindingReturnValue;
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm18get_extendedInsets_1t2_10grUiWidget13EnumInsetType(&grBindingReturnValue, grBindingGch, grBindingTypeUtils<grUiWidget::EnumInsetType>::translateArgFromNativeToManaged(grBindingArg_type));
        return grBindingReturnValue;
    }

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm19handleParentChanged_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> grBindingArg_parent) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm18updateNativeDevice_1t1_16grUiWidgetLayout(grBindingGch, grBindingTypeUtils<gnaWeakPointer<grUiWidgetLayout>>::translateArgFromNativeToManagedCls(grBindingArg_parent));
    }

    virtual bool get_layoutDirty() override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm15get_layoutDirty_0(grBindingGch));
    }

    virtual gtl::PooledAString get_actualCursor() const override {
        return grBindingTypeUtils<gtl::PooledAString>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm16get_actualCursor_0(grBindingGch));
    }

    virtual bool hitTest(grPoint grBindingArg_point) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm7hitTest_1t1_7grPoint(grBindingGch, grBindingTypeUtils<grPoint>::translateArgFromNativeToManaged(grBindingArg_point)));
    }

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::PooledAString & grBindingArg_id) override {
        return grBindingTypeUtils<gnaWeakPointer<grUiWidget>>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm8findByID_1t2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_id)));
    }

    virtual bool applyStyleProperty(const gtl::PooledAString & grBindingArg_name, gnaWeakPointer<grUiGSSPropVal> grBindingArg_value) override {
        return grBindingTypeUtils<bool>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm18applyStyleProperty_2t2_3gtl13PooledAStringt1_14grUiGSSPropVal(grBindingGch, grBindingTypeUtils<const gtl::PooledAString &>::translateArgFromNativeToManaged(grBindingArg_name), grBindingTypeUtils<gnaWeakPointer<grUiGSSPropVal>>::translateArgFromNativeToManagedCls(grBindingArg_value)));
    }

    virtual void updateStyleHierarchy() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm20updateStyleHierarchy_0(grBindingGch);
    }

    void grBindingMemberAccessor_updateDpiScaleFactor(gnaWeakPointer<grUiWidget> grBindingArg_parent) {
        grUiWidget::updateDpiScaleFactor(grBindingArg_parent);
    }

    void grBindingMemberAccessor_set_isRootWidget(bool grBindingArg_value) {
        grUiWidget::set_isRootWidget(grBindingArg_value);
    }

    virtual void widgetBorderChanged() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm19widgetBorderChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_widgetBorderChanged() {
        grUiWidget::widgetBorderChanged();
    }

    virtual void set_dpiScaleFactor(int32_t grBindingArg_dpi) override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm18set_dpiScaleFactor_1t1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_dpi));
    }

    void grBindingMemberAccessor_set_dpiScaleFactor(int32_t grBindingArg_dpi) {
        grUiWidget::set_dpiScaleFactor(grBindingArg_dpi);
    }

    virtual void onLostParent() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm12onLostParent_0(grBindingGch);
    }

    void grBindingMemberAccessor_onLostParent() {
        grUiWidget::onLostParent();
    }

    virtual void onBoundsChanged() override {
        grBindingProxyInfoInstance_grBinding_c15grUiWidgetEmpty.grBinding_c10grUiWidgetm15onBoundsChanged_0(grBindingGch);
    }

    void grBindingMemberAccessor_onBoundsChanged() {
        grUiWidget::onBoundsChanged();
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c15grUiWidgetEmpty, GTL_RTTI_INHERITS(grUiWidgetEmpty), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c15grUiWidgetEmpty, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptyg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c15grUiWidgetEmpty*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptyx(void *self) {
    return gtlDelete static_cast<grUiWidgetEmpty*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptyn0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c15grUiWidgetEmpty();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptyn0_0() {
    auto grBindingReturnValue = gtlNew grUiWidgetEmpty();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptym14initialMeasure_1t1_3intv(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiWidgetEmpty *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptym14initialMeasure_1t1_3int(grDimension * grBindingReturnPtr, void * grBindingSelfRaw, int32_t grBindingArgRaw_biasedSize) {
    auto grBindingSelf = static_cast<grUiWidgetEmpty *>(grBindingSelfRaw);
    auto grBindingArg_biasedSize = grBindingArgRaw_biasedSize;
    auto grBindingReturnValue = grBindingSelf->grUiWidgetEmpty::initialMeasure(grBindingArg_biasedSize);
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptym20updateDpiScaleFactor_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_parent) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetEmpty *>(grBindingSelfRaw);
    auto grBindingArg_parent = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_parent);
    grBindingSelf->grBindingMemberAccessor_updateDpiScaleFactor(grBindingArg_parent);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptym16set_isRootWidget_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetEmpty *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grBindingMemberAccessor_set_isRootWidget(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptym19widgetBorderChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetEmpty *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_widgetBorderChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptym18set_dpiScaleFactor_1t1_3int(void * grBindingSelfRaw, int32_t grBindingArgRaw_dpi) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetEmpty *>(grBindingSelfRaw);
    auto grBindingArg_dpi = grBindingArgRaw_dpi;
    grBindingSelf->grBindingMemberAccessor_set_dpiScaleFactor(grBindingArg_dpi);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptym12onLostParent_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetEmpty *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onLostParent();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c15grUiWidgetEmptym15onBoundsChanged_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grBindingProxyClass_grBinding_c15grUiWidgetEmpty *>(grBindingSelfRaw);
    grBindingSelf->grBindingMemberAccessor_onBoundsChanged();
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiDragObjectr() {
    return &grUiDragObject::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c14grUiDragObjectd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiDragObject*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c14grUiDragObject {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    int (GR_BINDING_DELEGATE_CALLCONV *grBinding_c14grUiDragObjectm8get_type_0)(void * grBindingGchRaw);
} static grBindingProxyInfoInstance_grBinding_c14grUiDragObject;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiDragObjectp(const grBindingProxyInfo_grBinding_c14grUiDragObject *info) {
    grBindingProxyInfoInstance_grBinding_c14grUiDragObject = *info;
}

class grBindingProxyClass_grBinding_c14grUiDragObject : public grUiDragObject {
public:
    GTL_RTTI_DECLARE();

    using grUiDragObject::grUiDragObject;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c14grUiDragObject() override {
        grBindingProxyInfoInstance_grBinding_c14grUiDragObject.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual grUiDragObject::Type get_type() const override {
        return grBindingTypeUtils<grUiDragObject::Type>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c14grUiDragObject.grBinding_c14grUiDragObjectm8get_type_0(grBindingGch));
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c14grUiDragObject, GTL_RTTI_INHERITS(grUiDragObject), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c14grUiDragObject, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiDragObjectg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c14grUiDragObject*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c14grUiDragObjectx(void *self) {
    return gtlDelete static_cast<grUiDragObject*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c14grUiDragObjectn0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c14grUiDragObject();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT int GR_BINDING_THUNK_CALLCONV grBinding_c14grUiDragObjectm8get_type_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiDragObject *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->get_type();
    return static_cast<int>(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererr() {
    return &grUiRenderer::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiRenderer*>(self)->get_rtti();
}

struct grBindingProxyInfo_grBinding_c12grUiRenderer {
    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c12grUiRendererm10drawSprite_4t1_5floatt1_5floatt1_10grUiSpritet1_8uint32_t)(void * grBindingGchRaw, float grBindingArgRaw_ox, float grBindingArgRaw_oy, void * grBindingArgRaw_sprite, uint32_t grBindingArgRaw_tint);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c12grUiRendererm16set_uiDrawEffect_2t1_18grUiDrawEffectDatat2_3gtl13PooledAString)(void * grBindingGchRaw, grUiDrawEffectData grBindingArgRaw_effectData, const gtl::ASCIICHAR * grBindingArgRaw_pipelineName);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c12grUiRendererm12drawTriangle_7t1_5floatt1_5floatt1_5floatt1_5floatt1_5floatt1_5floatt1_8uint32_t)(void * grBindingGchRaw, float grBindingArgRaw_x0, float grBindingArgRaw_y0, float grBindingArgRaw_x1, float grBindingArgRaw_y1, float grBindingArgRaw_x2, float grBindingArgRaw_y2, uint32_t grBindingArgRaw_color);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c12grUiRendererm8pushClip_1t1_11grRectangle)(void * grBindingGchRaw, grRectangle grBindingArgRaw_rc);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c12grUiRendererm7popClip_0)(void * grBindingGchRaw);
    void (GR_BINDING_DELEGATE_CALLCONV *grBinding_c12grUiRendererm21swapCompositionLayers_0)(void * grBindingGchRaw);
    void * (GR_BINDING_DELEGATE_CALLCONV *grBinding_c12grUiRendererm26get_compositionLayerSprite_4t1_3intt1_3intt1_3intt1_3int)(void * grBindingGchRaw, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y, int32_t grBindingArgRaw_width, int32_t grBindingArgRaw_height);
} static grBindingProxyInfoInstance_grBinding_c12grUiRenderer;

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererp(const grBindingProxyInfo_grBinding_c12grUiRenderer *info) {
    grBindingProxyInfoInstance_grBinding_c12grUiRenderer = *info;
}

class grBindingProxyClass_grBinding_c12grUiRenderer : public grUiRenderer {
public:
    GTL_RTTI_DECLARE();

    using grUiRenderer::grUiRenderer;

    void *grBindingGch;

    virtual ~grBindingProxyClass_grBinding_c12grUiRenderer() override {
        grBindingProxyInfoInstance_grBinding_c12grUiRenderer.dtor(grBindingGch);
        grBindingGlobal_releaseGch(grBindingGch);
    };

    virtual void drawSprite(float grBindingArg_ox, float grBindingArg_oy, const grUiSprite & grBindingArg_sprite, uint32_t grBindingArg_tint) override {
        grBindingProxyInfoInstance_grBinding_c12grUiRenderer.grBinding_c12grUiRendererm10drawSprite_4t1_5floatt1_5floatt1_10grUiSpritet1_8uint32_t(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_ox), grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_oy), grBindingTypeUtils<const grUiSprite &>::translateArgFromNativeToManagedCls(grBindingArg_sprite), grBindingTypeUtils<uint32_t>::translateArgFromNativeToManaged(grBindingArg_tint));
    }

    virtual void set_uiDrawEffect(const grUiDrawEffectData & grBindingArg_effectData, gtl::PooledAString grBindingArg_pipelineName) override {
        grBindingProxyInfoInstance_grBinding_c12grUiRenderer.grBinding_c12grUiRendererm16set_uiDrawEffect_2t1_18grUiDrawEffectDatat2_3gtl13PooledAString(grBindingGch, grBindingTypeUtils<const grUiDrawEffectData &>::translateArgFromNativeToManaged(grBindingArg_effectData), grBindingTypeUtils<gtl::PooledAString>::translateArgFromNativeToManaged(grBindingArg_pipelineName));
    }

    virtual void drawTriangle(float grBindingArg_x0, float grBindingArg_y0, float grBindingArg_x1, float grBindingArg_y1, float grBindingArg_x2, float grBindingArg_y2, uint32_t grBindingArg_color) override {
        grBindingProxyInfoInstance_grBinding_c12grUiRenderer.grBinding_c12grUiRendererm12drawTriangle_7t1_5floatt1_5floatt1_5floatt1_5floatt1_5floatt1_5floatt1_8uint32_t(grBindingGch, grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_x0), grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_y0), grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_x1), grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_y1), grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_x2), grBindingTypeUtils<float>::translateArgFromNativeToManaged(grBindingArg_y2), grBindingTypeUtils<uint32_t>::translateArgFromNativeToManaged(grBindingArg_color));
    }

    virtual void pushClip(const grRectangle & grBindingArg_rc) override {
        grBindingProxyInfoInstance_grBinding_c12grUiRenderer.grBinding_c12grUiRendererm8pushClip_1t1_11grRectangle(grBindingGch, grBindingTypeUtils<const grRectangle &>::translateArgFromNativeToManaged(grBindingArg_rc));
    }

    virtual void popClip() override {
        grBindingProxyInfoInstance_grBinding_c12grUiRenderer.grBinding_c12grUiRendererm7popClip_0(grBindingGch);
    }

    virtual void swapCompositionLayers() override {
        grBindingProxyInfoInstance_grBinding_c12grUiRenderer.grBinding_c12grUiRendererm21swapCompositionLayers_0(grBindingGch);
    }

    virtual grUiSprite get_compositionLayerSprite(int32_t grBindingArg_x, int32_t grBindingArg_y, int32_t grBindingArg_width, int32_t grBindingArg_height) override {
        return grBindingTypeUtils<grUiSprite>::translateReturnFromManagedToNative(grBindingProxyInfoInstance_grBinding_c12grUiRenderer.grBinding_c12grUiRendererm26get_compositionLayerSprite_4t1_3intt1_3intt1_3intt1_3int(grBindingGch, grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_x), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_y), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_width), grBindingTypeUtils<int32_t>::translateArgFromNativeToManaged(grBindingArg_height)));
    }

};

GTL_RTTI_DEFINE(grBindingProxyClass_grBinding_c12grUiRenderer, GTL_RTTI_INHERITS(grUiRenderer), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_grBinding_c12grUiRenderer, grBindingGch)));

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererg(void *self, void *gch) {
    static_cast<grBindingProxyClass_grBinding_c12grUiRenderer*>(self)->grBindingGch = gch;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererx(void *self) {
    return gtlDelete static_cast<grUiRenderer*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRenderern0_0v() {
    auto grBindingReturnValue = gtlNew grBindingProxyClass_grBinding_c12grUiRenderer();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm16set_renderWidget_1t1_10grUiWidget(void * grBindingSelfRaw, void * grBindingArgRaw_renderWidget) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto grBindingArg_renderWidget = grBindingExpandWeakPtr<grUiWidget>(grBindingArgRaw_renderWidget);
    grBindingSelf->grUiRenderer::set_renderWidget(grBindingArg_renderWidget);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm16get_renderWidget_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiRenderer::get_renderWidget();
    if (grBindingReturnValue) grBindingReturnValue->addRef();
    return &*(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm10drawSprite_4t1_5floatt1_5floatt1_10grUiSpritet1_8uint32_tv(void * grBindingSelfRaw, float grBindingArgRaw_ox, float grBindingArgRaw_oy, void * grBindingArgRaw_sprite, uint32_t grBindingArgRaw_tint) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto grBindingArg_ox = grBindingArgRaw_ox;
    auto grBindingArg_oy = grBindingArgRaw_oy;
    auto grBindingArg_sprite = *static_cast<grUiSprite *>(grBindingArgRaw_sprite);
    auto grBindingArg_tint = grBindingArgRaw_tint;
    grBindingSelf->drawSprite(grBindingArg_ox, grBindingArg_oy, grBindingArg_sprite, grBindingArg_tint);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm10drawSprite_3t1_5floatt1_5floatt1_10grUiSprite(void * grBindingSelfRaw, float grBindingArgRaw_ox, float grBindingArgRaw_oy, void * grBindingArgRaw_sprite) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto grBindingArg_ox = grBindingArgRaw_ox;
    auto grBindingArg_oy = grBindingArgRaw_oy;
    auto grBindingArg_sprite = *static_cast<grUiSprite *>(grBindingArgRaw_sprite);
    grBindingSelf->grUiRenderer::drawSprite(grBindingArg_ox, grBindingArg_oy, grBindingArg_sprite);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm16set_uiDrawEffect_2t1_18grUiDrawEffectDatat2_3gtl13PooledAStringv(void * grBindingSelfRaw, grUiDrawEffectData grBindingArgRaw_effectData, const gtl::ASCIICHAR * grBindingArgRaw_pipelineName) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto grBindingArg_effectData = static_cast<grUiDrawEffectData>(grBindingArgRaw_effectData);
    auto grBindingArg_pipelineName = static_cast<gtl::PooledAString>(grBindingArgRaw_pipelineName);
    grBindingSelf->set_uiDrawEffect(grBindingArg_effectData, grBindingArg_pipelineName);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm9drawRectf_5t1_5floatt1_5floatt1_5floatt1_5floatt1_8uint32_t(void * grBindingSelfRaw, float grBindingArgRaw_x, float grBindingArgRaw_y, float grBindingArgRaw_width, float grBindingArgRaw_height, uint32_t grBindingArgRaw_color) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    auto grBindingArg_width = grBindingArgRaw_width;
    auto grBindingArg_height = grBindingArgRaw_height;
    auto grBindingArg_color = grBindingArgRaw_color;
    grBindingSelf->grUiRenderer::drawRectf(grBindingArg_x, grBindingArg_y, grBindingArg_width, grBindingArg_height, grBindingArg_color);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm17set_flipTriangles_1t1_4bool(void * grBindingSelfRaw, bool grBindingArgRaw_value) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto grBindingArg_value = grBindingArgRaw_value;
    grBindingSelf->grUiRenderer::set_flipTriangles(grBindingArg_value);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm12drawTriangle_7t1_5floatt1_5floatt1_5floatt1_5floatt1_5floatt1_5floatt1_8uint32_tv(void * grBindingSelfRaw, float grBindingArgRaw_x0, float grBindingArgRaw_y0, float grBindingArgRaw_x1, float grBindingArgRaw_y1, float grBindingArgRaw_x2, float grBindingArgRaw_y2, uint32_t grBindingArgRaw_color) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto grBindingArg_x0 = grBindingArgRaw_x0;
    auto grBindingArg_y0 = grBindingArgRaw_y0;
    auto grBindingArg_x1 = grBindingArgRaw_x1;
    auto grBindingArg_y1 = grBindingArgRaw_y1;
    auto grBindingArg_x2 = grBindingArgRaw_x2;
    auto grBindingArg_y2 = grBindingArgRaw_y2;
    auto grBindingArg_color = grBindingArgRaw_color;
    grBindingSelf->drawTriangle(grBindingArg_x0, grBindingArg_y0, grBindingArg_x1, grBindingArg_y1, grBindingArg_x2, grBindingArg_y2, grBindingArg_color);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm8pushClip_1t1_11grRectanglev(void * grBindingSelfRaw, grRectangle grBindingArgRaw_rc) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto grBindingArg_rc = static_cast<grRectangle>(grBindingArgRaw_rc);
    grBindingSelf->pushClip(grBindingArg_rc);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm7popClip_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    grBindingSelf->popClip();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm21swapCompositionLayers_0v(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    grBindingSelf->swapCompositionLayers();
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm26get_compositionLayerSprite_4t1_3intt1_3intt1_3intt1_3intv(void * grBindingSelfRaw, int32_t grBindingArgRaw_x, int32_t grBindingArgRaw_y, int32_t grBindingArgRaw_width, int32_t grBindingArgRaw_height) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto grBindingArg_x = grBindingArgRaw_x;
    auto grBindingArg_y = grBindingArgRaw_y;
    auto grBindingArg_width = grBindingArgRaw_width;
    auto grBindingArg_height = grBindingArgRaw_height;
    auto grBindingReturnValue = grBindingSelf->get_compositionLayerSprite(grBindingArg_x, grBindingArg_y, grBindingArg_width, grBindingArg_height);
    return gtlNew grUiSprite(grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT gtlMath2::Matrix3x2f & GR_BINDING_THUNK_CALLCONV grBinding_c12grUiRendererm13get_transform_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiRenderer *>(grBindingSelfRaw);
    auto & grBindingReturnValue = grBindingSelf->grUiRenderer::get_transform();
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayr() {
    return &grUiLayoutOverlay::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiLayoutOverlay*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayx(void *self) {
    return gtlDelete static_cast<grUiLayoutOverlay*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecr() {
    return &grUiLayoutOverlay::ElementSpec::st_rtti;
}

extern "C" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecd(void *self) {
    if (!self) return nullptr;
    return static_cast<grUiLayoutOverlay::ElementSpec*>(self)->get_rtti();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecx(void *self) {
    return gtlDelete static_cast<grUiLayoutOverlay::ElementSpec*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT float GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecf17relativePositionXg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutOverlay::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutOverlay::ElementSpec::relativePositionX;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecf17relativePositionXs(void * grBindingSelfRaw, float grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutOverlay::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiLayoutOverlay::ElementSpec::relativePositionX = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT float GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecf17relativePositionYg(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutOverlay::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutOverlay::ElementSpec::relativePositionY;
    return (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecf17relativePositionYs(void * grBindingSelfRaw, float grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutOverlay::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = grBindingArgRaw_val;
    grBindingSelf->grUiLayoutOverlay::ElementSpec::relativePositionY = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecf7offsetXg(grUiUnitSizeI * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutOverlay::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutOverlay::ElementSpec::offsetX;
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecf7offsetXs(void * grBindingSelfRaw, grUiUnitSizeI grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutOverlay::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiUnitSizeI>(grBindingArgRaw_val);
    grBindingSelf->grUiLayoutOverlay::ElementSpec::offsetX = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecf7offsetYg(grUiUnitSizeI * grBindingReturnPtr, void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiLayoutOverlay::ElementSpec *>(grBindingSelfRaw);
    auto grBindingReturnValue = grBindingSelf->grUiLayoutOverlay::ElementSpec::offsetY;
    *grBindingReturnPtr = (grBindingReturnValue);
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecf7offsetYs(void * grBindingSelfRaw, grUiUnitSizeI grBindingArgRaw_val) {
    auto grBindingSelf = static_cast<grUiLayoutOverlay::ElementSpec *>(grBindingSelfRaw);
    auto grBindingArg_val = static_cast<grUiUnitSizeI>(grBindingArgRaw_val);
    grBindingSelf->grUiLayoutOverlay::ElementSpec::offsetY = grBindingArg_val;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayc11ElementSpecn0_4t1_5floatt1_5floatt1_13grUiUnitSizeIt1_13grUiUnitSizeI(float grBindingArgRaw_relativePositionX, float grBindingArgRaw_relativePositionY, grUiUnitSizeI grBindingArgRaw_offsetX, grUiUnitSizeI grBindingArgRaw_offsetY) {
    auto grBindingArg_relativePositionX = grBindingArgRaw_relativePositionX;
    auto grBindingArg_relativePositionY = grBindingArgRaw_relativePositionY;
    auto grBindingArg_offsetX = static_cast<grUiUnitSizeI>(grBindingArgRaw_offsetX);
    auto grBindingArg_offsetY = static_cast<grUiUnitSizeI>(grBindingArgRaw_offsetY);
    auto grBindingReturnValue = gtlNew grUiLayoutOverlay::ElementSpec(grBindingArg_relativePositionX, grBindingArg_relativePositionY, grBindingArg_offsetX, grBindingArg_offsetY);
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c17grUiLayoutOverlayn0_0() {
    auto grBindingReturnValue = gtlNew grUiLayoutOverlay();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void *GR_BINDING_THUNK_CALLCONV grBinding_c24grUiMultipatchImageCaches() {
    return gnaSingleton<grUiMultipatchImageCache>();
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c24grUiMultipatchImageCachex(void *self) {
    return gtlDelete static_cast<grUiMultipatchImageCache*>(self);
}

extern "C" GR_BINDING_THUNK_EXPORT void * GR_BINDING_THUNK_CALLCONV grBinding_c24grUiMultipatchImageCachen0_0() {
    auto grBindingReturnValue = gtlNew grUiMultipatchImageCache();
    return grBindingReturnValue;
}

extern "C" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBinding_c24grUiMultipatchImageCachem10dropCaches_0(void * grBindingSelfRaw) {
    auto grBindingSelf = static_cast<grUiMultipatchImageCache *>(grBindingSelfRaw);
    grBindingSelf->grUiMultipatchImageCache::dropCaches();
}

