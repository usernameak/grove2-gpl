Texture2D uiTexture : register(t0);
SamplerState uiTextureSampler : register(s0);

cbuffer UIEffectUniforms : register(b1) {
    uint uEffectId;
    float uEffectParam1;
};

struct InputData {
    float4 svPosition : SV_Position;
    float2 vTexCoord : TEXCOORD0;
    float4 vColor : COLOR0;
    float2 vPosition : POSITION0;
};

struct OutputData {
    float4 fragColor : SV_Target0;
};

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

OutputData main(InputData inputData) {
    OutputData outputData;

    float2 texCoord = inputData.vTexCoord;
    float4 color = float4(1.0, 0.0, 1.0, 1.0);
    if (uEffectId == 0) {
        color = uiTexture.Sample(uiTextureSampler, texCoord);
        // FIXME: proper gamma conversion
        // see https://github.com/alexcher-im/sgemu/blob/228d2bb6/engine/renderer/presets/fancy/coloring.py#L68
        color.rgb *= pow(inputData.vColor.rgb, 2.2);
        color.a *= inputData.vColor.a;
    } else if (uEffectId == 1) { // msdf
        float screenPxRange = uEffectParam1;

        float3 msd = uiTexture.Sample(uiTextureSampler, texCoord).rgb;
        float sd = median(msd.r, msd.g, msd.b);
        float screenPxDistance = screenPxRange*(sd - 0.5);
        float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);

        // FIXME: proper gamma conversion
        // see https://github.com/alexcher-im/sgemu/blob/228d2bb6/engine/renderer/presets/fancy/coloring.py#L68
        color = pow(inputData.vColor, 2.2);
        color.a *= opacity;
    }

    outputData.fragColor = color;

    return outputData;
}