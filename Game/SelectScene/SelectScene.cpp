/**
* @file SelectScene.cpp
* @brief �Z���N�g�V�[��
* @author ���V�x��
* @date 2022/04/26
* @details �Z���N�g�V�[��
*/
#include "pch.h"
#include "SelectScene.h"
#include "Game/Effects/Fade.h"
#include "Libraries/MyLibraries/ResourceManager.h"

#include "Game/PlayScene/Object/Player.h"
#include "Game/PlayScene/BulletManager.h"

#include "Game/PlayScene/Object/BackGround.h"
#include "Game/PlayScene/Object/Floor.h"

#include "Libraries/MyLibraries/FollowCamera.h"
#include "Game/Effects/PostEffect.h"

#include "SelectButton.h"
#include "SelectSceneLetter.h"

#include "Game/Score.h"

#include "Libraries/MyLibraries/InputManager.h"

// �萔-------------------------------------------------------------------------------
const DirectX::SimpleMath::Vector3 SelectScene::CAMERA_POS = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -4.0f);
//-------------------------------------------------------------------------------


// ���O��Ԃ̗��p
using namespace DirectX;

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
SelectScene::SelectScene():
	mPostCamera(DirectX::SimpleMath::Vector3::Zero),
	mPlayCount(0.0f),
	mSelectTrans(SELECT_TRANS::NONE),
	mStartWindow(SimpleMath::Matrix::Identity),
	mEndWindow(SimpleMath::Matrix::Identity),
	mFps(0),
	mState(SELECT_STATE::START)
{
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
SelectScene::~SelectScene()
{
	Finalize();
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void SelectScene::Initialize()
{
	// ���\�[�X��o�^����
	ResourcesRegister();

	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// D3D�f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̎擾
	auto device = pDR->GetD3DDevice();
	auto context = pDR->GetD3DDeviceContext();

	// �R�����X�e�[�g::D3D�����_�����O��ԃI�u�W�F�N�g
	mCommonState = std::make_unique<DirectX::CommonStates>(device);

	// �X�v���C�g�o�b�`::�f�o�b�O���̕\���ɕK�v
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	mSpriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources/Fonts/SegoeUI_18.spritefont");

	//-----------------------------------------
	DirectX::SimpleMath::Vector3 camera = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -4.0f);
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::CreateLookAt(camera, target, DirectX::SimpleMath::Vector3::UnitY);

	// �ŏ��̉�ʂ̑傫���ƍŌ�̉�ʂ̈ʒu�Ƒ傫�����擾���Ă���
	mStartWindow = view * SimpleMath::Matrix::CreateScale(1.4f, 1.0f, 1.0f) * SimpleMath::Matrix::CreateTranslation(-0.8f, 0.5f, 0.0f);
	
	// �r���[���W�̍쐬
	view = DirectX::SimpleMath::Matrix::CreateLookAt(SimpleMath::Vector3(0.0f, 0.0f, -2.25f), target, DirectX::SimpleMath::Vector3::UnitY);
	mEndWindow = view * SimpleMath::Matrix::CreateScale(1.4f, 1.0f, 1.0f) * SimpleMath::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);

	RECT outputSize = pDR->GetOutputSize();
	UINT backBufferWidth = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize.bottom - outputSize.top, 1);

	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(backBufferWidth) / float(backBufferHeight), 0.1f, 1000.f);

	mPostEffect = std::make_unique<PostEffect>();
	mPostEffect->Create(pDR, L"Resources\\Textures\\image01.png", 1);


	// �|�X�g�G�t�F�N�g�̕`��
	mPostEffect->SetRenderState(
		camera,
		mStartWindow,
		proj
	);
	//------------------------------------------
	

	// �J�����̍쐬
	mCamera = std::make_unique<FollowCamera>();
	// �e�ۂ̊Ǘ��쐬
	mpBulletManager = std::make_unique<BulletManager>();
	mpBulletManager->Initialize();

	// �v���C���̍쐬
	mpPlayer = std::make_unique<Player>(mpBulletManager.get());
	mpPlayer->Initialize();

	// �w�i�̍쐬
	mpBackGround = std::make_unique<BackGround>();
	mpBackGround->Initialize();

	// ���̍쐬
	mpFloor = std::make_unique<Floor>();
	mpFloor->Initialize();

	// �t�F�[�h�̍쐬
	mpFade = std::make_unique<Fade>(1.0f, 0.0f);
	mpFade->Initialize();

	// �Z���N�g�{�^���̐���
	mSelectButton = std::make_unique<SelectButton>();
	mSelectButton->Initialize();

	// �Z���N�g�V�[���̕����̐���
	mSelectSceneLetter = std::make_unique<SelectSceneLetter>();
	mSelectSceneLetter->Initialize();
}

