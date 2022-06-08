/**
* @file HeartObject.cpp
* @brief HPがあるオブジェクトのクラス
* @author 米澤駿介
* @date 2022/04/26
* @details HPがあるオブジェクトMoveObjectを継承している
*/
#include "pch.h"
#include "HeartObject.h"

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
HeartObject::HeartObject()
	: mHP(0)
{
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
HeartObject::~HeartObject()
{
}

//------------------------------------------------------------------
// 概要：ボスパーツを追加する
// 引数 (bossParts)：HeartObjectのユニークポインタ 
// 戻り値：なし
//-------------------------------------------------------------------
void HeartObject::AddBossParts(std::unique_ptr<HeartObject> bossParts)
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void HeartObject::Initialize()
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 (bossFactory):ボスの生成クラス
// 戻り値：なし
//----------------------------------------------------
void HeartObject::Initialize(BossFactory* bossFactory)
{
	UNREFERENCED_PARAMETER(bossFactory);
}

//----------------------------------------------------
// 概要：更新
// 引数:なし
// 戻り値：なし
//----------------------------------------------------
void HeartObject::Update()
{
}

//------------------------------------------------------
// 概要：更新
// 引数 (position)：座標
// 引数 (angle)：角度
// 引数 (offset)：素体との距離
// 引数 (playerPos)：プレイヤーの座標
// 引数 (stateNum)：ボスの状態
// 戻り値：なし
//-------------------------------------------------------
void HeartObject::Update(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& angle,
	const DirectX::SimpleMath::Vector3& offset,
	const DirectX::SimpleMath::Vector3& playerPos,
	const int& stateNum
)
{
	UNREFERENCED_PARAMETER(position);
	UNREFERENCED_PARAMETER(angle);
	UNREFERENCED_PARAMETER(offset);
	UNREFERENCED_PARAMETER(playerPos);
	UNREFERENCED_PARAMETER(stateNum);
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void HeartObject::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	UNREFERENCED_PARAMETER(commonStates);
	UNREFERENCED_PARAMETER(camera);
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void HeartObject::Finalize()
{
}

//------------------------------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void HeartObject::Move()
{
}

//------------------------------------------------------------------
// 概要：パーツを消す
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void HeartObject::DeleteParts()
{
}

//-----------------------------------------------------------------------
// 概要：当たり判定
// 引数：なし
// 戻り値：なし
//-----------------------------------------------------------------------
void HeartObject::Collision()
{
}

// ゲッター、セッター-----------------------------------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 HeartObject::GetObjectPos() const
{
	return MoveObject::GetObjectPos();
}
//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void HeartObject::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	MoveObject::SetObjectPos(pos);
}

//---------------------------------------
// 概要：向きのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 HeartObject::GetObjectDirection() const
{
	return MoveObject::GetObjectDirection();
}
//---------------------------------------
// 概要：向きのセッター
// 引数(direction)：オブジェクトの向き
// 戻り値：なし
//---------------------------------------
void HeartObject::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	MoveObject::SetObjectDirection(direction);
}

//---------------------------------------
// 概要：速さのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの速さ
//---------------------------------------
DirectX::SimpleMath::Vector3 HeartObject::GetObjectSpeed() const
{
	return MoveObject::GetObjectSpeed();
}
//---------------------------------------
// 概要：速さのセッター
// 引数(speed)：オブジェクトの速さ
// 戻り値：なし
//---------------------------------------
void HeartObject::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	MoveObject::SetObjectSpeed(speed);
}

//---------------------------------------
// 概要：使用状態のゲッター
// 引数：なし
// 戻り値(bool)：オブジェクトの使用状態
//---------------------------------------
bool HeartObject::GetActive() const
{
	return MoveObject::GetActive();
}
//---------------------------------------
// 概要：使用状態のセッター
// 引数(active)：オブジェクトの使用状態
// 戻り値：なし
//---------------------------------------
void HeartObject::SetActive(const bool& active)
{
	MoveObject::SetActive(active);
}

//---------------------------------------
// 概要：HPのゲッター
// 引数：なし
// 戻り値(int)：オブジェクトのHP
//---------------------------------------
int HeartObject::GetHP() const
{
	return mHP;
}
//---------------------------------------
// 概要：HPのセッター
// 引数(hp)：オブジェクトのHP
// 戻り値：なし
//---------------------------------------
void HeartObject::SetHP(const int& hp)
{
	mHP = hp;
}