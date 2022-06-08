/**
* @file Fade.cpp
* @brief �t�F�[�h�C���E�A�E�g
* @author ���V�x��
* @date 2022/05/19
* @details �t�F�[�h�C���E�A�E�g���s��
*/
#include "pch.h"
#include "Fade.h"

#include "DeviceResources.h"
#include <cassert>

// �V�F�[�_�̃R���p�C��
#include "ReadData.h"

Fade::Fade(float interval, float rate):
	mInterval(interval),
	mRate(rate),
	mFlagOpen(true),
	mCbChangesEveryFrame()
{
}

void Fade::Initialize()
{
	// �f�o�C�X���\�[�X�̎擾
	auto pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// �E�B���h�E�T�C�Y�̎擾
	int w = static_cast<int>(pDR->GetOutputSize().right);
	int h = static_cast<int>(pDR->GetOutputSize().bottom);

	// ���\�[�X�쐬�t���O
	HRESULT hr = E_FAIL;

	// �萔�o�b�t�@�̍쐬==================================
	D3D11_BUFFER_DESC cBufferDesc{};
	cBufferDesc.ByteWidth = sizeof(cbChangesEveryFrame);
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;
	cBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer(&cBufferDesc, nullptr, mCbBuffer.ReleaseAndGetAddressOf());
	assert(hr == S_OK && "mCbBuffer�̍쐬�Ɏ��s");

	// 2D�e�N�X�`���o�b�t�@�̍쐬==========================
	D3D11_TEXTURE2D_DESC texDesc{};
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.Width = w;
	texDesc.Height = h;
	texDesc.ArraySize = 1;
	texDesc.MipLevels = 1;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.CPUAccessFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&texDesc, nullptr, mTextureBuffer.ReleaseAndGetAddressOf());
	assert(hr == S_OK && "mTextureBuffer�̍쐬�Ɏ��s");

	// �V�F�[�_�[���\�[�X�r���[�̐���======================
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(mTextureBuffer.Get(), &srvDesc, mShaderResourceView.ReleaseAndGetAddressOf());
	assert(hr == S_OK && "mShaderResourceView�̍쐬�Ɏ��s");

	// �V�F�[�_�̍쐬======================================
	std::vector<uint8_t> blob = DX::ReadData(L"Resources/Shaders/FadePS.cso");
	hr = device->CreatePixelShader(blob.data(), blob.size(), nullptr, mPixelShader.ReleaseAndGetAddressOf());
	assert(hr == S_OK && "mPixelShader�̍쐬�Ɏ��s");
}

void Fade::Update(float elaspedTime)
{
	if (mFlagOpen)
	{
		// �I�[�v��
		mRate += elaspedTime / mInterval;

		if (mRate > 1.0f) mRate = 1.0f;
		mRate = std::min(mRate, 1.0f);
	}
	else
	{
		// �N���[�Y
		mRate -= elaspedTime / mInterval;

		if (mRate < 0.0f) mRate = 0.0f;
		mRate = std::max(mRate, 0.0f);
	}
}

void Fade::Draw(DirectX::SpriteBatch* batch)
{
	// �S�J�̎��͕`�悵�Ȃ�
	if (mRate >= 1.0f) { return; }

	// �f�o�C�X���\�[�X�̎擾
	auto pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// �E�B���h�E�T�C�Y�̎擾
	int w = static_cast<int>(pDR->GetOutputSize().right);
	int h = static_cast<int>(pDR->GetOutputSize().bottom);

	// ��ʃT�C�Y�̋�`��ݒ肷��
	RECT rect = { 0, 0, w, h };

	// �萔�o�b�t�@�\���̂̒l��ݒ肷��
	mCbChangesEveryFrame.radius = mRate;
	mCbChangesEveryFrame.aspectRatio = w / static_cast<float>(h);

	// ���C�v��Ԃ�`�悷��
	batch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [&]() {
		// �萔�o�b�t�@�ւ̏�������
		D3D11_MAPPED_SUBRESOURCE mappedResource{};
		context->Map(mCbBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		//CopyMemory(mappedResource.pData, &mCbChangesEveryFrame, sizeof(CbChangesEveryFrame));
		std::memcpy(mappedResource.pData, &mCbChangesEveryFrame, sizeof(cbChangesEveryFrame));
		context->Unmap(mCbBuffer.Get(), 0);
		// �Q�l�F�uCopyMemory�vWindowsAPI�A�umemcpy�vC,C++�̕W�����C�u����

		// �s�N�Z���V�F�[�_�ɒ萔�o�b�t�@��ݒ�
		ID3D11Buffer* buffers[] = { mCbBuffer.Get() };
		context->PSSetConstantBuffers(0, 1, buffers);

		// �s�N�Z���V�F�[�_�[��ݒ�
		context->PSSetShader(mPixelShader.Get(), nullptr, 0);
		});
	batch->Draw(mShaderResourceView.Get(), rect);
	batch->End();

}

void Fade::SetOpen()
{
	mFlagOpen = true;
}

void Fade::SetClose()
{
	mFlagOpen = false;
}

bool Fade::IsOpen() const
{
	if (mFlagOpen && mRate == 1.0f) return true;
	return false;
}

bool Fade::IsClose() const
{
	if (!mFlagOpen && mRate == 0.0f) return true;
	return false;
}