//----------------------------------------------------
// �T�v�F�X�V
// ����(timer)�F����
// �߂�l(GAME_SCENE)�F���̃V�[��
//----------------------------------------------------
GAME_SCENE SelectScene::Update(const DX::StepTimer& timer)
{
	auto keyStateT = InputManager::GetInstance();

	// �t���[�����[�g�̎擾
	mFps = timer.GetFramesPerSecond();

	// �e�ۂ̊Ǘ��X�V
	mpBulletManager->Update();

	mCamera->SetRefTargetPosition(mpPlayer->GetObjectPos());
	mCamera->SetRefEyePosition(mpPlayer->GetObjectPos() + mCamera->TARGET_TO_EYE_VEC);
	mCamera->Update();

	// �v���C���̍X�V
	mpPlayer->Update();

	// ���̍X�V
	mpFloor->Update();

	// �|�X�g�G�t�F�N�g�̍X�V
	mPostEffect->Update(timer);
	
	float elaspedTime = static_cast<float>(timer.GetElapsedSeconds());
	mpFade->Update(elaspedTime);

	switch (mState)
	{
		case SELECT_STATE::START:
		{
			// �t�F�[�h���J�����瑀��ł���
			if (mpFade->IsOpen())
			{
				mState = SELECT_STATE::PLAY;
			}
			break;
		}
		case SELECT_STATE::PLAY:
		{
			if (
				keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Z)
				&& mpFade->IsOpen()
				&& mSelectButton->GetSelectType() >= SelectButton::SELECT_TYPE::BOSS01
				)
			{
				mpFade->SetClose();
			}
			// ��ʂ����Ă����玟�̃V�[���֍s��
			if (mpFade->IsClose())
			{
				mState = SELECT_STATE::NEXT_SCENE;
			}

			// �Z���N�g�{�^���̍X�V
			mSelectButton->Update(timer);

			break;
		}
		case SELECT_STATE::NEXT_SCENE:
		{
			return GAME_SCENE::PLAY;
		}
		default:
		{
			assert("��O�������������܂����B");
			break;
		}
	}

	// �{�X�̃V�[����ύX
	auto pScore = Score::GetInstance();
	pScore->SetBossNum(static_cast<int>(mSelectButton->GetSelectType()));

	// �Z���N�g�V�[�������X�V
	mSelectSceneLetter->Update(timer);

	mSelectSceneLetter->SetSelectType(static_cast<int>(mSelectButton->GetSelectType()));

	return GAME_SCENE::NONE;
}

