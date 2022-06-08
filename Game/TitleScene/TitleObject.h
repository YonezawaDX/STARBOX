/**
* @file TitleObject.h
* @brief �^�C�g���I�u�W�F�N�g
* @author ���V�x��
* @date 2022/04/26
* @details �^�C�g���̕������f��
*/
#pragma once
#include "Game/PlayScene/Object/MoveObject.h"

/**
* @brief �^�C�g���I�u�W�F�N�g�̃N���X
* @details �^�C�g���̕������f��
*/
class TitleObject : public MoveObject
{
	// �萔--------------------------------------------------
	
	//! �J�n���_�̍��W
	static const DirectX::SimpleMath::Vector3 START_POS;
	//-------------------------------------------------------
public:
	/**
	* @brief �R���X�g���N�^
	*/
	TitleObject();

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~TitleObject() override;

	// ��{����
	
	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	void Initialize() override;
	/**
	* @brief �X�V
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
	DirectX::SimpleMath::Vector3 GetObjectDirection() const;
	/**
	* @brief �����̃Z�b�^�[
	* @param (direction) ����
	* @return void �Ȃ�
	*/
	void SetObjectDirection(const DirectX::SimpleMath::Vector3& direction);

	/**
	* @brief �����̃Q�b�^�[
	* @return Vector3 �I�u�W�F�N�g�̑���
	*/
	DirectX::SimpleMath::Vector3 GetObjectSpeed() const;
	/**
	* @brief �����̃Z�b�^�[
	* @param (speed) ����
	* @return void �Ȃ�
	*/
	void SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed);
};