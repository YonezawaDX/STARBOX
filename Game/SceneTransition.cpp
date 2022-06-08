/**
* @file SceneTransition.cpp
* @brief シーン遷移
* @author 米澤駿介
* @date 2022/04/26
* @details シングルトン
*/
#include "pch.h"
#include "SceneTransition.h"
#include "Game/Effects/Fade.h"

//----------------------------------------------------------
// 概要：初期化
// 引数()：なし
// 戻り値：なし
//----------------------------------------------------------
void SceneTransition::Initialize()
{
	// フェードの作成
	mFade = std::make_unique<Fade>();

	// 初期化
	mFade->Initialize();
}

//----------------------------------------------------------
// 概要：更新
// 引数()：なし
// 戻り値：なし
//----------------------------------------------------------
void SceneTransition::Update(const DX::StepTimer& timer)
{
}
