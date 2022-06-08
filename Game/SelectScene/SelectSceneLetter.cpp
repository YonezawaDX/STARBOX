/**
* @file SelectSceneLetter.cpp
* @brief �Z���N�g�V�[���̕������Ǘ�
* @author ���V�x��
* @date 2022/04/26
* @details �{�^����V�[���̕������Ǘ��A�`��
*/
#include "pch.h"
#include "SelectSceneLetter.h"

#include "Libraries/MyLibraries/ResourceManager.h"

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
SelectSceneLetter::SelectSceneLetter():
	mLetter(),
	mSelectType(0)
{
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void SelectSceneLetter::Initialize()
{
	// ���\�[�X�}�l�[�W���̎擾
	ResourceManager* pRM = ResourceManager::GetInstance();

	// �Z���N�g�^�C�v���I�y���[�g��
	mSelectType = 1;
	
	// �����̐�������
	mLetter.resize(5);
	for (unsigned int i = 0; i < mLetter.size(); i++)
	{
		mLetter[i] = std::make_unique<Letter>();
	
		mLetter[i]->Initialize(
			pRM->GetTexture("Letter"),
			0,
			0,
			"A",
			DirectX::Colors::White
		);
	}

	mLetter[0]->SetStr("PUSH UP");
	mLetter[0]->SetPos(700,20);

	mLetter[1]->SetStr("Z NEXT");
	mLetter[1]->SetPos(700, 500);

	mLetter[2]->SetStr("X BACK");
	mLetter[2]->SetPos(700, 550);

	mLetter[3]->SetStr("");
	mLetter[3]->SetPos(750, 70);
	
	mLetter[4]->SetStr("");
	mLetter[4]->SetPos(740, 120);
}

//----------------------------------------------------
// �T�v�F�X�V
// ����(timer):����
// �߂�l�F�Ȃ�
//----------------------------------------------------
void SelectSceneLetter::Update(DX::StepTimer timer)
{
	UNREFERENCED_PARAMETER(timer);

	if (mSelectType == 1)
	{
		mLetter[0]->SetStr("PUSH Z");
		mLetter[3]->SetStr("");
		mLetter[4]->SetStr("");
	}
	else if (mSelectType > 1)
	{
		mLetter[0]->SetStr("PUSH UP");
		mLetter[3]->SetStr("AND");
		mLetter[4]->SetStr("DOWN");
	}
}

//----------------------------------------------------------------------
// �T�v�F�`��
// ����(commonStates)�F�R�����X�e�C�g�̃|�C���^
// ����(camera)�F�J�����̃|�C���^
// �߂�l�F�Ȃ�
//---------------------------------------------------------------------
void SelectSceneLetter::Draw(DirectX::CommonStates* commStates, DirectX::SpriteBatch* spriteBatch)
{
	ResourceManager* pRM = ResourceManager::GetInstance();
	// �����̕`�������
	for (unsigned int i = 0; i < mLetter.size(); i++)
	{
		mLetter[i]->Draw(commStates, spriteBatch);
	}

	spriteBatch->Draw(
		pRM->GetTexture("Operation"),
		DirectX::SimpleMath::Vector2(0, 450),
		nullptr,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2::Zero,
		0.75f,
		DirectX::SpriteEffects::SpriteEffects_None,
		0.0f
	);
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void SelectSceneLetter::Finalize()
{
}

//---------------------------------------
// �T�v�F�{�^���̑I����Ԃ̃Q�b�^�[
// ����(num)�F�Z���N�g���Ă�����̂��擾
// �߂�l �Ȃ�
//---------------------------------------
void SelectSceneLetter::SetSelectType(int num)
{
	mSelectType = num;
}
