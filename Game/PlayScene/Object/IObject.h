/**
* @file オブジェクトのインターフェース
* @brief インターフェース
* @author 米澤駿介
* @date 2022/04/26
* @details すべてのオブジェクトの祖
*/
#pragma once
#include <SimpleMath.h>
#include <CommonStates.h>
#include "Libraries/MyLibraries/Camera.h"

/**
* @brief オブジェクトのインスターフェースクラス
* @details すべてのオブジェクトの祖
*/
class IObject
{
public:
	// 基本処理--------------------------------------------

	/**
	* @brief 初期化
	* @return void なし
	*/
	virtual void Initialize() = 0;
	
	/**
	* @brief 更新
	* @return void なし
	*/
	virtual void Update() = 0;

	/**
	* @brief 描画
	* @param (commonStates) コモンステイト
	* @param (camera) カメラ
	* @return void なし
	*/
	virtual void Draw(DirectX::CommonStates* commonStates, Camera* camera) = 0;

	/**
	* @brief 終了処理
	* @return void なし
	*/
	virtual void Finalize() = 0;

	// セッターゲッター------------------------------------------

	/**
	* @brief 座標のゲッター
	* @return Vector3 オブジェクトの座標
	*/
	virtual DirectX::SimpleMath::Vector3 GetObjectPos() const = 0;
	/**
	* @brief 座標のセッター
	* @param (pos) 座標
	* @return void なし
	*/
	virtual void SetObjectPos(const DirectX::SimpleMath::Vector3& pos) = 0;

	//-----------------------------------------------------------
	
	/**
	* @brief 純粋仮想デストラクタ
	*/
	virtual ~IObject() = 0;
};
inline IObject::~IObject() {};