/**
* @file MyEffect.h
* @brief エフェクト
* @author 米澤駿介
* @date
* @details エフェクト	
*/
#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

/**
* @brief エフェクトのクラス
* @details エフェクト
*/
class MyEffect
{
public:
	/**
	* @brief 初期化
	* @param (life) 生存時間
	* @param (pos) 座標
	* @return void なし
	*/
	void Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity);
	/**
	* @brief 更新
	* @param (timer) 時間
	* @return void なし
	*/
	void Update(DX::StepTimer timer);

	/**
	* @brief 座標のゲッター
	* @return Vector3 座標
	*/
	DirectX::SimpleMath::Vector3 GetPosition() { return mPosition; }
	
	/**
	* @brief ベロシティのゲッター
	* @return Vector3 ベロシティ
	*/
	DirectX::SimpleMath::Vector3 GetVelocity() { return mVelocity; }
private:

	//! 時間
	DX::StepTimer                           mTimer;

	//! 重力
	DirectX::SimpleMath::Vector3		mGravity;
	//! 座標
	DirectX::SimpleMath::Vector3		mPosition;
	
	//! ベロシティ
	DirectX::SimpleMath::Vector3		mVelocity;
	
	//! 生成時間
	float								mLife;

	//! 開始位置
	DirectX::SimpleMath::Vector3		mStartPosition;
	
	//! 開始ベロシティ
	DirectX::SimpleMath::Vector3		mStartVelocity;
	
	//! 開始生成時間
	float								mStartLife;

};