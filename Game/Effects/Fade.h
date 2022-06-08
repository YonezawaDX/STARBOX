/**
* @file Fade.h
* @brief �t�F�[�h�C���E�A�E�g
* @author ���V�x��
* @date 2022/05/19
* @details �t�F�[�h�C���E�A�E�g���s��
*/
#pragma once
#include <SpriteBatch.h>
#include <Effects.h>

/**
* @brief Fade�̃N���X
* @details Fade
*/
class Fade
{
public:
	Fade(float interval = 1.0f, float rate = 1.0f);
	~Fade() = default;

	void Initialize();
	void Update(float elasped);
	void Draw(DirectX::SpriteBatch* batch);

	// �J����
	void SetOpen();
	// ����
	void SetClose();
	// �J���Ă��邩
	bool IsOpen() const;
	// ���Ă��邩
	bool IsClose() const;
private:
	
	// �s�N�Z���V�F�[�_�[�ɓn���萔�o�b�t�@�̍\����
	struct cbChangesEveryFrame
	{
		float radius;				// ���a�̔䗦�F0�`1
		float aspectRatio;			// �A�X�y�N�g��
		DirectX::XMFLOAT2 dummy;	// �p�f�B���O�f�[�^
	};

	//! �萔�o�b�t�@�֘A
	cbChangesEveryFrame mCbChangesEveryFrame;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mCbBuffer;

	//! 2D�e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mTextureBuffer;

	//! �V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mShaderResourceView;

	//! �I�[�v�����̓N���[�Y����܂ł̃��C�v����
	float mInterval;

	//! ����(0�`1)�F0�̏ꍇ���Ă���
	float mRate;

	//! �I�[�v���t���O�Ftrue�̏ꍇ�I�[�v��
	bool mFlagOpen;

	//! �s�N�Z���V�F�[�_�֘A
	Microsoft::WRL::ComPtr<ID3DBlob> mBlobPixel;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
};
