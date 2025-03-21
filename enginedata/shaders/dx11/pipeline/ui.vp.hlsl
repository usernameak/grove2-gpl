struct InputData {
    float3 position : POSITION0;
    float2 texCoord : TEXCOORD0;
    float4 color : COLOR0;
};

struct OutputData {
    float4 svPosition : SV_Position;
    float2 vTexCoord : TEXCOORD0;
    float4 vColor : COLOR0;
    float2 vPosition : POSITION0;
};

cbuffer UIGlobalUniforms : register(b0) {
    float4x4 projectionMatrix;
};

OutputData main(InputData inputData) {
    OutputData outputData;
	outputData.vTexCoord = inputData.texCoord;
    outputData.vColor = inputData.color;

    outputData.vPosition = inputData.position.xy;
    outputData.svPosition = mul(projectionMatrix, float4(inputData.position, 1.0));
    return outputData;
}
