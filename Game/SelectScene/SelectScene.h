/**
* @file SelectScene.h
* @brief �Z���N�g�V�[��
* @author ���V�x��
* @date 2022/04/26
* @details �Z���N�g�V�[��
*/
#pragma once
#include <SimpleMath.h>
#include <CommonStates.h>
#include <Model.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include "../IScene.h"
#include "Game/GameMain.h"

// �O���錾
class FollowCamera;
class IObject;
class BulletManager;
class Player;
class Fade;
class PostEffect;
class SelectButton;
class SelectSceneLetter;

/**
* @brief �Z���N�g�V�[���̃N���X
* @details �Z���N�g�V�[��
*/
class SelectScene : public IScene
{
public:
	// �萔
	//! �J�������W
	static const DirectX::SimpleMath::Vector3 CAMERA_POS;
public:
	/**
	* @enum SELECT_TRANS
	* �Z���N�g�V�[���̑J��
	*/
	enum class SELECT_TRANS
	{
		NONE,		//! �����Ȃ�
		PLAY,		//! �v���C���
		SELECT,		//! �Z���N�g���
		ANIMATION	//! �V�[�����؂�ւ��
	};

	/**
	* @enum SELECT_STATE
	* �t�F�[�h�p�̑J��
	*/
	enum class SELECT_STATE
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
	SelectScene();

	/**
	* @brief �f�X�g���N�^
	*/
	~SelectScene();

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
	//! �w�i
	std::unique_ptr<IObject> mpBackGround;
	//! ��
	std::unique_ptr<IObject> mpFloor;
	//! Fade
	std::unique_ptr<Fade> mpFade;

	//! ���݂�FPS
	unsigned int mFps;


	//! �|�X�g�G�t�F�N�g�p
	std::unique_ptr<PostEffect> mPostEffect;

	//! �|�X�g�G�t�F�N�g�̃J�������W
	DirectX::SimpleMath::Vector3 mPostCamera;

	//! �v���C��ʁA�ŏ��̑傫��
	DirectX::SimpleMath::Matrix mStartWindow;
	//! �v���C��ʁA�Ō�̑傫��
	DirectX::SimpleMath::Matrix mEndWindow;

	//! �v���C�V�[���ւ̃J�E���^
	float mPlayCount;

	//! �Z���N�g�V�[�����̑J��
	SELECT_TRANS mSelectTrans;

	//! �Z���N�g�V�[���̃{�^��
	std::unique_ptr<SelectButton> mSelectButton;

	//! �Z���N�g�V�[���̕���
	std::unique_ptr<SelectSceneLetter> mSelectSceneLetter;

	SELECT_STATE mState;

};