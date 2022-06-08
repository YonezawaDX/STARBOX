/**
* @file Fade.cpp
* @brief フェードイン・アウト
* @author 米澤駿介
* @date 2022/05/19
* @details フェードイン・アウトを行う
*/
#include "pch.h"
#include "Fade.h"

#include "DeviceResources.h"
#include <cassert>

// シェーダのコンパイル
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
	// デバイスリソースの取得
	auto pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// ウィンドウサイズの取得
	int w = static_cast<int>(pDR->GetOutputSize().right);
	int h = static_cast<int>(pDR->GetOutputSize().bottom);

	// リソース作成フラグ
	HRESULT hr = E_FAIL;

	// 定数バッファの作成==================================
	D3D11_BUFFER_DESC cBufferDesc{};
	cBufferDesc.ByteWidth = sizeof(cbChangesEveryFrame);
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;
	cBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer(&cBufferDesc, nullptr, mCbBuffer.ReleaseAndGetAddressOf());
	assert(hr == S_OK && "mCbBufferの作成に失敗");

	// 2Dテクスチャバッファの作成==========================
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
	assert(hr == S_OK && "mTextureBufferの作成に失敗");

	// シェーダーリソースビューの生成======================
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(mTextureBuffer.Get(), &srvDesc, mShaderResourceView.ReleaseAndGetAddressOf());
	assert(hr == S_OK && "mShaderResourceViewの作成に失敗");

	// シェーダの作成======================================
	std::vector<uint8_t> blob = DX::ReadData(L"Resources/Shaders/FadePS.cso");
	hr = device->CreatePixelShader(blob.data(), blob.size(), nullptr, mPixelShader.ReleaseAndGetAddressOf());
	assert(hr == S_OK && "mPixelShaderの作成に失敗");
}

void Fade::Update(float elaspedTime)
{
	if (mFlagOpen)
	{
		// オープン
		mRate += elaspedTime / mInterval;

		if (mRate > 1.0f) mRate = 1.0f;
		mRate = std::min(mRate, 1.0f);
	}
	else
	{
		// クローズ
		mRate -= elaspedTime / mInterval;

		if (mRate < 0.0f) mRate = 0.0f;
		mRate = std::max(mRate, 0.0f);
	}
}

void Fade::Draw(DirectX::SpriteBatch* batch)
{
	// 全開の時は描画しない
	if (mRate >= 1.0f) { return; }

	// デバイスリソースの取得
	auto pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// ウィンドウサイズの取得
	int w = static_cast<int>(pDR->GetOutputSize().right);
	int h = static_cast<int>(pDR->GetOutputSize().bottom);

	// 画面サイズの矩形を設定する
	RECT rect = { 0, 0, w, h };

	// 定数バッファ構造体の値を設定する
	mCbChangesEveryFrame.radius = mRate;
	mCbChangesEveryFrame.aspectRatio = w / static_cast<float>(h);

	// ワイプ状態を描画する
	batch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [&]() {
		// 定数バッファへの書き込み
		D3D11_MAPPED_SUBRESOURCE mappedResource{};
		context->Map(mCbBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		//CopyMemory(mappedResource.pData, &mCbChangesEveryFrame, sizeof(CbChangesEveryFrame));
		std::memcpy(mappedResource.pData, &mCbChangesEveryFrame, sizeof(cbChangesEveryFrame));
		context->Unmap(mCbBuffer.Get(), 0);
		// 参考：「CopyMemory」WindowsAPI、「memcpy」C,C++の標準ライブラリ

		// ピクセルシェーダに定数バッファを設定
		ID3D11Buffer* buffers[] = { mCbBuffer.Get() };
		context->PSSetConstantBuffers(0, 1, buffers);

		// ピクセルシェーダーを設定
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
