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
	float Radius; // ���a�̔䗦�F0�`1
	float AspectRatio; // �A�X�y�N�g��
	float2 Dummy; // �p�f�B���O�f�[�^
};
///////////////////////////////////////////////////////////////////////////////
// Pixel Shader
///////////////////////////////////////////////////////////////////////////////
float4 main(float4 color : COLOR0, float2 texCoord : TEXCOORD0) : SV_Target0
{
	// Radius���P�̎���ʑS�̂������Ȃ�
	float r = 0.6f * Radius;
	float x = abs(texCoord.x - 0.5f);
	float y = abs(texCoord.y - 0.5f) / AspectRatio;
	// �e�N�X�`�����W���~�̒����ǂ����Ŕ��f����
	if (x * x + y * y < r * r)
	{
		// ����
		return float4(0.0f, 0.0f, 0.0f, 0.0f);
		}
	// �A���t�@�͂P�ɂ���
	float4 col = tex0.Sample(TextureSampler, texCoord) * color;
	return float4(col.r, col.g, col.b, 1.0f);
}
