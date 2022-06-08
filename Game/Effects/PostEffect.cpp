/**
* @file PostEffect.cpp
* @brief �|�X�g�G�t�F�N�g���Ǘ�
* @author ���V�x��
* @date
* @details �|�X�g�G�t�F�N�g
*/
#include "pch.h"
#include "PostEffect.h"
#include <WICTextureLoader.h>
#include "../BinaryFile.h"
#include "d3d11.h"
#include <Model.h>
#include <Mouse.h>
#include <array>
#include "Game.h"
#include <CommonStates.h>

// ���O��Ԃ𗘗p
using namespace DirectX::SimpleMath;
using namespace DirectX;

// �C���v�b�g���C�A�E�g�̐ݒ�
const std::vector<D3D11_INPUT_ELEMENT_DESC> PostEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//------------------------------------------------------------
// �T�v�F����
// ����(deviceResources)�F�f�o�C�X���\�[�X
// ����(name)�F�t�@�C����
// ����(count)�F��
// @return void �Ȃ�
//--------------------------------------------------------------
void PostEffect::Create(DX::DeviceResources* deviceResources, const wchar_t* name, int count)
{
	UNREFERENCED_PARAMETER(name);
	mDeviceResources = deviceResources;
	auto device = mDeviceResources->GetD3DDevice();
	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		mInputLayout.GetAddressOf());


	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, mVertexShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}
	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, mGeometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, mPixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	// �v���~�e�B�u�o�b�`�̍쐬
	mBatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(mDeviceResources->GetD3DDeviceContext());

	mStates = std::make_unique<CommonStates>(device);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &mCBuffer);
	mFxFactory = std::make_unique<EffectFactory>(device);
	mFxFactory->SetDirectory(L"Resources/Models");

	for (int i = 0; i < count; i++) 
	{
		MyEffect* effect = new MyEffect();
		mEffectList.push_back(std::move(effect));
	}
}
//---------------------------------------------------------
// �T�v�F����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------------
void PostEffect::Lost()
{
	for (std::list<MyEffect*>::iterator itr = mEffectList.begin(); itr != mEffectList.end(); ++itr)
	{
		if ((*itr) != nullptr)
		{
			delete (*itr);
		}
	}
	mEffectList.clear();
}
//----------------------------------------------------------
// �T�v�F������
// ���� (life) :��������
// ���� (pos): ���W
// �߂�l void�F�Ȃ�
//---------------------------------------------------------
void PostEffect::Initialize(float life, DirectX::SimpleMath::Vector3 pos)
{
	UNREFERENCED_PARAMETER(life);
	UNREFERENCED_PARAMETER(pos);
}
//----------------------------------------------------------
// �T�v�F�X�V
// ���� (timer) :��������
// �߂�l void : �Ȃ�
//---------------------------------------------------------
void PostEffect::Update(DX::StepTimer timer)
{
	mTimer = timer;
	for (std::list<MyEffect*>::iterator itr = mEffectList.begin(); itr != mEffectList.end(); itr++)
	{
		(*itr)->Update(timer);
	}
}
//----------------------------------------------------------
// �T�v�F�|�X�g�G�t�F�N�g�̊J�n
// ���� :�Ȃ�
// �߂�l void : �Ȃ�
//---------------------------------------------------------
void PostEffect::StartEffect()
{
	auto context = mDeviceResources->GetD3DDeviceContext();

	D3D11_TEXTURE2D_DESC texDesc;
	mDeviceResources->GetRenderTarget()->GetDesc(&texDesc);
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	mDeviceResources->GetD3DDevice()->CreateTexture2D(&texDesc, NULL, mCapture.ReleaseAndGetAddressOf());

	// �����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	// �����_�[�^�[�Q�b�g�r���[�̐���
	mDeviceResources->GetD3DDevice()->CreateRenderTargetView(mCapture.Get(), &rtvDesc, &mRtv);

	//�V�F�[�_���\�[�X�r���[�̐ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

	mdesc = srvDesc;

	ID3D11DepthStencilView* pDSV = mDeviceResources->GetDepthStencilView();

	//�w�i�F�̐ݒ�i�A���t�@���O�ɂ���ƃI�u�W�F�N�g�̂ݕ\���j
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 0.0f };

	//�����_�[�^�[�Q�b�g�r���[���Z�b�g���A����������
	context->OMSetRenderTargets(1, mRtv.GetAddressOf(), pDSV);
	context->ClearRenderTargetView(mRtv.Get(), clearColor);
	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//----------------------------------------------------------
// �T�v�F�`��
// ���� :�Ȃ�
// �߂�l void : �Ȃ�
//---------------------------------------------------------
void PostEffect::Render()
{
	mVertex.clear();
	//�}�l�[�W���ŊǗ����Ă���G�t�F�N�g���C�e���[�^����
	for (auto itr = mEffectList.begin(); itr != mEffectList.end(); itr++)
	{
		//�G�t�F�N�g�̒��_�̍��W�Ƒ��x���擾����
		Vector3 pos = (*itr)->GetPosition();
		Vector3 vel = (*itr)->GetVelocity();

		{
			//�擾�������W��o�^����
			VertexPositionColorTexture vertex;
			//vertex = VertexPositionColorTexture(pos, Vector4(vel.x,vel.y,vel.z,1), Vector2(0.0f,3.0f));
			vertex = VertexPositionColorTexture(pos, Vector4::Zero, Vector2::Zero);
			mVertex.push_back(vertex);
		}
	}
	static float rot = 0;
	rot++;

	//----------------------------------------------------------------------------
	//�`�悵����ʂ�m_srv�ɕۑ�
	auto hr = mDeviceResources->GetD3DDevice()->CreateShaderResourceView(
		mCapture.Get(), &mdesc, mSrv.ReleaseAndGetAddressOf());
	UNREFERENCED_PARAMETER(hr);
	//------------------------------------------------------------------

	//�S��ʃG�t�F�N�g

	//Matrix  mat = Matrix::Identity;
	//Draw(mat, mat, mat);


	//�|���S���G�t�F�N�g
	Draw(mBillboardTranslation, mView, mProj);

}

