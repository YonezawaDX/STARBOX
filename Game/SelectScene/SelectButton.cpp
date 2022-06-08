/**
* @file SelectButton.cpp
* @brief 選択されるボタン
* @author 米澤駿介
* @date 2022/04/26
* @details 選択されるボタンの描画と処理
*/
#include "pch.h"
#include "SelectButton.h"

#include "Libraries/MyLibraries/ResourceManager.h"
#include <Keyboard.h>
#include "Libraries/MyLibraries/InputManager.h"

// 定数-----------------------------------------------------------------

// 小さいボタンのサイズ
const float SelectButton::BUTTON_SIZE_NORMAL = 0.75f;
// 大きいボタンのサイズ
const float SelectButton::BUTTON_SIZE_BIG = 0.80f;

// ボタンのX座標
const int SelectButton::BUTTON_POS_X = 700;
// ボタン１のY座標
const int SelectButton::BUTTON_POS_Y_01 = 200;
// ボタン２のY座標
const int SelectButton::BUTTON_POS_Y_02 = BUTTON_POS_Y_01 + 150;
//----------------------------------------------------------------------

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
SelectButton::SelectButton() :
	mSelectType(SELECT_TYPE::NONE),
	mButtonSize01(0.0f),
	mButtonSize02(0.0f),
	mBossLetter()
{
}
//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void SelectButton::Initialize()
{
	// セレクトタイプを操作にしておく
	mSelectType = SELECT_TYPE::OPERATE;
	
	// ボタンのサイズを設定しておく
	mButtonSize01 = BUTTON_SIZE_NORMAL;
	mButtonSize02 = BUTTON_SIZE_NORMAL;

	mBossLetter.resize(2);
	
	// リソースマネージャの取得
	ResourceManager* pRM = ResourceManager::GetInstance();
	for (unsigned int i = 0; i < mBossLetter.size(); i++)
	{
		mBossLetter[i] = std::make_unique<Letter>();

		mBossLetter[i]->Initialize(
			pRM->GetTexture("Letter"),
			0,
			0,
			"AA",
			DirectX::Colors::White
		);
	}

	mBossLetter[0]->SetPos(BUTTON_POS_X, BUTTON_POS_Y_01);
	mBossLetter[0]->SetStr("BOSS01");

	mBossLetter[1]->SetPos(BUTTON_POS_X, BUTTON_POS_Y_02);
	mBossLetter[1]->SetStr("BOSS02");
}

//----------------------------------------------------
// 概要：更新
// 引数(timer):時間
// 戻り値：なし
//----------------------------------------------------

void SelectButton::Update(DX::StepTimer timer)
{
	UNREFERENCED_PARAMETER(timer);
	// キー入力情報を取得する
	auto keyStateT = InputManager::GetInstance();

	// セレクトシーンの処理
	if (keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Z) && (mSelectType == SELECT_TYPE::OPERATE))
	{
		mSelectType = SELECT_TYPE::BOSS01;
		mButtonSize01 = BUTTON_SIZE_BIG;
	}
	// オペレートじゃない場合
	if (mSelectType != SELECT_TYPE::OPERATE)
	{
		// オペレートに戻る
		if (keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::X))
		{
			mSelectType = SELECT_TYPE::OPERATE;
			// ボタンのサイズを設定しておく
			mButtonSize01 = BUTTON_SIZE_NORMAL;
			mButtonSize02 = BUTTON_SIZE_NORMAL;
		}
		if (keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Up))
		{
			mSelectType = SELECT_TYPE::BOSS01;
			mButtonSize01 = BUTTON_SIZE_BIG;
			mButtonSize02 = BUTTON_SIZE_NORMAL;
		}
		if (keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Down))		{
			mSelectType = SELECT_TYPE::BOSS02;
			mButtonSize01 = BUTTON_SIZE_NORMAL;
			mButtonSize02 = BUTTON_SIZE_BIG;
		}
	}
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void SelectButton::Draw(DirectX::CommonStates* commStates ,DirectX::SpriteBatch* spriteBatch)
{
	// リソースマネージャの取得
	ResourceManager* pRM = ResourceManager::GetInstance();
	// 座標指定

	// ボタンの描画
	spriteBatch->Draw(
		pRM->GetTexture("Button"),
		DirectX::SimpleMath::Vector2(BUTTON_POS_X, BUTTON_POS_Y_01),
		nullptr,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		mButtonSize01,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	// ボタンの描画
	spriteBatch->Draw(
		pRM->GetTexture("Button"),
		DirectX::SimpleMath::Vector2(BUTTON_POS_X, BUTTON_POS_Y_02),
		nullptr,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		mButtonSize02,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	// 文字の描画
	for (unsigned int i = 0; i < mBossLetter.size(); i++)
	{
		mBossLetter[i]->Draw(commStates, spriteBatch);
	}
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void SelectButton::Finalize()
{
}

// ゲッター、セッター----------------------------------------------------

//---------------------------------------
// 概要：ボタンの選択状態のゲッター
// 引数：なし
// 戻り値(SELECT_TYPE)：選択状態
//---------------------------------------
SelectButton::SELECT_TYPE SelectButton::GetSelectType() const
{
	return mSelectType;
}
