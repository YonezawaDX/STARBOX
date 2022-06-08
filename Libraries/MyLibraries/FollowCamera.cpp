/**
* @file FollowCamera.cpp
* @brief �Ǐ]�J����
* @author
* @date
* @details �Ǐ]�J����
*/
#include "pch.h"
#include "FollowCamera.h"

#include "DeviceResources.h"
#include <Keyboard.h>

// ���O��Ԃ̗��p
using namespace DirectX;
using namespace DirectX::SimpleMath;

// �萔-----------------------------------------------------------------
// �^�[�Q�b�g�̏������_
const DirectX::SimpleMath::Vector3 FollowCamera::TARGET_TO_EYE_VEC = DirectX::SimpleMath::Vector3(0.0f, -2.0f, 30.0f);

// �v���C���[���n�ʂɂ���Ƃ��̎��_
const float FollowCamera::POINT_OF_VIEW_WORK = 1.5f;		

// �v���C���[�����ł���Ƃ��̎��_
const float FollowCamera::POINT_OF_VIEW_BOOST = 7.0f;		
//-------------------------------------------------------------------------------------------------

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
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
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
FollowCamera::~FollowCamera()
{
}

//------------------------------------------------------------------
// �T�v�F�X�V
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void FollowCamera::Update()
{
	DirectX::SimpleMath::Vector3 eye = this->GetEyePosition();

	DirectX::SimpleMath::Vector3 refEye = DirectX::SimpleMath::Vector3(mRefEye.x,mRefEye.y,mRefEye.z);
	eye += (refEye - eye) * 0.035f;

	// �J�����̍��W�ɐ�����������
	eye.Clamp(DirectX::SimpleMath::Vector3(-10.0f, 5.0f, -33.0f), DirectX::SimpleMath::Vector3(10.0f, 8.0f, 33.0f));
	this->SetEyePosition(eye);

	DirectX::SimpleMath::Vector3 target = GetTargetPosition();
	target += (mRefTarget - target) * 0.035f;
	
	// �����_�ɐ�����������
	target.Clamp(DirectX::SimpleMath::Vector3(-10.0f, 5.0f, -23.0f), DirectX::SimpleMath::Vector3(10.0f, 8.0f, 23.0f));
	this->SetTargetPosition(target);

	CalculateViewMatrix();
}

//-------------------------------------------------------------------
// �r���[�s��̎Z�o
// �����F�Ȃ�
// �߂�l�F�Ȃ�
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
// �v���W�F�N�V�����s��̎Z�o
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void FollowCamera::CalculateProjectionMatrix()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// �E�B���h�E�T�C�Y�̎擾
	float width = static_cast<float>(pDR->GetOutputSize().right);
	float height = static_cast<float>(pDR->GetOutputSize().bottom);

	constexpr float fieldOfView = XMConvertToRadians(45.0f);    // ��p
	float aspectRatio = width / height;							// ��ʏc����
	float nearPlane = 1.0f;                                     // �J���������ԋ߂����e��
	float farPlane = 500.0f;                                    // �J���������ԉ������e��
	this->SetProjectionMatrix(SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane));
}
