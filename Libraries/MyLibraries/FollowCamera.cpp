/**
* @file FollowCamera.cpp
* @brief 追従カメラ
* @author
* @date
* @details 追従カメラ
*/
#include "pch.h"
#include "FollowCamera.h"

#include "DeviceResources.h"
#include <Keyboard.h>

// 名前空間の利用
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 定数-----------------------------------------------------------------
// ターゲットの初期視点
const DirectX::SimpleMath::Vector3 FollowCamera::TARGET_TO_EYE_VEC = DirectX::SimpleMath::Vector3(0.0f, -2.0f, 30.0f);

// プレイヤーが地面にいるときの視点
const float FollowCamera::POINT_OF_VIEW_WORK = 1.5f;		

// プレイヤーが飛んでいるときの視点
const float FollowCamera::POINT_OF_VIEW_BOOST = 7.0f;		
//-------------------------------------------------------------------------------------------------

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
FollowCamera::FollowCamera()
	: mCameraRot(0.0f)
{
	SetViewMatrix(DirectX::SimpleMath::Matrix::Identity);
	SetEyePosition(DirectX::SimpleMath::Vector3(0.0f, -2.0f, 30.0f));
	SetTargetPosition(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	SetUpVector(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f));
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
FollowCamera::~FollowCamera()
{
}

//------------------------------------------------------------------
// 概要：更新
// 引数：なし
// 戻り値：なし
//-------------------------------------------------------------------
void FollowCamera::Update()
{
	DirectX::SimpleMath::Vector3 eye = this->GetEyePosition();

	DirectX::SimpleMath::Vector3 refEye = DirectX::SimpleMath::Vector3(mRefEye.x,mRefEye.y,mRefEye.z);
	eye += (refEye - eye) * 0.035f;

	// カメラの座標に制限をかける
	eye.Clamp(DirectX::SimpleMath::Vector3(-10.0f, 5.0f, -33.0f), DirectX::SimpleMath::Vector3(10.0f, 8.0f, 33.0f));
	this->SetEyePosition(eye);

	DirectX::SimpleMath::Vector3 target = GetTargetPosition();
	target += (mRefTarget - target) * 0.035f;
	
	// 注視点に制限をかける
	target.Clamp(DirectX::SimpleMath::Vector3(-10.0f, 5.0f, -23.0f), DirectX::SimpleMath::Vector3(10.0f, 8.0f, 23.0f));
	this->SetTargetPosition(target);

	CalculateViewMatrix();
}

//-------------------------------------------------------------------
// ビュー行列の算出
// 引数：なし
// 戻り値：なし
//-------------------------------------------------------------------
void FollowCamera::CalculateViewMatrix()
{
	this->SetViewMatrix(
		DirectX::SimpleMath::Matrix::CreateLookAt(
			GetEyePosition(),
			GetTargetPosition(),
			GetUpVector())
	);
}

//-------------------------------------------------------------------
// プロジェクション行列の算出
// 引数：なし
// 戻り値：なし
//-------------------------------------------------------------------
void FollowCamera::CalculateProjectionMatrix()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// ウィンドウサイズの取得
	float width = static_cast<float>(pDR->GetOutputSize().right);
	float height = static_cast<float>(pDR->GetOutputSize().bottom);

	constexpr float fieldOfView = XMConvertToRadians(45.0f);    // 画角
	float aspectRatio = width / height;							// 画面縦横比
	float nearPlane = 1.0f;                                     // カメラから一番近い投影面
	float farPlane = 500.0f;                                    // カメラから一番遠い投影面
	this->SetProjectionMatrix(SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane));
}
