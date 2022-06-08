///////////////////////////////////////////////////////////////////////////////
// Filename: psWipe.hlsl
///////////////////////////////////////////////////////////////////////////////
///////////////////
// TEXTURE //
///////////////////
Texture2D<float4> tex0 : register(t0);
///////////////////
// SAMPLE STATES //
///////////////////
sampler TextureSampler : register(s0);
//////////////////////
// CONSTANT BUFFERS //
//////////////////////
cbuffer cbChangesEveryFrame : register(b0)
{
	float Radius; // 半径の比率：0～1
	float AspectRatio; // アスペクト比
	float2 Dummy; // パディングデータ
};
///////////////////////////////////////////////////////////////////////////////
// Pixel Shader
///////////////////////////////////////////////////////////////////////////////
float4 main(float4 color : COLOR0, float2 texCoord : TEXCOORD0) : SV_Target0
{
	// Radiusが１の時画面全体が黒くなる
	float r = 0.6f * Radius;
	float x = abs(texCoord.x - 0.5f);
	float y = abs(texCoord.y - 0.5f) / AspectRatio;
	// テクスチャ座標が円の中かどうかで判断する
	if (x * x + y * y < r * r)
	{
		// 透明
		return float4(0.0f, 0.0f, 0.0f, 0.0f);
		}
	// アルファは１にする
	float4 col = tex0.Sample(TextureSampler, texCoord) * color;
	return float4(col.r, col.g, col.b, 1.0f);
}
