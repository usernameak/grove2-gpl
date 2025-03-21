struct InputData {
    float4 svPosition : SV_Position;
    float4 vShadowmapPos : POSITION1;
#ifdef GR_VERTEXFORMAT_TEXCOORD
    float2 vTexCoord : TEXCOORD0;
#endif
#ifdef GR_VERTEXFORMAT_NORMAL
    float3 vNormal : NORMAL0;
#endif
#ifdef GR_VERTEXFORMAT_COLOR
    float4 vColor : COLOR0;
#endif
};

struct OutputData {
    float4 fragColor : SV_Target0;
};

#ifdef GR_VERTEXFORMAT_TEXCOORD
Texture2D textureBaseColor : register(t0);
SamplerState textureBaseColorSampler : register(s0);
#endif

cbuffer ObjectUniforms : register(b1) {
    float4 materialColor;
};

OutputData main(InputData inputData) {
    OutputData outputData;
    outputData.fragColor = materialColor;
#ifdef GR_VERTEXFORMAT_TEXCOORD
    outputData.fragColor *= textureBaseColor.Sample(textureBaseColorSampler, inputData.vTexCoord);
#endif
#ifdef GR_VERTEXFORMAT_COLOR
    outputData.fragColor *= inputData.vColor;
#endif

    if(outputData.fragColor.a <= 0.01) discard;
    return outputData;
}