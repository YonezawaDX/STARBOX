/**
* @file Tire.cpp
* @brief �^�C���N���X
* @author ���V�x��
* @date 2022/05/11
* @details �{�X02�̃^�C���N���X
*/
#include "pch.h"
#include "Tire.h"
#include "../BossFactory.h"

//------------------------------------------------------------------
// �T�v�F�{�X�p�[�c��ǉ�����
// ���� (bossParts)�FHeartObject�̃��j�[�N�|�C���^ 
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void Tire::AddBossParts(std::unique_ptr<HeartObject> bossParts)
{
	UNREFERENCED_PARAMETER(bossParts);
}

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// ����(offset)�F�f�̂Ƃ̋���
//------------------------------------------------------------------
Tire::Tire(const DirectX::SimpleMath::Vector3& offset) :
	mPosOffset(offset),
	mAngleOffset(DirectX::SimpleMath::Vector3::Zero),
	mBossState(0),
	mIsDown(false),
	mRotate(0)
{
	SetObjectPos(DirectX::SimpleMath::Vector3::Zero);
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);
	SetObjectSpeed(DirectX::SimpleMath::Vector3(-0.2f, -0.2f, 0.2f));
	SetHP(3);
	SetActive(true);
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
Tire::~Tire()
{
	Finalize();
}

//----------------------------------------------------
// �T�v�F������
// ���� (bossFactory):�{�X�̐����N���X
// �߂�l�F�Ȃ�
//----------------------------------------------------
void Tire::Initialize(BossFactory* bossFactory)
{
	UNREFERENCED_PARAMETER(bossFactory);
}

//------------------------------------------------------
// �T�v�F�X�V
// ���� (position)�F���W
// ���� (angle)�F�p�x
// ���� (offset)�F�f�̂Ƃ̊p�x
// ���� (playerPos)�F�v���C���[�̍��W
// ���� (stateNum)�F�{�X�̏��
// �߂�l�F�Ȃ�
//-------------------------------------------------------
void Tire::Update(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& angle,
	const DirectX::SimpleMath::Vector3& offset,
	const DirectX::SimpleMath::Vector3& playerPos,
	const int& stateNum
)
{
	UNREFERENCED_PARAMETER(playerPos);

	Move();
	// �{�X�̏�Ԃ��i�[
	mBossState = stateNum;

	// �ʒu��ݒ肷��
	SetObjectPos(position + mPosOffset);

	// ������ݒ肷��
	SetObjectDirection(angle + offset);

	// �����̃I�t�Z�b�g
	mAngleOffset = offset;
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void Tire::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
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
		(GetObjectDirection().x + mRotate) * 0.05f,
		GetObjectDirection().z * 0.05f
	);

	// ���f���̕`��
	pRM->GetCmoModel("Tire")->Draw(
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
void Tire::Finalize()
{
}

//------------------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void Tire::Move()
{
	mRotate += Boss02::PARTS_ROTATE;
}

//-----------------------------------------------------------------------
// �T�v�F�����蔻��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-----------------------------------------------------------------------
void Tire::Collision()
{
	// �^�C���ɂ͓����蔻��݂͐��Ȃ�
	return;
}

// �Q�b�^�[�A�Z�b�^�[------------------------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Tire::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}
//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void Tire::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Tire::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void Tire::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 Tire::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void Tire::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(bool)�F�I�u�W�F�N�g�̎g�p���
//---------------------------------------
bool Tire::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Z�b�^�[
// ����(active)�F�I�u�W�F�N�g�̎g�p���
// �߂�l�F�Ȃ�
//---------------------------------------
void Tire::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// �T�v�FHP�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(int)�F�I�u�W�F�N�g��HP
//---------------------------------------
int Tire::GetHP() const
{
	return HeartObject::GetHP();
}
//---------------------------------------
// �T�v�FHP�̃Z�b�^�[
// ����(hp)�F�I�u�W�F�N�g��HP
// �߂�l�F�Ȃ�
//---------------------------------------
void Tire::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}