//----------------------------------------------------------
// �T�v�F�|�X�g�G�t�F�N�g�̏I��
// ���� :�Ȃ�
// �߂�l void : �Ȃ�
//---------------------------------------------------------
void PostEffect::EndEffect()
{
	auto context = mDeviceResources->GetD3DDeviceContext();

	//�w�i�F�̐ݒ�i�A���t�@���O�ɂ���ƃI�u�W�F�N�g�̂ݕ\���j
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 0.0f };

	ID3D11RenderTargetView* defaultRTV = mDeviceResources->GetRenderTargetView();
	ID3D11DepthStencilView* pDSV = mDeviceResources->GetDepthStencilView();

	//�ݒ�����Ƃɖ߂�
	clearColor[0] = 0.3f;
	clearColor[1] = 0.3f;
	context->OMSetRenderTargets(1, &defaultRTV, pDSV);
	context->ClearRenderTargetView(defaultRTV, clearColor);
	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
//---------------------------------------------------
// �T�v�F�`��ݒ�
// ����(camera)�F�J�������W
// ����(view)�F�r���[���W
// ����(proj)�F�v���W�F�N�V�������W
// �߂�l�F�Ȃ�
//-------------------------------------------------
void PostEffect::SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	mView = view;
	mProj = proj;

	mBillboardTranslation = Matrix::CreateBillboard(mCenterPosition, camera, Vector3::UnitY);

	//�r���{�[�h�̌v�Z�ŗ��Ԃ�̂ŕ␳
	//Y����180�x��]����s��
	Matrix rev = Matrix::Identity;
	rev._11 = -1;
	rev._33 = -1;

	//�␳�s����ɂ����đ��ɉe�����Ȃ��悤�ɂ���
	mBillboardTranslation = rev * mBillboardTranslation;

}
//---------------------------------------------------
// �T�v�F�`��
// ����(camera)�F�J�������W
// ����(view)�F�r���[���W
// ����(proj)�F�v���W�F�N�V�������W
// �߂�l�F�Ȃ�
//-------------------------------------------------
void PostEffect::Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto context = mDeviceResources->GetD3DDeviceContext();

	// �}�E�X���͏����擾����
	auto mouseState = DirectX::Mouse::Get().GetState();
	DirectX::SimpleMath::Vector2 mousePos = DirectX::SimpleMath::Vector2((float)mouseState.x, (float)mouseState.y);

	//�萔�o�b�t�@�œn���l�̐ݒ�
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = world.Transpose();
	//Time		x:�o�ߎ���(�g�[�^���b)	y:1F�̌o�ߎ���(�b�j	z:�����i�T�C���J�[�u�j w:���g�p�i�b��łP�j
	cbuff.Time = Vector4((float)mTimer.GetTotalSeconds(), (float)mTimer.GetElapsedSeconds(), sinf((float)mTimer.GetTotalSeconds()), 1);

	cbuff.MouseP = DirectX::SimpleMath::Vector4(mouseState.x / 800.0f, mouseState.y / 600.0f, mouseState.leftButton, mouseState.rightButton);

	//�萔�o�b�t�@�̓��e�X�V
	context->UpdateSubresource(mCBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	ID3D11BlendState* blendstate = mStates->NonPremultiplied();
	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�͎Q�Ƃ̂�
	context->OMSetDepthStencilState(mStates->DepthRead(), 0);
	// �J�����O�͔����v���
	context->RSSetState(mStates->CullCounterClockwise());

	//�萔�o�b�t�@���V�F�[�_�ɓn���i�Ƃ肠����PS�͗v��Ȃ��̂ŃR�����g�A�E�g�j
	ID3D11Buffer* cb[1] = { mCBuffer.Get() };
	//context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);



	//�T���v���[�A�V�F�[�_�A�摜�����ꂼ��o�^
	ID3D11SamplerState* sampler[1] = { mStates->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	context->VSSetShader(mVertexShader.Get(), nullptr, 0);
	context->GSSetShader(mGeometryShader.Get(), nullptr, 0);
	context->PSSetShader(mPixelShader.Get(), nullptr, 0);
	context->PSSetShaderResources(0, 1, mSrv.GetAddressOf());
	context->PSSetShaderResources(1, 1, mTexture.GetAddressOf());

	//���̓��C�A�E�g�𔽉f
	context->IASetInputLayout(mInputLayout.Get());


	//�o�b�`�ɒ��_����n��
	mBatch->Begin();
	//m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	mBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &mVertex[0], mVertex.size());
	mBatch->End();


	//���̃��f���ɉe�����o��\��������̂Ŏg���I�������V�F�[�_���O��
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}