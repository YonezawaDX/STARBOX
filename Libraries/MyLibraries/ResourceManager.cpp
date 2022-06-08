/**
* @file ResourceManager.cpp
* @brief リソースマネージャー
* @author 米澤駿介
* @date
* @details モデルや画像を管理する
*/
#include "pch.h"
#include "ResourceManager.h"
#include <WICTextureLoader.h>
#include <Effects.h>
#include "DeviceResources.h"

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
ResourceManager::ResourceManager()
{
}
//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
	// すべてのリソースの削除
	this->DeleteAllData();
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void ResourceManager::Initialize()
{
	this->DeleteAllData();
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void ResourceManager::Finalize()
{
	this->DeleteAllData();
}

//------------------------------------------------------------------
// 概要：画像の取得
// 引数(key)：鍵
// 戻り値 ID3D11ShaderResourceView*：画像
//------------------------------------------------------------------
ID3D11ShaderResourceView* ResourceManager::GetTexture(const std::string& key)
{
	return mTextureDB[key].Get();
}

//------------------------------------------------------------------
// 概要：モデルの取得
// 引数(key)：鍵
// 戻り値 Model*：モデル
//------------------------------------------------------------------
DirectX::Model* ResourceManager::GetCmoModel(const std::string& key)
{
	return mCmoModelDB[key].get();
}

//-----------------------------------------------------------------------------
// 概要：テクスチャの登録
// 引数(path): テクスチャの相対パス(ワイド文字列)
// 引数(key) : テクスチャの識別名(文字列)
// 戻り値 void：なし
//-----------------------------------------------------------------------------
void ResourceManager::RegisterTexture(const wchar_t* path, const std::string& key)
{
	// デバイスリソースの取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// テクスチャの読み込み	: SRVの作成
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	DirectX::CreateWICTextureFromFile(
		device,
		path,
		nullptr,
		texture.ReleaseAndGetAddressOf()
	);

	// DB(Map)にテクスチャを追加
	mTextureDB[key] = std::move(texture);
}

//-----------------------------------------------------------------------------
// 概要：CMOモデルの登録
// 引数(path): CMOモデルの相対パス(ワイド文字列)
// 引数(key) : CMOモデルの識別名(文字列)
// 戻り値 void : なし
//-----------------------------------------------------------------------------
void ResourceManager::RegisterCmoModel(const wchar_t* path, const std::string& key)
{
	// デバイスリソースの取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// モデルの保存場所等を保持するインスタンスの生成
	std::unique_ptr<DirectX::EffectFactory> factory = std::make_unique<DirectX::EffectFactory>(device);
	factory->SetDirectory(L"Resources/Models");

	// モデルのロード
	std::unique_ptr<DirectX::Model> model = DirectX::Model::CreateFromCMO(device, path, *factory);

	// DB(Map)にモデルを登録
	mCmoModelDB[key] = std::move(model);
}

//----------------------------------------------------
// 概要：すべてのリソースを削除
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void ResourceManager::DeleteAllData()
{
	mTextureDB.clear();
	mCmoModelDB.clear();
}