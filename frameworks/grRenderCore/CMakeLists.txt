cmake_minimum_required(VERSION 3.17)

include(StaticExportAll)

add_library(grRenderCore ${GROVE2_LINK_TYPE}
        grRenderCore/RenderCoreDLL.h
        grRenderCore/Pipeline/PipelineObject.cpp
        grRenderCore/Pipeline/PipelineObject.h
        grRenderCore/Pipeline/PipelineLibrary.cpp
        grRenderCore/Pipeline/PipelineLibrary.h
        grRenderCore/RenderInterface.h
        grRenderCore/RenderTarget/RenderTargetSet.h
        grRenderCore/Mesh/VertexFormat.h
        grRenderCore/Mesh/Mesh.cpp
        grRenderCore/Mesh/Mesh.h
        grRenderCore/Mesh/Mesh.h
        grRenderCore/Mesh/Mesh.cpp
        grRenderCore/ConstantBuffer/ConstantBuffer.h
        grRenderCore/CmdList/CmdListEmitter.h
        grRenderCore/CmdList/CmdList.h
        grRenderCore/CmdList/CmdConstants.h
        grRenderCore/RenderTypes.h
        grRenderCore/Stats/RenderStats.cpp
        grRenderCore/Stats/RenderStats.h
        grRenderCore/RenderPass/RenderPass.h
        grRenderCore/RenderPass/RenderPass.cpp
        grRenderCore/RenderInterface.cpp
        grRenderCore/VideoOutput/VideoOutput.h
        grRenderCore/VideoOutput/VideoOutputManager.h
        grRenderCore/Mesh/InstancedMesh.cpp
        grRenderCore/Mesh/InstancedMesh.h
        grRenderCore/Mesh/Renderable.h
        grRenderCore/Sampler/SamplerProperties.h
        grRenderCore/Sampler/Sampler.h
        grRenderCore/Mesh/Renderable.cpp
        grRenderCore/RenderCoreModule.cpp
        grRenderCore/RenderCoreModule.h
        grRenderCore/Pipeline/PipelineEnums.h)


target_include_directories(grRenderCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(grRenderCore PUBLIC gtl grImg gtlMath2)

target_compile_definitions(grRenderCore PRIVATE _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(grRenderCore INTERFACE GROVE2_IMPORT_MODULE_grRenderCore)

if(GROVE2_LINK_TYPE STREQUAL "SHARED")
    target_compile_definitions(grRenderCore PRIVATE GR_RENDERCORE_BUILD_DLL GROVE2_BUILDING_MODULE_AS_DLL)
    target_compile_definitions(grRenderCore INTERFACE GR_RENDERCORE_LOAD_DLL GROVE2_IMPORT_DLL_MODULE_grRenderCore)
endif()

if(GROVE2_LINK_TYPE STREQUAL "STATIC")
    gbuild_StaticExportAll(grRenderCore)
endif()
