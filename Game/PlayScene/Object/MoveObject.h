/**
* @file MoveObject.h
* @brief �����I�u�W�F�N�g�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �����I�u�W�F�N�gObject���p�����Ă���
*/
#pragma once
#include "Object.h"

/**
* @brief �����I�u�W�F�N�g�̃N���X
* @details �����I�u�W�F�N�g�̊��
*/
class MoveObject : public Object
{
public:

	/**
	* @brief �R���X�g���N�^
	*/
	MoveObject();

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~MoveObject() override;

	// ��{����

	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	virtual void Initialize() override;

	/**
	* @brief �X�V
	* @return void �Ȃ�
	*/
	virtual void Update() override;

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

private:
	//! �I�u�W�F�N�g�̌���
	DirectX::SimpleMath::Vector3 mDirection;

	//! �I�u�W�F�N�g�̑���
	DirectX::SimpleMath::Vector3 mSpeed;

	//! �g�p���
	bool mIsActive;
};