cmake_minimum_required(VERSION 3.17)

add_library(grBinding ${GROVE2_LINK_TYPE} Binding.cpp grBinding/BindingSupport.h grBinding/BindingSupport.cpp)

if (MSVC)
    target_compile_options(grBinding PRIVATE -w)
endif ()

target_compile_definitions(grBinding PRIVATE _CRT_SECURE_NO_WARNINGS)
set_target_properties(grBinding PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(grBinding PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if (GROVE2_LINK_TYPE STREQUAL "SHARED")
    target_compile_definitions(grBinding PRIVATE GR_BINDING_BUILD_DLL)
    target_compile_definitions(grBinding INTERFACE GR_BINDING_LOAD_DLL)
elseif(GROVE2_LINK_TYPE STREQUAL "STATIC")
    gbuild_StaticExportAll(grBinding)
endif ()

target_link_libraries(grBinding PRIVATE gtl)

option(GR_BINDING_BUILD_SINGLE_DLL "Build a single binding DLL" OFF)

if (GR_BINDING_BUILD_SINGLE_DLL)
    add_library(grBindingSingleDLL SHARED dummy.cpp)
    set_target_properties(grBindingSingleDLL PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(grBindingSingleDLL PRIVATE grBinding grBindingImg grBindingUi grBindingMath2)
endif ()
