cmake_minimum_required(VERSION 3.17)

add_library(
        grMain

        "grMain.cpp"
        "grMain.h" )

target_include_directories(grMain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(grMain PUBLIC gtl)
