/**
* @file SelectSceneLetter.cpp
* @brief セレクトシーンの文字を管理
* @author 米澤駿介
* @date 2022/04/26
* @details ボタンやシーンの文字を管理、描画
*/
#include "pch.h"
#include "SelectSceneLetter.h"

#include "Libraries/MyLibraries/ResourceManager.h"

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
SelectSceneLetter::SelectSceneLetter():
	mLetter(),
	mSelectType(0)
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void SelectSceneLetter::Initialize()
{
	// リソースマネージャの取得
	ResourceManager* pRM = ResourceManager::GetInstance();

	// セレクトタイプをオペレートに
	mSelectType = 1;
	
	// 文字の数を入れる
	mLetter.resize(5);
	for (unsigned int i = 0; i < mLetter.size(); i++)
	{
		mLetter[i] = std::make_unique<Letter>();
	
		mLetter[i]->Initialize(
			pRM->GetTexture("Letter"),
			0,
			0,
			"A",
			DirectX::Colors::White
		);
	}

	mLetter[0]->SetStr("PUSH UP");
	mLetter[0]->SetPos(700,20);

	mLetter[1]->SetStr("Z NEXT");
	mLetter[1]->SetPos(700, 500);

	mLetter[2]->SetStr("X BACK");
	mLetter[2]->SetPos(700, 550);

	mLetter[3]->SetStr("");
	mLetter[3]->SetPos(750, 70);
	
	mLetter[4]->SetStr("");
	mLetter[4]->SetPos(740, 120);
}

//----------------------------------------------------
// 概要：更新
// 引数(timer):時間
// 戻り値：なし
//----------------------------------------------------
void SelectSceneLetter::Update(DX::StepTimer timer)
{
	UNREFERENCED_PARAMETER(timer);

	if (mSelectType == 1)
	{
		mLetter[0]->SetStr("PUSH Z");
		mLetter[3]->SetStr("");
		mLetter[4]->SetStr("");
	}
	else if (mSelectType > 1)
	{
		mLetter[0]->SetStr("PUSH UP");
		mLetter[3]->SetStr("AND");
		mLetter[4]->SetStr("DOWN");
	}
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void SelectSceneLetter::Draw(DirectX::CommonStates* commStates, DirectX::SpriteBatch* spriteBatch)
{
	ResourceManager* pRM = ResourceManager::GetInstance();
	// 文字の描画をする
	for (unsigned int i = 0; i < mLetter.size(); i++)
	{
		mLetter[i]->Draw(commStates, spriteBatch);
	}

	spriteBatch->Draw(
		pRM->GetTexture("Operation"),
		DirectX::SimpleMath::Vector2(0, 450),
		nullptr,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		0.75f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void SelectSceneLetter::Finalize()
{
}

//---------------------------------------
// 概要：ボタンの選択状態のゲッター
// 引数(num)：セレクトしているものを取得
// 戻り値 なし
//---------------------------------------
void SelectSceneLetter::SetSelectType(int num)
{
	mSelectType = num;
}
