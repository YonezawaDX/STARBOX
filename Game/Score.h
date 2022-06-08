/**
* @file Score.h
* @brief �X�R�A�ۑ�
* @author ���V�x��
* @date
* @details �X�R�A�ۑ�
*/
#pragma once

/**
* @brief �X�R�A�̕ۑ��N���X
* @details �X�R�A�ۑ�
*/
class Score
{
public:
	/**
	* @brief �C���X�^���X
	* @return Score* �X�R�A�̃|�C���^
	*/
	static Score* GetInstance()
	{
		static Score instance;
		return &instance;
	}

	// �g�p�֐�---------------------------------------------------
	
	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	void Initialize();
	
	/**
	* @brief �X�R�A�̉��Z
	* @param (score) �ǉ������X�R�A
	* @return void �Ȃ�
	*/
	void AddScore(int score);

	/**
	* @brief �X�R�A�̉��Z
	* @return int �X�R�A�̎擾
	*/
	int GetScore() const;

	/**
	* @brief �{�X�̎��
	* @return int �{�X�̎��
	*/
	int GetBossNum() const;

	/**
	* @brief �{�X�̎��
	* @param (num) �{�X�̎��
	*/
	void SetBossNum(int num);
private:
	/**
	* @brief �R���X�g���N�^
	*/
	Score();
	/**
	* @brief �f�X�g���N�^
	*/
	~Score();
private:
	// �g�p�ϐ�---------------------------------------------
	//! �X�R�A�̒l
	int mScore;

	//! �Z���N�g�V�[���őI�񂾃{�X
	int mBossNum;
};