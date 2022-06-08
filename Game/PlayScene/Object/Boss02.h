/**
* @file Boss02.h
* @brief �{�X02�̃N���X
* @author ���V�x��
* @date 2022/05/01
* @details �{�X02�̃N���X
*/
#pragma once
#include "HeartObject.h"
#include "Game/PlayScene/BulletManager.h"

class EnemyManager;

/**
* @brief �{�X02
* @details  2�̖ڂ̃{�X
*/
class Boss02 : public HeartObject
{
public:
	//! ���x
	static const DirectX::SimpleMath::Vector3 SPEED;
	//! �������W								  
	static const DirectX::SimpleMath::Vector3 START_POS;
	static const DirectX::SimpleMath::Vector3 MOVE_POS;
	
	//! �p�[�c�̏������W�i�R�A�p�[�c�j					  
	static const DirectX::SimpleMath::Vector3 CORE_OFFSET;

	//! �p�[�c�̏������W�i�J�o�[�j
	static const DirectX::SimpleMath::Vector3 COVER_OFFSET;

	//! �p�[�c�̏������W�i�^�C���j
	static const DirectX::SimpleMath::Vector3 TIRE_OFFSET;

	//! �R�A�p�[�c��J�o�[�̊�
	static const float PARTS_BETWEEN;

	//! �����̒萔01
	static const DirectX::SimpleMath::Vector3 BOSS_MOVE_01;
	//! �����̒萔02
	static const DirectX::SimpleMath::Vector3 BOSS_MOVE_02;

	//! �{�X�̃A���O��
	static const float RESULT_ANGLE;

	//! �{�X�̈ړ�����
	static const float RESULT_COUNT;

	//! �p�[�c�̉�]
	static const float PARTS_ROTATE;

public:
	/**
	* @enum BOSS_STATE
	* �{�X�̈ړ����
	*/
	enum class BOSS_STATE
	{
		//! �����l	
		NONE,
		//! ����
		ADMISSION,
		//! �����
		ADMISSION_AFTER,
		//! ���ɓ���
		LEFT_MOVE,
		//! �E�ɓ���
		RIGHT_MOVE,
		//! ���
		ROLL_MOVE
	};

public:
	
	/**
	* @brief �R���X�g���N�^
	* @param (pBulletManager) �e�̊Ǘ���
	* @param (pEnemyManager) �G�̃|�C���^
	*/
	Boss02(BulletManager* pBulletManager, EnemyManager* pEnemyManager);

	/**
	* @brief �f�X�g���N�^
	*/
	~Boss02();

	// ��{����-----------------------------------------------------------------------

/**
* @brief ������
* @param �Ȃ�
* @return void �Ȃ�
*/
	virtual void Initialize() override;

	/**
	* @brief �X�V
	* @param �Ȃ�
	* @return void �Ȃ�
	*/
	virtual void Update() override;

	// @brief �X�V
	// @param (playerPos) �v���C���[�̍��W
	// @return void �Ȃ�
	virtual void Update(DirectX::SimpleMath::Vector3 playerPos);

	/**
	* @brief �`��
	* @param (commonStates) �R�����X�e�C�g
	* @param (camera) �J����
	* @return void �Ȃ�
	*/
	virtual void Draw(DirectX::CommonStates* commonStates, Camera* camera) override;

	/**
	* @brief �I������
	* @return void �Ȃ�
	*/
	virtual void Finalize() override;

	/**
	* @brief ����悤�֐�
	* @return void �Ȃ�
	*/
	void Move() override;

	/**
	* @brief �����蔻��
	* @return void �Ȃ�
	*/
	void Collision() override;
	// �Q�b�^�[�A�Z�b�^�[---------------------------------------------------------------------------

	/**
	* @brief ���W�̃Q�b�^�[
	* @return Vector3 �I�u�W�F�N�g�̍��W
	*/
	DirectX::SimpleMath::Vector3 GetObjectPos() const override;
	/**
	* @brief ���W�̃Z�b�^�[
	* @param (pos) ���W
	* @return void �Ȃ�
	*/
	void SetObjectPos(const DirectX::SimpleMath::Vector3& pos) override;

	/**
	* @brief �����̃Q�b�^�[
	* @return Vector3 �I�u�W�F�N�g�̌���
	*/
	DirectX::SimpleMath::Vector3 GetObjectDirection() const override;
	/**
	* @brief �����̃Z�b�^�[
	* @param (direction) ����
	* @return void �Ȃ�
	*/
	void SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)override;

	/**
	* @brief �����̃Q�b�^�[
	* @return Vector3 �I�u�W�F�N�g�̑���
	*/
	DirectX::SimpleMath::Vector3 GetObjectSpeed() const override;
	/**
	* @brief �����̃Z�b�^�[
	* @param (speed) ����
	* @return void �Ȃ�
	*/
	void SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)override;

	/**
	* @brief �g�p��Ԃ̃Q�b�^�[
	* @return bool �g�p���
	*/
	bool GetActive() const override;
	/**
	* @brief �g�p��Ԃ̃Z�b�^�[
	* @param (active) �g�p���
	* @return void �Ȃ�
	*/
	void SetActive(const bool& active) override;

	/**
	* @brief HP�̃Q�b�^�[
	* @return int HP�̒l
	*/
	int GetHP() const override;
	/**
	* @brief HP�̃Z�b�^�[
	* @param (hp) HP�̒l
	* @return void �Ȃ�
	*/
	void SetHP(const int& hp) override;

private:
	//! �ԑ̃I�u�W�F�N�g
	std::unique_ptr<HeartObject> mpPrime;

	//! �{�X�̃X�e�[�g
	BOSS_STATE mBossState;

	//! �J�E���^
	float mCount;

	//! �ŏ��̊p�x�ύX�p
	float mTempAngle;

	//! �Ō�̊p�x�ύX�p
	float mResultAngle;

	//! �{�X���s�����鎞�_�ł̍��W
	DirectX::SimpleMath::Vector3 mTempPos;

	//! �{�X���s�����I��鎞�_�ł̍��W
	DirectX::SimpleMath::Vector3 mResultPos;

	//! �e���˗p
	BulletManager* mpBullets;

	//! �G�o���p
	EnemyManager* mpEnemies;
};
