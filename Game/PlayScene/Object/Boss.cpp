/**
* @file Boss.cpp
* @brief �{�X�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �{�X01�̃N���X
*/
#include "pch.h"
#include "Boss.h"
#include "../BossFactory.h"
#include "Game/PlayScene/Collision.h"
#include <random>


// �萔�̃p�����[�^�����߂�
const DirectX::SimpleMath::Vector3 Boss::SPEED = DirectX::SimpleMath::Vector3(2.0f, 2.0f, 2.0f);
const DirectX::SimpleMath::Vector3 Boss::START_POS = DirectX::SimpleMath::Vector3(0.0f, 20.0f, 50.0f);
const DirectX::SimpleMath::Vector3 Boss::MOVE_POS = DirectX::SimpleMath::Vector3(0.0f, 2.0f, -50.0f);

// ���ꂼ��̃p�[�c�̍��W
const DirectX::SimpleMath::Vector3 Boss::ARM_OFFSET_01 = DirectX::SimpleMath::Vector3(-10.0f, 8.0f, 0.0f);
const DirectX::SimpleMath::Vector3 Boss::ARM_OFFSET_02 = DirectX::SimpleMath::Vector3(-10.0f, 0.0f, 0.0f);
const DirectX::SimpleMath::Vector3 Boss::ARM_OFFSET_03 = DirectX::SimpleMath::Vector3( 10.0f, 0.0f, 0.0f);

// �����̒萔
const DirectX::SimpleMath::Vector3 Boss::BOSS_MOVE_01 = DirectX::SimpleMath::Vector3(-15.0f, 2.0f, -50.0f);
const DirectX::SimpleMath::Vector3 Boss::BOSS_MOVE_02 = DirectX::SimpleMath::Vector3(15.0f, 2.0f, -50.0f);

// �{�X�̃A���O���̒萔
const float Boss::RESULT_ANGLE = 20.0f;
const float Boss::RESULT_COUNT = 10.0f;

//-------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// ����(pBulletManager)�F�e�̔��ˊǗ����
// ����(pEnemyManager)�F�G�̊Ǘ����
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
Boss::Boss(
	BulletManager* pBulletManager,
	EnemyManager* pEnemyManager
):
	mpBody(nullptr),
	mBossState(BOSS_STATE::NONE),
	mCount(0.0f),
	mTempPos(DirectX::SimpleMath::Vector3::Zero),
	mResultPos(DirectX::SimpleMath::Vector3::Zero),
	mTempAngle(0.0f),
	mResultAngle(0.0f),
	mpBullets(pBulletManager),
	mpEnemies(pEnemyManager)
{
	SetObjectPos(Boss::START_POS);
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);
	SetActive(true);
}

//---------------------------------------------------------
// �T�v�F�f�X�g���N�^
//---------------------------------------------------------
Boss::~Boss()
{
	// Finalize���Ăяo��
	Finalize();
}

//----------------------------------------------------------
// �T�v�F������
// ����()�F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------------
void Boss::Initialize()
{
	// BossFactory�I�u�W�F�N�g�𐶐�����
	BossFactory bossFactory(mpBullets, mpEnemies);
	// BossFactory�I�u�W�F�N�g������������
	bossFactory.Initialize();

	// body�I�u�W�F�N�g�𐶐�����
	mpBody = bossFactory.Create(BOSS_PARTS_ID::BODY, DirectX::SimpleMath::Vector3::Zero);
	
	// body�I�u�W�F�N�g��SmallArm1��ǉ�����
	mpBody->AddBossParts(bossFactory.Create(BOSS_PARTS_ID::SMALL_ARM, ARM_OFFSET_01));
	// body�I�u�W�F�N�g��SmallArm2��ǉ�����
	mpBody->AddBossParts(bossFactory.Create(BOSS_PARTS_ID::SMALL_ARM, ARM_OFFSET_02));
	// body�I�u�W�F�N�g��BigArm��ǉ�����
	mpBody->AddBossParts(bossFactory.Create(BOSS_PARTS_ID::BIG_ARM, ARM_OFFSET_03));

	// �o��V�[���ɕύX����
	mBossState = BOSS_STATE::ADMISSION;
}

//-----------------------------------------------------------
// �T�v�F�X�V
// ����()�F�Ȃ�
// �߂�l�F�Ȃ�
//-----------------------------------------------------------
void Boss::Update()
{
	// �ԑ̂��X�V
	//mpBody->Update(GetObjectPos(), GetObjectDirection(), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	// ����
	Move();
	Collision();

}

//------------------------------------------------------------
// �T�v�F�X�V
// ����(playerPos)�F�v���C���[�̍��W
// �߂�l�F�Ȃ�
//------------------------------------------------------------
void Boss::Update(DirectX::SimpleMath::Vector3 playerPos)
{
	// �ԑ̂��X�V
	mpBody->Update(
		GetObjectPos(),
		GetObjectDirection(),
		DirectX::SimpleMath::Vector3::Zero,
		playerPos,
		static_cast<int>(mBossState)
	);
	// ����
	Move();
	Collision();

	if (!mpBody->GetActive())
	{
		SetActive(false);
	}
}

