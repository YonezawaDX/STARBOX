/**
* @file InputManager.cpp
* @brief �C���v�b�g�}�l�[�W���[
* @author ���V�x��
* @date
* @details �}�E�X�A�L�[�{�[�h�̓��͂𐿂�����
*/
#include "pch.h"
#include "InputManager.h"

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
void InputManager::Initialize(const HWND& window)
{
	// �L�[�{�[�h�֘A
	mKeyboard = std::make_unique<DirectX::Keyboard>();
	mKeyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	
	// �}�E�X�֘A
	mMouse = std::make_unique<DirectX::Mouse>();
	mMouse->SetWindow(window);
	mButtonStateTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();

}

//------------------------------------------------------------------
// �T�v�F�X�V
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//-------------------------------------------------------------------
void InputManager::Update()
{
	// �L�[�{�[�h�̏�ԍX�V
	mKeyboardState = mKeyboard->GetState();
	// �L�[�{�[�h�g���b�J�[�̍X�V
	mKeyboardStateTracker->Update(mKeyboardState);

	// �}�E�X�̏�ԍX�V
	mMouseState = mMouse->GetState();
	// �}�E�X�{�^���g���b�J�[�̍X�V
	mButtonStateTracker->Update(mMouseState);
}
