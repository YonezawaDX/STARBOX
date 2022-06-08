/**
* @file InputManager.h
* @brief �C���v�b�g�}�l�[�W���[
* @author ���V�x��
* @date
* @details �}�E�X�A�L�[�{�[�h�̓��͂𐿂�����
*/
#pragma once
#include <Mouse.h>
#include <Keyboard.h>

/**
* @brief �C���v�b�g�}�l�[�W���[�̃N���X
* @details �}�E�X�A�L�[�{�[�h�̓��͂𐿂�����
*/
class InputManager
{
public:
	/**
	* @brief �C���v�b�g�}�l�[�W���[�𐶐�����
	* @return InputManager* �C���v�b�g�}�l�[�W���[�̃|�C���^
	*/
	static InputManager* GetInstance()
	{
		static InputManager instance;
		return &instance;
	}
private:
	//! �}�E�X�֘A
	std::unique_ptr<DirectX::Mouse> mMouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> mButtonStateTracker;
	DirectX::Mouse::State mMouseState;
	//! �L�[�{�[�h�֘A
	std::unique_ptr<DirectX::Keyboard> mKeyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> mKeyboardStateTracker;
	DirectX::Keyboard::State mKeyboardState;

private:
	/**
	* @brief �R���X�g���N�^
	*/
	InputManager() : mKeyboardState(), mMouseState() {};
	/**
	* @brief �f�X�g���N�^
	*/
	~InputManager() = default;

private:
	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param (InputManager&) �Q��
	*/
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	
	/**
	* @brief ���[�u�R���X�g���N�^
	* @param (InputManager&&) �Q��
	*/
	InputManager(const InputManager&&) = delete;
	InputManager&& operator=(const InputManager&&) = delete;

public:
	/**
	* @brief ������
	* @param (window) ��ʂ̑傫�����擾
	* @return void �Ȃ�
	*/
	void Initialize(const HWND& window);
	/**
	* @brief �X�V
	* @return void �Ȃ�
	*/
	void Update();
	// �e��Q�b�^
	
	/**
	* @brief �}�E�X�̏�Ԃ̃Q�b�^�[
	* @return Mouse::State& �}�E�X�̏��
	*/
	DirectX::Mouse::State& GetMouseState() { return mMouseState; }
	
	/**
	* @brief �L�[�{�[�h�̏�Ԃ̃Q�b�^�[
	* @return Keyboard::State& �L�[�{�[�h�̏��
	*/
	DirectX::Keyboard::State& GetKeyboardState() { return mKeyboardState; }

	/**
	* @brief �{�^���̏�Ԃ̃Q�b�^�[
	* @return ButtonStateTracker* �{�^���̏�ԃ|�C���^
	*/
	DirectX::Mouse::ButtonStateTracker* GetButtonStateTracker() const { return mButtonStateTracker.get(); }
	
	/**
	* @brief �L�[�{�[�h�̏�Ԃ̃Q�b�^�[
	* @return KeyboardStateTracker* �L�[�{�[�h�̏�ԃ|�C���^
	*/
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker()const { return mKeyboardStateTracker.get(); }

};