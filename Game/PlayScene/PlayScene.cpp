/**
* @file PlayScene.cpp
* @brief �v���C�V�[��
* @author ���V�x��
* @date 2022/04/26
* @details �v���C�V�[��
*/
#include "pch.h"
#include "PlayScene.h"

#include "../GameMain.h"
#include "DeviceResources.h"

#include "Libraries/MyLibraries/ResourceManager.h"
#include "Libraries/MyLibraries/FollowCamera.h"

#include "Game/PlayScene/Object/Player.h"
#include "Game/PlayScene/BulletManager.h"
#include "Game/PlayScene/EnemyManager.h"
#include "Game/PlayScene/Object/BackGround.h"
#include "Game/PlayScene/Object/Floor.h"
#include "Game/PlayScene/Object/Boss.h"
#include "Game/PlayScene/Object/Boss02.h"

#include "Game/Score.h"
#include "UI.h"

#include "Game/Effects/Fade.h"

// ���O��Ԃ̗��p
using namespace DirectX;

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
PlayScene::PlayScene()
	: mFps(0)
	, mpPlayer(nullptr)
	, mpBulletManager(nullptr)
	, mpEnemyManager(nullptr)
	, mpBackGround(nullptr)
	, mpFloor(nullptr)
	, mpBoss(nullptr)
	, mpUI(nullptr)
	, mpFade(nullptr)
	, mpBoss02(nullptr)
	, mState(PLAY_STATE::START)
{
}

//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
PlayScene::~PlayScene()
{
	Finalize();
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void PlayScene::Initialize()
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

	// �J�����̍쐬
	mCamera = std::make_unique<FollowCamera>();
	// �e�ۂ̊Ǘ��쐬
	mpBulletManager = std::make_unique<BulletManager>();
	mpBulletManager->Initialize();
	
	// �G�̊Ǘ��Ґ���
	mpEnemyManager = std::make_unique<EnemyManager>();
	mpEnemyManager->Initialize(mpBulletManager.get());

	// �v���C���̍쐬
	mpPlayer = std::make_unique<Player>(mpBulletManager.get());
	mpPlayer->Initialize();

	// �w�i�̍쐬
	mpBackGround = std::make_unique<BackGround>();
	mpBackGround->Initialize();

	// ���̍쐬
	mpFloor = std::make_unique<Floor>();
	mpFloor->Initialize();

	// �{�X�̍쐬
	mpBoss = std::make_unique<Boss>(mpBulletManager.get(), mpEnemyManager.get());
	mpBoss->Initialize();

	// �{�X�̍쐬
	mpBoss02 = std::make_unique<Boss02>(mpBulletManager.get(), mpEnemyManager.get());
	mpBoss02->Initialize();

	// UI�̍쐬
	mpUI = std::make_unique<UI>();
	mpUI->Initialize(mpPlayer->GetHP(), mpBoss->GetHP(), 1);

	// �t�F�[�h�̍쐬
	mpFade = std::make_unique<Fade>(1.0f, 0.0f);
	mpFade->Initialize();
}

//----------------------------------------------------
// �T�v�F�X�V
// ����(timer)�F����
// �߂�l(GAME_SCENE)�F���̃V�[��
//----------------------------------------------------
GAME_SCENE PlayScene::Update(const DX::StepTimer& timer)
{
	// �t���[�����[�g�̎擾
	mFps = timer.GetFramesPerSecond();

	// �e�ۂ̊Ǘ��X�V
	mpBulletManager->Update();

	mCamera->SetRefTargetPosition(mpPlayer->GetObjectPos());
	mCamera->SetRefEyePosition(mpPlayer->GetObjectPos() + mCamera->TARGET_TO_EYE_VEC);
	mCamera->Update();
	// �G�̊Ǘ��ҍX�V
	//mpEnemyManager->Update();

	for (int i = 0; i < mpEnemyManager->GetEnemyNum(); i++)
	{
		// ���g�p��ԂȂ珈�������Ȃ�
		if (!mpEnemyManager->GetEnemies(i)->GetActive())
		{
			continue;
		}
		mpBulletManager->CheckHitEnemy(mpEnemyManager->GetEnemies(i));
	}

	// �v���C���[�ƒe�Ƃ̓����蔻��
	//mpBulletManager->CheckHitPlayer(mpPlayer.get());

	// �G�ƃv���C���[�̓����蔻��
	//mpEnemyManager->CheckHitPlayer(mpPlayer.get());
	
	// �v���C���̍X�V
	mpPlayer->Update();

	// ���̍X�V
	mpFloor->Update();

	int bossHP = 0;

	auto pScore = Score::GetInstance();
	if (pScore->GetBossNum() == 2)
	{
		// �{�X�̍X�V
		mpBoss->Update(mpPlayer->GetObjectPos());
		bossHP = mpBoss->GetHP();
	}
	else if (pScore->GetBossNum() == 3)
	{
		// �{�X�O�Q�̍X�V
		mpBoss02->Update(mpPlayer->GetObjectPos());
		bossHP = mpBoss02->GetHP();
	}

	float elaspedTime = static_cast<float>(timer.GetElapsedSeconds());
	mpFade->Update(elaspedTime);
	switch (mState)
	{
		case PLAY_STATE::START:
		{
			// �t�F�[�h���J�����瑀��ł���
			if (mpFade->IsOpen())
			{
				mState = PLAY_STATE::PLAY;
			}
			break;
		}
		case PLAY_STATE::PLAY:
		{
			if (bossHP <= 1)
			{
				mpFade->SetClose();
			}
			// ��ʂ����Ă����玟�̃V�[���֍s��
			if (mpFade->IsClose())
			{
				mState = PLAY_STATE::NEXT_SCENE;
			}
			break;
		}
		case PLAY_STATE::NEXT_SCENE:
		{
			return GAME_SCENE::TITLE;
		}

		default:
		{
			assert("��O�������������܂����B");
			break;
		}
	}

	// UI�̍X�V
	mpUI->Update(mpPlayer->GetHP(), bossHP, 1);

	return GAME_SCENE::NONE;
}

