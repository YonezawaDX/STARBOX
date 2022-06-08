/**
* @file PostEffect.h
* @brief �|�X�g�G�t�F�N�g���Ǘ�
* @author ���V�x��
* @date
* @details �|�X�g�G�t�F�N�g
*/
#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include "Model.h"
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <list>
#include "MyEffect.h"

/**
* @brief �|�X�g�G�t�F�N�g�̃N���X
* @details ��ʂɑ΂���V�F�[�_
*/
class PostEffect
{
public:
	/**
	* @struct �R���X�g�o�b�t�@�[
	*/
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;	//! ���[���h���W
		DirectX::SimpleMath::Matrix		matView;	//! �r���[���W
		DirectX::SimpleMath::Matrix		matProj;	//! �v���W�F�N�V�������W
		DirectX::SimpleMath::Vector4	Time;		//! �^�C��
		DirectX::SimpleMath::Vector4	MouseP;		//! �}�E�X�̍��W
	};
	//! �C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	

	/**
	* @brief ����
	* @param (deviceResources) �f�o�C�X���\�[�X
	* @param (name) �t�@�C����
	* @param (count) ��
	* @return void �Ȃ�
	*/
	void Create(DX::DeviceResources* deviceResources, const wchar_t* name, int count);
	
	/**
	* @brief ������
	* @param (life) ��������
	* @param (pos) ���W
	* @return void �Ȃ�
	*/
	void Initialize(float life, DirectX::SimpleMath::Vector3 pos);
	
	/**
	* @brief �X�V
	* @param (timer) ����
	* @return void �Ȃ�
	*/
	void Update(DX::StepTimer timer);
	
	/**
	* @brief �|�X�g�G�t�F�N�g�̊J�n
	* @return void �Ȃ�
	*/
	void StartEffect();
	
	/**
	* @brief �`��
	* @return void �Ȃ�
	*/
	void Render();
	
	/**
	* @brief �|�X�g�G�t�F�N�g�̏I��
	* @return void �Ȃ�
	*/
	void EndEffect();
	
	/**
	* @brief ����
	* @return void �Ȃ�
	*/
	void Lost();

	/**
	* @brief �`��ݒ�
	* @param (camera) �J�������W
	* @param (view) �r���[���W
	* @param (proj) �v���W�F�N�V�������W
	* @return void �Ȃ�
	*/
	void SetRenderState(
		DirectX::SimpleMath::Vector3 camera, 
		DirectX::SimpleMath::Matrix view, 
		DirectX::SimpleMath::Matrix proj
	);

	/**
	* @brief �`��
	* @param (camera) ���[���h�s��
	* @param (view) �r���[�s��
	* @param (proj) �v���W�F�N�V�����s��
	* @return void �Ȃ�
	*/
	void Draw(
		DirectX::SimpleMath::Matrix world,
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix proj
	);
	/**
	* @brief �`��
	* @return CommonStates* �R�����X�e�C�g
	*/
	DirectX::CommonStates* GetCommonstate() { return mStates.get(); }
private:
	//! �G�t�F�N�g�̃��X�g
	std::list<MyEffect*>		mEffectList;
	//! �摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;
	//! ����
	DX::StepTimer                           mTimer;

	//! �f�o�C�X���\�[�X
	DX::DeviceResources* mDeviceResources;
	//! �V�[�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	mCBuffer;
	//! �R�����X�e�C�g
	std::unique_ptr<DirectX::CommonStates> mStates;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGeometryShader;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> mBatch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
	//! ���_
	std::vector<DirectX::VertexPositionColorTexture>  mVertex;

	//! ���S���W
	DirectX::SimpleMath::Vector3 mCenterPosition;

	//! �r���{�[�h
	DirectX::SimpleMath::Matrix mBillboardTranslation;
	//! �r���[
	DirectX::SimpleMath::Matrix mView;
	//! �v���W�F�N�V����
	DirectX::SimpleMath::Matrix mProj;
	//! �����t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> mFxFactory;

	//! �摜�ۑ�
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mCapture;

	//! �����_�[�^�[�Q�b�g�r���[
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	mRtv;
	//Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_rtv2;

	//! �u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> mpBlendState;

	//! �V�F�[�_�[���\�[�X
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSrv;

	//! �f�X�N
	D3D11_SHADER_RESOURCE_VIEW_DESC mdesc;
	//! ���f��
	std::unique_ptr<DirectX::Model> mModel;

};