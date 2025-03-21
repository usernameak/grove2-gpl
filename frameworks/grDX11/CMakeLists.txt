cmake_minimum_required(VERSION 3.17)

if (WIN32)
    include(GroveServiceManifest)

    add_library(grDX11 SHARED
            grDX11/DX11RenderInterface.cpp
            grDX11/DX11RenderInterface.h
            grDX11/VideoOutputManager.cpp
            grDX11/VideoOutputManager.h
            grDX11/PipelineObject.cpp
            grDX11/PipelineObject.h
            grDX11/DX11DLL.h
            grDX11/PipelineRenderObject.cpp
            grDX11/PipelineRenderObject.h
            grDX11/RenderTargetSet.cpp
            grDX11/RenderTargetSet.h
            grDX11/ImageRenderData.cpp
            grDX11/ImageRenderData.h
            grDX11/CmdList.cpp
            grDX11/CmdList.h
            grDX11/DX11MeshRenderer.cpp
            grDX11/DX11MeshRenderer.h
            grDX11/ConstBuffer.cpp
            grDX11/ConstBuffer.h
            grDX11/Sampler.cpp
            grDX11/Sampler.h
            grDX11/DX11Module.cpp
            grDX11/DX11Module.h
            grDX11/StateCaches.cpp
            grDX11/StateCaches.h)

    add_subdirectory(dx11plcc)

    target_include_directories(grDX11 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(grDX11 PUBLIC grRenderCore gtl)

    target_compile_definitions(grDX11 PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(grDX11 INTERFACE GROVE2_IMPORT_MODULE_grDX11)

    if(GROVE2_LINK_TYPE STREQUAL "SHARED")
        target_compile_definitions(grDX11 PRIVATE GR_DX11_BUILD_DLL GROVE2_BUILDING_MODULE_AS_DLL)
        target_compile_definitions(grDX11 INTERFACE GR_DX11_LOAD_DLL GROVE2_IMPORT_DLL_MODULE_grDX11)
    endif()

    gbuild_CreateServiceManifest(grDX11 RenderInterface)
endif ()