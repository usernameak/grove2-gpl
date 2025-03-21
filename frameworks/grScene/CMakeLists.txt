cmake_minimum_required(VERSION 3.17)

add_library(grScene SHARED
        grScene/Material/MaterialInstance.h
        grScene/Material/MaterialInstance.cpp
        grScene/SceneGeom.h
        grScene/SceneGeom.cpp
        grScene/SceneObject.h
        grScene/SceneObject.cpp
        grScene/SceneNode.h
        grScene/SceneNode.cpp
        grScene/SceneEmpty.h
        grScene/SceneEmpty.cpp
        grScene/Camera.h
        grScene/Camera.cpp
        grScene/SceneDLL.h
        grScene/Scene_StaticInit.h
        grScene/Scene_StaticInit.cpp
        grScene/Light/SceneLight.cpp
        grScene/Light/SceneLight.h
        grScene/Scene.cpp
        grScene/Scene.h)

target_include_directories(grScene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(grScene PUBLIC grImg grRenderCore)

target_compile_definitions(grScene PRIVATE _CRT_SECURE_NO_WARNINGS GR_SCENE_BUILD_DLL)
target_compile_definitions(grScene INTERFACE GR_SCENE_LOAD_DLL)
