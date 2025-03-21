cmake_minimum_required(VERSION 3.17)

add_library(grBindingUi ${GROVE2_LINK_TYPE} Binding.cpp)

if (MSVC)
    target_compile_options(grBindingUi PRIVATE -w)
endif ()

if (GROVE2_LINK_TYPE STREQUAL "STATIC")
    gbuild_StaticExportAll(grBindingUi)
endif ()

target_compile_definitions(grBindingUi PRIVATE _CRT_SECURE_NO_WARNINGS)
set_target_properties(grBindingUi PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(grBindingUi PRIVATE grUi grBinding)
