cmake_minimum_required(VERSION 3.17)

add_library(grImg ${GROVE2_LINK_TYPE}
        thirdparty/stb_image.h

        grImg/Image.h
        grImg/Image.cpp
        grImg/ImgDLL.h

        grImg/Loaders/ImageLoaderSTBI.h
        grImg/Loaders/ImageLoaderSTBI.cpp
        grImg/Loaders/ImageLoaderDDS.cpp
        grImg/Loaders/ImageLoaderDDS.h
        grImg/ImgModule.cpp
        grImg/ImgModule.h)

target_include_directories(grImg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(grImg gtl)

target_compile_definitions(grImg PRIVATE _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(grImg INTERFACE GROVE2_IMPORT_MODULE_grImg)

if(GROVE2_LINK_TYPE STREQUAL "SHARED")
    target_compile_definitions(grImg PRIVATE GR_IMG_BUILD_DLL GROVE2_BUILDING_MODULE_AS_DLL)
    target_compile_definitions(grImg INTERFACE GR_IMG_LOAD_DLL GROVE2_IMPORT_DLL_MODULE_grImg)
endif()
