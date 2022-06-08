/**
* @file Cover.cpp
* @brief �R�A�J�o�[�̃N���X
* @author ���V�x��
* @date 2022/05/01
* @details �{�X02�̃R�A�̏�����邭�����Ă���I�u�W�F�N�g
*/
#include "pch.h"

#include "pch.h"
#include "Cover.h"
#include "../BossFactory.h"

//------------------------------------------------------------------
// �T�v�F�{�X�p�[�c��ǉ�����
// ���� (bossParts)�FHeartObject�̃��j�[�N�|�C���^ 
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void Cover::AddBossParts(std::unique_ptr<HeartObject> bossParts)
{
	UNREFERENCED_PARAMETER(bossParts);
}

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// ����(offset)�F�f�̂Ƃ̋���
// ����(pBulletManager)�F�e�̔��ˊǗ����
//------------------------------------------------------------------
Cover::Cover(
	const DirectX::SimpleMath::Vector3& offset,
	BulletManager* pBulletmanager
) :
	mPosOffset(offset),
	mAngleOffset(DirectX::SimpleMath::Vector3::Zero),
	mBossState(0),
	mpBulletManager(pBulletmanager),
	mShootIntervalTimer(0),
	mIsDown(false)
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
Cover::~Cover()
{
	Finalize();
}

//----------------------------------------------------
// �T�v�F������
// ���� (bossFactory):�{�X�̐����N���X
// �߂�l�F�Ȃ�
//----------------------------------------------------
void Cover::Initialize(BossFactory* bossFactory)
{
	UNREFERENCED_PARAMETER(bossFactory);
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
void Cover::Update(
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

	if (GetObjectPos().y <= -10.0f)
	{
		SetActive(false);
	}

	if (mIsDown)
	{
		return;
	}
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
void Cover::Draw(DirectX::CommonStates* commonStates, Camera* camera)
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
		GetObjectDirection().x * 0.05f,
		GetObjectDirection().z * 0.05f
	);


	pRM->GetCmoModel("Cover")->Draw(
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
void Cover::Finalize()
{
}

//------------------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void Cover::Move()
{
	DirectX::SimpleMath::Vector3 downVel = GetObjectPos();
	if (GetHP() <= 0)
	{
		downVel += GetObjectSpeed();
		mIsDown = true;
	}
	SetObjectPos(downVel);
}

//-----------------------------------------------------------------------
// �T�v�F�����蔻��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-----------------------------------------------------------------------
void Cover::Collision()
{
	// ���ׂĂ̒e�Ɠn���ꂽ�ΏۂƂ̔�������
	for (unsigned int i = 0; i < 512; i++)
	{
		// ����̏����Ȃ�Δ��肵�Ȃ�
		if (
			!mpBulletManager->GetBullet(i)->GetActive() ||			// �e�����ˏ�ԂłȂ�
			mpBulletManager->GetBullet(i)->GetShooterType() == Bullet::eShooterType::ENEMY_SHOT
			)
		{
			continue;
		}


		// �����蔻��p�̈ꎞ�ϐ�
		Collision::Sphere bullet;
		Collision::Sphere enemy;

		bullet.center = mpBulletManager->GetBullet(i)->GetObjectPos();
		bullet.radius = 1.0f;

		enemy.center = GetObjectPos();
		enemy.center.y += 5.0f;
		enemy.radius = 5.0f;

		// �������Ă��Ȃ���Ύ���
		if (!Collision::HitCheckSphereToSphere(bullet, enemy))
		{
			continue;
		}

		// �_���[�W�����G�l�~�[
		mpBulletManager->GetBullet(i)->SetActive(false);

		int hp = GetHP();
		hp -= 1;
		SetHP(hp);
	}
}

//---------------------------------------
// �T�v�F�e����
// ����(pos)�F���W
// �߂�l�F�Ȃ�
//---------------------------------------
void Cover::BulletFire(DirectX::SimpleMath::Vector3 pos)
{
	++mShootIntervalTimer %= 20;
	//���ˊp���v�Z����
	DirectX::SimpleMath::Vector3 myPos = GetObjectPos();
	myPos.y += 5.0f;
	myPos.z += 15.0f;
	DirectX::SimpleMath::Vector3 launch = myPos - pos;
	mpBulletManager->Shot(2, myPos, launch);

	if (mShootIntervalTimer == 0)
	{

	}
}

// �Q�b�^�[�A�Z�b�^�[------------------------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Cover::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}
//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void Cover::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Cover::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void Cover::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 Cover::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}
//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void Cover::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(bool)�F�I�u�W�F�N�g�̎g�p���
//---------------------------------------
bool Cover::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Z�b�^�[
// ����(active)�F�I�u�W�F�N�g�̎g�p���
// �߂�l�F�Ȃ�
//---------------------------------------
void Cover::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// �T�v�FHP�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(int)�F�I�u�W�F�N�g��HP
//---------------------------------------
int Cover::GetHP() const
{
	return HeartObject::GetHP();
}
//---------------------------------------
// �T�v�FHP�̃Z�b�^�[
// ����(hp)�F�I�u�W�F�N�g��HP
// �߂�l�F�Ȃ�
//---------------------------------------
void Cover::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}