/**
* @file MoveObject.cpp
* @brief �����I�u�W�F�N�g�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �����I�u�W�F�N�gObject���p�����Ă���
*/
#include "pch.h"
#include "MoveObject.h"

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
MoveObject::MoveObject()
	: mDirection(DirectX::SimpleMath::Vector3::Zero)
	, mSpeed(0.0f)
	, mIsActive(false)
{
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
MoveObject::~MoveObject()
{
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void MoveObject::Initialize()
{
}
//----------------------------------------------------
// �T�v�F�X�V
// ����:�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void MoveObject::Update()
{
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void MoveObject::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	UNREFERENCED_PARAMETER(commonStates);
	UNREFERENCED_PARAMETER(camera);
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void MoveObject::Finalize()
{
}

//------------------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void MoveObject::Move()
{
}

//------------------------------------------------------------------
// �T�v�F�p�[�c������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void MoveObject::DeleteParts()
{
}

//-----------------------------------------------------------------------
// �T�v�F�����蔻��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-----------------------------------------------------------------------
void MoveObject::Collision()
{
}

// �Q�b�^�[�A�Z�b�^�[-----------------------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 MoveObject::GetObjectPos() const
{
	return Object::GetObjectPos();
}

//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void MoveObject::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	Object::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//--------------------------------------
DirectX::SimpleMath::Vector3 MoveObject::GetObjectDirection() const
{
	return mDirection;
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void MoveObject::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	mDirection = direction;
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 MoveObject::GetObjectSpeed() const
{
	return mSpeed;
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void MoveObject::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	mSpeed = speed;
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(bool)�F�I�u�W�F�N�g�̎g�p���
//---------------------------------------
bool MoveObject::GetActive() const
{
	return mIsActive;
}
//---------------------------------------
// �T�v�F�g�p��Ԃ̃Z�b�^�[
// ����(active)�F�I�u�W�F�N�g�̎g�p���
// �߂�l�F�Ȃ�
//---------------------------------------
void MoveObject::SetActive(const bool& active)
{
	mIsActive = active;
}
