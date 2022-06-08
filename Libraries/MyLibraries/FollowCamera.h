/**
* @file FollowCamera.h
* @brief 追従カメラ
* @author
* @date
* @details 追従カメラ
*/
#pragma once
#include "Camera.h"
#include <SimpleMath.h>

/**
* @brief 追従カメラのクラス
* @details 追従カメラ
*/
class FollowCamera :public Camera
{
public:
	//! カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;	
	
	//! 視点と注視点
	static const DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC; 

	//! プレイヤーが地面にいるときの視点
	static const float POINT_OF_VIEW_WORK;		
	
	//! プレイヤーが飛んでいるときの視点
	static const float POINT_OF_VIEW_BOOST;		

public:
	/**
	* @brief コンストラクタ
	*/
	FollowCamera();

	/**
	* @brief デストラクタ
	*/
	~FollowCamera();

	/**
	* @brief 更新
	* @return void なし
	*/
	void Update() override;

	//-------------------------------------------------------

	/**
	* @brief ビュー行列のセッター
	* @param (view) ビュー行列
	* @return void なし
	*/
	void SetViewMatrix(const DirectX::SimpleMath::Matrix &view) override { Camera::SetViewMatrix(view); }
	/**
    * @brief ビュー行列のゲッター
    * @return Matrix ビュー行列
    */
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return Camera::GetViewMatrix(); }

	/**
	* @brief プロジェクション行列のセッター
	* @param (view) プロジェクション行列
	* @return void なし
	*/
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix &projection) override { Camera::SetProjectionMatrix(projection); }
	/**
	* @brief プロジェクション行列のゲッター
	* @return Matrix プロジェクション行列
	*/
	DirectX::SimpleMath::Matrix GetProjectionMatrix() const override { return Camera::GetProjectionMatrix(); }

	/**
	* @brief Eye座標のセッター
	* @param (eye) Eye座標
	* @return void なし
	*/
	void SetEyePosition(const DirectX::SimpleMath::Vector3 &eye) override { Camera::SetEyePosition(eye); }
	/**
	* @brief Eye座標のゲッター
	* @return Vector3 アイ座標
	*/
	DirectX::SimpleMath::Vector3 GetEyePosition() const override { return Camera::GetEyePosition(); }

	/**
	* @brief ターゲット座標のセッター
	* @param (target) ターゲット座標
	* @return void なし
	*/
	void SetTargetPosition(const DirectX::SimpleMath::Vector3 &target) override { Camera::SetTargetPosition(target); }
	/**
	* @brief ターゲット座標のゲッター
	* @return Vector3 ターゲット座標
	*/
	DirectX::SimpleMath::Vector3 GetTargetPosition() const override { return Camera::GetTargetPosition(); }

	/**
	* @brief 上向きベクトルのセッター
	* @param (up) 上向きベクトル
	* @return void なし
	*/
	void SetUpVector(const DirectX::SimpleMath::Vector3 &up) override { Camera::SetUpVector(up); }
	/**
	* @brief 上向きベクトルのゲッター
	* @return Vector3 上向きベクトル
	*/
	DirectX::SimpleMath::Vector3 GetUpVector() const override { return Camera::GetUpVector(); }

	/**
	* @brief 参照視点のセッター
	* @param (refeye) 参照視点
	* @return void なし
	*/
	void SetRefEyePosition(const DirectX::SimpleMath::Vector3 &refeye){ mRefEye = refeye; }
	/**
	* @brief 参照視点のゲッター
	* @return Vector3 参照視点
	*/
	void SetRefTargetPosition(const DirectX::SimpleMath::Vector3 &reftarget) { mRefTarget = reftarget; }

	/**
	* @brief カメラの角度のゲッター
	* @return float カメラの角度
	*/
	float GetCameraRot() const { return mCameraRot; }

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

	//! 参照視点
	DirectX::SimpleMath::Vector3 mRefEye;

	//! 参照注視点
	DirectX::SimpleMath::Vector3 mRefTarget;

	//! 回転値
	float mCameraRot;
};
