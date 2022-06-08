/**
* @file	TitleBackground.cpp
* @brief タイトルの背景
* @author 米澤駿介
* @date 2022/04/26
* @details 回転しているタイトルの背景
*/
#include "pch.h"
#include "TitleBackground.h"
#include <Effects.h>

// 定数------------------------------------------

// 動く速さ
const float TitleBackground::MOVE_SPEED = 0.01f;
//------------------------------------------------


//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
TitleBackground::TitleBackground():
	mpModel(nullptr)
{
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
TitleBackground::~TitleBackground()
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void TitleBackground::Initialize()
{
	// 座標を指定
	SetObjectPos(DirectX::SimpleMath::Vector3::Zero);

	// 向きを指定
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);

	// 速度を指定
	SetObjectSpeed(DirectX::SimpleMath::Vector3::Zero);

	auto pRM = ResourceManager::GetInstance();
	// モデル保存用
	mpModel = pRM->GetCmoModel("TitleBackground");
	mpModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights)
			{
				//ライトの影響をなくす

				lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}
			DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				// エミッション色を白に設定する
				basicEffect->SetEmissiveColor(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
			}
		});
}

//----------------------------------------------------
// 概要：更新
// 引数:なし
// 戻り値：なし
//----------------------------------------------------
void TitleBackground::Update()
{
	Move();
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void TitleBackground::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	DirectX::SimpleMath::Vector3 pos = GetObjectPos();
	//デバイスコンテキストの取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// 射影行列の取得
	DirectX::SimpleMath::Matrix projection = camera->GetProjectionMatrix();
	// ビュー行列の取得
	DirectX::SimpleMath::Matrix view = camera->GetViewMatrix();

	// ワールド座標の取得
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(GetObjectPos());

	//world *= DirectX::SimpleMath::Matrix::CreateScale(0.1f);

	// モデルの回転
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		GetObjectDirection().y * 0.05f,
		GetObjectDirection().x * 0.05f,
		GetObjectDirection().z * 0.05f
	);


	// モデル描画
	mpModel->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(q) * world,
		view,
		projection
	);
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void TitleBackground::Finalize()
{
	if(mpModel != nullptr)
	mpModel = nullptr;
}

//------------------------------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void TitleBackground::Move()
{
	DirectX::SimpleMath::Vector3 dir = GetObjectDirection();

	dir.x += MOVE_SPEED;
	dir.y += MOVE_SPEED;

	SetObjectDirection(dir);
}

// ゲッター、セッター------------------------------------------------------------------------
//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 TitleBackground::GetObjectPos() const
{
	return MoveObject::GetObjectPos();
}
//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void TitleBackground::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	MoveObject::SetObjectPos(pos);
}

//---------------------------------------
// 概要：向きのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 TitleBackground::GetObjectDirection() const
{
	return MoveObject::GetObjectDirection();
}
//---------------------------------------
// 概要：向きのセッター
// 引数(direction)：オブジェクトの向き
// 戻り値：なし
//---------------------------------------
void TitleBackground::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	MoveObject::SetObjectDirection(direction);
}

//---------------------------------------
// 概要：速さのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの速さ
//---------------------------------------
DirectX::SimpleMath::Vector3 TitleBackground::GetObjectSpeed() const
{
	return MoveObject::GetObjectSpeed();
}
//---------------------------------------
// 概要：速さのセッター
// 引数(speed)：オブジェクトの速さ
// 戻り値：なし
//---------------------------------------
void TitleBackground::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	MoveObject::SetObjectSpeed(speed);
}
