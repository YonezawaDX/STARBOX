/**
* @file BossFactory.h
* @brief �{�X�̍H��
* @author ���V�x��
* @date 2022/04/26
* @details �{�X�̊e�p�[�c�𐶐�����
*/
#pragma once
#include <memory>
#include "Libraries/MyLibraries/Model3D.h"
#include "BulletManager.h"
#include "EnemyManager.h"

class Boss;
class HeartObject;

/**
* @enum BOSS_PARTS_ID
* �{�X�̃p�[�c�̗�
*/
enum class BOSS_PARTS_ID
{
	//! ��
	BODY,
	//! �������r
	SMALL_ARM,			
	//! �傫���r
	BIG_ARM,			
	//! �{�X02�̑�
	PRIME,				
	//! �L���^�s���E
	CATERPILLER_RIGHT,	
	//! �L���^�s�^��
	CATERPILLER_LEFT,	
	//! �R�A
	CORE,				
	//! �J�o�[
	COVER,
	//! �^�C��
	TIRE
};

/**
* @brief �{�X�̍H��̃N���X
* @details �{�X�̍H��
*/
class BossFactory
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param (pBulletManager) �e���˗p
	* @param (pEnemyManager) �G���˗p
	*/
	BossFactory(BulletManager* pBullets, EnemyManager* pEnemies);

	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	void Initialize();

	/**
	* @brief �{�X�p�[�c�̐���
	* @param (bossPartsID) �{�X�p�[�c��ID
	* @param (offset) �p�[�c�̍��W�A�e�p�[�c����̋��� 
	* @return unique_ptr<HeartObject> �I�u�W�F�N�g�𐶐����ĕԂ�
	*/
	std::unique_ptr<HeartObject> BossFactory::Create(
		BOSS_PARTS_ID bossPartsID,
		const DirectX::SimpleMath::Vector3& offset
	);

	/**
	* @brief �I������
	* @return void �Ȃ�
	*/
	void Finalize();

private:

	//! �e�ۂ̊Ǘ��҃|�C���^
	BulletManager* mpBullets;
	
	//! �G�̊Ǘ��҃|�C���^
	EnemyManager* mpEnemies;
};