/**
* @file Camera.cpp
* @brief �J����
* @author
* @date
* @details �J����
*/
#include "pch.h"
#include "Camera.h"

#include "DeviceResources.h"


using namespace DirectX;

// �萔�̏�����
const float Camera::DEFAULT_CAMERA_DISTANCE = 5.0f;

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
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
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
Camera::~Camera()
{
}
//------------------------------------------------------------------
// �T�v�F�X�V
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void Camera::Update()
{
}

//-------------------------------------------------------------------
// �r���[�s��̎Z�o
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void Camera::CalculateViewMatrix()
{
	mView = DirectX::SimpleMath::Matrix::CreateLookAt(mEye, mTarget, mUp);
}

//-------------------------------------------------------------------
// �v���W�F�N�V�����s��̎Z�o
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void Camera::CalculateProjectionMatrix()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// �E�B���h�E�T�C�Y�̎擾
	float width = static_cast<float>(pDR->GetOutputSize().right);
	float height = static_cast<float>(pDR->GetOutputSize().bottom);

	constexpr float fieldOfView = XMConvertToRadians(45.0f);    // ��p
	float aspectRatio = width / height;							// ��ʏc����
	float nearPlane = 1.0f;                                     // �J���������ԋ߂����e��
	float farPlane = 1000.0f;                                    // �J���������ԉ������e��
	mProjection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);
}
