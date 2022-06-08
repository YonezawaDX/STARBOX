/**
* @file IScene.h
* @brief �V�[���̃C���^�[�t�F�[�X
* @author 
* @date
* @details �V�[���̃C���^�[�t�F�[�X
*/
#pragma once

#include "StepTimer.h"
#include "GameMain.h"

/**
* @brief �V�[���̃C���^�[�t�F�[�X�̃N���X
* @details �V�[���̃C���^�[�t�F�[�X
*/
class IScene
{
public:
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~IScene() = default;

	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	virtual void Initialize() = 0;

	/**
	* @brief �X�V
	* @param (timer) ����
	* @return GAME_SCENE �Q�[���̃V�[����Ԃ��A�ύX
	*/
	virtual GAME_SCENE Update(const DX::StepTimer& timer) = 0;

	/**
	* @brief �`��
	* @return void �Ȃ�
	*/
	virtual void Draw() = 0;

	/**
	* @brief �I������
	* @return void �Ȃ�
	*/
	virtual void Finalize() = 0;
};