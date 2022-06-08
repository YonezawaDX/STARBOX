/**
* @file Camera.h
* @brief カメラ
* @author 
* @date 
* @details カメラ
*/
#pragma once

#include <SimpleMath.h>

/**
* @brief カメラのクラス
* @details カメラ
*/
class Camera
{
public:
	
	//! カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;	

public:
	/**
	* @brief コンストラクタ
	*/
	Camera();

	/**
	* @brief デストラクタ
	*/
	~Camera();

	/**
	* @brief 更新
	* @return void なし
	*/
	virtual void Update();
	
	//----------------------------------------------------------------------------------------------------

	/**
	* @brief ビュー行列のセッター
	* @param (view) ビュー行列
	* @return void なし
	*/
	virtual void SetViewMatrix(const DirectX::SimpleMath::Matrix &view) { mView = view; }
	/**
    * @brief ビュー行列のゲッター
    * @return Matrix ビュー行列
    */
	virtual DirectX::SimpleMath::Matrix GetViewMatrix() const { return mView; }

	/**
	* @brief プロジェクション行列のセッター
	* @param (view) プロジェクション行列
	* @return void なし
	*/
	virtual void SetProjectionMatrix(const DirectX::SimpleMath::Matrix &projection) { mProjection = projection; }
	/**
	* @brief プロジェクション行列のゲッター
	* @return Matrix プロジェクション行列
	*/
	virtual DirectX::SimpleMath::Matrix GetProjectionMatrix() const { return mProjection; }

	/**
	* @brief Eye座標のセッター
	* @param (eye) Eye座標
	* @return void なし
	*/
	virtual void SetEyePosition(const DirectX::SimpleMath::Vector3 &eye) { mEye = eye; }
	/**
	* @brief Eye座標のゲッター
	* @return Vector3 アイ座標
	*/
	virtual DirectX::SimpleMath::Vector3 GetEyePosition() const { return mEye; }

	/**
	* @brief ターゲット座標のセッター
	* @param (target) ターゲット座標
	* @return void なし
	*/
	virtual void SetTargetPosition(const DirectX::SimpleMath::Vector3 &target) { mTarget = target; }
	/**
	* @brief ターゲット座標のゲッター
	* @return Vector3 ターゲット座標
	*/
	virtual DirectX::SimpleMath::Vector3 GetTargetPosition() const { return mTarget; }

	/**
	* @brief 上向きベクトルのセッター
	* @param (up) 上向きベクトル
	* @return void なし
	*/
	virtual void SetUpVector(const DirectX::SimpleMath::Vector3 &up) { mUp = up; }
	/**
	* @brief 上向きベクトルのゲッター
	* @return Vector3 上向きベクトル
	*/
	virtual DirectX::SimpleMath::Vector3 GetUpVector() const { return mUp; }

protected:

	/**
	* @brief ビュー行列の算出
	* @return void なし
	*/
	virtual void CalculateViewMatrix();

	/**
	* @brief プロジェクション行列の算出
	* @return void なし
	*/
	virtual void CalculateProjectionMatrix();

private:

	//! ビュー行列
	DirectX::SimpleMath::Matrix mView;

	//! プロジェクション行列
	DirectX::SimpleMath::Matrix mProjection;

	//! カメラ座標
	DirectX::SimpleMath::Vector3 mEye;

	//! 注視点
	DirectX::SimpleMath::Vector3 mTarget;

	//! 上向きベクトル
	DirectX::SimpleMath::Vector3 mUp;

};
