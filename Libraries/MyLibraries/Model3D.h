/**
* @file Model3D.h
* @brief モデル3Dのクラス
* @author 米澤駿介
* @date 
* @details モデルを簡易的に出せるようにする
*/
#pragma once
#include <SimpleMath.h>
#include "StepTimer.h"
#include <CommonStates.h>
#include <Model.h>

// 前方宣言
class Camera;
class FollowCamera;

/**
* @brief Model3Dのクラス
* @details モデルを簡易的に出せるようにする
*/
class Model3D
{
public:
	// 関数------------------------------------
	/**
	* @brief コンストラクタ
	*/
	Model3D();
	/**
	* @brief デストラクタ
	*/
	~Model3D() = default;

	/**
	* @brief 初期化
	* @param (fileName) モデルのファイル名
	* @return void なし
	*/
	void Initialize(const wchar_t* fileName);

	/**
	* @brief 描画
	* @param (commonStates) コモンステイト
	* @param (world) ワールド座標
	* @param (camera) カメラ
	* @return void なし
	*/
	void Draw(
		DirectX::CommonStates* commonStates,
		DirectX::SimpleMath::Matrix* world,
		Camera* camera
	);

	/**
	* @brief 終了処理
	* @return void なし
	*/
	void Finalize();

	/**
	* @brief モデルのX回転セット
	* @param (rotate) 回転量
	* @return void なし
	*/
	void SetModelRotationX(float rotate) { mRotateX = rotate; }
	
	/**
	* @brief モデルのY回転セット
	* @param (rotate) 回転量
	* @return void なし
	*/
	void SetModelRotationY(float rotate) { mRotateY = rotate; }
	
	/**
	* @brief モデルのZ回転セット
	* @param (rotate) 回転量
	* @return void なし
	*/
	void SetModelRotationZ(float rotate) { mRotateZ = rotate; }

	/**
	* @brief モデルのXYZ回転セット
	* @param (rotate) 回転量
	* @return void なし
	*/
	void SetModelRotation(DirectX::SimpleMath::Vector3 rotate) 
	{
		mRotateX = rotate.x;
		mRotateY = rotate.y;
		mRotateZ = rotate.z;
	}
	/**
	* @brief モデルの回転軸をセット
	* @param (axis) 軸
	* @return void なし
	*/
	void SetModelAxis(DirectX::SimpleMath::Vector3 axis) { mAxis = axis; }
private:
	//! モデル
	std::unique_ptr<DirectX::Model> mModel;

	//! 回転軸の変数X
	float mRotateX;
	//! 回転軸の変数Y
	float mRotateY;
	//! 回転軸の変数Z
	float mRotateZ;

	//! モデルの回転軸
	DirectX::SimpleMath::Vector3 mAxis;
};