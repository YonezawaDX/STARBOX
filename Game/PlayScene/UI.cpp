/**
* @file UI.cpp
* @brief ユーザーインターフェース
* @author 米澤駿介
* @date
* @details UI(HP)を描画するクラス
*/
#include "pch.h"
#include "UI.h"
#include "Libraries/MyLibraries/ResourceManager.h"
#include <SimpleMath.h>

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
UI::UI() :
	mPlayerHP(0),
	mBossHP(0),
	mScore(0)
{
}
//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
UI::~UI()
{
}

//----------------------------------------------------
// 概要：初期化
// 引数(playerHP) : プレイヤーの体力
// 引数(bossHP) : ボスの体力
// 戻り値：なし
//----------------------------------------------------
void UI::Initialize(int playerHp, int bossHp, int score)
{
	// それぞれの変数を格納する
	mPlayerHP = playerHp;
	mBossHP = bossHp;
	mScore = score;
}

//----------------------------------------------------
// 概要：更新
// 引数(playerHP) : プレイヤーの体力
// 引数(bossHP) : ボスの体力
// 戻り値：なし
//----------------------------------------------------
void UI::Update(int playerHp, int bossHp, int score)
{
	mPlayerHP = playerHp;
	mBossHP = bossHp;
	mScore = score;
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void UI::Draw(DirectX::CommonStates* commonStates, DirectX::SpriteBatch* spriteBatch, Camera* camera)
{
	UNREFERENCED_PARAMETER(commonStates);
	UNREFERENCED_PARAMETER(camera);
	DrawBossHP(spriteBatch);
	DrawPlayerHP(spriteBatch);
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void UI::Finalize()
{
}

//-------------------------------------------------------------------
// 概要：スコアの描画
// 引数(spriteBatch)：画像情報
// 戻り値：なし
//-------------------------------------------------------------------
void UI::DrawScore(DirectX::SpriteBatch* spriteBatch)
{
	UNREFERENCED_PARAMETER(spriteBatch);

	// 切り取りする
	RECT* re = new RECT();
	re->top = (LONG)0.0f;
	re->left = (LONG)0.0f;
	re->bottom = (LONG)100.0f;
	re->right = (LONG)300.0f;

	// 削除する
	delete re;
}

//-------------------------------------------------------------------
// 概要：ボスの体力の描画
// 引数(spriteBatch)：画像情報
// 戻り値：なし
//-------------------------------------------------------------------
void UI::DrawBossHP(DirectX::SpriteBatch* spriteBatch)
{
	// リソースの呼び出し
	auto pRM = ResourceManager::GetInstance();

	// 座標指定
	DirectX::SimpleMath::Vector2 pos(700, 0);

	// 切り取りする
	RECT* re = new RECT();
	re->top = (LONG)0.0f;
	re->left = (LONG)0.0f;
	re->bottom = (LONG)20.0f;
	re->right = (LONG)(10.0f * 16.5f);

	// HPの外枠を描画する
	spriteBatch->Draw(
		pRM->GetTexture("HpOut"),
		pos,
		re,
		DirectX::Colors::Gray,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		2.0f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	re->right = mBossHP * (LONG)16.5f;
	// 描画する
	spriteBatch->Draw(
		pRM->GetTexture("bossHp"),
		pos,
		re,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		2.0f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	// 削除する
	delete re;
}

//-------------------------------------------------------------------
// 概要：プレイヤーの体力の描画
// 引数(spriteBatch)：画像情報
// 戻り値：なし
//-------------------------------------------------------------------
void UI::DrawPlayerHP(DirectX::SpriteBatch* spriteBatch)
{
	// リソースの呼び出し
	auto pRM = ResourceManager::GetInstance();

	// 座標指定
	DirectX::SimpleMath::Vector2 pos(0, 680);

	// 切り取りする
	RECT* re = new RECT();
	re->top = (LONG)0.0f;
	re->left = (LONG)0.0f;
	re->bottom = (LONG)20.0f;
	re->right = (LONG)(10.0f * 16.5f);

	// HPの外枠を描画する
	spriteBatch->Draw(
		pRM->GetTexture("HpOut"),
		pos,
		re,
		DirectX::Colors::Gray,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		2.0f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	re->right = (LONG)(mPlayerHP * 16.5f);
	// 描画する
	spriteBatch->Draw(
		pRM->GetTexture("Hp"),
		pos,
		re,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		2.0f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	// 削除する
	delete re;
}
