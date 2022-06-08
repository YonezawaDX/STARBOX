/**
* @file TitleScene.h
* @brief �^�C�g���V�[��
* @author ���V�x��
* @date 
* @details �^�C�g���V�[��
*/
#pragma once

#include <CommonStates.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include "../IScene.h"
#include "Game/GameMain.h"

#include "Game/Effects/Fade.h"

// �O���錾
class Fade;
class Camera;
class TitlePlane;
class TitleObject;
class TitleBackground;

/**
* @brief �^�C�g���V�[���̃N���X
* @details �^�C�g���V�[��
*/
class TitleScene : public IScene
{
public:
	/**
    * @enum TITLE_STATE
    * �^�C�g���V�[���̏��
    */
	enum class TITLE_STATE
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
	TitleScene();

	/**
	* @brief �f�X�g���N�^
	*/
	~TitleScene();

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
private:

	//! �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> mCommonState;
	//! �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	//! �X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> mSpriteFont;
	//! �J����
	std::unique_ptr<Camera> mCamera;
	//! �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;


	//! ��s�@���f��
	std::unique_ptr<TitlePlane> mpPlane;
	//! �^�C�g�����f��
	std::unique_ptr<TitleObject> mpTitleObject;
	//! �w�i���f��
	std::unique_ptr<TitleBackground> mpTitleBackground;

	//! �t�F�[�h�C���p�N���X
	std::unique_ptr<Fade> mFade;

	//! �^�C�g���̏��
	TITLE_STATE mState;
};