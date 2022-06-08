/**
* @file BulletManager.h
* @brief �e�̊Ǘ��҃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �e�̊Ǘ�������A���˂Ȃ�
*/
#pragma once
#include "Game/PlayScene/Object/Bullet.h"

// �O���錾
class Model3D;
class Enemy;
class Player;

/**
* @brief �e�̊Ǘ��҃N���X
* @details �e�̊Ǘ�������A���˂Ȃ�
*/
class BulletManager
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	BulletManager();

	/**
	* @brief �f�X�g���N�^
	*/
	~BulletManager();

	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	void Initialize();

	/**
	* @brief �X�V
	* @return void �Ȃ�
	*/
	void Update();

	/**
	* @brief �`��
	* @param (commonStates) �R�����X�e�C�g
	* @param (camera) �J����
	* @return void �Ȃ�
	*/
	void Draw(DirectX::CommonStates* commonStates, Camera* camera);

	/**
	* @brief �e�̔���
	* @param (shooterType) ���˂���G���e�B�e�B
	* @param (pos) ���W
	* @param (angle) �p�x
	* @return bool �����Ă��邩�m�F
	*/
	bool Shot(int shooterType, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 angle);

	/**
	* @brief �G�Ƃ̓����蔻��
	* @param (pEnemy) �G�̃|�C���^
	* @return void �Ȃ�
	*/
	void CheckHitEnemy(Enemy* pEnemy);

	/**
	* @brief �v���C���[�Ƃ̓����蔻��
	* @param (pEnemy) �v���C���[�̃|�C���^
	* @return void �Ȃ�
	*/
	void CheckHitPlayer(IObject* pPlayer);

	/**
	* @brief ��̒e���擾����
	* @param (i) ��̒e�̂��i�[����Ă���ԍ�
	* @return Bullet* �e�̃|�C���^
	*/
	Bullet* GetBullet(int i) { return mBullets[i].get(); }

private:// �ϐ�-------------------------------------------------------------------------------------------
	//! �e
	std::vector<std::unique_ptr<Bullet>> mBullets;

	//! �e�̃��f��
	std::unique_ptr<Model3D> mBulletModel3D;
};