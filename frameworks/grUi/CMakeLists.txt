cmake_minimum_required(VERSION 3.17)

add_library(grUi ${GROVE2_LINK_TYPE}
        grUi.natvis
        "grUi/UiDLL.h"

        grUi/Style/Background/BackgroundBase.h
        grUi/Style/Background/Background.h
        grUi/Style/Background/Background.cpp
        grUi/Style/Background/BackgroundMultipatch.cpp
        grUi/Style/Background/BackgroundMultipatch.h

        grUi/Style/Border/BorderBase.h
        grUi/Style/Border/Border.h
        grUi/Style/Border/Border.cpp
        grUi/Style/Border/BorderMultipatch.h
        grUi/Style/Border/BorderNative.h

        "grUi/Widget/Widget.h"
        "grUi/Widget/Widget.cpp"
        "grUi/Widget/WidgetLayout.h"
        "grUi/Widget/WidgetLayout.cpp"
        "grUi/Widget/WidgetText.h"
        "grUi/Widget/WidgetText.cpp"
        "grUi/Widget/WidgetTextField.cpp"
        "grUi/Widget/WidgetTextField.h"
        "grUi/Widget/WidgetButton.h" 
        "grUi/Widget/WidgetButton.cpp"
        "grUi/Widget/WidgetScrollPane.h" 
        "grUi/Widget/WidgetScrollPane.cpp"
        "grUi/Widget/WidgetEmpty.h"
        "grUi/Widget/WidgetEmpty.cpp"
        "grUi/Widget/WidgetCheckbox.h" 
        "grUi/Widget/WidgetCheckbox.cpp" 
        "grUi/Widget/DropDownMenu.cpp" 
        "grUi/Widget/DropDownMenu.h"
        "grUi/Widget/ListWidget.cpp"
        "grUi/Widget/ListWidget.h"

        "grUi/Widget/Window/RootWindowManager.h" 
        "grUi/Widget/Window/RootWindowManager.cpp" 
        "grUi/Widget/Window/WindowManager.h"
        "grUi/Widget/Window/WindowManager.cpp"
        "grUi/Widget/Window/Frame.h"
        "grUi/Widget/Window/Frame.cpp"
        
        "grUi/Widget/Native/NativeFramePlatform.h"
        
        "grUi/Render/UiRenderer.h"

        "grUi/Layout/Layout.h"
        "grUi/Layout/LayoutLinear.h" 
        "grUi/Layout/LayoutLinear.cpp" 

        "grUi/Font/FontCache.h" 
        "grUi/Font/FontCache.cpp"
        "grUi/Font/FontRenderer.h"
        "grUi/Font/FontRenderer.cpp"
        
        "grUi/Utils/ClipboardManager.cpp"
        "grUi/Utils/ClipboardManager.h"
        "grUi/Utils/Sprite.h" 
        "grUi/Utils/Sprite.cpp"
        "grUi/Utils/DoubleClickEventSink.h"
        "grUi/Utils/DoubleClickEventSink.cpp"
        "grUi/Utils/UiTime.h" 
        "grUi/Utils/UiTime.cpp" 
        "grUi/Utils/Keycode.h"
        grUi/Utils/MultipatchImage.cpp
        grUi/Utils/MultipatchImage.h
        grUi/Utils/MultipatchImageCache.cpp
        grUi/Utils/MultipatchImageCache.h

        "grUi/Drag/DragContext.h"
        "grUi/Drag/DragObject.h"

        "grUi/Event/UIEvents.h"

        "grUi/GUI_Module.cpp"

        "grUi/Layout/LayoutOverlay.cpp"
        "grUi/Layout/LayoutOverlay.h"
        
        "grUi/Native/NativePlatformDevice.h"
        grUi/Widget/Window/FrameBorderInterface.h
        grUi/Widget/Window/FrameCaptionInterface.h
        grUi/Style/StyleManager.cpp
        grUi/Style/StyleManager.h
        grUi/Layout/LayoutGrid.cpp
        grUi/Layout/LayoutGrid.h

        "grUi/Utils/DragOrClick.cpp"
        "grUi/Utils/DragOrClick.h"
        grUi/Text/SpannedText.h
        grUi/Text/TextRenderer.cpp
        grUi/Text/TextRenderer.h
        grUi/Widget/WidgetTooltip.cpp
        grUi/Widget/WidgetTooltip.h
        grUi/Utils/UnitSize.h
        grUi/Widget/WidgetTabbedPane.cpp
        grUi/Widget/WidgetTabbedPane.h
        grUi/Layout/LayoutEnums.h
        grUi/Layout/LayoutAbsolute.cpp
        grUi/Layout/LayoutAbsolute.h
        grUi/Render/UiRenderer.cpp
        grUi/Widget/WidgetIconText.cpp
        grUi/Widget/WidgetIconText.h
        grUi/Widget/WidgetComboBox.cpp
        grUi/Widget/WidgetComboBox.h
        grUi/Widget/WidgetScrollBar.cpp
        grUi/Widget/WidgetScrollBar.h
        grUi/Widget/WidgetRichTextField.cpp
        grUi/Widget/WidgetRichTextField.h
        grUi/Widget/WidgetTableLayout.cpp
        grUi/Widget/WidgetTableLayout.h
        grUi/Style/GSS/Parser.cpp
        grUi/Style/GSS/Parser.h
        grUi/Style/GSS/Selector.h
        grUi/Style/GSS/Rule.h
        grUi/Style/GSS/Tokenizer.cpp
        grUi/Style/GSS/Tokenizer.h
        grUi/Style/GSS/Props/PropVal.h
        grUi/Style/GSS/Props/Background.cpp
        grUi/Style/GSS/Props/Background.h
        grUi/Style/GSS/Utils.cpp
        grUi/Style/GSS/Utils.h
        grUi/Style/GSS/StyleSheet.cpp
        grUi/Style/GSS/StyleSheet.h
        grUi/Style/GSS/Props/Color.cpp
        grUi/Style/GSS/Props/Color.h
        grUi/Style/GSS/Props/PropVal.cpp
        grUi/Style/GSS/Props/Border.cpp
        grUi/Style/GSS/Props/Border.h
        grUi/Style/GSS/Props/Unit.cpp
        grUi/Style/GSS/Props/Unit.h
        grUi/Style/GSS/Props/Helpers.cpp
        grUi/Style/GSS/Props/Helpers.h
        grUi/Style/GSS/Props/TextAlign.cpp
        grUi/Style/GSS/Props/TextAlign.h
        grUi/Style/GSS/Props/Icon.cpp
        grUi/Style/GSS/Props/Icon.h
        grUi/Style/GSS/Props/Font.cpp
        grUi/Style/GSS/Props/Font.h
        grUi/Style/Background/BackgroundBase.cpp
        grUi/Style/Border/BorderBase.cpp
        grUi/Style/Border/BorderMultipatch.cpp
        grUi/Style/Border/BorderNative.cpp
        grUi/Style/GSS/Props/Padding.cpp
        grUi/Style/GSS/Props/Padding.h
        grUi/GUI_Module.h
        grUi/Layout/Layout.cpp
        grUi/Native/NativePlatformDevice.cpp
        grUi/Widget/Native/NativeFramePlatform.cpp
        grUi/Drag/DragContext.cpp
        grUi/Drag/DragObject.cpp
        grUi/Widget/WidgetImage.cpp
        grUi/Widget/WidgetImage.h
        grUi/Text/TextLayout.h)

target_include_directories(grUi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(grUi PUBLIC gtlMath2 grImg nlohmann_json tsl::ordered_map)

target_compile_definitions(grUi PRIVATE _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(grUi INTERFACE GROVE2_IMPORT_MODULE_grUi)

if(GROVE2_LINK_TYPE STREQUAL "SHARED")
    target_compile_definitions(grUi PRIVATE GR_UI_BUILD_DLL GROVE2_BUILDING_MODULE_AS_DLL)
    target_compile_definitions(grUi INTERFACE GR_UI_LOAD_DLL GROVE2_IMPORT_DLL_MODULE_grUi)
endif()

enable_testing()
add_subdirectory(tests)
