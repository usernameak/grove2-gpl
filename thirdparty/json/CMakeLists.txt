cmake_minimum_required(VERSION 3.17)

add_library(nlohmann_json OBJECT "nlohmann/json.hpp")

set_target_properties(nlohmann_json PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(nlohmann_json PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})