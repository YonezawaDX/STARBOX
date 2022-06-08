/**
* @file Letter.cpp
* @brief 文字
* @author 米澤駿介
* @date
* @details 文字※アルファベット大文字と数字のみ対応
*/
#include "pch.h"
#include "pch.h"
#include "Letter.h"
#include "Game.h"

// 名前空間の利用
using namespace DirectX;
using namespace DirectX::SimpleMath;

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
Letter::Letter():
	mTexture(nullptr), 
	mX(0), 
	mY(0),
	mColor(Colors::White)
{
}

//----------------------------------------------------
// 概要：初期化
// 引数(texture)：使う画像
// 引数(x)：x座標
// 引数(y)：y座標
// 引数(str)：書きたい文字
// 引数(color)：色
// 戻り値：なし
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
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
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
// 概要：描画
// 引数(str):文字
// 戻り値：なし
//---------------------------------------------------------------------
void Letter::SetStr(const char* str)
{
	mStr = std::string(str);
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(x)：X座標
// 引数(y)：Y座標
// 戻り値：なし
//---------------------------------------------------------------------
void Letter::SetPos(int x, int y)
{
	mX = x;
	mY = y;
}
