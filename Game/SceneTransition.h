/**
* @file SceneTransition.h
* @brief �V�[���J��
* @author ���V�x��
* @date 2022/05/11
* @details �V�[���J�ڗp�̃V���O���g��
*/
#pragma once
#include <StepTimer.h>

// �O���錾
class Fade;

/**
* @brief �V�[���J�ڗp
* @details �V�[���J�ڂ��Ǘ�����V���O���g��
*/
class SceneTransition
{
public:
	/**
	* @brief �V�[���J�ڂ𐶐�����
	* @return SceneTransition* �V�[���J�ڂ̃|�C���^
	*/
	static SceneTransition* GetInstance()
	{
		static SceneTransition instance;
		return &instance;
	}

private:
	/**
	* @brief �R���X�g���N�^
	*/
	SceneTransition();
	
	/**
	* @brief �f�X�g���N�^
	*/
	~SceneTransition() = default;

private:
	//! �t�F�[�h�p
	std::unique_ptr<Fade> mFade;

private:
	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param (SceneTransition&) �Q��
	*/
	SceneTransition(const SceneTransition&) = delete;
	SceneTransition& operator=(const SceneTransition&) = delete;
	
	/**
	* @brief ���[�u�R���X�g���N�^
	* @param (SceneTransition&&) �Q��
	*/
	SceneTransition(const SceneTransition&&) = delete;
	SceneTransition&& operator=(const SceneTransition&&) = delete;


public:
	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	void Initialize();
	/**
	* @brief �X�V
	* @return void �Ȃ�
	*/
	void Update(const DX::StepTimer& timer);
};