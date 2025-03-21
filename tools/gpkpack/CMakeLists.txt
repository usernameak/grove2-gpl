cmake_minimum_required(VERSION 3.17)

add_executable(
        gpkpack

        "gpkpack/gpkpack.cpp")
        
target_include_directories(gpkpack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gpkpack PUBLIC gtl miniz grMain)
