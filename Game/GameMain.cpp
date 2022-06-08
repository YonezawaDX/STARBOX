/**
* @file GameMain.cpp
* @brief ゲームメイン
* @author 米澤駿介
* @date
* @details ゲーム全体を管理
*/
#include "pch.h"

#include "DeviceResources.h"
#include "GameMain.h"

#include "Game/TitleScene/TitleScene.h"
#include "Game/SelectScene/SelectScene.h"
#include "Game/PlayScene/PlayScene.h"

#include "Libraries/MyLibraries/InputManager.h"

// 名前空間の利用
using namespace DirectX;

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
GameMain::GameMain()
	: mNextScene(GAME_SCENE::TITLE)		// 初期シーンの設定
	, mpScene(nullptr)
{
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
GameMain::~GameMain()
{
	Finalize();
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void GameMain::Initialize()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// InputManager::Singleton版
	InputManager* inputManager = InputManager::GetInstance();
	inputManager->Initialize(pDR->GetHwnd());

	// シーン作成
	CreateScene();
}

//----------------------------------------------------
// 概要：更新
// 引数(timer)：時間
// 戻り値：なし
//----------------------------------------------------
void GameMain::Update(const DX::StepTimer& timer)
{
	// インプットマネージャの取得
	InputManager* inputManager = InputManager::GetInstance();
	inputManager->Update();

	// ESCキーで終了
	if (inputManager->GetKeyboardState().Escape)PostQuitMessage(0);

	// 次のシーンが設定されていたらシーン切り替え
	if (mNextScene != GAME_SCENE::NONE)
	{
		// シーン削除
		DeleteScene();
		
		// シーン作成
		CreateScene();
	}

	// 実態があれば更新
	if (mpScene != nullptr)
	{
		mNextScene = mpScene->Update(timer);
	}
}

//----------------------------------------------------------------------
// 概要：描画
// 引数：なし
// 戻り値：なし
//---------------------------------------------------------------------
void GameMain::Render()
{
	// 実態があれば描画
	if (mpScene != nullptr)
	{
		mpScene->Draw();
	}
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void GameMain::Finalize()
{
	DeleteScene();
}

//------------------------------------------------------------------
// 概要：シーンの作成
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void GameMain::CreateScene()
{
	// シーンが作成されているときは処理しない
	if (mpScene != nullptr)
	{
		return;
	}

	// 次シーンの作成
	switch (mNextScene)
	{
		case GAME_SCENE::TITLE:
		{
			mpScene = new TitleScene();
			break;
		}
		case GAME_SCENE::SELECT:
		{
			mpScene = new SelectScene();
			break;
		}
		case GAME_SCENE::PLAY:
		{
			mpScene = new PlayScene();
			break;
		}
		default:
		{
			// 例外なので処理を中断
			return;
		}
	}

	// 作成したシーンを初期化
	mpScene->Initialize();
}

//------------------------------------------------------------------
// 概要：シーンの削除
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void GameMain::DeleteScene()
{
	// シーンが作成されていなければ処理しない
	if (mpScene == nullptr)
	{
		return;
	}

	// 現シーンの終了処理
	mpScene->Finalize();

	// 現シーンの削除
	delete mpScene;
	mpScene = nullptr;
}
