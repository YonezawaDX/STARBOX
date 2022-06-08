/**
* @file Fade.h
* @brief フェードイン・アウト
* @author 米澤駿介
* @date 2022/05/19
* @details フェードイン・アウトを行う
*/
#pragma once
#include <SpriteBatch.h>
#include <Effects.h>

/**
* @brief Fadeのクラス
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

	// 開ける
	void SetOpen();
	// 閉じる
	void SetClose();
	// 開いているか
	bool IsOpen() const;
	// 閉じているか
	bool IsClose() const;
private:
	
	// ピクセルシェーダーに渡す定数バッファの構造体
	struct cbChangesEveryFrame
	{
		float radius;				// 半径の比率：0～1
		float aspectRatio;			// アスペクト比
		DirectX::XMFLOAT2 dummy;	// パディングデータ
	};

	//! 定数バッファ関連
	cbChangesEveryFrame mCbChangesEveryFrame;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mCbBuffer;

	//! 2Dテクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mTextureBuffer;

	//! シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mShaderResourceView;

	//! オープン又はクローズするまでのワイプ時間
	float mInterval;

	//! 割合(0～1)：0の場合閉じている
	float mRate;

	//! オープンフラグ：trueの場合オープン
	bool mFlagOpen;

	//! ピクセルシェーダ関連
	Microsoft::WRL::ComPtr<ID3DBlob> mBlobPixel;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
};
