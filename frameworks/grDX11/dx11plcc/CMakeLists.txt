cmake_minimum_required(VERSION 3.17)

add_executable(dx11plcc main.cpp)

target_include_directories(dx11plcc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dx11plcc PUBLIC gtl grMain grRenderCore d3dcompiler nlohmann_json grDX11)
target_compile_definitions(dx11plcc PRIVATE NOMINMAX)
