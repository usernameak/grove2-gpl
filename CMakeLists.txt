cmake_minimum_required(VERSION 3.17)

project(GroveEngine2)

enable_testing()

if(MSVC)
add_compile_options(/wd26812 /we4541)
endif()
#if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#add_compile_options(-flto)
#add_link_options(-flto)
#endif()

find_package(ICU REQUIRED COMPONENTS uc data i18n)

add_link_options("$<$<CONFIG:RelWithDebInfo>:/INCREMENTAL:NO>")

set(GROVE2_LINK_TYPE SHARED CACHE STRING "Grove Engine 2 library type")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)
set(GROVE2_DIST_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/dist")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GROVE2_DIST_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GROVE2_DIST_DIRECTORY})
set(CMAKE_PDB_OUTPUT_DIRECTORY "${GROVE2_DIST_DIRECTORY}/DebugInfo")

add_subdirectory(thirdparty/json)
add_subdirectory(thirdparty/miniz-2.2.0)
add_subdirectory(thirdparty/ordered-map-1.1.0)

add_subdirectory(frameworks/gtl)
add_subdirectory(frameworks/gtlMath2)
add_subdirectory(frameworks/grEngine)
add_subdirectory(frameworks/grImg)
add_subdirectory(frameworks/grRenderCore)
add_subdirectory(frameworks/grUi)
add_subdirectory(frameworks/grUiNative)
add_subdirectory(frameworks/grApplication)
add_subdirectory(frameworks/grRenderView)
add_subdirectory(frameworks/grScene)
add_subdirectory(frameworks/grMain)
add_subdirectory(frameworks/grDX11)
add_subdirectory(frameworks/grGitRevision)
add_subdirectory(frameworks/gtlTestLib)

add_subdirectory(tools/ged)
add_subdirectory(tools/gpkpack)
add_subdirectory(tools/textool)

add_subdirectory(bindings/grBinding)
add_subdirectory(bindings/grBindingUi)
add_subdirectory(bindings/grBindingImg)
add_subdirectory(bindings/grBindingMath2)
