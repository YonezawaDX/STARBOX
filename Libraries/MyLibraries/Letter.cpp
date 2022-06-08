/**
* @file Letter.cpp
* @brief ����
* @author ���V�x��
* @date
* @details �������A���t�@�x�b�g�啶���Ɛ����̂ݑΉ�
*/
#include "pch.h"
#include "pch.h"
#include "Letter.h"
#include "Game.h"

// ���O��Ԃ̗��p
using namespace DirectX;
using namespace DirectX::SimpleMath;

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
Letter::Letter():
	mTexture(nullptr), 
	mX(0), 
	mY(0),
	mColor(Colors::White)
{
}

//----------------------------------------------------
// �T�v�F������
// ����(texture)�F�g���摜
// ����(x)�Fx���W
// ����(y)�Fy���W
// ����(str)�F������������
// ����(color)�F�F
// �߂�l�F�Ȃ�
//----------------------------------------------------
void Letter::Initialize(ID3D11ShaderResourceView* texture, int x, int y, const char* str, FXMVECTOR color)
{
	mTexture = texture;
	mX = x;
	mY = y;
	SetStr(str);
	mColor = color;
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void Letter::Draw(DirectX::CommonStates* commonStates, DirectX::SpriteBatch* spriteBatch)
{
	UNREFERENCED_PARAMETER(commonStates);

	int x = mX;
	int y = mY;

	if (!mTexture) return;

	for (size_t i = 0; i < mStr.size(); i++)
	{
		if (mStr[i] >= '0' && mStr[i] <= 'Z')
		{
			int val = mStr[i] - '0';
			int xx = val % 16;
			int yy = val / 16;
			RECT srcRect = { xx * SIZE, yy * SIZE, (xx + 1) * SIZE, (yy + 1) * SIZE };
			spriteBatch->Draw(mTexture, Vector2((float)x, (float)y), &srcRect, mColor);
		}
		x += SIZE;
	}
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(str):����
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void Letter::SetStr(const char* str)
{
	mStr = std::string(str);
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(x)�FX���W
// ����(y)�FY���W
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void Letter::SetPos(int x, int y)
{
	mX = x;
	mY = y;
}
