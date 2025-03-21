#include "common.inc.hlsl"

struct InputData {
    float3 position : POSITION0;
#ifdef GR_VERTEXFORMAT_TEXCOORD
    float2 texCoord : TEXCOORD0;
#endif
#ifdef GR_VERTEXFORMAT_NORMAL
    float3 normal : NORMAL0;
#ifdef GR_VERTEXFORMAT_TANGENT
    float4 tangent : TANGENT0;
#endif
#endif
#ifdef GR_VERTEXFORMAT_COLOR
    float4 color : COLOR0;
#endif
    float3x4 modelMatrix : POSITION1;
};

struct OutputData {
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

OutputData main(InputData inputData) {
    OutputData outputData;
#ifdef GR_VERTEXFORMAT_TEXCOORD
    outputData.vTexCoord = inputData.texCoord;
#endif
    float4x3 modelMatrix = transpose(inputData.modelMatrix);
#ifdef GR_VERTEXFORMAT_NORMAL
    float3x3 normalMatrix = (float3x3) modelMatrix;
    outputData.vNormal = normalize(mul(normalMatrix, inputData.normal));
#ifdef GR_VERTEXFORMAT_TANGENT
    outputData.vTangent = normalize(mul(normalMatrix, inputData.tangent.xyz));
    outputData.vBitangent = normalize(mul(normalMatrix, cross(inputData.normal, inputData.tangent.xyz) * inputData.tangent.w));
#endif
#endif
#ifdef GR_VERTEXFORMAT_COLOR
    outputData.vColor = inputData.color;
#endif
    float3 modelPosition = mul(float4(inputData.position, 1.0), modelMatrix);
    outputData.svPosition = mul(viewProjectionMatrix, float4(modelPosition, 1.0));
    outputData.vShadowmapPos = mul(shadowmapMatrix, float4(modelPosition, 1.0));
    return outputData;
}
