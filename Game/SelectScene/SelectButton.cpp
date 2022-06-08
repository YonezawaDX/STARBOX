/**
* @file SelectButton.cpp
* @brief �I�������{�^��
* @author ���V�x��
* @date 2022/04/26
* @details �I�������{�^���̕`��Ə���
*/
#include "pch.h"
#include "SelectButton.h"

#include "Libraries/MyLibraries/ResourceManager.h"
#include <Keyboard.h>
#include "Libraries/MyLibraries/InputManager.h"

// �萔-----------------------------------------------------------------

// �������{�^���̃T�C�Y
const float SelectButton::BUTTON_SIZE_NORMAL = 0.75f;
// �傫���{�^���̃T�C�Y
const float SelectButton::BUTTON_SIZE_BIG = 0.80f;

// �{�^����X���W
const int SelectButton::BUTTON_POS_X = 700;
// �{�^���P��Y���W
const int SelectButton::BUTTON_POS_Y_01 = 200;
// �{�^���Q��Y���W
const int SelectButton::BUTTON_POS_Y_02 = BUTTON_POS_Y_01 + 150;
//----------------------------------------------------------------------

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
SelectButton::SelectButton() :
	mSelectType(SELECT_TYPE::NONE),
	mButtonSize01(0.0f),
	mButtonSize02(0.0f),
	mBossLetter()
{
}
//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void SelectButton::Initialize()
{
	// �Z���N�g�^�C�v�𑀍�ɂ��Ă���
	mSelectType = SELECT_TYPE::OPERATE;
	
	// �{�^���̃T�C�Y��ݒ肵�Ă���
	mButtonSize01 = BUTTON_SIZE_NORMAL;
	mButtonSize02 = BUTTON_SIZE_NORMAL;

	mBossLetter.resize(2);
	
	// ���\�[�X�}�l�[�W���̎擾
	ResourceManager* pRM = ResourceManager::GetInstance();
	for (unsigned int i = 0; i < mBossLetter.size(); i++)
	{
		mBossLetter[i] = std::make_unique<Letter>();

		mBossLetter[i]->Initialize(
			pRM->GetTexture("Letter"),
			0,
			0,
			"AA",
			DirectX::Colors::White
		);
	}

	mBossLetter[0]->SetPos(BUTTON_POS_X, BUTTON_POS_Y_01);
	mBossLetter[0]->SetStr("BOSS01");

	mBossLetter[1]->SetPos(BUTTON_POS_X, BUTTON_POS_Y_02);
	mBossLetter[1]->SetStr("BOSS02");
}

//----------------------------------------------------
// �T�v�F�X�V
// ����(timer):����
// �߂�l�F�Ȃ�
//----------------------------------------------------

void SelectButton::Update(DX::StepTimer timer)
{
	UNREFERENCED_PARAMETER(timer);
	// �L�[���͏����擾����
	auto keyStateT = InputManager::GetInstance();

	// �Z���N�g�V�[���̏���
	if (keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Z) && (mSelectType == SELECT_TYPE::OPERATE))
	{
		mSelectType = SELECT_TYPE::BOSS01;
		mButtonSize01 = BUTTON_SIZE_BIG;
	}
	// �I�y���[�g����Ȃ��ꍇ
	if (mSelectType != SELECT_TYPE::OPERATE)
	{
		// �I�y���[�g�ɖ߂�
		if (keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::X))
		{
			mSelectType = SELECT_TYPE::OPERATE;
			// �{�^���̃T�C�Y��ݒ肵�Ă���
			mButtonSize01 = BUTTON_SIZE_NORMAL;
			mButtonSize02 = BUTTON_SIZE_NORMAL;
		}
		if (keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Up))
		{
			mSelectType = SELECT_TYPE::BOSS01;
			mButtonSize01 = BUTTON_SIZE_BIG;
			mButtonSize02 = BUTTON_SIZE_NORMAL;
		}
		if (keyStateT->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Down))		{
			mSelectType = SELECT_TYPE::BOSS02;
			mButtonSize01 = BUTTON_SIZE_NORMAL;
			mButtonSize02 = BUTTON_SIZE_BIG;
		}
	}
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void SelectButton::Draw(DirectX::CommonStates* commStates ,DirectX::SpriteBatch* spriteBatch)
{
	// ���\�[�X�}�l�[�W���̎擾
	ResourceManager* pRM = ResourceManager::GetInstance();
	// ���W�w��

	// �{�^���̕`��
	spriteBatch->Draw(
		pRM->GetTexture("Button"),
		DirectX::SimpleMath::Vector2(BUTTON_POS_X, BUTTON_POS_Y_01),
		nullptr,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		mButtonSize01,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	// �{�^���̕`��
	spriteBatch->Draw(
		pRM->GetTexture("Button"),
		DirectX::SimpleMath::Vector2(BUTTON_POS_X, BUTTON_POS_Y_02),
		nullptr,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		mButtonSize02,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	// �����̕`��
	for (unsigned int i = 0; i < mBossLetter.size(); i++)
	{
		mBossLetter[i]->Draw(commStates, spriteBatch);
	}
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void SelectButton::Finalize()
{
}

// �Q�b�^�[�A�Z�b�^�[----------------------------------------------------

//---------------------------------------
// �T�v�F�{�^���̑I����Ԃ̃Q�b�^�[
// �����F�Ȃ�
// �߂�l(SELECT_TYPE)�F�I�����
//---------------------------------------
SelectButton::SELECT_TYPE SelectButton::GetSelectType() const
{
	return mSelectType;
}
