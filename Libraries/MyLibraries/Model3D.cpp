/**
* @file Model3D.cpp
* @brief ���f��3D�̃N���X
* @author ���V�x��
* @date
* @details ���f�����ȈՓI�ɏo����悤�ɂ���
*/
#include "pch.h"
#include "Model3D.h"

#include <Effects.h>
#include "DeviceResources.h"
#include "Libraries/MyLibraries/Camera.h"

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
Model3D::Model3D()
	:mModel(nullptr)
	,mRotateX(0.0f)
	,mRotateY(0.0f)
	,mRotateZ(0.0f)
{
}


//----------------------------------------------------
// �T�v�F������
// ����(fileName): ���f���̃t�@�C����
// �߂�l�F�Ȃ�
//----------------------------------------------------
void Model3D::Initialize(const wchar_t* fileName)
{
	// �f�o�C�X�̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// ���f���f�[�^�̓����Ă���t�H���_�̎w��
	std::unique_ptr<DirectX::EffectFactory> factory = std::make_unique<DirectX::EffectFactory>(device);
	factory->SetDirectory(L"Resources/Models");

	// 3D���f���̃��[�h
	mModel = DirectX::Model::CreateFromCMO(device, fileName, *factory);
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(world)�F���[���h���W
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void Model3D::Draw(DirectX::CommonStates* commonStates, DirectX::SimpleMath::Matrix* world, Camera* camera)
{
	//�f�o�C�X�R���e�L�X�g�̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// �ˉe�s��̎擾
	DirectX::SimpleMath::Matrix projection = camera->GetProjectionMatrix();

	// �r���[�s��̎擾
	DirectX::SimpleMath::Matrix view = camera->GetViewMatrix();

	// ���f���̉�]���s
	// ���f���̕`��
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
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void Model3D::Finalize()
{
}
