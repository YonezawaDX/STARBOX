/**
* @file PostEffect.h
* @brief ポストエフェクトを管理
* @author 米澤駿介
* @date
* @details ポストエフェクト
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
* @brief ポストエフェクトのクラス
* @details 画面に対するシェーダ
*/
class PostEffect
{
public:
	/**
	* @struct コンストバッファー
	*/
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;	//! ワールド座標
		DirectX::SimpleMath::Matrix		matView;	//! ビュー座標
		DirectX::SimpleMath::Matrix		matProj;	//! プロジェクション座標
		DirectX::SimpleMath::Vector4	Time;		//! タイム
		DirectX::SimpleMath::Vector4	MouseP;		//! マウスの座標
	};
	//! インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	

	/**
	* @brief 生成
	* @param (deviceResources) デバイスリソース
	* @param (name) ファイル名
	* @param (count) 数
	* @return void なし
	*/
	void Create(DX::DeviceResources* deviceResources, const wchar_t* name, int count);
	
	/**
	* @brief 初期化
	* @param (life) 生存時間
	* @param (pos) 座標
	* @return void なし
	*/
	void Initialize(float life, DirectX::SimpleMath::Vector3 pos);
	
	/**
	* @brief 更新
	* @param (timer) 時間
	* @return void なし
	*/
	void Update(DX::StepTimer timer);
	
	/**
	* @brief ポストエフェクトの開始
	* @return void なし
	*/
	void StartEffect();
	
	/**
	* @brief 描画
	* @return void なし
	*/
	void Render();
	
	/**
	* @brief ポストエフェクトの終了
	* @return void なし
	*/
	void EndEffect();
	
	/**
	* @brief 消す
	* @return void なし
	*/
	void Lost();

	/**
	* @brief 描画設定
	* @param (camera) カメラ座標
	* @param (view) ビュー座標
	* @param (proj) プロジェクション座標
	* @return void なし
	*/
	void SetRenderState(
		DirectX::SimpleMath::Vector3 camera, 
		DirectX::SimpleMath::Matrix view, 
		DirectX::SimpleMath::Matrix proj
	);

	/**
	* @brief 描画
	* @param (camera) ワールド行列
	* @param (view) ビュー行列
	* @param (proj) プロジェクション行列
	* @return void なし
	*/
	void Draw(
		DirectX::SimpleMath::Matrix world,
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix proj
	);
	/**
	* @brief 描画
	* @return CommonStates* コモンステイト
	*/
	DirectX::CommonStates* GetCommonstate() { return mStates.get(); }
private:
	//! エフェクトのリスト
	std::list<MyEffect*>		mEffectList;
	//! 画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;
	//! 時間
	DX::StepTimer                           mTimer;

	//! デバイスリソース
	DX::DeviceResources* mDeviceResources;
	//! シーバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	mCBuffer;
	//! コモンステイト
	std::unique_ptr<DirectX::CommonStates> mStates;

	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGeometryShader;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> mBatch;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
	//! 頂点
	std::vector<DirectX::VertexPositionColorTexture>  mVertex;

	//! 中心座標
	DirectX::SimpleMath::Vector3 mCenterPosition;

	//! ビルボード
	DirectX::SimpleMath::Matrix mBillboardTranslation;
	//! ビュー
	DirectX::SimpleMath::Matrix mView;
	//! プロジェクション
	DirectX::SimpleMath::Matrix mProj;
	//! ｆｘファクトリ
	std::unique_ptr<DirectX::EffectFactory> mFxFactory;

	//! 画像保存
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mCapture;

	//! レンダーターゲットビュー
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	mRtv;
	//Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_rtv2;

	//! ブレンドステート
	Microsoft::WRL::ComPtr<ID3D11BlendState> mpBlendState;

	//! シェーダーリソース
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSrv;

	//! デスク
	D3D11_SHADER_RESOURCE_VIEW_DESC mdesc;
	//! モデル
	std::unique_ptr<DirectX::Model> mModel;

};