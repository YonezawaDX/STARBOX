/**
* @file HeartObject.h
* @brief HP������I�u�W�F�N�g�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details HP������I�u�W�F�N�gMoveObject���p�����Ă���
*/
#pragma once
#include "MoveObject.h"
class BossFactory;

/**
* @brief HP������I�u�W�F�N�g�̃N���X
* @details HP������I�u�W�F�N�g�̊��
*/
class HeartObject : public MoveObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	HeartObject();
	
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~HeartObject() override;

	/**
	* @brief �{�X�p�[�c��ǉ�����֐�
	* @param (bossParts) �ǉ��������{�X�̃p�[�c
	* @return void �Ȃ�
	*/
	virtual void AddBossParts(std::unique_ptr<HeartObject> bossParts);

	// ��{����

	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	virtual void Initialize() override;

	/**
	* @brief ������
	* @param (bossFactory) �{�X�̍쐬������
	* @return void �Ȃ�
	*/
	virtual void Initialize(BossFactory* bossFactory);

	/**
	* @brief �X�V
	* @return void �Ȃ�
	*/
	virtual void Update() override;

	/**
	* @brief �X�V
	* @param (position) ���W
	* @param (angle) �p�x
	* @param (offset) �e�p�[�c�Ƃ̋���
	* @param (playerPos) �v���C���[�̍��W�@
	* @param (stateNum) �{�X�̏��
	* @return void �Ȃ�
	*/
	virtual void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& angle,
		const DirectX::SimpleMath::Vector3& offset,
		const DirectX::SimpleMath::Vector3& playerPos,
		const int& stateNum
	);

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
	virtual void Move();
	
	/**
	* @brief �p�[�c�������֐�
	* @return void �Ȃ�
	*/
	virtual void DeleteParts();

	/**
	* @brief �����蔻��
	* @return void �Ȃ�
	*/
	virtual void Collision();
	
	// �Q�b�^�[�A�Z�b�^�[---------------------------------------------------------------------------
	
	/**
	* @brief ���W�̃Q�b�^�[
	* @return Vector3 �I�u�W�F�N�g�̍��W
	*/
	virtual DirectX::SimpleMath::Vector3 GetObjectPos() const override;
	/**
	* @brief ���W�̃Z�b�^�[
	* @param (pos) ���W
	* @return void �Ȃ�
	*/
	virtual void SetObjectPos(const DirectX::SimpleMath::Vector3& pos) override;

	/**
	* @brief �����̃Q�b�^�[
	* @return Vector3 �I�u�W�F�N�g�̌���
	*/
	virtual DirectX::SimpleMath::Vector3 GetObjectDirection() const;
	/**
	* @brief �����̃Z�b�^�[
	* @param (direction) ����
	* @return void �Ȃ�
	*/
	virtual void SetObjectDirection(const DirectX::SimpleMath::Vector3& direction);

	/**
	* @brief �����̃Q�b�^�[
	* @return Vector3 �I�u�W�F�N�g�̑���
	*/
	virtual DirectX::SimpleMath::Vector3 GetObjectSpeed() const;
	/**
	* @brief �����̃Z�b�^�[
	* @param (speed) ����
	* @return void �Ȃ�
	*/
	virtual void SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed);

	/**
	* @brief �g�p��Ԃ̃Q�b�^�[
	* @return bool �g�p���
	*/
	virtual bool GetActive() const;
	/**
	* @brief �g�p��Ԃ̃Z�b�^�[
	* @param (active) �g�p���
	* @return void �Ȃ�
	*/
	virtual void SetActive(const bool& active);

	/**
	* @brief HP�̃Q�b�^�[
	* @return int HP�̒l
	*/
	virtual int GetHP() const;
	/**
	* @brief HP�̃Z�b�^�[
	* @param (hp) HP�̒l
	* @return void �Ȃ�
	*/
	virtual void SetHP(const int& hp);

private:

	//! �I�u�W�F�N�g�̗̑�
	int mHP;
};
