/**
* @file PlayScene.h
* @brief �v���C�V�[��
* @author ���V�x��
* @date
* @details �v���C�V�[��
*/
#pragma once

#include <CommonStates.h>
#include <Model.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include "../IScene.h"
#include "Game/GameMain.h"

// �O���錾
class FollowCamera;
class Boss;
class Boss02;
class IObject;
class BulletManager;
class EnemyManager;
class Player;
class UI;
class Fade;

/**
* @brief �v���C�V�[���̃N���X
* @details �v���C�V�[��
*/
class PlayScene : public IScene
{
public:
	/**
	* @enum PLAY_STATE
	* �t�F�[�h�p�̑J��
	*/
	enum class PLAY_STATE
	{
		//! �Ȃ�
		NONE,
		//! ��ʂ��J������܂ł̊�
		START,
		//! ����ҋ@
		PLAY,
		//! ���ɍs��
		NEXT_SCENE
	};
public:

	/**
	* @brief �R���X�g���N�^
	*/
	PlayScene();

	/**
	* @brief �f�X�g���N�^
	*/
	~PlayScene();

	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	void Initialize() override;

	/**
	* @brief �X�V
	* @param (timer) ����
	* @return GAME_SCENE �Q�[���̃V�[����Ԃ��A�ύX
	*/
	GAME_SCENE Update(const DX::StepTimer& timer) override;

	/**
	* @brief �`��
	* @return void �Ȃ�
	*/
	void Draw() override;

	/**
	* @brief �I������
	* @return void �Ȃ�
	*/
	void Finalize() override;

	/**
	* @brief ���\�[�X�ǂݍ���
	* @return void �Ȃ�
	*/
	void ResourcesRegister();

private:

	//! �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> mCommonState;
	//! �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	//! �X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> mSpriteFont;

	//! �f�o�b�O�J����
	std::unique_ptr<FollowCamera> mCamera;

	//! �v���C���[
	std::unique_ptr<Player> mpPlayer;
	//! �e�ۂ̊Ǘ�
	std::unique_ptr<BulletManager> mpBulletManager;
	//! �G�̊Ǘ�
	std::unique_ptr<EnemyManager> mpEnemyManager;
	//! �w�i
	std::unique_ptr<IObject> mpBackGround;
	//! ��
	std::unique_ptr<IObject> mpFloor;
	
	//! �{�X
	std::unique_ptr<Boss> mpBoss;
	//! �{�X
	std::unique_ptr<Boss02> mpBoss02;
	//! UI
	std::unique_ptr<UI> mpUI;

	//! Fade
	std::unique_ptr<Fade> mpFade;
	
	//! �v���C�V�[���̃X�e�[�g
	PLAY_STATE mState;

	//! ���݂�FPS
	unsigned int mFps;
};