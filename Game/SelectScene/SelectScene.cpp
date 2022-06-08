/**
* @file SelectScene.cpp
* @brief セレクトシーン
* @author 米澤駿介
* @date 2022/04/26
* @details セレクトシーン
*/
#include "pch.h"
#include "SelectScene.h"
#include "Game/Effects/Fade.h"
#include "Libraries/MyLibraries/ResourceManager.h"

#include "Game/PlayScene/Object/Player.h"
#include "Game/PlayScene/BulletManager.h"

#include "Game/PlayScene/Object/BackGround.h"
#include "Game/PlayScene/Object/Floor.h"

#include "Libraries/MyLibraries/FollowCamera.h"
#include "Game/Effects/PostEffect.h"

#include "SelectButton.h"
#include "SelectSceneLetter.h"

#include "Game/Score.h"

#include "Libraries/MyLibraries/InputManager.h"

// 定数-------------------------------------------------------------------------------
const DirectX::SimpleMath::Vector3 SelectScene::CAMERA_POS = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -4.0f);
//-------------------------------------------------------------------------------


// 名前空間の利用
using namespace DirectX;

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
SelectScene::SelectScene():
	mPostCamera(DirectX::SimpleMath::Vector3::Zero),
	mPlayCount(0.0f),
	mSelectTrans(SELECT_TRANS::NONE),
	mStartWindow(SimpleMath::Matrix::Identity),
	mEndWindow(SimpleMath::Matrix::Identity),
	mFps(0),
	mState(SELECT_STATE::START)
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
SelectScene::~SelectScene()
{
	Finalize();
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void SelectScene::Initialize()
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

	//-----------------------------------------
	DirectX::SimpleMath::Vector3 camera = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -4.0f);
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::CreateLookAt(camera, target, DirectX::SimpleMath::Vector3::UnitY);

	// 最初の画面の大きさと最後の画面の位置と大きさを取得しておく
	mStartWindow = view * SimpleMath::Matrix::CreateScale(1.4f, 1.0f, 1.0f) * SimpleMath::Matrix::CreateTranslation(-0.8f, 0.5f, 0.0f);
	
	// ビュー座標の作成
	view = DirectX::SimpleMath::Matrix::CreateLookAt(SimpleMath::Vector3(0.0f, 0.0f, -2.25f), target, DirectX::SimpleMath::Vector3::UnitY);
	mEndWindow = view * SimpleMath::Matrix::CreateScale(1.4f, 1.0f, 1.0f) * SimpleMath::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);

	RECT outputSize = pDR->GetOutputSize();
	UINT backBufferWidth = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize.bottom - outputSize.top, 1);

	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(backBufferWidth) / float(backBufferHeight), 0.1f, 1000.f);

	mPostEffect = std::make_unique<PostEffect>();
	mPostEffect->Create(pDR, L"Resources\\Textures\\image01.png", 1);


	// ポストエフェクトの描画
	mPostEffect->SetRenderState(
		camera,
		mStartWindow,
		proj
	);
	//------------------------------------------
	

	// カメラの作成
	mCamera = std::make_unique<FollowCamera>();
	// 弾丸の管理作成
	mpBulletManager = std::make_unique<BulletManager>();
	mpBulletManager->Initialize();

	// プレイヤの作成
	mpPlayer = std::make_unique<Player>(mpBulletManager.get());
	mpPlayer->Initialize();

	// 背景の作成
	mpBackGround = std::make_unique<BackGround>();
	mpBackGround->Initialize();

	// 床の作成
	mpFloor = std::make_unique<Floor>();
	mpFloor->Initialize();

	// フェードの作成
	mpFade = std::make_unique<Fade>(1.0f, 0.0f);
	mpFade->Initialize();

	// セレクトボタンの生成
	mSelectButton = std::make_unique<SelectButton>();
	mSelectButton->Initialize();

	// セレクトシーンの文字の生成
	mSelectSceneLetter = std::make_unique<SelectSceneLetter>();
	mSelectSceneLetter->Initialize();
}

//----------------------------------------------------
// 概要：更新
// 引数(timer)：時間
// 戻り値(GAME_SCENE)：次のシーン
//----------------------------------------------------
GAME_SCENE SelectScene::Update(const DX::StepTimer& timer)
{
	auto keyStateT = InputManager::GetInstance();

	// フレームレートの取得
	mFps = timer.GetFramesPerSecond();

	// 弾丸の管理更新
	mpBulletManager->Update();

	mCamera->SetRefTargetPosition(mpPlayer->GetObjectPos());
	mCamera->SetRefEyePosition(mpPlayer->GetObjectPos() + mCamera->TARGET_TO_EYE_VEC);
	mCamera->Update();

	// プレイヤの更新
	mpPlayer->Update();

	// 床の更新
	mpFloor->Update();

	// ポストエフェクトの更新
	mPostEffect->Update(timer);
	
	float elaspedTime = static_cast<float>(timer.GetElapsedSeconds());
	mpFade->Update(elaspedTime);

	switch (mState)
	{
		case SELECT_STATE::START:
		{
			// フェードが開いたら操作できる
			if (mpFade->IsOpen())
			{
				mState = SELECT_STATE::PLAY;
			}
			break;
		}
		case SELECT_STATE::PLAY:
		{
			if (
				keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Z)
				&& mpFade->IsOpen()
				&& mSelectButton->GetSelectType() >= SelectButton::SELECT_TYPE::BOSS01
				)
			{
				mpFade->SetClose();
			}
			// 画面が閉じていたら次のシーンへ行く
			if (mpFade->IsClose())
			{
				mState = SELECT_STATE::NEXT_SCENE;
			}

			// セレクトボタンの更新
			mSelectButton->Update(timer);

			break;
		}
		case SELECT_STATE::NEXT_SCENE:
		{
			return GAME_SCENE::PLAY;
		}
		default:
		{
			assert("例外処理が発生しました。");
			break;
		}
	}

	// ボスのシーンを変更
	auto pScore = Score::GetInstance();
	pScore->SetBossNum(static_cast<int>(mSelectButton->GetSelectType()));

	// セレクトシーン文字更新
	mSelectSceneLetter->Update(timer);

	mSelectSceneLetter->SetSelectType(static_cast<int>(mSelectButton->GetSelectType()));

	return GAME_SCENE::NONE;
}

