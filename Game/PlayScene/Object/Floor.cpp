/**
* @file Floor.cpp
* @brief �������̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �����ڂ���������
*/
#include "pch.h"
#include "Floor.h"

// �萔
// ��������
const float Floor::MOVE_SPEED = 0.5f;

// ���E�̍��W
const float Floor::LIMIT_POS = 5.5f;

// �Ԃ̍��W
const float Floor::OFFSET = 50.0f;

//-------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
Floor::Floor()
{
}
//---------------------------------------------------------
// �T�v�F�f�X�g���N�^
//---------------------------------------------------------
Floor::~Floor()
{
}

//----------------------------------------------------------
// �T�v�F������
// ����()�F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------------
void Floor::Initialize()
{
}


//-----------------------------------------------------------
// �T�v�F�X�V
// ����()�F�Ȃ�
// �߂�l�F�Ȃ�
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
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g
// ����(camera)�F�J����
// �߂�l�F�Ȃ�
//-------------------------------------------------------------
void Floor::Draw(DirectX::CommonStates* commonStates, Camera* camera)
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
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//--------------------------------------------------------------
void Floor::Finalize()
{
}

//--------------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//--------------------------------------------------------------
void Floor::Move()
{
}

// �Q�b�^�[�A�Z�b�^�[---------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Floor::GetObjectPos() const
{
	return Object::GetObjectPos();
}

//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void Floor::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	Object::SetObjectPos(pos);
}