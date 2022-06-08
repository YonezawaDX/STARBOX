/**
* @file Letter.h
* @brief ����
* @author ���V�x��
* @date
* @details �������A���t�@�x�b�g�啶���Ɛ����̂ݑΉ�
*/
#pragma once
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <CommonStates.h>
#include <string>

/**
* @brief �����̃N���X
* @details �������A���t�@�x�b�g�啶���Ɛ����̂ݑΉ�
*/
class Letter
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Letter();

	/**
	* @brief ������
	* @param (texture) �g���摜
	* @param (x) x���W
	* @param (y) y���W
	* @param (str) ������������
	* @param (color) �F
	* @return void �Ȃ�
	*/
	void Initialize(
		ID3D11ShaderResourceView* texture,
		int x, 
		int y, 
		const char* str,
		DirectX::FXMVECTOR color = DirectX::Colors::White
	);

	/**
	* @brief �`��
	* @param (commonStates) �R�����X�e�C�g
	* @param (camera) �J����
	* @return void �Ȃ�
	*/
	void Draw(DirectX::CommonStates* commonStates, DirectX::SpriteBatch* spriteBatch);

    /**
    * @brief ������ݒ�֐�
    * @param (str) ����
    * @return void �Ȃ�
    */
	void SetStr(const char* str);

	/**
	* @brief �\���ʒu�̐ݒ�֐�
	* @param (x) X���W
	* @param (y) Y���W
	* @return void �Ȃ�
	*/
	void SetPos(int x, int y);

private:
	//! �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;

	//! �����̃T�C�Y
	static const int SIZE = 48;

	//! �e�N�X�`���n���h��
	ID3D11ShaderResourceView* mTexture;

	//! ������
	std::string mStr;

	//! �\���ʒu
	int mX, mY;

	//! �����̐F
	DirectX::SimpleMath::Color mColor;

};
