cmake_minimum_required(VERSION 3.17)

add_executable(
        textool

        "textool.cpp")

target_include_directories(textool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(textool PUBLIC gtl miniz grMain grImg)
