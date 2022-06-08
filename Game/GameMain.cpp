/**
* @file GameMain.cpp
* @brief �Q�[�����C��
* @author ���V�x��
* @date
* @details �Q�[���S�̂��Ǘ�
*/
#include "pch.h"

#include "DeviceResources.h"
#include "GameMain.h"

#include "Game/TitleScene/TitleScene.h"
#include "Game/SelectScene/SelectScene.h"
#include "Game/PlayScene/PlayScene.h"

#include "Libraries/MyLibraries/InputManager.h"

// ���O��Ԃ̗��p
using namespace DirectX;

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
GameMain::GameMain()
	: mNextScene(GAME_SCENE::TITLE)		// �����V�[���̐ݒ�
	, mpScene(nullptr)
{
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
GameMain::~GameMain()
{
	Finalize();
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void GameMain::Initialize()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// InputManager::Singleton��
	InputManager* inputManager = InputManager::GetInstance();
	inputManager->Initialize(pDR->GetHwnd());

	// �V�[���쐬
	CreateScene();
}

//----------------------------------------------------
// �T�v�F�X�V
// ����(timer)�F����
// �߂�l�F�Ȃ�
//----------------------------------------------------
void GameMain::Update(const DX::StepTimer& timer)
{
	// �C���v�b�g�}�l�[�W���̎擾
	InputManager* inputManager = InputManager::GetInstance();
	inputManager->Update();

	// ESC�L�[�ŏI��
	if (inputManager->GetKeyboardState().Escape)PostQuitMessage(0);

	// ���̃V�[�����ݒ肳��Ă�����V�[���؂�ւ�
	if (mNextScene != GAME_SCENE::NONE)
	{
		// �V�[���폜
		DeleteScene();
		
		// �V�[���쐬
		CreateScene();
	}

	// ���Ԃ�����΍X�V
	if (mpScene != nullptr)
	{
		mNextScene = mpScene->Update(timer);
	}
}

//----------------------------------------------------------------------
// �T�v�F�`��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void GameMain::Render()
{
	// ���Ԃ�����Ε`��
	if (mpScene != nullptr)
	{
		mpScene->Draw();
	}
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void GameMain::Finalize()
{
	DeleteScene();
}

//------------------------------------------------------------------
// �T�v�F�V�[���̍쐬
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void GameMain::CreateScene()
{
	// �V�[�����쐬����Ă���Ƃ��͏������Ȃ�
	if (mpScene != nullptr)
	{
		return;
	}

	// ���V�[���̍쐬
	switch (mNextScene)
	{
		case GAME_SCENE::TITLE:
		{
			mpScene = new TitleScene();
			break;
		}
		case GAME_SCENE::SELECT:
		{
			mpScene = new SelectScene();
			break;
		}
		case GAME_SCENE::PLAY:
		{
			mpScene = new PlayScene();
			break;
		}
		default:
		{
			// ��O�Ȃ̂ŏ����𒆒f
			return;
		}
	}

	// �쐬�����V�[����������
	mpScene->Initialize();
}

//------------------------------------------------------------------
// �T�v�F�V�[���̍폜
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void GameMain::DeleteScene()
{
	// �V�[�����쐬����Ă��Ȃ���Ώ������Ȃ�
	if (mpScene == nullptr)
	{
		return;
	}

	// ���V�[���̏I������
	mpScene->Finalize();

	// ���V�[���̍폜
	delete mpScene;
	mpScene = nullptr;
}
