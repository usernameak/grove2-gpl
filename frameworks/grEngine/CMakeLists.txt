cmake_minimum_required(VERSION 3.17)

add_library(
        grEngine SHARED
        
         "grEngine/Engine.h"
         "grEngine/Engine.cpp"
         "grEngine/IEngineApplication.h"
        "grEngine/EngineDLL.h")
        
target_include_directories(grEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(grEngine PUBLIC gtl)

if(WIN32)
    target_sources(
        grEngine PRIVATE

        "grEngine/EngineW32.h"
        "grEngine/EngineW32.cpp"
    )
endif()

target_compile_definitions(grEngine PRIVATE _CRT_SECURE_NO_WARNINGS GR_ENGINE_BUILD_DLL)
target_compile_definitions(grEngine INTERFACE GR_ENGINE_LOAD_DLL)
