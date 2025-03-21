cmake_minimum_required(VERSION 3.17)

add_library(grUiNative SHARED    
	"grUiNative/Manager/UiManager.h"
    "grUiNative/Manager/UiManager.cpp"

	"grUiNative/Render/UiRendererImpl.h"
	"grUiNative/Render/UiRendererImpl.cpp"

	"grUiNative/UiNativeDLL.h"

	"grUiNative/Device/NativePlatformDeviceImpl.h"
	"grUiNative/Device/NativePlatformDeviceImpl.cpp"

	"grUiNative/WidgetImpl/NativeFramePlatformW32.h"
	"grUiNative/WidgetImpl/NativeFramePlatformW32.cpp"
	"grUiNative/WidgetImpl/NativeDropSourceW32.h"
	"grUiNative/WidgetImpl/NativeDropSourceW32.cpp" 
	"grUiNative/WidgetImpl/NativeDropDataObjectW32.h" 
	"grUiNative/WidgetImpl/NativeDropDataObjectW32.cpp"
	"grUiNative/WidgetImpl/NativeDropTargetW32.h"
	"grUiNative/WidgetImpl/NativeDropTargetW32.cpp"

    "grUiNative/Widget/Widget3DView.h"
    "grUiNative/Widget/Widget3DView.cpp"
		grUiNative/WidgetImpl/NativeFramePlatformShared.h)

target_include_directories(grUiNative PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(grUiNative PUBLIC grUi grEngine grRenderCore)

target_compile_definitions(grUiNative PRIVATE _CRT_SECURE_NO_WARNINGS GR_UI_NATIVE_BUILD_DLL)
target_compile_definitions(grUiNative INTERFACE GR_UI_NATIVE_LOAD_DLL)
