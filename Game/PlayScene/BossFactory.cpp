/**
* @file BossFactory.cpp
* @brief �{�X�̍H��
* @author ���V�x��
* @date 2022/04/26
* @details �{�X�̊e�p�[�c�𐶐�����
*/
#include "pch.h"
#include "BossFactory.h"

#include "Object/Body.h"
#include "Object/SmallArm.h"
#include "Object/BigArm.h"
#include "Object/Prime.h"
#include "Object/CaterpillerRight.h"
#include "Object/CaterpillerLeft.h"
#include "Object/Core.h"
#include "Object/Cover.h"
#include "Object/Tire.h"

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// ����(pBoss)�F�{�X�̃|�C���^
// ����(pBulletManager)�F�e���˗p
// ����(pEnemyManager)�F�G���˗p
//------------------------------------------------------------------
BossFactory::BossFactory(BulletManager* pBullets, EnemyManager* pEnemies)
	: mpBullets(pBullets)
	, mpEnemies(pEnemies)
{
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void BossFactory::Initialize()
{
	// ���݂̓��\�[�X�}�l�[�W���ł̊Ǘ������Ă���
}

//---------------------------------------------------------------------
// �T�v�F�{�X�p�[�c�̐���
// ����(bossPartsID)�F�{�X�p�[�c��ID
// ����(offset)�F�p�[�c�̍��W�A�e�p�[�c����̋���
// �߂�l(unique_ptr<HeartObject>)�F�I�u�W�F�N�g�𐶐����ĕԂ�
//---------------------------------------------------------------------
std::unique_ptr<HeartObject> BossFactory::Create(
	BOSS_PARTS_ID bossPartsID,
	const DirectX::SimpleMath::Vector3& offset
)
{
	std::unique_ptr<HeartObject> bossParts;

	switch (bossPartsID)
	{
		case BOSS_PARTS_ID::BODY:
			// Body�̃I�u�W�F�N�g�𐶐�����
			bossParts.reset((HeartObject*)new Body(offset,mpBullets));
			break;
		case BOSS_PARTS_ID::SMALL_ARM:
			// SmallArm�̃I�u�W�F�N�g�𐶐�����
			bossParts.reset((HeartObject*)new SmallArm(offset , mpBullets));
			break;
		case BOSS_PARTS_ID::BIG_ARM:
			// BigArm�̃I�u�W�F�N�g�𐶐�����
			bossParts.reset((HeartObject*)new BigArm(offset,mpEnemies,mpBullets));
			break;
		case BOSS_PARTS_ID::PRIME:
			// Prime�̃I�u�W�F�N�g�𐶐�����
			bossParts.reset((HeartObject*)new Prime(offset,mpBullets));
			break;
		case BOSS_PARTS_ID::CORE:
			// Core�̃I�u�W�F�N�g�𐶐�����
			bossParts.reset((HeartObject*)new Core(offset, mpBullets));
			break;
		case BOSS_PARTS_ID::COVER:
			// Cover�̃I�u�W�F�N�g�𐶐�����
			bossParts.reset((HeartObject*)new Cover(offset, mpBullets));
			break;
		case BOSS_PARTS_ID::TIRE:
			// Cover�̃I�u�W�F�N�g�𐶐�����
			bossParts.reset((HeartObject*)new Tire(offset));
			break;

		default:
			return nullptr;
	}

	// ���ꂼ��̃{�X�p�[�c������������
	bossParts->Initialize(this);
	return std::move(bossParts);
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void BossFactory::Finalize()
{
}
