/**
* @file	TitleBackground.cpp
* @brief �^�C�g���̔w�i
* @author ���V�x��
* @date 2022/04/26
* @details ��]���Ă���^�C�g���̔w�i
*/
#include "pch.h"
#include "TitleBackground.h"
#include <Effects.h>

// �萔------------------------------------------

// ��������
const float TitleBackground::MOVE_SPEED = 0.01f;
//------------------------------------------------


//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
TitleBackground::TitleBackground():
	mpModel(nullptr)
{
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
TitleBackground::~TitleBackground()
{
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void TitleBackground::Initialize()
{
	// ���W���w��
	SetObjectPos(DirectX::SimpleMath::Vector3::Zero);

	// �������w��
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);

	// ���x���w��
	SetObjectSpeed(DirectX::SimpleMath::Vector3::Zero);

	auto pRM = ResourceManager::GetInstance();
	// ���f���ۑ��p
	mpModel = pRM->GetCmoModel("TitleBackground");
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

//----------------------------------------------------
// �T�v�F�X�V
// ����:�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void TitleBackground::Update()
{
	Move();
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void TitleBackground::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	DirectX::SimpleMath::Vector3 pos = GetObjectPos();
	//�f�o�C�X�R���e�L�X�g�̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// �ˉe�s��̎擾
	DirectX::SimpleMath::Matrix projection = camera->GetProjectionMatrix();
	// �r���[�s��̎擾
	DirectX::SimpleMath::Matrix view = camera->GetViewMatrix();

	// ���[���h���W�̎擾
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(GetObjectPos());

	//world *= DirectX::SimpleMath::Matrix::CreateScale(0.1f);

	// ���f���̉�]
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		GetObjectDirection().y * 0.05f,
		GetObjectDirection().x * 0.05f,
		GetObjectDirection().z * 0.05f
	);


	// ���f���`��
	mpModel->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(q) * world,
		view,
		projection
	);
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void TitleBackground::Finalize()
{
	if(mpModel != nullptr)
	mpModel = nullptr;
}

//------------------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void TitleBackground::Move()
{
	DirectX::SimpleMath::Vector3 dir = GetObjectDirection();

	dir.x += MOVE_SPEED;
	dir.y += MOVE_SPEED;

	SetObjectDirection(dir);
}

// �Q�b�^�[�A�Z�b�^�[------------------------------------------------------------------------
//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 TitleBackground::GetObjectPos() const
{
	return MoveObject::GetObjectPos();
}
//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void TitleBackground::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	MoveObject::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 TitleBackground::GetObjectDirection() const
{
	return MoveObject::GetObjectDirection();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void TitleBackground::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	MoveObject::SetObjectDirection(direction);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 TitleBackground::GetObjectSpeed() const
{
	return MoveObject::GetObjectSpeed();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void TitleBackground::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	MoveObject::SetObjectSpeed(speed);
}