//-------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g
// ����(camera)�F�J����
// �߂�l�F�Ȃ�
//-------------------------------------------------------------
void Boss::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	//�ԑ̂�`�悷��
	mpBody->Draw(commonStates, camera);
}

//--------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//--------------------------------------------------------------
void Boss::Finalize()
{
	// �ԑ̂����Z�b�g����
	//mpBody.reset();
}

//--------------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//--------------------------------------------------------------
void Boss::Move()
{
	// ���W
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;

	// �p�x
	DirectX::SimpleMath::Vector3 angle = DirectX::SimpleMath::Vector3::Zero;

	float resultCount = 0.0f;

	// �{�X�̏�Ԃɉ����ē���
	switch (mBossState)
	{
		case BOSS_STATE::ADMISSION:
			mResultPos = MOVE_POS;
			resultCount = RESULT_COUNT;
			break;
		case BOSS_STATE::ADMISSION_AFTER:
			mBossState = static_cast<BOSS_STATE>((rand() % 2) + 3);
			return;
		case BOSS_STATE::LEFT_MOVE:
			mResultPos = BOSS_MOVE_01;
			mResultAngle = RESULT_ANGLE;
			resultCount = RESULT_COUNT;
			break;
		case BOSS_STATE::RIGHT_MOVE:
			mResultPos = BOSS_MOVE_02;
			mResultAngle = -RESULT_ANGLE;
			resultCount = RESULT_COUNT;
			break;
		case BOSS_STATE::ROLL_MOVE:
			break;
		default:
			break;
	}

	// �����O�̍��W����ꍞ��
	if (mCount <= 0.0f)
	{
		mTempPos = GetObjectPos();
		mTempAngle = GetObjectDirection().y;
	}

	// 1�b��1/60�b
	mCount += 1.0f / (resultCount * 60.0f);

	// ���W���v�Z����
	pos = DirectX::SimpleMath::Vector3::SmoothStep(mTempPos, mResultPos, mCount);
	
	// �p�x���v�Z����
	angle = DirectX::SimpleMath::Vector3::SmoothStep(
		DirectX::SimpleMath::Vector3(0.0f,mTempAngle,0.0f),
		DirectX::SimpleMath::Vector3(0.0f, mResultAngle, 0.0f),
		mCount
	);
	// ���W���Z�b�g����
	SetObjectPos(pos);
	SetObjectDirection(angle);

	// �Ō�܂œ�����������ɐ؂�ւ���
	if (mResultPos == GetObjectPos())
	{
		mCount = 0.0f;
		mBossState = BOSS_STATE::ADMISSION_AFTER;
	}
}

//--------------------------------------------------------------------------
// �T�v�F�����蔻��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//--------------------------------------------------------------------------
void Boss::Collision()
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
		enemy.radius = 15.0f;

		// �������Ă��Ȃ���Ύ���
		if (!Collision::HitCheckSphereToSphere(bullet, enemy))
		{
			continue;
		}

		// �_���[�W�����G�l�~�[
		// �e�p�[�c�Ɉڍs����
		mpBody->Collision();
	}
}

// �Q�b�^�[�A�Z�b�^�[----------------------------------------------------------------------------------

//---------------------------------------
// �T�v�F���W�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Boss::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}

//---------------------------------------
// �T�v�F���W�̃Z�b�^�[
// ����(pos)�F�I�u�W�F�N�g�̍��W
// �߂�l�F�Ȃ�
//---------------------------------------
void Boss::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̍��W
//---------------------------------------
DirectX::SimpleMath::Vector3 Boss::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}

//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(direction)�F�I�u�W�F�N�g�̌���
// �߂�l�F�Ȃ�
//---------------------------------------
void Boss::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// �T�v�F�����̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g�̑���
//---------------------------------------
DirectX::SimpleMath::Vector3 Boss::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}

//---------------------------------------
// �T�v�F�����̃Z�b�^�[
// ����(speed)�F�I�u�W�F�N�g�̑���
// �߂�l�F�Ȃ�
//---------------------------------------
void Boss::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(bool)�F�I�u�W�F�N�g�̎g�p���
//---------------------------------------
bool Boss::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// �T�v�F�g�p��Ԃ̃Z�b�^�[
// ����(active)�F�I�u�W�F�N�g�̎g�p���
// �߂�l�F�Ȃ�
//---------------------------------------
void Boss::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// �T�v�FHP�̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(Vector3)�F�I�u�W�F�N�g��HP
//---------------------------------------
int Boss::GetHP() const
{
	return mpBody->GetHP();
}

//---------------------------------------
// �T�v�FHP�̃Z�b�^�[
// ����(hp)�F�I�u�W�F�N�g��HP
// �߂�l�F�Ȃ�
//---------------------------------------
void Boss::SetHP(const int& hp)
{
	UNREFERENCED_PARAMETER(hp);
	HeartObject::SetHP(mpBody->GetHP());
}
