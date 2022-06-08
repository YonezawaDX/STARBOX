/**
* @file PlayScene.cpp
* @brief プレイシーン
* @author 米澤駿介
* @date 2022/04/26
* @details プレイシーン
*/
#include "pch.h"
#include "PlayScene.h"

#include "../GameMain.h"
#include "DeviceResources.h"

#include "Libraries/MyLibraries/ResourceManager.h"
#include "Libraries/MyLibraries/FollowCamera.h"

#include "Game/PlayScene/Object/Player.h"
#include "Game/PlayScene/BulletManager.h"
#include "Game/PlayScene/EnemyManager.h"
#include "Game/PlayScene/Object/BackGround.h"
#include "Game/PlayScene/Object/Floor.h"
#include "Game/PlayScene/Object/Boss.h"
#include "Game/PlayScene/Object/Boss02.h"

#include "Game/Score.h"
#include "UI.h"

#include "Game/Effects/Fade.h"

// 名前空間の利用
using namespace DirectX;

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
PlayScene::PlayScene()
	: mFps(0)
	, mpPlayer(nullptr)
	, mpBulletManager(nullptr)
	, mpEnemyManager(nullptr)
	, mpBackGround(nullptr)
	, mpFloor(nullptr)
	, mpBoss(nullptr)
	, mpUI(nullptr)
	, mpFade(nullptr)
	, mpBoss02(nullptr)
	, mState(PLAY_STATE::START)
{
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
PlayScene::~PlayScene()
{
	Finalize();
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void PlayScene::Initialize()
{
	// リソースを登録する
	ResourcesRegister();

	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// D3Dデバイスとデバイスコンテキストの取得
	auto device = pDR->GetD3DDevice();
	auto context = pDR->GetD3DDeviceContext();

	// コモンステート::D3Dレンダリング状態オブジェクト
	mCommonState = std::make_unique<DirectX::CommonStates>(device);

	// スプライトバッチ::デバッグ情報の表示に必要
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	mSpriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources/Fonts/SegoeUI_18.spritefont");

	// カメラの作成
	mCamera = std::make_unique<FollowCamera>();
	// 弾丸の管理作成
	mpBulletManager = std::make_unique<BulletManager>();
	mpBulletManager->Initialize();
	
	// 敵の管理者生成
	mpEnemyManager = std::make_unique<EnemyManager>();
	mpEnemyManager->Initialize(mpBulletManager.get());

	// プレイヤの作成
	mpPlayer = std::make_unique<Player>(mpBulletManager.get());
	mpPlayer->Initialize();

	// 背景の作成
	mpBackGround = std::make_unique<BackGround>();
	mpBackGround->Initialize();

	// 床の作成
	mpFloor = std::make_unique<Floor>();
	mpFloor->Initialize();

	// ボスの作成
	mpBoss = std::make_unique<Boss>(mpBulletManager.get(), mpEnemyManager.get());
	mpBoss->Initialize();

	// ボスの作成
	mpBoss02 = std::make_unique<Boss02>(mpBulletManager.get(), mpEnemyManager.get());
	mpBoss02->Initialize();

	// UIの作成
	mpUI = std::make_unique<UI>();
	mpUI->Initialize(mpPlayer->GetHP(), mpBoss->GetHP(), 1);

	// フェードの作成
	mpFade = std::make_unique<Fade>(1.0f, 0.0f);
	mpFade->Initialize();
}

//----------------------------------------------------
// 概要：更新
// 引数(timer)：時間
// 戻り値(GAME_SCENE)：次のシーン
//----------------------------------------------------
GAME_SCENE PlayScene::Update(const DX::StepTimer& timer)
{
	// フレームレートの取得
	mFps = timer.GetFramesPerSecond();

	// 弾丸の管理更新
	mpBulletManager->Update();

	mCamera->SetRefTargetPosition(mpPlayer->GetObjectPos());
	mCamera->SetRefEyePosition(mpPlayer->GetObjectPos() + mCamera->TARGET_TO_EYE_VEC);
	mCamera->Update();
	// 敵の管理者更新
	//mpEnemyManager->Update();

	for (int i = 0; i < mpEnemyManager->GetEnemyNum(); i++)
	{
		// 未使用状態なら処理をしない
		if (!mpEnemyManager->GetEnemies(i)->GetActive())
		{
			continue;
		}
		mpBulletManager->CheckHitEnemy(mpEnemyManager->GetEnemies(i));
	}

	// プレイヤーと弾との当たり判定
	//mpBulletManager->CheckHitPlayer(mpPlayer.get());

	// 敵とプレイヤーの当たり判定
	//mpEnemyManager->CheckHitPlayer(mpPlayer.get());
	
	// プレイヤの更新
	mpPlayer->Update();

	// 床の更新
	mpFloor->Update();

	int bossHP = 0;

	auto pScore = Score::GetInstance();
	if (pScore->GetBossNum() == 2)
	{
		// ボスの更新
		mpBoss->Update(mpPlayer->GetObjectPos());
		bossHP = mpBoss->GetHP();
	}
	else if (pScore->GetBossNum() == 3)
	{
		// ボス０２の更新
		mpBoss02->Update(mpPlayer->GetObjectPos());
		bossHP = mpBoss02->GetHP();
	}

	float elaspedTime = static_cast<float>(timer.GetElapsedSeconds());
	mpFade->Update(elaspedTime);
	switch (mState)
	{
		case PLAY_STATE::START:
		{
			// フェードが開いたら操作できる
			if (mpFade->IsOpen())
			{
				mState = PLAY_STATE::PLAY;
			}
			break;
		}
		case PLAY_STATE::PLAY:
		{
			if (bossHP <= 1)
			{
				mpFade->SetClose();
			}
			// 画面が閉じていたら次のシーンへ行く
			if (mpFade->IsClose())
			{
				mState = PLAY_STATE::NEXT_SCENE;
			}
			break;
		}
		case PLAY_STATE::NEXT_SCENE:
		{
			return GAME_SCENE::TITLE;
		}

		default:
		{
			assert("例外処理が発生しました。");
			break;
		}
	}

	// UIの更新
	mpUI->Update(mpPlayer->GetHP(), bossHP, 1);

	return GAME_SCENE::NONE;
}

//----------------------------------------------------------------------
// 概要：描画
// 引数：なし
// 戻り値：なし
//---------------------------------------------------------------------
void PlayScene::Draw()
{
	// 変換行列の宣言(ワールド、ビュー、射影)
	SimpleMath::Matrix world, view, projection;

	// ワールド行列の初期化(単位行列)
	world = SimpleMath::Matrix::Identity;

	// 射影行列の取得
	projection = mCamera->GetProjectionMatrix();

	// ビュー行列の取得
	view = mCamera->GetViewMatrix();

	// プレイヤの描画
	mpPlayer->Draw(mCommonState.get(), mCamera.get());

	// 背景
	mpBackGround->Draw(mCommonState.get(), mCamera.get());
	
	// 床の描画
	mpFloor->Draw(mCommonState.get(), mCamera.get());
	// 弾丸の描画
	mpBulletManager->Draw(mCommonState.get(), mCamera.get());
	// 敵の描画
	mpEnemyManager->Draw(mCommonState.get(), mCamera.get());

	auto pScore = Score::GetInstance();
	if (pScore->GetBossNum() == 2)
	{
		// ボスの描画
		mpBoss->Draw(mCommonState.get(), mCamera.get());
	}
	else if (pScore->GetBossNum() == 3)
	{
		// ボスの描画
		mpBoss02->Draw(mCommonState.get(), mCamera.get());
	}

	// FPSの取得と表示文字列の準備
	wchar_t buf[32];
	swprintf_s(buf, 32, L"FPS = %d", mFps);

	// スプライトバッチによるデバッグ情報の表示
	mSpriteBatch->Begin();

	// UIの描画
	mpUI->Draw(mCommonState.get(), mSpriteBatch.get(), mCamera.get());

	mSpriteBatch->End();

	// フェードを行う
	mpFade->Draw(mSpriteBatch.get());
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void PlayScene::Finalize()
{
	// ボスオブジェクトをリセットする
	//mpBoss->Finalize();
	//mpBackGround->Finalize();

}

//------------------------------------------------------------------
// 概要：リソース登録用
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void PlayScene::ResourcesRegister()
{
	// リソースの登録
	auto pRM = ResourceManager::GetInstance();

	// ボスの１体目
	pRM->RegisterCmoModel(L"Resources/Models/AttackCarrierBody.cmo", "BossBody");
	pRM->RegisterCmoModel(L"Resources/Models/SmallArm.cmo", "BossSmallArm");
	pRM->RegisterCmoModel(L"Resources/Models/BigArm.cmo", "BossBigArm");

	// ボスの２体目
	pRM->RegisterCmoModel(L"Resources/Models/Core.cmo", "Core");
	pRM->RegisterCmoModel(L"Resources/Models/Cover.cmo", "Cover");
	pRM->RegisterCmoModel(L"Resources/Models/Prime2.cmo", "Prime");
	pRM->RegisterCmoModel(L"Resources/Models/Tire.cmo", "Tire");

}
