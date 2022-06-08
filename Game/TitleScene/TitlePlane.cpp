/**
* @file TitlePlane.cpp
* @brief タイトルシーンの飛行機
* @author 米澤駿介
* @date 2022/04/26
* @details タイトルシーンの回転している飛行機
*/
#include "pch.h"
#include "TitlePlane.h"

// 定数--------------------------------------------------
// 最初の位置
const DirectX::SimpleMath::Vector3 TitlePlane::START_POS = DirectX::SimpleMath::Vector3(0.0f, -1.0f, 0.0f);
// 最初のアングル 
const DirectX::SimpleMath::Vector3 TitlePlane::START_ANGLE = DirectX::SimpleMath::Vector3(-6.0f, 50.0f, -7.0f);

// 回転する速さ
const float TitlePlane::MOVE_SPEED = 0.4f;
//-------------------------------------------------------

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
TitlePlane::TitlePlane()
{
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
TitlePlane::~TitlePlane()
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void TitlePlane::Initialize()
{
	// 座標を指定
	SetObjectPos(START_POS);

	// 向きを指定
	SetObjectDirection(START_ANGLE);
	
	// 速度を指定
	SetObjectSpeed(DirectX::SimpleMath::Vector3::Zero);
}

//----------------------------------------------------
// 概要：更新
// 引数:なし
// 戻り値：なし
//----------------------------------------------------
void TitlePlane::Update()
{
	// 動く
	Move();
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void TitlePlane::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	DirectX::SimpleMath::Vector3 pos = GetObjectPos();

	auto pRM = ResourceManager::GetInstance();
	//デバイスコンテキストの取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// 射影行列の取得
	DirectX::SimpleMath::Matrix projection = camera->GetProjectionMatrix();
	// ビュー行列の取得
	DirectX::SimpleMath::Matrix view = camera->GetViewMatrix();

	// ワールド座標の取得
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(GetObjectPos());

	// モデルの回転
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		GetObjectDirection().y * 0.05f,
		GetObjectDirection().x * 0.05f,
		GetObjectDirection().z * 0.05f
	);

	// 描画
	pRM->GetCmoModel("Player")->Draw(
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
void TitlePlane::Finalize()
{
}

//------------------------------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void TitlePlane::Move()
{
	DirectX::SimpleMath::Vector3 dir = GetObjectDirection();

	dir.z += MOVE_SPEED;
	
	SetObjectDirection(dir);
}

// ゲッター、セッター------------------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 TitlePlane::GetObjectPos() const
{
	return MoveObject::GetObjectPos();
}
//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void TitlePlane::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	MoveObject::SetObjectPos(pos);
}

//---------------------------------------
// 概要：向きのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 TitlePlane::GetObjectDirection() const
{
	return MoveObject::GetObjectDirection();
}
//---------------------------------------
// 概要：向きのセッター
// 引数(direction)：オブジェクトの向き
// 戻り値：なし
//---------------------------------------
void TitlePlane::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	MoveObject::SetObjectDirection(direction);
}

//---------------------------------------
// 概要：速さのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの速さ
//---------------------------------------
DirectX::SimpleMath::Vector3 TitlePlane::GetObjectSpeed() const
{
	return MoveObject::GetObjectSpeed();
}
//---------------------------------------
// 概要：速さのセッター
// 引数(speed)：オブジェクトの速さ
// 戻り値：なし
//---------------------------------------
void TitlePlane::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	MoveObject::SetObjectSpeed(speed);
}
