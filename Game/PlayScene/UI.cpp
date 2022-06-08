/**
* @file UI.cpp
* @brief ���[�U�[�C���^�[�t�F�[�X
* @author ���V�x��
* @date
* @details UI(HP)��`�悷��N���X
*/
#include "pch.h"
#include "UI.h"
#include "Libraries/MyLibraries/ResourceManager.h"
#include <SimpleMath.h>

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
UI::UI() :
	mPlayerHP(0),
	mBossHP(0),
	mScore(0)
{
}
//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
UI::~UI()
{
}

//----------------------------------------------------
// �T�v�F������
// ����(playerHP) : �v���C���[�̗̑�
// ����(bossHP) : �{�X�̗̑�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void UI::Initialize(int playerHp, int bossHp, int score)
{
	// ���ꂼ��̕ϐ����i�[����
	mPlayerHP = playerHp;
	mBossHP = bossHp;
	mScore = score;
}

//----------------------------------------------------
// �T�v�F�X�V
// ����(playerHP) : �v���C���[�̗̑�
// ����(bossHP) : �{�X�̗̑�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void UI::Update(int playerHp, int bossHp, int score)
{
	mPlayerHP = playerHp;
	mBossHP = bossHp;
	mScore = score;
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void UI::Draw(DirectX::CommonStates* commonStates, DirectX::SpriteBatch* spriteBatch, Camera* camera)
{
	UNREFERENCED_PARAMETER(commonStates);
	UNREFERENCED_PARAMETER(camera);
	DrawBossHP(spriteBatch);
	DrawPlayerHP(spriteBatch);
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void UI::Finalize()
{
}

//-------------------------------------------------------------------
// �T�v�F�X�R�A�̕`��
// ����(spriteBatch)�F�摜���
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void UI::DrawScore(DirectX::SpriteBatch* spriteBatch)
{
	UNREFERENCED_PARAMETER(spriteBatch);

	// �؂��肷��
	RECT* re = new RECT();
	re->top = (LONG)0.0f;
	re->left = (LONG)0.0f;
	re->bottom = (LONG)100.0f;
	re->right = (LONG)300.0f;

	// �폜����
	delete re;
}

//-------------------------------------------------------------------
// �T�v�F�{�X�̗̑͂̕`��
// ����(spriteBatch)�F�摜���
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void UI::DrawBossHP(DirectX::SpriteBatch* spriteBatch)
{
	// ���\�[�X�̌Ăяo��
	auto pRM = ResourceManager::GetInstance();

	// ���W�w��
	DirectX::SimpleMath::Vector2 pos(700, 0);

	// �؂��肷��
	RECT* re = new RECT();
	re->top = (LONG)0.0f;
	re->left = (LONG)0.0f;
	re->bottom = (LONG)20.0f;
	re->right = (LONG)(10.0f * 16.5f);

	// HP�̊O�g��`�悷��
	spriteBatch->Draw(
		pRM->GetTexture("HpOut"),
		pos,
		re,
		DirectX::Colors::Gray,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		2.0f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	re->right = mBossHP * (LONG)16.5f;
	// �`�悷��
	spriteBatch->Draw(
		pRM->GetTexture("bossHp"),
		pos,
		re,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		2.0f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	// �폜����
	delete re;
}

//-------------------------------------------------------------------
// �T�v�F�v���C���[�̗̑͂̕`��
// ����(spriteBatch)�F�摜���
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void UI::DrawPlayerHP(DirectX::SpriteBatch* spriteBatch)
{
	// ���\�[�X�̌Ăяo��
	auto pRM = ResourceManager::GetInstance();

	// ���W�w��
	DirectX::SimpleMath::Vector2 pos(0, 680);

	// �؂��肷��
	RECT* re = new RECT();
	re->top = (LONG)0.0f;
	re->left = (LONG)0.0f;
	re->bottom = (LONG)20.0f;
	re->right = (LONG)(10.0f * 16.5f);

	// HP�̊O�g��`�悷��
	spriteBatch->Draw(
		pRM->GetTexture("HpOut"),
		pos,
		re,
		DirectX::Colors::Gray,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		2.0f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	re->right = (LONG)(mPlayerHP * 16.5f);
	// �`�悷��
	spriteBatch->Draw(
		pRM->GetTexture("Hp"),
		pos,
		re,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		2.0f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);

	// �폜����
	delete re;
}
