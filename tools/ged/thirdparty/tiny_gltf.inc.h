#pragma once

#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_EXTERNAL_IMAGE
#define TINYGLTF_USE_CPP14
#define TINYGLTF_NO_INCLUDE_JSON
#undef snprintf
#include <cstdio>
#include <nlohmann/json.hpp>
#include <thirdparty/tiny_gltf.h>
