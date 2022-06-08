/**
* @file Letter.h
* @brief 文字
* @author 米澤駿介
* @date
* @details 文字※アルファベット大文字と数字のみ対応
*/
#pragma once
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <CommonStates.h>
#include <string>

/**
* @brief 文字のクラス
* @details 文字※アルファベット大文字と数字のみ対応
*/
class Letter
{
public:
	/**
	* @brief コンストラクタ
	*/
	Letter();

	/**
	* @brief 初期化
	* @param (texture) 使う画像
	* @param (x) x座標
	* @param (y) y座標
	* @param (str) 書きたい文字
	* @param (color) 色
	* @return void なし
	*/
	void Initialize(
		ID3D11ShaderResourceView* texture,
		int x, 
		int y, 
		const char* str,
		DirectX::FXMVECTOR color = DirectX::Colors::White
	);

	/**
	* @brief 描画
	* @param (commonStates) コモンステイト
	* @param (camera) カメラ
	* @return void なし
	*/
	void Draw(DirectX::CommonStates* commonStates, DirectX::SpriteBatch* spriteBatch);

    /**
    * @brief 文字列設定関数
    * @param (str) 文字
    * @return void なし
    */
	void SetStr(const char* str);

	/**
	* @brief 表示位置の設定関数
	* @param (x) X座標
	* @param (y) Y座標
	* @return void なし
	*/
	void SetPos(int x, int y);

private:
	//! スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;

	//! 文字のサイズ
	static const int SIZE = 48;

	//! テクスチャハンドル
	ID3D11ShaderResourceView* mTexture;

	//! 文字列
	std::string mStr;

	//! 表示位置
	int mX, mY;

	//! 文字の色
	DirectX::SimpleMath::Color mColor;

};
