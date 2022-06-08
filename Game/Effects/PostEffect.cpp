/**
* @file PostEffect.cpp
* @brief ポストエフェクトを管理
* @author 米澤駿介
* @date
* @details ポストエフェクト
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

// 名前空間を利用
using namespace DirectX::SimpleMath;
using namespace DirectX;

// インプットレイアウトの設定
const std::vector<D3D11_INPUT_ELEMENT_DESC> PostEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//------------------------------------------------------------
// 概要：生成
// 引数(deviceResources)：デバイスリソース
// 引数(name)：ファイル名
// 引数(count)：数
// @return void なし
//--------------------------------------------------------------
void PostEffect::Create(DX::DeviceResources* deviceResources, const wchar_t* name, int count)
{
	UNREFERENCED_PARAMETER(name);
	mDeviceResources = deviceResources;
	auto device = mDeviceResources->GetD3DDevice();
	// コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		mInputLayout.GetAddressOf());


	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, mVertexShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}
	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, mGeometryShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, mPixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	// プリミティブバッチの作成
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
// 概要：消す
// 引数：なし
// 戻り値：なし
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
// 概要：初期化
// 引数 (life) :生存時間
// 引数 (pos): 座標
// 戻り値 void：なし
//---------------------------------------------------------
void PostEffect::Initialize(float life, DirectX::SimpleMath::Vector3 pos)
{
	UNREFERENCED_PARAMETER(life);
	UNREFERENCED_PARAMETER(pos);
}
//----------------------------------------------------------
// 概要：更新
// 引数 (timer) :生存時間
// 戻り値 void : なし
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
// 概要：ポストエフェクトの開始
// 引数 :なし
// 戻り値 void : なし
//---------------------------------------------------------
void PostEffect::StartEffect()
{
	auto context = mDeviceResources->GetD3DDeviceContext();

	D3D11_TEXTURE2D_DESC texDesc;
	mDeviceResources->GetRenderTarget()->GetDesc(&texDesc);
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	mDeviceResources->GetD3DDevice()->CreateTexture2D(&texDesc, NULL, mCapture.ReleaseAndGetAddressOf());

	// レンダーターゲットビューの設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	// レンダーターゲットビューの生成
	mDeviceResources->GetD3DDevice()->CreateRenderTargetView(mCapture.Get(), &rtvDesc, &mRtv);

	//シェーダリソースビューの設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

	mdesc = srvDesc;

	ID3D11DepthStencilView* pDSV = mDeviceResources->GetDepthStencilView();

	//背景色の設定（アルファを０にするとオブジェクトのみ表示）
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 0.0f };

	//レンダーターゲットビューをセットし、初期化する
	context->OMSetRenderTargets(1, mRtv.GetAddressOf(), pDSV);
	context->ClearRenderTargetView(mRtv.Get(), clearColor);
	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//----------------------------------------------------------
// 概要：描画
// 引数 :なし
// 戻り値 void : なし
//---------------------------------------------------------
void PostEffect::Render()
{
	mVertex.clear();
	//マネージャで管理しているエフェクト分イテレータを回す
	for (auto itr = mEffectList.begin(); itr != mEffectList.end(); itr++)
	{
		//エフェクトの頂点の座標と速度を取得する
		Vector3 pos = (*itr)->GetPosition();
		Vector3 vel = (*itr)->GetVelocity();

		{
			//取得した座標を登録する
			VertexPositionColorTexture vertex;
			//vertex = VertexPositionColorTexture(pos, Vector4(vel.x,vel.y,vel.z,1), Vector2(0.0f,3.0f));
			vertex = VertexPositionColorTexture(pos, Vector4::Zero, Vector2::Zero);
			mVertex.push_back(vertex);
		}
	}
	static float rot = 0;
	rot++;

	//----------------------------------------------------------------------------
	//描画した画面をm_srvに保存
	auto hr = mDeviceResources->GetD3DDevice()->CreateShaderResourceView(
		mCapture.Get(), &mdesc, mSrv.ReleaseAndGetAddressOf());
	UNREFERENCED_PARAMETER(hr);
	//------------------------------------------------------------------

	//全画面エフェクト

	//Matrix  mat = Matrix::Identity;
	//Draw(mat, mat, mat);


	//板ポリゴンエフェクト
	Draw(mBillboardTranslation, mView, mProj);

}

//----------------------------------------------------------
// 概要：ポストエフェクトの終了
// 引数 :なし
// 戻り値 void : なし
//---------------------------------------------------------
void PostEffect::EndEffect()
{
	auto context = mDeviceResources->GetD3DDeviceContext();

	//背景色の設定（アルファを０にするとオブジェクトのみ表示）
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 0.0f };

	ID3D11RenderTargetView* defaultRTV = mDeviceResources->GetRenderTargetView();
	ID3D11DepthStencilView* pDSV = mDeviceResources->GetDepthStencilView();

	//設定をもとに戻す
	clearColor[0] = 0.3f;
	clearColor[1] = 0.3f;
	context->OMSetRenderTargets(1, &defaultRTV, pDSV);
	context->ClearRenderTargetView(defaultRTV, clearColor);
	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
//---------------------------------------------------
// 概要：描画設定
// 引数(camera)：カメラ座標
// 引数(view)：ビュー座標
// 引数(proj)：プロジェクション座標
// 戻り値：なし
//-------------------------------------------------
void PostEffect::SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	mView = view;
	mProj = proj;

	mBillboardTranslation = Matrix::CreateBillboard(mCenterPosition, camera, Vector3::UnitY);

	//ビルボードの計算で裏返るので補正
	//Y軸で180度回転する行列
	Matrix rev = Matrix::Identity;
	rev._11 = -1;
	rev._33 = -1;

	//補正行列を先にかけて他に影響がないようにする
	mBillboardTranslation = rev * mBillboardTranslation;

}
//---------------------------------------------------
// 概要：描画
// 引数(camera)：カメラ座標
// 引数(view)：ビュー座標
// 引数(proj)：プロジェクション座標
// 戻り値：なし
//-------------------------------------------------
void PostEffect::Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto context = mDeviceResources->GetD3DDeviceContext();

	// マウス入力情報を取得する
	auto mouseState = DirectX::Mouse::Get().GetState();
	DirectX::SimpleMath::Vector2 mousePos = DirectX::SimpleMath::Vector2((float)mouseState.x, (float)mouseState.y);

	//定数バッファで渡す値の設定
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = world.Transpose();
	//Time		x:経過時間(トータル秒)	y:1Fの経過時間(秒）	z:反復（サインカーブ） w:未使用（暫定で１）
	cbuff.Time = Vector4((float)mTimer.GetTotalSeconds(), (float)mTimer.GetElapsedSeconds(), sinf((float)mTimer.GetTotalSeconds()), 1);

	cbuff.MouseP = DirectX::SimpleMath::Vector4(mouseState.x / 800.0f, mouseState.y / 600.0f, mouseState.leftButton, mouseState.rightButton);

	//定数バッファの内容更新
	context->UpdateSubresource(mCBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	ID3D11BlendState* blendstate = mStates->NonPremultiplied();
	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// 深度バッファは参照のみ
	context->OMSetDepthStencilState(mStates->DepthRead(), 0);
	// カリングは反時計回り
	context->RSSetState(mStates->CullCounterClockwise());

	//定数バッファをシェーダに渡す（とりあえずPSは要らないのでコメントアウト）
	ID3D11Buffer* cb[1] = { mCBuffer.Get() };
	//context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);



	//サンプラー、シェーダ、画像をそれぞれ登録
	ID3D11SamplerState* sampler[1] = { mStates->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	context->VSSetShader(mVertexShader.Get(), nullptr, 0);
	context->GSSetShader(mGeometryShader.Get(), nullptr, 0);
	context->PSSetShader(mPixelShader.Get(), nullptr, 0);
	context->PSSetShaderResources(0, 1, mSrv.GetAddressOf());
	context->PSSetShaderResources(1, 1, mTexture.GetAddressOf());

	//入力レイアウトを反映
	context->IASetInputLayout(mInputLayout.Get());


	//バッチに頂点情報を渡す
	mBatch->Begin();
	//m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	mBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &mVertex[0], mVertex.size());
	mBatch->End();


	//他のモデルに影響が出る可能性があるので使い終わったらシェーダを外す
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}