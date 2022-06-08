/**
* @file CaterpillerLeft.h
* @brief �L���^�s���̃N���X
* @author ���V�x��
* @date 2022/05/01
* @details �{�X02�̃^�C�����̃N���X
*/
#pragma once
#include "HeartObject.h"
#include "Boss02.h"

/**
* @brief �{�X�p�[�c�̃L���^�s���E�̃N���X
* @details �^�C���t���̃N���X
*/
class CaterpillerLeft : public HeartObject
{
public:
	/**
	* @brief �{�X�p�[�c��ǉ�����֐�
	* @param (bossParts) �ǉ��������{�X�̃p�[�c
	* @return void �Ȃ�
	* @details �t�@�N�g���̊֌W�Ŋe�p�[�c�ɒǉ��Ȃ���΂����Ȃ�
	*/
	void AddBossParts(std::unique_ptr<HeartObject> bossParts) override;

	/**
	* @brief �R���X�g���N�^
	* @param (offset) �e�p�[�c�Ƃ̋���
	* @param (pEnemies) �ׂ����G�̃|�C���^
	* @param (pBulletManager) �e�̔��˗p
	*/
	CaterpillerLeft(
		const DirectX::SimpleMath::Vector3& offset,
		BulletManager* pBulletManager
	);


	/**
	* @brief �f�X�g���N�^
	*/
	~CaterpillerLeft();

	// ��{����-----------------------------------------------------------------------

	/**
	* @brief ������
	* @param (bossFactory) �{�X�̍쐬������
	* @return void �Ȃ�
	*/
	void Initialize(BossFactory* bossFactory) override;

	/**
	* @brief �X�V
	* @param (position) ���W
	* @param (angle) �p�x
	* @param (offset) �e�p�[�c�Ƃ̋���
	* @param (playerPos) �v���C���[�̍��W�@
	* @param (stateNum) �{�X�̏��
	* @return void �Ȃ�
	*/
	void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& angle,
		const DirectX::SimpleMath::Vector3& offset,
		const DirectX::SimpleMath::Vector3& playerPos,
		const int& stateNum
	) override;

	/**
	* @brief �`��
	* @param (commonStates) �R�����X�e�C�g
	* @param (camera) �J����
	* @return void �Ȃ�
	*/
	void Draw(DirectX::CommonStates* commonStates, Camera* camera) override;

	/**
	* @brief �I������
	* @return void �Ȃ�
	*/
	void Finalize() override;

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

	/**
	* @brief �p�[�c������
	* @return void �Ȃ�
	*/
	void DeleteParts() override;


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

	//! �p�[�c��ǉ�����
	std::vector<std::unique_ptr<HeartObject>> mpBossParts;

	//! �ʒu�I�t�Z�b�g
	DirectX::SimpleMath::Vector3 mPosOffset;

	//! ��]�p�I�t�Z�b�g
	DirectX::SimpleMath::Vector3 mAngleOffset;

	//! �e�̊Ǘ��҂��i�[
	BulletManager* mpBullets;

	//! �J������ۑ����Ă���
	Camera* mCamera;
};