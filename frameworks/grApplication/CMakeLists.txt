cmake_minimum_required(VERSION 3.17)

add_library(
        grApplication

        "grApplication.cpp"
        "grApplication.h")
        
target_include_directories(grApplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(grApplication PUBLIC grUi grUiNative gtl grEngine grRenderCore)
add_dependencies(grApplication grDX11)
