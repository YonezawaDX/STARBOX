/**
* @file Hatch.h
* @brief ���~���̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �{�X�̎�_�̃J�o�[�̃N���X
*/
#pragma once
#include "HeartObject.h"

/**
* @brief �J�o�[
* @details  �J�o�[
*/
class Hatch : public HeartObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Hatch();
	/**
	* @brief �f�X�g���N�^
	*/
	~Hatch();

	// ��{����------------------------------------------------------------------------
	
	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	void Initialize() override;
	
	/**
	* @brief �X�V
	* @param (position) ���W
	* @return void �Ȃ�
	*/
	void Update() override;
	
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
	* @brief �n�b�`�̊J�̃Q�b�^�[
	* @return bool �J���Ă��邩
	*/
	void GetIsOpen() const;

private:

	//! ���~���̏��
	bool mIsHatchOpen;
};