/**
* @file Floor.cpp
* @brief 動く床のクラス
* @author 米澤駿介
* @date 2022/04/26
* @details 見た目だけ動く床
*/
#include "pch.h"
#include "Floor.h"

// 定数
// 動く速さ
const float Floor::MOVE_SPEED = 0.5f;

// 限界の座標
const float Floor::LIMIT_POS = 5.5f;

// 間の座標
const float Floor::OFFSET = 50.0f;

//-------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
// 戻り値：なし
//-------------------------------------------------------------------
Floor::Floor()
{
}
//---------------------------------------------------------
// 概要：デストラクタ
//---------------------------------------------------------
Floor::~Floor()
{
}

//----------------------------------------------------------
// 概要：初期化
// 引数()：なし
// 戻り値：なし
//----------------------------------------------------------
void Floor::Initialize()
{
}


//-----------------------------------------------------------
// 概要：更新
// 引数()：なし
// 戻り値：なし
//-----------------------------------------------------------
void Floor::Update()
{
	DirectX::SimpleMath::Vector3 pos = this->GetObjectPos();

	pos.z += MOVE_SPEED;

	if (pos.z > LIMIT_POS)
	{
		pos.z = 0.0f;
	}

	SetObjectPos(pos);
}

//-------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイト
// 引数(camera)：カメラ
// 戻り値：なし
//-------------------------------------------------------------
void Floor::Draw(DirectX::CommonStates* commonStates, Camera* camera)
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

	pRM->GetCmoModel("Floor")->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateTranslation(GetObjectPos()),
		view,
		projection
	);

	pRM->GetCmoModel("Floor")->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateTranslation(pos.x, pos.y, pos.z + OFFSET),
		view,
		projection
	);

	pRM->GetCmoModel("Floor")->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateTranslation(pos.x, pos.y, pos.z - OFFSET),
		view,
		projection
	);

}

//--------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//--------------------------------------------------------------
void Floor::Finalize()
{
}

//--------------------------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//--------------------------------------------------------------
void Floor::Move()
{
}

// ゲッター、セッター---------------------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Floor::GetObjectPos() const
{
	return Object::GetObjectPos();
}

//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void Floor::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	Object::SetObjectPos(pos);
}