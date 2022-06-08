/**
* @file Tire.cpp
* @brief タイヤクラス
* @author 米澤駿介
* @date 2022/05/11
* @details ボス02のタイヤクラス
*/
#include "pch.h"
#include "Tire.h"
#include "../BossFactory.h"

//------------------------------------------------------------------
// 概要：ボスパーツを追加する
// 引数 (bossParts)：HeartObjectのユニークポインタ 
// 戻り値：なし
//-------------------------------------------------------------------
void Tire::AddBossParts(std::unique_ptr<HeartObject> bossParts)
{
	UNREFERENCED_PARAMETER(bossParts);
}

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数(offset)：素体との距離
//------------------------------------------------------------------
Tire::Tire(const DirectX::SimpleMath::Vector3& offset) :
	mPosOffset(offset),
	mAngleOffset(DirectX::SimpleMath::Vector3::Zero),
	mBossState(0),
	mIsDown(false),
	mRotate(0)
{
	SetObjectPos(DirectX::SimpleMath::Vector3::Zero);
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);
	SetObjectSpeed(DirectX::SimpleMath::Vector3(-0.2f, -0.2f, 0.2f));
	SetHP(3);
	SetActive(true);
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
Tire::~Tire()
{
	Finalize();
}

//----------------------------------------------------
// 概要：初期化
// 引数 (bossFactory):ボスの生成クラス
// 戻り値：なし
//----------------------------------------------------
void Tire::Initialize(BossFactory* bossFactory)
{
	UNREFERENCED_PARAMETER(bossFactory);
}

//------------------------------------------------------
// 概要：更新
// 引数 (position)：座標
// 引数 (angle)：角度
// 引数 (offset)：素体との角度
// 引数 (playerPos)：プレイヤーの座標
// 引数 (stateNum)：ボスの状態
// 戻り値：なし
//-------------------------------------------------------
void Tire::Update(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& angle,
	const DirectX::SimpleMath::Vector3& offset,
	const DirectX::SimpleMath::Vector3& playerPos,
	const int& stateNum
)
{
	UNREFERENCED_PARAMETER(playerPos);

	Move();
	// ボスの状態を格納
	mBossState = stateNum;

	// 位置を設定する
	SetObjectPos(position + mPosOffset);

	// 向きを設定する
	SetObjectDirection(angle + offset);

	// 向きのオフセット
	mAngleOffset = offset;
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void Tire::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
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
		(GetObjectDirection().x + mRotate) * 0.05f,
		GetObjectDirection().z * 0.05f
	);

	// モデルの描画
	pRM->GetCmoModel("Tire")->Draw(
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
void Tire::Finalize()
{
}

//------------------------------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void Tire::Move()
{
	mRotate += Boss02::PARTS_ROTATE;
}

//-----------------------------------------------------------------------
// 概要：当たり判定
// 引数：なし
// 戻り値：なし
//-----------------------------------------------------------------------
void Tire::Collision()
{
	// タイヤには当たり判定は設けない
	return;
}

// ゲッター、セッター------------------------------------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Tire::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}
//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void Tire::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// 概要：向きのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Tire::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}
//---------------------------------------
// 概要：向きのセッター
// 引数(direction)：オブジェクトの向き
// 戻り値：なし
//---------------------------------------
void Tire::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// 概要：速さのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの速さ
//---------------------------------------
DirectX::SimpleMath::Vector3 Tire::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}
//---------------------------------------
// 概要：速さのセッター
// 引数(speed)：オブジェクトの速さ
// 戻り値：なし
//---------------------------------------
void Tire::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// 概要：使用状態のゲッター
// 引数：なし
// 戻り値(bool)：オブジェクトの使用状態
//---------------------------------------
bool Tire::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// 概要：使用状態のセッター
// 引数(active)：オブジェクトの使用状態
// 戻り値：なし
//---------------------------------------
void Tire::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// 概要：HPのゲッター
// 引数：なし
// 戻り値(int)：オブジェクトのHP
//---------------------------------------
int Tire::GetHP() const
{
	return HeartObject::GetHP();
}
//---------------------------------------
// 概要：HPのセッター
// 引数(hp)：オブジェクトのHP
// 戻り値：なし
//---------------------------------------
void Tire::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}