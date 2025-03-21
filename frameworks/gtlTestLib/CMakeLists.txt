cmake_minimum_required(VERSION 3.17)

add_library(gtlTestLib STATIC
        testutils.h
        testutils.cpp
        testMockResMgr.cpp
        testMockResMgr.h)
set_target_properties(gtlTestLib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(gtlTestLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gtlTestLib PUBLIC gtl)

target_compile_definitions(gtlTestLib PRIVATE _CRT_SECURE_NO_WARNINGS)
