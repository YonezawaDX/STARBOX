/**
* @file HeartObject.cpp
* @brief HP������I�u�W�F�N�g�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details HP������I�u�W�F�N�gMoveObject���p�����Ă���
*/
#include "pch.h"
#include "HeartObject.h"

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
HeartObject::HeartObject()
	: mHP(0)
{
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
HeartObject::~HeartObject()
{
}

//------------------------------------------------------------------
// �T�v�F�{�X�p�[�c��ǉ�����
// ���� (bossParts)�FHeartObject�̃��j�[�N�|�C���^ 
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void HeartObject::AddBossParts(std::unique_ptr<HeartObject> bossParts)
{
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void HeartObject::Initialize()
{
}

//----------------------------------------------------
// �T�v�F������
// ���� (bossFactory):�{�X�̐����N���X
// �߂�l�F�Ȃ�
//----------------------------------------------------
void HeartObject::Initialize(BossFactory* bossFactory)
{
	UNREFERENCED_PARAMETER(bossFactory);
}

//----------------------------------------------------
// �T�v�F�X�V
// ����:�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void HeartObject::Update()
{
}

//------------------------------------------------------
// �T�v�F�X�V
// ���� (position)�F���W
// ���� (angle)�F�p�x
// ���� (offset)�F�f�̂Ƃ̋���
// ���� (playerPos)�F�v���C���[�̍��W
// ���� (stateNum)�F�{�X�̏��
// �߂�l�F�Ȃ�
//-------------------------------------------------------
void HeartObject::Update(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& angle,
	const DirectX::SimpleMath::Vector3& offset,
	const DirectX::SimpleMath::Vector3& playerPos,
	const int& stateNum
)
{
	UNREFERENCED_PARAMETER(position);
	UNREFERENCED_PARAMETER(angle);
	UNREFERENCED_PARAMETER(offset);
	UNREFERENCED_PARAMETER(playerPos);
	UNREFERENCED_PARAMETER(stateNum);
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void HeartObject::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	UNREFERENCED_PARAMETER(commonStates);
	UNREFERENCED_PARAMETER(camera);
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void HeartObject::Finalize()
{
}

//------------------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void HeartObject::Move()
{
}

//------------------------------------------------------------------
// �T�v�F�p�[�c������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void HeartObject::DeleteParts()
{
}

//-----------------------------------------------------------------------
// �T�v�F�����蔻��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-----------------------------------------------------------------------
void HeartObject::Collision()
{
}

// �Q�b�^�[�A�Z�b�^�[-----------------------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 HeartObject::GetObjectPos() const
{
	return MoveObject::GetObjectPos();
}
//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void HeartObject::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	MoveObject::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 HeartObject::GetObjectDirection() const
{
	return MoveObject::GetObjectDirection();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void HeartObject::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	MoveObject::SetObjectDirection(direction);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 HeartObject::GetObjectSpeed() const
{
	return MoveObject::GetObjectSpeed();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void HeartObject::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	MoveObject::SetObjectSpeed(speed);
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(bool)�F�I�u�W�F�N�g�̎g�p���
//---------------------------------------
bool HeartObject::GetActive() const
{
	return MoveObject::GetActive();
}
//---------------------------------------
// �T�v�F�g�p��Ԃ̃Z�b�^�[
// ����(active)�F�I�u�W�F�N�g�̎g�p���
// �߂�l�F�Ȃ�
//---------------------------------------
void HeartObject::SetActive(const bool& active)
{
	MoveObject::SetActive(active);
}

//---------------------------------------
// �T�v�FHP�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(int)�F�I�u�W�F�N�g��HP
//---------------------------------------
int HeartObject::GetHP() const
{
	return mHP;
}
//---------------------------------------
// �T�v�FHP�̃Z�b�^�[
// ����(hp)�F�I�u�W�F�N�g��HP
// �߂�l�F�Ȃ�
//---------------------------------------
void HeartObject::SetHP(const int& hp)
{
	mHP = hp;
}