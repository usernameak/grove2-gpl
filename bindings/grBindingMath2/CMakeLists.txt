cmake_minimum_required(VERSION 3.17)

add_library(grBindingMath2 ${GROVE2_LINK_TYPE} Binding.cpp)

if (MSVC)
    target_compile_options(grBindingMath2 PRIVATE -w)
endif ()

if (GROVE2_LINK_TYPE STREQUAL "STATIC")
    gbuild_StaticExportAll(grBindingMath2)
endif ()

target_compile_definitions(grBindingMath2 PRIVATE _CRT_SECURE_NO_WARNINGS)
set_target_properties(grBindingMath2 PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(grBindingMath2 PRIVATE gtlMath2 grBinding)
