/**
* @file BackGround.h
* @brief プレイシーン背景のクラス
* @author 米澤駿介
* @date 2022/04/26
* @details プレイシーンの背景
*/
#include "pch.h"
#include "BackGround.h"
#include <Effects.h>

//-------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
// 戻り値：なし
//-------------------------------------------------------------------
BackGround::BackGround():
	mpModel(nullptr)
{
}

//---------------------------------------------------------
// 概要：デストラクタ
//---------------------------------------------------------
BackGround::~BackGround()
{
}

//----------------------------------------------------------
// 概要：初期化
// 引数()：なし
// 戻り値：なし
//----------------------------------------------------------
void BackGround::Initialize()
{
	// モデルの保存
	auto pRM = ResourceManager::GetInstance();

	mpModel = pRM->GetCmoModel("PlayBackGround");

	mpModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights)
			{
				//ライトの影響をなくす

				lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}
			DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				// エミッション色を白に設定する
				basicEffect->SetEmissiveColor(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
			}
		});
}

//-----------------------------------------------------------
// 概要：更新
// 引数()：なし
// 戻り値：なし
//-----------------------------------------------------------
void BackGround::Update()
{
}

//-------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイト
// 引数(camera)：カメラ
// 戻り値：なし
//-------------------------------------------------------------
void BackGround::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{

	//デバイスコンテキストの取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// 射影行列の取得
	DirectX::SimpleMath::Matrix projection = camera->GetProjectionMatrix();
	// ビュー行列の取得
	DirectX::SimpleMath::Matrix view = camera->GetViewMatrix();

	// ワールド座標の取得
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(GetObjectPos());


	mpModel->Draw(
		context,
		*commonStates,
		world,
		view,
		projection
	);

}

//--------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//--------------------------------------------------------------
void BackGround::Finalize()
{
}

// セッター、ゲッター---------------------------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 BackGround::GetObjectPos() const
{
	return Object::GetObjectPos();
}

//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void BackGround::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	Object::SetObjectPos(pos);
}