/**
* @file �I�u�W�F�N�g�̃C���^�[�t�F�[�X
* @brief �C���^�[�t�F�[�X
* @author ���V�x��
* @date 2022/04/26
* @details ���ׂẴI�u�W�F�N�g�̑c
*/
#pragma once
#include <SimpleMath.h>
#include <CommonStates.h>
#include "Libraries/MyLibraries/Camera.h"

/**
* @brief �I�u�W�F�N�g�̃C���X�^�[�t�F�[�X�N���X
* @details ���ׂẴI�u�W�F�N�g�̑c
*/
class IObject
{
public:
	// ��{����--------------------------------------------

	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	virtual void Initialize() = 0;
	
	/**
	* @brief �X�V
	* @return void �Ȃ�
	*/
	virtual void Update() = 0;

	/**
	* @brief �`��
	* @param (commonStates) �R�����X�e�C�g
	* @param (camera) �J����
	* @return void �Ȃ�
	*/
	virtual void Draw(DirectX::CommonStates* commonStates, Camera* camera) = 0;

	/**
	* @brief �I������
	* @return void �Ȃ�
	*/
	virtual void Finalize() = 0;

	// �Z�b�^�[�Q�b�^�[------------------------------------------

	/**
	* @brief ���W�̃Q�b�^�[
	* @return Vector3 �I�u�W�F�N�g�̍��W
	*/
	virtual DirectX::SimpleMath::Vector3 GetObjectPos() const = 0;
	/**
	* @brief ���W�̃Z�b�^�[
	* @param (pos) ���W
	* @return void �Ȃ�
	*/
	virtual void SetObjectPos(const DirectX::SimpleMath::Vector3& pos) = 0;

	//-----------------------------------------------------------
	
	/**
	* @brief �������z�f�X�g���N�^
	*/
	virtual ~IObject() = 0;
};
inline IObject::~IObject() {};