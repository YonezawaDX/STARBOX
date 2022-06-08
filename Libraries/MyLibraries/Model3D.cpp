/**
* @file Model3D.cpp
* @brief モデル3Dのクラス
* @author 米澤駿介
* @date
* @details モデルを簡易的に出せるようにする
*/
#include "pch.h"
#include "Model3D.h"

#include <Effects.h>
#include "DeviceResources.h"
#include "Libraries/MyLibraries/Camera.h"

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
Model3D::Model3D()
	:mModel(nullptr)
	,mRotateX(0.0f)
	,mRotateY(0.0f)
	,mRotateZ(0.0f)
{
}


//----------------------------------------------------
// 概要：初期化
// 引数(fileName): モデルのファイル名
// 戻り値：なし
//----------------------------------------------------
void Model3D::Initialize(const wchar_t* fileName)
{
	// デバイスの取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// モデルデータの入っているフォルダの指定
	std::unique_ptr<DirectX::EffectFactory> factory = std::make_unique<DirectX::EffectFactory>(device);
	factory->SetDirectory(L"Resources/Models");

	// 3Dモデルのロード
	mModel = DirectX::Model::CreateFromCMO(device, fileName, *factory);
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(world)：ワールド座標
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void Model3D::Draw(DirectX::CommonStates* commonStates, DirectX::SimpleMath::Matrix* world, Camera* camera)
{
	//デバイスコンテキストの取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// 射影行列の取得
	DirectX::SimpleMath::Matrix projection = camera->GetProjectionMatrix();

	// ビュー行列の取得
	DirectX::SimpleMath::Matrix view = camera->GetViewMatrix();

	// モデルの回転も行
	// モデルの描画
	DirectX::SimpleMath::Quaternion q = 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll
		(
			DirectX::XMConvertToRadians(mRotateY),
			DirectX::XMConvertToRadians(mRotateX),
			DirectX::XMConvertToRadians(mRotateZ)
		);


	mModel->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(q) * *world,
		view,
		projection);
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void Model3D::Finalize()
{
}
