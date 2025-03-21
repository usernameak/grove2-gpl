cmake_minimum_required(VERSION 3.17)

add_library(gtlMath2 ${GROVE2_LINK_TYPE}
        gtlMath2/Matrix/Matrix3x2.h
        gtlMath2/Vector/Vector3.h
        gtlMath2/Vector/Vector2.h
        gtlMath2/Vector/Vector4.h
        gtlMath2/MathUtils.h
        gtlMath2/Vector/VectorTraits.h
        gtlMath2/Vector/VectorSerializers.h
        gtlMath2/Vector/VectorCommon.h
        gtlMath2/Transform/Transform.cpp
        gtlMath2/Transform/Transform.h
        gtlMath2/Quaternion/Quaternion.h
        gtlMath2/Transform/TransformSerializers.h
        gtlMath2/Quaternion/QuaternionSerializers.h
        gtlMath2/Matrix/Matrix4x4.h
        gtlMath2/Matrix/Matrix4x3.h
        gtlMath2/Math2DLL.h)

target_sources(gtlMath2 PUBLIC gtlMath2/gtlMath2.natvis)

target_compile_definitions(gtlMath2 PUBLIC NOMINMAX)
target_include_directories(gtlMath2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gtlMath2 PUBLIC gtl)

if(GROVE2_LINK_TYPE STREQUAL "SHARED")
    target_compile_definitions(gtlMath2 PRIVATE GTL_MATH2_BUILD_DLL)
    target_compile_definitions(gtlMath2 INTERFACE GTL_MATH2_LOAD_DLL)
endif()
