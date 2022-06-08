/**
* @file SceneTransition.cpp
* @brief �V�[���J��
* @author ���V�x��
* @date 2022/04/26
* @details �V���O���g��
*/
#include "pch.h"
#include "SceneTransition.h"
#include "Game/Effects/Fade.h"

//----------------------------------------------------------
// �T�v�F������
// ����()�F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------------
void SceneTransition::Initialize()
{
	// �t�F�[�h�̍쐬
	mFade = std::make_unique<Fade>();

	// ������
	mFade->Initialize();
}

//----------------------------------------------------------
// �T�v�F�X�V
// ����()�F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------------
void SceneTransition::Update(const DX::StepTimer& timer)
{
}