//----------------------------------------------------------------------
// �T�v�F�`��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void SelectScene::Draw()
{
	ResourceManager* pRM = ResourceManager::GetInstance();

	// �ϊ��s��̐錾(���[���h�A�r���[�A�ˉe)
	 SimpleMath::Matrix world, view, projection;

	// ���[���h�s��̏�����(�P�ʍs��)
	world = SimpleMath::Matrix::Identity;

	// �ˉe�s��̎擾
	projection = mCamera->GetProjectionMatrix();

	// �r���[�s��̎擾
	view = mCamera->GetViewMatrix();

	mPostEffect->StartEffect();

	// �e�ۂ̕`��
	mpBulletManager->Draw(mCommonState.get(), mCamera.get());


	// �v���C���̕`��
	mpPlayer->Draw(mCommonState.get(), mCamera.get());

	// �w�i
	mpBackGround->Draw(mCommonState.get(), mCamera.get());

	// ���̕`��
	mpFloor->Draw(mCommonState.get(), mCamera.get());

	// �|�X�g�G�t�F�N�g���I��������
	mPostEffect->EndEffect();
	mPostEffect->Render();


	// �X�v���C�g�o�b�`�ɂ��摜�̕\��--------------------------------------
	mSpriteBatch->Begin();
	 
	mSelectButton->Draw(mCommonState.get(),mSpriteBatch.get());
	mSelectSceneLetter->Draw(mCommonState.get(), mSpriteBatch.get());

	auto bossTex = pRM->GetTexture("Boss01");

	// �{�X�̎ʐ^��ύX����
	if (mSelectButton->GetSelectType() == SelectButton::SELECT_TYPE::BOSS01)
	{
		bossTex = pRM->GetTexture("Boss01");
	}
	if (mSelectButton->GetSelectType() == SelectButton::SELECT_TYPE::BOSS02)
	{
		bossTex = pRM->GetTexture("Boss02");
	}

	// �{�^����`�悷��
	if (mSelectButton->GetSelectType() >= SelectButton::SELECT_TYPE::BOSS01)
	{
		
		mSpriteBatch->Draw(
			bossTex,
			DirectX::SimpleMath::Vector2(43, 30),
			nullptr,
			DirectX::Colors::White,
			0.0f,
			DirectX::SimpleMath::Vector2::Zero,
			1.0f,
			DirectX::SpriteEffects::SpriteEffects_None,
			0.0f
		);
	}

	mSpriteBatch->End();
	//-----------------------------------------------------------------------

	// �t�F�[�h���s��
	mpFade->Draw(mSpriteBatch.get());
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void SelectScene::Finalize()
{
	if (mPostEffect != nullptr)
	{
		mPostEffect->Lost();
	}
}

//------------------------------------------------------------------
// �T�v�F���\�[�X�o�^�p
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void SelectScene::ResourcesRegister()
{
	auto pRM = ResourceManager::GetInstance();

	pRM->Initialize();

	// ���\�[�X�}�l�[�W���Ƀ��f����o�^����
	pRM->RegisterCmoModel(L"Resources/Models/Arwing.cmo", "Player");
	pRM->RegisterCmoModel(L"Resources/Models/Bullet.cmo", "Bullet");
	pRM->RegisterCmoModel(L"Resources/Models/Floor.cmo", "Floor");
	pRM->RegisterCmoModel(L"Resources/Models/BackGround.cmo", "PlayBackGround");
	pRM->RegisterCmoModel(L"Resources/Models/dice.cmo", "dice");
	pRM->RegisterCmoModel(L"Resources/Models/Enemy.cmo", "Enemy");

	// ���\�[�X�}�l�[�W���ɉ摜��ۑ�����
	pRM->RegisterTexture(L"Resources/Textures/bossHp.png", "bossHp");
	pRM->RegisterTexture(L"Resources/Textures/Hp.png", "Hp");
	pRM->RegisterTexture(L"Resources/Textures/out.png", "HpOut");
	pRM->RegisterTexture(L"Resources/Textures/Number.png", "Number");
	pRM->RegisterTexture(L"Resources/Textures/butto.png", "Button");
	pRM->RegisterTexture(L"Resources/Textures/texture01.png", "Letter");
	pRM->RegisterTexture(L"Resources/Textures/Operation.png", "Operation");
	pRM->RegisterTexture(L"Resources/Textures/BossSpr.png", "Boss01");
	pRM->RegisterTexture(L"Resources/Textures/BossSpr02.png", "Boss02");
}