//----------------------------------------------------------------------
// �T�v�F�`��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void PlayScene::Draw()
{
	// �ϊ��s��̐錾(���[���h�A�r���[�A�ˉe)
	SimpleMath::Matrix world, view, projection;

	// ���[���h�s��̏�����(�P�ʍs��)
	world = SimpleMath::Matrix::Identity;

	// �ˉe�s��̎擾
	projection = mCamera->GetProjectionMatrix();

	// �r���[�s��̎擾
	view = mCamera->GetViewMatrix();

	// �v���C���̕`��
	mpPlayer->Draw(mCommonState.get(), mCamera.get());

	// �w�i
	mpBackGround->Draw(mCommonState.get(), mCamera.get());
	
	// ���̕`��
	mpFloor->Draw(mCommonState.get(), mCamera.get());
	// �e�ۂ̕`��
	mpBulletManager->Draw(mCommonState.get(), mCamera.get());
	// �G�̕`��
	mpEnemyManager->Draw(mCommonState.get(), mCamera.get());

	auto pScore = Score::GetInstance();
	if (pScore->GetBossNum() == 2)
	{
		// �{�X�̕`��
		mpBoss->Draw(mCommonState.get(), mCamera.get());
	}
	else if (pScore->GetBossNum() == 3)
	{
		// �{�X�̕`��
		mpBoss02->Draw(mCommonState.get(), mCamera.get());
	}

	// FPS�̎擾�ƕ\��������̏���
	wchar_t buf[32];
	swprintf_s(buf, 32, L"FPS = %d", mFps);

	// �X�v���C�g�o�b�`�ɂ��f�o�b�O���̕\��
	mSpriteBatch->Begin();

	// UI�̕`��
	mpUI->Draw(mCommonState.get(), mSpriteBatch.get(), mCamera.get());

	mSpriteBatch->End();

	// �t�F�[�h���s��
	mpFade->Draw(mSpriteBatch.get());
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void PlayScene::Finalize()
{
	// �{�X�I�u�W�F�N�g�����Z�b�g����
	//mpBoss->Finalize();
	//mpBackGround->Finalize();

}

//------------------------------------------------------------------
// �T�v�F���\�[�X�o�^�p
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void PlayScene::ResourcesRegister()
{
	// ���\�[�X�̓o�^
	auto pRM = ResourceManager::GetInstance();

	// �{�X�̂P�̖�
	pRM->RegisterCmoModel(L"Resources/Models/AttackCarrierBody.cmo", "BossBody");
	pRM->RegisterCmoModel(L"Resources/Models/SmallArm.cmo", "BossSmallArm");
	pRM->RegisterCmoModel(L"Resources/Models/BigArm.cmo", "BossBigArm");

	// �{�X�̂Q�̖�
	pRM->RegisterCmoModel(L"Resources/Models/Core.cmo", "Core");
	pRM->RegisterCmoModel(L"Resources/Models/Cover.cmo", "Cover");
	pRM->RegisterCmoModel(L"Resources/Models/Prime2.cmo", "Prime");
	pRM->RegisterCmoModel(L"Resources/Models/Tire.cmo", "Tire");

}
