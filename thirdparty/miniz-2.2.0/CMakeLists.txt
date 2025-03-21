cmake_minimum_required(VERSION 3.17)

add_library(miniz miniz.c miniz.h)

target_include_directories(miniz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
