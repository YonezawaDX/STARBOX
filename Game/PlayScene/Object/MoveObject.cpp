/**
* @file MoveObject.cpp
* @brief 動くオブジェクトのクラス
* @author 米澤駿介
* @date 2022/04/26
* @details 動くオブジェクトObjectを継承している
*/
#include "pch.h"
#include "MoveObject.h"

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
MoveObject::MoveObject()
	: mDirection(DirectX::SimpleMath::Vector3::Zero)
	, mSpeed(0.0f)
	, mIsActive(false)
{
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
MoveObject::~MoveObject()
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void MoveObject::Initialize()
{
}
//----------------------------------------------------
// 概要：更新
// 引数:なし
// 戻り値：なし
//----------------------------------------------------
void MoveObject::Update()
{
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void MoveObject::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	UNREFERENCED_PARAMETER(commonStates);
	UNREFERENCED_PARAMETER(camera);
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void MoveObject::Finalize()
{
}

//------------------------------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void MoveObject::Move()
{
}

//------------------------------------------------------------------
// 概要：パーツを消す
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void MoveObject::DeleteParts()
{
}

//-----------------------------------------------------------------------
// 概要：当たり判定
// 引数：なし
// 戻り値：なし
//-----------------------------------------------------------------------
void MoveObject::Collision()
{
}

// ゲッター、セッター-----------------------------------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 MoveObject::GetObjectPos() const
{
	return Object::GetObjectPos();
}

//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void MoveObject::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	Object::SetObjectPos(pos);
}

//---------------------------------------
// 概要：向きのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//--------------------------------------
DirectX::SimpleMath::Vector3 MoveObject::GetObjectDirection() const
{
	return mDirection;
}
//---------------------------------------
// 概要：向きのセッター
// 引数(direction)：オブジェクトの向き
// 戻り値：なし
//---------------------------------------
void MoveObject::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	mDirection = direction;
}

//---------------------------------------
// 概要：速さのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの速さ
//---------------------------------------
DirectX::SimpleMath::Vector3 MoveObject::GetObjectSpeed() const
{
	return mSpeed;
}
//---------------------------------------
// 概要：速さのセッター
// 引数(speed)：オブジェクトの速さ
// 戻り値：なし
//---------------------------------------
void MoveObject::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	mSpeed = speed;
}

//---------------------------------------
// 概要：使用状態のゲッター
// 引数：なし
// 戻り値(bool)：オブジェクトの使用状態
//---------------------------------------
bool MoveObject::GetActive() const
{
	return mIsActive;
}
//---------------------------------------
// 概要：使用状態のセッター
// 引数(active)：オブジェクトの使用状態
// 戻り値：なし
//---------------------------------------
void MoveObject::SetActive(const bool& active)
{
	mIsActive = active;
}