//----------------------------------------------------------------------
// 概要：描画
// 引数：なし
// 戻り値：なし
//---------------------------------------------------------------------
void SelectScene::Draw()
{
	ResourceManager* pRM = ResourceManager::GetInstance();

	// 変換行列の宣言(ワールド、ビュー、射影)
	 SimpleMath::Matrix world, view, projection;

	// ワールド行列の初期化(単位行列)
	world = SimpleMath::Matrix::Identity;

	// 射影行列の取得
	projection = mCamera->GetProjectionMatrix();

	// ビュー行列の取得
	view = mCamera->GetViewMatrix();

	mPostEffect->StartEffect();

	// 弾丸の描画
	mpBulletManager->Draw(mCommonState.get(), mCamera.get());


	// プレイヤの描画
	mpPlayer->Draw(mCommonState.get(), mCamera.get());

	// 背景
	mpBackGround->Draw(mCommonState.get(), mCamera.get());

	// 床の描画
	mpFloor->Draw(mCommonState.get(), mCamera.get());

	// ポストエフェクトを終了させる
	mPostEffect->EndEffect();
	mPostEffect->Render();


	// スプライトバッチによる画像の表示--------------------------------------
	mSpriteBatch->Begin();
	 
	mSelectButton->Draw(mCommonState.get(),mSpriteBatch.get());
	mSelectSceneLetter->Draw(mCommonState.get(), mSpriteBatch.get());

	auto bossTex = pRM->GetTexture("Boss01");

	// ボスの写真を変更する
	if (mSelectButton->GetSelectType() == SelectButton::SELECT_TYPE::BOSS01)
	{
		bossTex = pRM->GetTexture("Boss01");
	}
	if (mSelectButton->GetSelectType() == SelectButton::SELECT_TYPE::BOSS02)
	{
		bossTex = pRM->GetTexture("Boss02");
	}

	// ボタンを描画する
	if (mSelectButton->GetSelectType() >= SelectButton::SELECT_TYPE::BOSS01)
	{
		
		mSpriteBatch->Draw(
			bossTex,
			DirectX::SimpleMath::Vector2(43, 30),
			nullptr,
			DirectX::Colors::White,
			0.0f,
			DirectX::SimpleMath::Vector2::Zero,
			1.0f,
			DirectX::SpriteEffects::SpriteEffects_None,
			0.0f
		);
	}

	mSpriteBatch->End();
	//-----------------------------------------------------------------------

	// フェードを行う
	mpFade->Draw(mSpriteBatch.get());
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void SelectScene::Finalize()
{
	if (mPostEffect != nullptr)
	{
		mPostEffect->Lost();
	}
}

//------------------------------------------------------------------
// 概要：リソース登録用
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void SelectScene::ResourcesRegister()
{
	auto pRM = ResourceManager::GetInstance();

	pRM->Initialize();

	// リソースマネージャにモデルを登録する
	pRM->RegisterCmoModel(L"Resources/Models/Arwing.cmo", "Player");
	pRM->RegisterCmoModel(L"Resources/Models/Bullet.cmo", "Bullet");
	pRM->RegisterCmoModel(L"Resources/Models/Floor.cmo", "Floor");
	pRM->RegisterCmoModel(L"Resources/Models/BackGround.cmo", "PlayBackGround");
	pRM->RegisterCmoModel(L"Resources/Models/dice.cmo", "dice");
	pRM->RegisterCmoModel(L"Resources/Models/Enemy.cmo", "Enemy");

	// リソースマネージャに画像を保存する
	pRM->RegisterTexture(L"Resources/Textures/bossHp.png", "bossHp");
	pRM->RegisterTexture(L"Resources/Textures/Hp.png", "Hp");
	pRM->RegisterTexture(L"Resources/Textures/out.png", "HpOut");
	pRM->RegisterTexture(L"Resources/Textures/Number.png", "Number");
	pRM->RegisterTexture(L"Resources/Textures/butto.png", "Button");
	pRM->RegisterTexture(L"Resources/Textures/texture01.png", "Letter");
	pRM->RegisterTexture(L"Resources/Textures/Operation.png", "Operation");
	pRM->RegisterTexture(L"Resources/Textures/BossSpr.png", "Boss01");
	pRM->RegisterTexture(L"Resources/Textures/BossSpr02.png", "Boss02");
}
