#ifndef __SHADOWMAP_INC_HLSL__
#define __SHADOWMAP_INC_HLSL__

#ifdef USE_SHADOWMAP

Texture2D textureShadowMap : register(t3);
SamplerComparisonState textureShadowMapSampler : register(s3);

float ProcessShadowmap(in float4 posShadowmap) {
    float2 ShadowTexC = float2(0.5, -0.5) * posShadowmap.xy / posShadowmap.w + float2(0.5, 0.5);

    float actualDepthValue = posShadowmap.z / posShadowmap.w;

    return textureShadowMap.SampleCmp(textureShadowMapSampler, ShadowTexC, actualDepthValue);
}

#else
float ProcessShadowmap(in float4 posShadowmap) {
    return 1.0;
}
#endif

#endif