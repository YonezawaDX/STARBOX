/**
* @file EnemyManager.h
* @brief �G�̊Ǘ���
* @author ���V�x��
* @date 2022/04/26
* @details �ׂ����G���Ǘ�����
*/
#pragma once
#include "Game/PlayScene/Object/Enemy.h"
#include "Game/PlayScene/BulletManager.h"

/**
* @struct �G�̃f�[�^
*/
struct EnemyData
{
	int mCount;				//! �o������
	int mEnemyNum;			//! �G�̎��
	
	float mPosX;			//! X���W
	float mPosY;			//! Y���W

	int mHP;				//! �̗�
};

// �O���錾
class Model3D;
class IObject;

/**
* @brief �G�̊Ǘ��҃N���X
* @details �ׂ����G���Ǘ�����
*/
class EnemyManager
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	EnemyManager();

	/**
	* @brief �f�X�g���N�^
	*/
	~EnemyManager();

	/**
	* @brief ������
	* @param (pBulletManager) �e���˗p
	* @return void �Ȃ�
	*/
	void Initialize(BulletManager* pBulletManager);

	/**
	* @brief �X�V
	* @return void �Ȃ�
	*/
	void Update();

	/**
	* @brief �{�X�̍X�V
	* @param (enemyNum) �G�̎��
	* @param (pos) ���W
	* @param (angle) �p�x
	* @param (hp) �̗́@
	* @param (move) �����Ă��邩
	* @return void �Ȃ�
	*/
	void BossUpdate(
		int enemyNum,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 angle,
		int hp,
		bool move
		);

	/**
	* @brief �`��
	* @param (commonStates) �R�����X�e�C�g
	* @param (camera) �J����
	* @return void �Ȃ�
	*/
	void Draw(DirectX::CommonStates* commonStates, Camera* camera);

	/**
	* @brief �I��
	* @return bool �I�����Ă��邩
	*/
	bool IsEnd();

	/**
	* @brief �v���C���[�Ƃ̓����蔻��
	* @param (pPlayer) �v���C���[�̃|�C���^
	* @return void �Ȃ�
	*/
	void CheckHitPlayer(IObject* pPlayer);

	/**
	* @brief csv��ǂݍ���
	* @param (mapFile) �t�@�C���̖��O
	* @return bool �ǂݍ��݂��ł�����
	*/
	bool LoadCSV(const wchar_t* mapFile);

	/**
	* @brief �G�̏���n��
	* @param (i) �P�̓G�̔ԍ����擾
	* @return Enemy* �P�̓G�̃|�C���^
	*/
	Enemy* GetEnemies(int i);

	/**
	* @brief �G�̐���n��
	* @return int �G�̐�
	*/
	int GetEnemyNum() const;
private:
	//! �G�̔z��
	std::vector<std::unique_ptr<Enemy>> mEnemies;

	//! �G�̐�
	int mEnemyNum;

	//! �G�̐��l���i�[����z��
	std::vector<EnemyData> mEnemyData;

	//! �e�̊Ǘ��Ҋi�[�p
	BulletManager* mpBulletManager;

	//! �G�̏o������
	int mTimer;

	//! �G�̃��f��
	std::unique_ptr<Model3D> mpEnemyModel3D;
};