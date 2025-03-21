cmake_minimum_required(VERSION 3.17)

add_library(grBindingImg ${GROVE2_LINK_TYPE} Binding.cpp)

if (MSVC)
    target_compile_options(grBindingImg PRIVATE -w)
endif ()

if (GROVE2_LINK_TYPE STREQUAL "STATIC")
    gbuild_StaticExportAll(grBindingImg)
endif ()

target_compile_definitions(grBindingImg PRIVATE _CRT_SECURE_NO_WARNINGS)
set_target_properties(grBindingImg PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(grBindingImg PRIVATE grImg grBinding)
