#include "Particle.hlsli"


Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float random(float2 uv)
{
	return frac(sin(dot(uv, float2(12.9898f, 78.233f))) * 43758.5453f);
}


// 灰色
float gray(float4 col)
{
	return col.r * 0.3f + col.g * 0.6f + col.b * 0.1f;
}

float4 green(float4 col)
{
	float g = gray(col);
	return float4(g * 0.9f, g * 1.98f, g * 0.9f, col.a);
}

float4 sepia(float4 col)
{
	float g = gray(col);
	return float4(g * 1.44f, g * 0.99f, g * 0.57f, col.a);
}


float4 GreenOldTV(float2 inUV)
{
	float2 uv = inUV;
	
	// 中心をずらす
	uv = uv - 0.5f;
	float vignette = length(uv);
	uv /= 1 - vignette * 0.2f;
	// 中心に戻す
	float2 texUV = uv + 0.5f;
	float4 base = tex.Sample(samLinear, texUV);


	texUV.x += (random(floor(texUV.y * 100) + Time.x) - 0.5f) * 0.01f;

	// 四隅を暗くする
	float3 col = float3(0, 0, 0);
	col.r = -1 * tex.Sample(samLinear, texUV).r;
	col.g = -1 * tex.Sample(samLinear, texUV + float2(0.002f, 0)).g;
	col.b = -1 * tex.Sample(samLinear, texUV + float2(0.004f, 0)).b;
	
	col += float3(1.35f, 1.35f, 1.35f);

	col = lerp(col, float3(
		random(uv + float2(123 + Time.z, 0)),
		random(uv + float2(123 + Time.z, 1)),
		random(uv + float2(123 + Time.z, 2))),
		step(random(floor(texUV.y * 500) + Time.z), 0.001f));

	// 四隅を暗くする
	col *= 1 - vignette * 1.5f;

	base = float4(col, base.a);

	base.g *= 0.6f;

	base = lerp(base, float4(0, 0, 0, 1), step(0, max(abs(uv.y) - 0.5f, abs(uv.x) - 0.5f)));
	
	return green(base);
}

//歪みの偏差を求める処理
float distortion(float2 center, float r, float d_r, float2 uv)
{
	//今のピクセルと中心座標の距離
	float dist = distance(center, uv);
	//半径d_rの歪みを作る。
	return 1 - smoothstep(r, d_r, dist);
}

float4 mosaic(float2 baseUV, float mag)
{
	return tex.Sample(samLinear, floor(baseUV * mag) / mag);
}

float4 main(PS_INPUT input) : SV_TARGET
{
	return mosaic(input.Tex,500);
}
