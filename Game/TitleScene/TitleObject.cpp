/**
* @file TitleObject.cpp
* @brief �^�C�g���I�u�W�F�N�g
* @author ���V�x��
* @date 2022/04/26
* @details �^�C�g���̕������f��
*/
#include "pch.h"
#include "TitleObject.h"

// �萔--------------------------------------------------
// �I�u�W�F�N�g�̍��W
const DirectX::SimpleMath::Vector3 TitleObject::START_POS = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
//-------------------------------------------------------

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
TitleObject::TitleObject()
{
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
TitleObject::~TitleObject()
{
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void TitleObject::Initialize()
{
	// ���W���w��
	SetObjectPos(START_POS);

	// �������w��
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);

	// ���x���w��
	SetObjectSpeed(DirectX::SimpleMath::Vector3::Zero);
}

//----------------------------------------------------
// �T�v�F�X�V
// ����:�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void TitleObject::Update()
{
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void TitleObject::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	DirectX::SimpleMath::Vector3 pos = GetObjectPos();

	auto pRM = ResourceManager::GetInstance();
	//�f�o�C�X�R���e�L�X�g�̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// �ˉe�s��̎擾
	DirectX::SimpleMath::Matrix projection = camera->GetProjectionMatrix();
	// �r���[�s��̎擾
	DirectX::SimpleMath::Matrix view = camera->GetViewMatrix();

	// ���[���h���W�̎擾
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(GetObjectPos());

	// ���f���̉�]
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		GetObjectDirection().y * 0.05f,
		GetObjectDirection().x * 0.05f,
		GetObjectDirection().z * 0.05f
	);


	pRM->GetCmoModel("Title")->Draw(
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
void TitleObject::Finalize()
{
}

//------------------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void TitleObject::Move()
{
}

// �Q�b�^�[�A�Z�b�^�[------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 TitleObject::GetObjectPos() const
{
	return MoveObject::GetObjectPos();
}
//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void TitleObject::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	MoveObject::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 TitleObject::GetObjectDirection() const
{
	return MoveObject::GetObjectDirection();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void TitleObject::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	MoveObject::SetObjectDirection(direction);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 TitleObject::GetObjectSpeed() const
{
	return MoveObject::GetObjectSpeed();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void TitleObject::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	MoveObject::SetObjectSpeed(speed);
}
