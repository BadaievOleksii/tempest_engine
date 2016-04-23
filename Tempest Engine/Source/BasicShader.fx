struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
	float2 TexCoord : TEXCOORD;
};

cbuffer cbPerObject
{
	float4x4 WVP;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

VOut VShader(float4 Pos : POSITION, float4 Normal : NORMAL, float2 Tex : TEXCOORD)
{
    VOut output;

	output.position = mul(Pos, WVP);

	/*
	output.color.g = ((color & 0x0000FF00) >> 8) / 255.0f;
	output.color.b = (color & 0x000000FF) / 255.0f;
	output.color.r = ((color & 0x00FF0000) >> 16) / 255.0f;
	output.color.a = ((color & 0xFF000000) >> 24) / 255.0f;

	*/


	//VS_OUTPUT output = (VS_OUTPUT)0;
	//output.Pos = mul(Pos, World);
	//output.Pos = mul(output.Pos, View);
	//output.Pos = mul(output.Pos, Projection);
	//float3 vLightDirection = (-1, 0, 0.25);
	//float4 vLightColor = (1, 1, 1, 1);
	//output.Color = saturate(dot((float3)vLightDirection, output.Pos*0.5f) * vLightColor);
	output.color.g = 1.0f;
	output.color.b = 1.0f;
	output.color.r = 1.0f;
	output.color.a = 0.5f;
	//output.Tex = Tex;
	//return output;
	

	output.TexCoord = Tex;

    return output;
}












float4 PShader(VOut input) : SV_TARGET
{
	
	float4 output = ObjTexture.Sample(ObjSamplerState, input.TexCoord);// *input.color;
	

	return output;
}