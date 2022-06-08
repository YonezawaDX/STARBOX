/**
* @file EnemyManager.cpp
* @brief �G�̊Ǘ���
* @author ���V�x��
* @date 2022/04/26
* @details �ׂ����G���Ǘ�����
*/
#include "pch.h"
#include <cassert>
#include <fstream>
#include <sstream>

#include "Libraries/MyLibraries/Model3D.h"
#include "EnemyManager.h"
#include "Object/Player.h"

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
EnemyManager::EnemyManager()
	: mEnemies{}
	, mEnemyData{}
	, mEnemyNum(0)
	, mpBulletManager{}
	, mTimer(0)
	, mpEnemyModel3D{}
{
	LoadCSV(L"Resources/CSV/EnemyData.csv");
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
EnemyManager::~EnemyManager()
{
}

//----------------------------------------------------
// �T�v�F������
// ���� (pBulletManager):�e�̊Ǘ���
// �߂�l�F�Ȃ�
//----------------------------------------------------
void EnemyManager::Initialize(BulletManager* pBulletManager)
{
	// ���f���̃��[�h
	mpEnemyModel3D = std::make_unique<Model3D>();
	mpEnemyModel3D->Initialize(L"Resources/Models/dice.cmo");

	// �^�C�}�[�̏�����
	mTimer = 0;

	// �e�̊Ǘ��Ҋi�[
	mpBulletManager = pBulletManager;

	// ���ׂĂ̓G�𖢎g�p�̏�Ԃɂ���
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->SetActive(false);
	}
}

//----------------------------------------------------
// �T�v�F�X�V
// ����:�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void EnemyManager::Update()
{
	// �^�C�}�[�̍X�V
	mTimer++;

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		// ���łɓ����Ă���G�͖���
		if (mEnemies[i]->GetActive())
		{
			continue;
		}

		// ���Ԃ������Ă��Ȃ������疳��
		if (mEnemyData[i].mCount > mTimer)
		{
			continue;
		}

		// �G�̐���
		mEnemies[i]->Initialize(
			mpEnemyModel3D.get(),
			mEnemyData[i].mEnemyNum,
			DirectX::SimpleMath::Vector3(mEnemyData[i].mPosX, mEnemyData[i].mPosY, -100.0f),
			DirectX::SimpleMath::Vector3::Zero,
			mEnemyData[i].mHP,
			mpBulletManager
		);
	}

	// �G���X�V
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Update();
	}

}

//---------------------------------------------
// �T�v�F�{�X�̍X�V
// ���� (enemyNum)�F�G�̎��
// ���� (pos)�F���W
// ���� (angle)�F�p�x
// ���� (hp)�F�̗́@
// ���� (move)�F�����Ă��邩
// �߂�l�Fvoid �Ȃ�
//---------------------------------------------
void EnemyManager::BossUpdate(
	int enemyNum,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 angle,
	int hp,
	bool move
)
{
	// �^�C�}�[�̍X�V
	mTimer++;


	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		// ���łɓ����Ă���G�͖���
		if (mEnemies[i]->GetActive())
		{
			continue;
		}

		// ���Ԃ������Ă��Ȃ������疳��
		if (mEnemyData[i].mCount > mTimer)
		{
			continue;
		}
		if (move)
		{
			// �G�̐���
			mEnemies[i]->Initialize(
				mpEnemyModel3D.get(),
				enemyNum,
				pos,
				angle,
				hp,
				mpBulletManager
			);
		}
	}

	// �G���X�V
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Update();
	}
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void EnemyManager::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Draw(commonStates,camera);
	}
}

//------------------------------------------------------------------
// �T�v�F�I��
// �����F�Ȃ�
// �߂�l (bool)�F�I��������
//------------------------------------------------------------------
bool EnemyManager::IsEnd()
{
	return false;
}

