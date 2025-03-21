#ifndef __COMMON_INC_HLSL__
#define __COMMON_INC_HLSL__

static const uint MAX_LIGHTS = 16;

cbuffer SceneUniforms : register(b0) {
    float4x4 viewProjectionMatrix;
    float4x4 shadowmapMatrix;
};

cbuffer ObjectUniforms : register(b1) {
    float4 materialColor;
};

struct LightUniforms {
    float4 lightColor;
    float4 lightDir;
    uint4 typeInfo;
};

cbuffer LightsUniforms : register(b2) {
    LightUniforms lights[MAX_LIGHTS];
};

#endif
