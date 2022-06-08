/**
* @file TitleScene.cpp
* @brief タイトルシーン
* @author 米澤駿介
* @date
* @details タイトルシーン
*/
#include "pch.h"

#include <WICTextureLoader.h>
#include <SimpleMath.h>

#include "../GameMain.h"
#include "DeviceResources.h"
#include "Game/Effects/Fade.h"

#include "TitleScene.h"
#include "Libraries/MyLibraries/ResourceManager.h"
#include "Libraries/MyLibraries/Camera.h"

#include "TitlePlane.h"
#include "TitleObject.h"
#include "TitleBackground.h"

#include "Libraries/MyLibraries/InputManager.h"

// 名前空間の利用
using namespace DirectX;

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
TitleScene::TitleScene():
	mState(TITLE_STATE::START)
{
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
TitleScene::~TitleScene()
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void TitleScene::Initialize()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// D3Dデバイスとデバイスコンテキストの取得
	auto device = pDR->GetD3DDevice();
	auto context = pDR->GetD3DDeviceContext();

	// コモンステート::D3Dレンダリング状態オブジェクト
	mCommonState = std::make_unique<DirectX::CommonStates>(device);

	// スプライトバッチ::デバッグ情報の表示に必要
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	mSpriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources/Fonts/SegoeUI_18.spritefont");

	// テクスチャの読み込み
	CreateWICTextureFromFile(
		device,
		L"Resources/Textures/TridentLogo.png",
		nullptr,
		mTexture.ReleaseAndGetAddressOf()
	);

	auto pRM = ResourceManager::GetInstance();
	pRM->Initialize();

	// リソースマネージャにモデルを登録する
	pRM->RegisterCmoModel(L"Resources/Models/StarBox.cmo", "Title");
	pRM->RegisterCmoModel(L"Resources/Models/Arwing.cmo", "Player");
	pRM->RegisterCmoModel(L"Resources/Models/bg.cmo", "TitleBackground");

	// カメラの作成
	mCamera = std::make_unique<Camera>();

	// タイトルのモデル
	mpTitleObject = std::make_unique<TitleObject>();
	mpTitleObject->Initialize();

	// 飛行機モデルの作成
	mpPlane = std::make_unique<TitlePlane>();
	mpPlane->Initialize();

	// 背景のモデル
	mpTitleBackground = std::make_unique<TitleBackground>();
	mpTitleBackground->Initialize();
	
	// mFade
	mFade = std::make_unique<Fade>(1.0f,0.0f);
	mFade->Initialize();
	//mFade->SetClose();
}

//----------------------------------------------------
// 概要：更新
// 引数(timer)：時間
// 戻り値(GAME_SCENE)：次のシーン
//----------------------------------------------------
GAME_SCENE TitleScene::Update(const DX::StepTimer& timer)
{
	// マウス入力情報を取得する
	auto mouseState = DirectX::Mouse::Get().GetState();

	auto keyStateT = InputManager::GetInstance();

	float elaspedTime = static_cast<float>(timer.GetElapsedSeconds());

	// タイトルモデルの更新
	mpTitleObject->Update();
	// 飛行機の更新
	mpPlane->Update();
	// 背景のモデル
	mpTitleBackground->Update();

	// フェードの更新
	mFade->Update(elaspedTime);

	switch (mState)
	{
		case TITLE_STATE::START:
		{
			if (mFade->IsOpen())
			{
				mState = TITLE_STATE::PLAY;
			}
			break;
		}
		case TITLE_STATE::PLAY:
		{
			// Zキーが押されたらセレクトシーンに移行する
			if (
				keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Z)
				&& mFade->IsOpen()
				)
			{
				mFade->SetClose();
			}
			if (mFade->IsClose())
			{
				mState = TITLE_STATE::NEXT_SCENE;
			}
			break;
		}
		case TITLE_STATE::NEXT_SCENE:
		{	
			return GAME_SCENE::SELECT;
			break;
		}
		default:
		{
			assert("例外処理が発生しました。");
			break;
		}
	}

	return GAME_SCENE::NONE;
}

//----------------------------------------------------------------------
// 概要：描画
// 引数：なし
// 戻り値：なし
//---------------------------------------------------------------------
void TitleScene::Draw()
{
	// タイトルオブジェクトの描画
	mpTitleObject->Draw(mCommonState.get(), mCamera.get());
	// 飛行機の描画
	mpPlane->Draw(mCommonState.get(),mCamera.get());
	// 背景のモデル
	mpTitleBackground->Draw(mCommonState.get(), mCamera.get());

	mSpriteBatch->Begin(SpriteSortMode_Deferred, mCommonState->NonPremultiplied());

	mSpriteBatch->End();

	mFade->Draw(mSpriteBatch.get());
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void TitleScene::Finalize()
{
	// タイトルの背景を削除
	mpTitleBackground->Finalize();
}
