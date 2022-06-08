/**
* @file UI.h
* @brief ���[�U�[�C���^�[�t�F�[�X
* @author ���V�x��
* @date
* @details UI(HP)��`�悷��N���X
*/
#pragma once
#include <CommonStates.h>
#include <SpriteBatch.h>

// �O���錾
class Camera;

/**
* @brief ���[�U�[�C���^�[�t�F�[�X
* @details UI(HP)��`�悷��N���X
*/
class UI
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	UI();
	
	/**
	* @brief �f�X�g���N�^
	*/
	~UI();

	/**
	* @brief ������
	* @param (playerHP) �v���C���[�̗̑�
	* @param (bossHP) �{�X�̗̑�
	* @return void �Ȃ�
	*/
	void Initialize(int playerHp, int bossHp, int score);
	/**
	* @brief �X�V
	* @param (playerHP) �v���C���[�̗̑�
	* @param (bossHP) �{�X�̗̑�
	* @return void �Ȃ�
	*/
	void Update(int playerHp, int bossHp, int score);

	/**
	* @brief �`��
	* @param (commonStates) �R�����X�e�C�g
	* @param (camera) �J����
	* @return void �Ȃ�
	*/
	void Draw(DirectX::CommonStates* commonStates,DirectX::SpriteBatch* spriteBatch, Camera* camera);

	/**
	* @brief �I������
	* @return void �Ȃ�
	*/
	void Finalize();

private:
	/**
	* @brief �X�R�A�̕`��
	* @param (spriteBatch) �摜���
	* @return void �Ȃ�
	*/
	void DrawScore(DirectX::SpriteBatch* spriteBatch);
	
	/**
	* @brief �{�X�̗̑͂̕`��
	* @param (spriteBatch) �摜���
	* @return void �Ȃ�
	*/
	void DrawBossHP(DirectX::SpriteBatch* spriteBatch);
	
	/**
	* @brief �v���C���[�̗̑͂̕`��
	* @param (spriteBatch) �摜���
	* @return void �Ȃ�
	*/
	void DrawPlayerHP(DirectX::SpriteBatch* spriteBatch);

private:
	//! �v���C���[��HP
	int mPlayerHP;
	//! �{�X��HP
	int mBossHP;
	//! �X�R�A
	int mScore;

	// �{�X�̃p�[�c�摜(����̓��\�[�X�}�l�[�W���[�Ŏ����Ă���)
	// �e�����\�[�X�}�l�[�W���Ŏ����Ă����摜��\��
	// HP�o�[�~�Q�A�X�R�A�̐���(score0000010)������Ȋ���
};