//-----------------------------------------------------------------------
// �T�v�F�v���C���[�Ƃ̓����蔻��
// ���� (pPlayer)�F�v���C���[�̃|�C���^
// �߂�l�F�Ȃ�
//-----------------------------------------------------------------------
void EnemyManager::CheckHitPlayer(IObject* pPlayer)
{
	// ���ׂĂ̓G�Ƃ̔���
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		// ����̏����Ȃ�Ώ��������Ȃ�
		if (
			!mEnemies[i]->GetActive() 	// �e���g�p��ԂłȂ�
			// �v���C���[����e��ԂłȂ�
			)
		{
			continue;
		}

		// �������Ă��Ȃ���Ύ���
		// �����蔻��p�̈ꎞ�ϐ�
		Collision::Sphere enemy;
		Collision::Sphere player;

		enemy.center = mEnemies[i]->GetObjectPos();
		enemy.radius = 100.0f;

		player.center = pPlayer->GetObjectPos();
		player.radius = 5.0f;

		if (!Collision::HitCheckSphereToSphere(enemy,player))
		{
			continue;
		}

		//pPlayer->Damage(1);
	}
}

//--------------------------------------------------
// �T�v�Fcsv��ǂݍ���
// ����(mapFile)�F�t�@�C���̖��O
// �߂�l(bool)�F �ǂݍ��݂��ł�����
//---------------------------------------------------
bool EnemyManager::LoadCSV(const wchar_t* mapFile)
{
	// ���[�J���ϐ�
	std::ifstream ifs;		// ���̓t�@�C���X�g���[��
	std::istringstream iss;	// ���͕�����X�g���[��
	std::string line;		// 1�s���̕�����
	std::string data;		// (�J���}�ŋ�؂�ꂽ)1�f�[�^���̕�����

	ifs.open(mapFile);
	// �t�@�C�����J���Ȃ���΁A���s
	if (ifs.fail()) { return false; }

	// �ŏ��̍s�͓ǂݔ�΂�
	std::getline(ifs, line);

	// �G�̐���ǂݍ���
	std::getline(ifs, line);
	mEnemyNum = std::stoi(line);

	// �G�̐����m�肷��
	mEnemies.resize(mEnemyNum);
	mEnemyData.resize(mEnemyNum);
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		// ��s���̕������ǂݍ���
		std::getline(ifs, line);
		// iss�̏�Ԃ��N���A -> ���Ȃ��ƃn�}��
		iss.clear(std::istringstream::goodbit);
		// �����񂩂當����X�g���[���ɕϊ�
		iss.str(line);

		// �J���}��؂�ŕ������int�^�ɕϊ����A�z��Ɋi�[����
		for (int j = 0; j < 5; j++)
		{
			std::getline(iss, data, ',');

			// ���ꂼ��̃f�[�^���i�[����
			switch (j)
			{
				case 0:
				{
					mEnemyData[i].mCount = std::stoi(data);
					break;
				}
				case 1:
				{
					mEnemyData[i].mEnemyNum = std::stoi(data);
					break;
				}
				case 2:
				{
					mEnemyData[i].mPosX = (float)std::stoi(data);
					break;
				}
				case 3:
				{
					mEnemyData[i].mPosY = (float)std::stoi(data);
					break;
				}
				case 4:
				{
					mEnemyData[i].mHP = std::stoi(data);
					break;
				}
				default:
					break;
			}
		}
	}

	// �t�@�C�������
	ifs.close();

	// �G�̍쐬
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i] = std::make_unique<Enemy>();
	}

	// �t�@�C���̓ǂݍ��ݐ���
	return true;
}

//----------------------------------------------
// �T�v�F�G�̏���n��
// ����(i)�F�P�̓G�̔ԍ����擾
// �߂�l (Enemy*)�F�P�̓G�̃|�C���^
//--------------------------------------------------
Enemy* EnemyManager::GetEnemies(int i)
{
	return mEnemies[i].get();
}

//----------------------------------------------
// �T�v�F�G�̐���n��
// �߂�l(int)�F�G�̐�
//-----------------------------------------------
int EnemyManager::GetEnemyNum() const
{
	return mEnemyNum;
}
