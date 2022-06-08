/**
* @file ResourceManager.h
* @brief リソースマネージャー
* @author 米澤駿介
* @date
* @details モデルや画像を管理する
*/
#pragma once
#include <string>
#include <unordered_map>
#include <Model.h>

/**
* @brief リソースマネージャーのクラス
* @details モデルや画像を管理する
*/
class ResourceManager
{
public:
	/**
	* @brief インスタンスの取得
	* @return ResourceManager リソースマネージャのポインタ
	*/
	static ResourceManager* GetInstance()
	{
		static ResourceManager instance;
		return &instance;
	}

private:
	//! テクスチャ保持用マップ
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mTextureDB;
	//! CMO保持用マップ
	std::unordered_map<std::string, std::unique_ptr<DirectX::Model>> mCmoModelDB;

private:
	/**
	* @brief コンストラクタ
	*/
	ResourceManager();
	/**
	* @brief デストラクタ
	*/
	~ResourceManager();

	/**
	* @brief コピーコンストラクタ
	* @param (InputManager&) 参照
	*/
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;

	/**
	* @brief ムーブコンストラクタ
	* @param (InputManager&&) 参照
	*/
	ResourceManager(const ResourceManager&&) = delete;
	ResourceManager& operator= (const ResourceManager&&) = delete;

public:
	/**
	* @brief 初期化
	* @return void なし
	*/
	void Initialize();

    /**
    * @brief 終了処理
    * @return void なし
    */
	void Finalize();

	/**
    * @brief 画像のゲッター
	* @param (key) リソースの鍵
	* @return ID3D11ShaderResourceView* シェーダリソース
    */
	ID3D11ShaderResourceView* GetTexture(const std::string& key);

	/**
    * @brief モデルのゲッター
	* @param (key) リソースの鍵
	* @return Model* モデル
    */
	DirectX::Model* GetCmoModel(const std::string& key);

	/**
	* @brief 画像の登録
	* @param (path) リソースの場所のパス
	* @param (key) リソースの鍵
	* @return void なし
	*/
	void RegisterTexture(const wchar_t* path, const std::string& key);

	/**
    * @brief モデルの登録
	* @param (path) リソースの場所のパス
	* @param (key) リソースの鍵
	* @return void なし
    */
	void RegisterCmoModel(const wchar_t* path, const std::string& key);

private:
	/**
	* @brief すべてのリソースの削除
	* @return void なし
	*/
	void DeleteAllData();
};