/**
* @file Camera.cpp
* @brief カメラ
* @author
* @date
* @details カメラ
*/
#include "pch.h"
#include "Camera.h"

#include "DeviceResources.h"


using namespace DirectX;

// 定数の初期化
const float Camera::DEFAULT_CAMERA_DISTANCE = 5.0f;

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
Camera::Camera()
	: mView(DirectX::SimpleMath::Matrix::Identity)
	, mEye(0.0f, 2.0f, 20.0f)
	, mTarget(0.0f, 0.0f, 0.0f)
	, mUp(0.0f, 1.0f, 0.0f)
{
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}


//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
Camera::~Camera()
{
}
//------------------------------------------------------------------
// 概要：更新
// 引数：なし
// 戻り値：なし
//-------------------------------------------------------------------
void Camera::Update()
{
}

//-------------------------------------------------------------------
// ビュー行列の算出
// 引数：なし
// 戻り値：なし
//-------------------------------------------------------------------
void Camera::CalculateViewMatrix()
{
	mView = DirectX::SimpleMath::Matrix::CreateLookAt(mEye, mTarget, mUp);
}

//-------------------------------------------------------------------
// プロジェクション行列の算出
// 引数：なし
// 戻り値：なし
//-------------------------------------------------------------------
void Camera::CalculateProjectionMatrix()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// ウィンドウサイズの取得
	float width = static_cast<float>(pDR->GetOutputSize().right);
	float height = static_cast<float>(pDR->GetOutputSize().bottom);

	constexpr float fieldOfView = XMConvertToRadians(45.0f);    // 画角
	float aspectRatio = width / height;							// 画面縦横比
	float nearPlane = 1.0f;                                     // カメラから一番近い投影面
	float farPlane = 1000.0f;                                    // カメラから一番遠い投影面
	mProjection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);
}
