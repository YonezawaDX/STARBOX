/**
* @file BackGround.h
* @brief �v���C�V�[���w�i�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �v���C�V�[���̔w�i
*/
#include "pch.h"
#include "BackGround.h"
#include <Effects.h>

//-------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
BackGround::BackGround():
	mpModel(nullptr)
{
}

//---------------------------------------------------------
// �T�v�F�f�X�g���N�^
//---------------------------------------------------------
BackGround::~BackGround()
{
}

//----------------------------------------------------------
// �T�v�F������
// ����()�F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------------
void BackGround::Initialize()
{
	// ���f���̕ۑ�
	auto pRM = ResourceManager::GetInstance();

	mpModel = pRM->GetCmoModel("PlayBackGround");

	mpModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights)
			{
				//���C�g�̉e�����Ȃ���

				lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}
			DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				// �G�~�b�V�����F�𔒂ɐݒ肷��
				basicEffect->SetEmissiveColor(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
			}
		});
}

//-----------------------------------------------------------
// �T�v�F�X�V
// ����()�F�Ȃ�
// �߂�l�F�Ȃ�
//-----------------------------------------------------------
void BackGround::Update()
{
}

//-------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g
// ����(camera)�F�J����
// �߂�l�F�Ȃ�
//-------------------------------------------------------------
void BackGround::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{

	//�f�o�C�X�R���e�L�X�g�̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// �ˉe�s��̎擾
	DirectX::SimpleMath::Matrix projection = camera->GetProjectionMatrix();
	// �r���[�s��̎擾
	DirectX::SimpleMath::Matrix view = camera->GetViewMatrix();

	// ���[���h���W�̎擾
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(GetObjectPos());


	mpModel->Draw(
		context,
		*commonStates,
		world,
		view,
		projection
	);

}

//--------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//--------------------------------------------------------------
void BackGround::Finalize()
{
}

// �Z�b�^�[�A�Q�b�^�[---------------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 BackGround::GetObjectPos() const
{
	return Object::GetObjectPos();
}

//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void BackGround::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	Object::SetObjectPos(pos);
}