/**
* @file BigArm.cpp
* @brief �傫�Șr�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �G���ˏo����傫���r
*/

#include "pch.h"
#include "BigArm.h"
#include "../BossFactory.h"

//----------------------------------------------------------------
// �T�v�F�{�X�p�[�c��ǉ�����֐�
// ����(bossParts)�F�ǉ��������{�X�̃p�[�c
// �߂�l�F�Ȃ�
// �ڍׁF�t�@�N�g���̊֌W�Ŋe�p�[�c�ɒǉ��Ȃ���΂����Ȃ�
//----------------------------------------------------------------
void BigArm::AddBossParts(std::unique_ptr<HeartObject> bossParts)
{
	UNREFERENCED_PARAMETER(bossParts);
}

//----------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// ����(offset)�F�e�p�[�c�Ƃ̋���
// ����(pEnemies)�F�ׂ����G�̃|�C���^
// ����(pBulletManager)�F�e�̔��˗p
//----------------------------------------------------------------
BigArm::BigArm(
	const DirectX::SimpleMath::Vector3& offset, 
	EnemyManager* pEnemies,
	BulletManager* pBulletManager
):
	mPosOffset(offset),
	mAngleOffset(DirectX::SimpleMath::Vector3::Zero),
	mpEnemies(pEnemies),
	mBossState(0),
	mpBullets(pBulletManager),
	mIsDown(false)
{
	SetObjectPos(DirectX::SimpleMath::Vector3::Zero);
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);
	SetObjectSpeed(DirectX::SimpleMath::Vector3(0.2f,-0.2f,0.2f));
	SetHP(5);
	SetActive(true);
}

//------------------------------------
// �T�v�F�f�X�g���N�^
//------------------------------------
BigArm::~BigArm()
{
	Finalize();
}

//-----------------------------------------------------
// �T�v�F������
// ���� (bossFactory):�{�X�̐����N���X
// �߂�l�F�Ȃ�
//-----------------------------------------------------
void BigArm::Initialize(BossFactory* bossFactory)
{
	UNREFERENCED_PARAMETER(bossFactory);
}


void BigArm::Update(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& angle,
	const DirectX::SimpleMath::Vector3& offset,
	const DirectX::SimpleMath::Vector3& playerPos,
	const int& stateNum
)
{
	Move();
	// �{�X�̏�Ԃ��i�[
	mBossState = stateNum;

	if (GetObjectPos().y<= -10.0f)
	{
		SetActive(false);
	}
	
	if (mIsDown)
	{
		return;
	}

	// �ʒu��ݒ肷��
	SetObjectPos(position);

	// ������ݒ肷��
	SetObjectDirection(angle);

	// �����̃I�t�Z�b�g
	mAngleOffset = offset;

	// �e����
	BulletFire(playerPos);
}

//-----------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//-----------------------------------------------------------
void BigArm::Draw(DirectX::CommonStates* commonStates, Camera* camera)
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
	DirectX::SimpleMath::Matrix offsetPosWorld = DirectX::SimpleMath::Matrix::CreateTranslation(mPosOffset);
	DirectX::SimpleMath::Matrix objectPosWorld = DirectX::SimpleMath::Matrix::CreateTranslation(GetObjectPos());


	// ���f���̉�]
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		GetObjectDirection().y * 0.05f,
		GetObjectDirection().x * 0.05f,
		GetObjectDirection().z * 0.05f
	);

	pRM->GetCmoModel("BossBigArm")->Draw(
		context,
		*commonStates,
		offsetPosWorld * DirectX::SimpleMath::Matrix::CreateFromQuaternion(q) * objectPosWorld,
		view,
		projection
	);
}

//----------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------
void BigArm::Finalize()
{
}

//------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------
void BigArm::Move()
{
	DirectX::SimpleMath::Vector3 downVel = GetObjectPos();
	if (GetHP() <= 0)
	{
		downVel += GetObjectSpeed();
		mIsDown = true;
	}
	SetObjectPos(downVel);
}

//---------------------------------------
// �T�v�F�����蔻��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//---------------------------------------
void BigArm::Collision()
{
	// ���ׂĂ̒e�Ɠn���ꂽ�ΏۂƂ̔�������
	for (unsigned int i = 0; i < 512; i++)
	{
		// ����̏����Ȃ�Δ��肵�Ȃ�
		if (
			!mpBullets->GetBullet(i)->GetActive() ||			// �e�����ˏ�ԂłȂ�
			mpBullets->GetBullet(i)->GetShooterType() == Bullet::eShooterType::ENEMY_SHOT
			)
		{
			continue;
		}

		// �����蔻��p�̈ꎞ�ϐ�
		Collision::Sphere bullet;
		Collision::Sphere enemy;

		bullet.center = mpBullets->GetBullet(i)->GetObjectPos();
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
		mpBullets->GetBullet(i)->SetActive(false);

		int hp = GetHP();
		hp -= 1;
		SetHP(hp);
	}
}

//---------------------------------------
// �T�v�F�G�ˏo
// ����(pos)�F���W
// �߂�l�F�Ȃ�
//---------------------------------------
void BigArm::BulletFire(DirectX::SimpleMath::Vector3 pos)
{
	//���ˊp���v�Z����
	DirectX::SimpleMath::Vector3 myPos = GetObjectPos();
	myPos.y += 5.0f;
	myPos.z += 15.0f;
	DirectX::SimpleMath::Vector3 launch = myPos - pos;
	bool move = true;

	if (mBossState != 4)
	{
		move = false;
	}

	// �G�𐶐�����
	mpEnemies->BossUpdate(1, myPos, launch, 1, move);
}

// �Q�b�^�[�A�Z�b�^�[------------------------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 BigArm::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}

//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void BigArm::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 BigArm::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}

//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void BigArm::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 BigArm::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}

//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void BigArm::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(bool)�F�I�u�W�F�N�g�̎g�p���
//---------------------------------------
bool BigArm::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Z�b�^�[
// ����(active)�F�I�u�W�F�N�g�̎g�p���
// �߂�l�F�Ȃ�
//---------------------------------------
void BigArm::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// �T�v�FHP�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g��HP
//---------------------------------------
int BigArm::GetHP() const
{
	return HeartObject::GetHP();
}

//---------------------------------------
// �T�v�FHP�̃Z�b�^�[
// ����(hp)�F�I�u�W�F�N�g��HP
// �߂�l�F�Ȃ�
//---------------------------------------
void BigArm::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}
