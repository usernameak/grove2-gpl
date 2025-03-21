cmake_minimum_required(VERSION 3.17)

include(StaticExportAll)

add_library(grRenderView
        grRenderView/Render/RenderPassView.h
        grRenderView/Render/RenderPassView.cpp
        grRenderView/Render/RenderPassShadowView.cpp
        grRenderView/Render/RenderPassShadowView.h)

target_include_directories(grRenderView PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(grRenderView PUBLIC grRenderCore grScene)

if(GROVE2_LINK_TYPE STREQUAL "STATIC")
    gbuild_StaticExportAll(grRenderView)
endif()
