/**
* @file TitleScene.cpp
* @brief �^�C�g���V�[��
* @author ���V�x��
* @date
* @details �^�C�g���V�[��
*/
#include "pch.h"

#include <WICTextureLoader.h>
#include <SimpleMath.h>

#include "../GameMain.h"
#include "DeviceResources.h"
#include "Game/Effects/Fade.h"

#include "TitleScene.h"
#include "Libraries/MyLibraries/ResourceManager.h"
#include "Libraries/MyLibraries/Camera.h"

#include "TitlePlane.h"
#include "TitleObject.h"
#include "TitleBackground.h"

#include "Libraries/MyLibraries/InputManager.h"

// ���O��Ԃ̗��p
using namespace DirectX;

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
TitleScene::TitleScene():
	mState(TITLE_STATE::START)
{
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
TitleScene::~TitleScene()
{
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void TitleScene::Initialize()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// D3D�f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̎擾
	auto device = pDR->GetD3DDevice();
	auto context = pDR->GetD3DDeviceContext();

	// �R�����X�e�[�g::D3D�����_�����O��ԃI�u�W�F�N�g
	mCommonState = std::make_unique<DirectX::CommonStates>(device);

	// �X�v���C�g�o�b�`::�f�o�b�O���̕\���ɕK�v
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	mSpriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources/Fonts/SegoeUI_18.spritefont");

	// �e�N�X�`���̓ǂݍ���
	CreateWICTextureFromFile(
		device,
		L"Resources/Textures/TridentLogo.png",
		nullptr,
		mTexture.ReleaseAndGetAddressOf()
	);

	auto pRM = ResourceManager::GetInstance();
	pRM->Initialize();

	// ���\�[�X�}�l�[�W���Ƀ��f����o�^����
	pRM->RegisterCmoModel(L"Resources/Models/StarBox.cmo", "Title");
	pRM->RegisterCmoModel(L"Resources/Models/Arwing.cmo", "Player");
	pRM->RegisterCmoModel(L"Resources/Models/bg.cmo", "TitleBackground");

	// �J�����̍쐬
	mCamera = std::make_unique<Camera>();

	// �^�C�g���̃��f��
	mpTitleObject = std::make_unique<TitleObject>();
	mpTitleObject->Initialize();

	// ��s�@���f���̍쐬
	mpPlane = std::make_unique<TitlePlane>();
	mpPlane->Initialize();

	// �w�i�̃��f��
	mpTitleBackground = std::make_unique<TitleBackground>();
	mpTitleBackground->Initialize();
	
	// mFade
	mFade = std::make_unique<Fade>(1.0f,0.0f);
	mFade->Initialize();
	//mFade->SetClose();
}

//----------------------------------------------------
// �T�v�F�X�V
// ����(timer)�F����
// �߂�l(GAME_SCENE)�F���̃V�[��
//----------------------------------------------------
GAME_SCENE TitleScene::Update(const DX::StepTimer& timer)
{
	// �}�E�X���͏����擾����
	auto mouseState = DirectX::Mouse::Get().GetState();

	auto keyStateT = InputManager::GetInstance();

	float elaspedTime = static_cast<float>(timer.GetElapsedSeconds());

	// �^�C�g�����f���̍X�V
	mpTitleObject->Update();
	// ��s�@�̍X�V
	mpPlane->Update();
	// �w�i�̃��f��
	mpTitleBackground->Update();

	// �t�F�[�h�̍X�V
	mFade->Update(elaspedTime);

	switch (mState)
	{
		case TITLE_STATE::START:
		{
			if (mFade->IsOpen())
			{
				mState = TITLE_STATE::PLAY;
			}
			break;
		}
		case TITLE_STATE::PLAY:
		{
			// Z�L�[�������ꂽ��Z���N�g�V�[���Ɉڍs����
			if (
				keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Z)
				&& mFade->IsOpen()
				)
			{
				mFade->SetClose();
			}
			if (mFade->IsClose())
			{
				mState = TITLE_STATE::NEXT_SCENE;
			}
			break;
		}
		case TITLE_STATE::NEXT_SCENE:
		{	
			return GAME_SCENE::SELECT;
			break;
		}
		default:
		{
			assert("��O�������������܂����B");
			break;
		}
	}

	return GAME_SCENE::NONE;
}

//----------------------------------------------------------------------
// �T�v�F�`��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void TitleScene::Draw()
{
	// �^�C�g���I�u�W�F�N�g�̕`��
	mpTitleObject->Draw(mCommonState.get(), mCamera.get());
	// ��s�@�̕`��
	mpPlane->Draw(mCommonState.get(),mCamera.get());
	// �w�i�̃��f��
	mpTitleBackground->Draw(mCommonState.get(), mCamera.get());

	mSpriteBatch->Begin(SpriteSortMode_Deferred, mCommonState->NonPremultiplied());

	mSpriteBatch->End();

	mFade->Draw(mSpriteBatch.get());
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void TitleScene::Finalize()
{
	// �^�C�g���̔w�i���폜
	mpTitleBackground->Finalize();
}
