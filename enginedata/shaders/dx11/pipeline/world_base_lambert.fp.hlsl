#define USE_SHADOWMAP

#include "common.inc.hlsl"
#include "shadowmap.inc.hlsl"

struct InputData {
    float4 svPosition : SV_Position;
    float4 vShadowmapPos : POSITION1;
#ifdef GR_VERTEXFORMAT_TEXCOORD
    float2 vTexCoord : TEXCOORD0;
#endif
#ifdef GR_VERTEXFORMAT_NORMAL
    float3 vNormal : NORMAL0;

    // FIXME: somehow disable the permutation with tangent but no normal
#ifdef GR_VERTEXFORMAT_TANGENT
    float3 vTangent : TANGENT0;
    float3 vBitangent : BITANGENT0;
#endif

#endif
#ifdef GR_VERTEXFORMAT_COLOR
    float4 vColor : COLOR0;
#endif
};

struct OutputData {
    float4 fragColor : SV_Target0;
};

Texture2D textureBaseColor : register(t0);
Texture2D textureNormal : register(t1);
SamplerState textureBaseColorSampler : register(s0);
SamplerState textureNormalSampler : register(s1);

OutputData main(InputData inputData) {
    OutputData outputData;

    float4 baseColor = materialColor;
#ifdef GR_VERTEXFORMAT_TEXCOORD
    baseColor *= textureBaseColor.Sample(textureBaseColorSampler, inputData.vTexCoord);
#endif
#ifdef GR_VERTEXFORMAT_COLOR
    baseColor *= inputData.vColor;
#endif
    float4 finalColor = float4(0.0, 0.0, 0.0, baseColor.a);
    finalColor.rgb += baseColor.rgb * 0.025; // ambient light

#if defined(GR_VERTEXFORMAT_TANGENT) && defined(GR_VERTEXFORMAT_TEXCOORD)
    float3x3 tbn = float3x3(inputData.vTangent, inputData.vBitangent, inputData.vNormal);
    float3 normal = textureNormal.Sample(textureNormalSampler, inputData.vTexCoord).xyz;
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(mul(normal, tbn));
#else
    float3 normal = inputData.vNormal;
#endif

    for (uint i = 0; i < MAX_LIGHTS; i++) {
        if (lights[i].typeInfo.x == 0) {
            break;
        } else if (lights[i].typeInfo.x == 1) { // directional light
            float3 L = lights[i].lightDir.xyz;
            float NdotL = ProcessShadowmap(inputData.vShadowmapPos) * saturate(dot(normal, L));
            finalColor.rgb += baseColor.rgb * NdotL;
        }
    }

    outputData.fragColor = finalColor;
    // outputData.fragColor = float4(normal.xyz * 0.5 + 0.5, 1.0);
    return outputData;
}