/**
* @file BulletManager.cpp
* @brief �e�̊Ǘ��҃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �e�̊Ǘ�������A���˂Ȃ�
*/
#include "pch.h"
#include "BulletManager.h"
#include "Game/PlayScene/Object/Enemy.h"
#include "Game/PlayScene/Object/Player.h"

#include "Libraries/MyLibraries/Model3D.h"
#include "Game/PlayScene/Object/Boss.h"

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
BulletManager::BulletManager()
	: mBullets{}
	, mBulletModel3D{}
{
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
BulletManager::~BulletManager()
{
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void BulletManager::Initialize()
{
	// �e�ۂ̗ʂ̊m��
	mBullets.resize(512);

	// �e�ۂ̃��f�������[�h
	mBulletModel3D = std::make_unique<Model3D>();
	mBulletModel3D->Initialize(L"Resources/Models/Bullet.cmo");

	// ���ׂĂ̒e�𖢎g�p��Ԃɂ���
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i] = std::make_unique<Bullet>();
		mBullets[i]->SetActive(false);
	}
}

//----------------------------------------------------
// �T�v�F�X�V
// ����:�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void BulletManager::Update()
{
	// �v���C���[�̒e�̍X�V
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->Update();
	}
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void BulletManager::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	// �v���C���[�̒e�̍X�V
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->Draw(commonStates,camera);
	}
}

//----------------------------------------------------------------------
// �T�v�F�e�̔���
// ����(shooterType)�F���˂���G���e�B�e�B
// ����(pos)�F���W
// ����(angle)�F�p�x
// �߂�l(bool)�F�����Ă��邩�m�F
//---------------------------------------------------------------------
bool BulletManager::Shot(int shooterType, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 angle)
{
	bool res = false;

	// ���ˉ\�Ȓe��T��
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		// �A�N�e�B�u(�g�p��)�Ȃ玟��
		if (mBullets[i]->GetActive() == true)
		{
			continue;
		}

		// �g�p����Ă��Ȃ��Ȃ珉����
		mBullets[i]->Initialize(mBulletModel3D.get(), shooterType, pos, angle);

		// �e�̔��˂ɐ���
		res = true;

		// �����𒆒f����
		break;
	}

	return res;
}

//------------------------------------------------------------------
// �T�v�F�G�Ƃ̓����蔻��
// ���� (pEnemy)�F�G�̃|�C���^
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void BulletManager::CheckHitEnemy(Enemy* pEnemy)
{
	// ���ׂĂ̒e�Ɠn���ꂽ�ΏۂƂ̔�������
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		// ����̏����Ȃ�Δ��肵�Ȃ�
		if (
			!mBullets[i]->GetActive() ||			// �e�����ˏ�ԂłȂ�
			pEnemy->GetHP() <= 0 ||				// �G�̗̑͂��Ȃ�
			mBullets[i]->GetShooterType() == Bullet::eShooterType::ENEMY_SHOT
			)
		{
			continue;
		}


		// �����蔻��p�̈ꎞ�ϐ�
		Collision::Sphere bullet;
		Collision::Sphere enemy;

		bullet.center = mBullets[i]->GetObjectPos();
		bullet.radius = 1.0f;

		enemy.center = pEnemy->GetObjectPos();
		enemy.radius = 1.0f;

		// �������Ă��Ȃ���Ύ���
		if (!Collision::HitCheckSphereToSphere(bullet,enemy))
		{
			continue;
		}

		// �_���[�W�����G�l�~�[
		pEnemy->Damage(1);

		// �e�𖢎g�p��Ԃɂ���
		mBullets[i]->SetActive(false);
	}
}

//------------------------------------------------------------------
// �T�v�F�v���C���[�Ƃ̓����蔻��
// ���� (pEnemy)�F�v���C���[�̃|�C���^
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void BulletManager::CheckHitPlayer(IObject* pPlayer)
{
	// ���ׂĂ̒e�Ɠn���ꂽ�ΏۂƂ̔�������
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		// ����̏����Ȃ�Δ��肵�Ȃ�
		if (
			!mBullets[i]->GetActive() ||			// �e�����ˏ�ԂłȂ�
			mBullets[i]->GetShooterType() == Bullet::eShooterType::PLAYER_SHOT
			// �v���C���[����e��
			)
		{
			continue;
		}
		// �����蔻��p�̈ꎞ�ϐ�
		Collision::Sphere bullet;
		Collision::Sphere player;

		bullet.center = mBullets[i]->GetObjectPos();
		bullet.radius = 3.0f;

		player.center = pPlayer->GetObjectPos();
		player.radius = 5.0f;

		// �������Ă��Ȃ���Ύ���
		if (Collision::HitCheckSphereToSphere(bullet, player))
		{
			continue;
		}
		// �_���[�W�����G�l�~�[
		//pPlayer->Damage(1);

		// �e�𖢎g�p��Ԃɂ���
		mBullets[i]->SetActive(false);
	}
}