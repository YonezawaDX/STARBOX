/**
* @file MoveObject.h
* @brief 動くオブジェクトのクラス
* @author 米澤駿介
* @date 2022/04/26
* @details 動くオブジェクトObjectを継承している
*/
#pragma once
#include "Object.h"

/**
* @brief 動くオブジェクトのクラス
* @details 動くオブジェクトの基盤
*/
class MoveObject : public Object
{
public:

	/**
	* @brief コンストラクタ
	*/
	MoveObject();

	/**
	* @brief デストラクタ
	*/
	virtual ~MoveObject() override;

	// 基本処理

	/**
	* @brief 初期化
	* @return void なし
	*/
	virtual void Initialize() override;

	/**
	* @brief 更新
	* @return void なし
	*/
	virtual void Update() override;

	/**
	* @brief 描画
	* @param (commonStates) コモンステイト
	* @param (camera) カメラ
	* @return void なし
	*/
	virtual void Draw(DirectX::CommonStates* commonStates, Camera* camera) override;

	/**
	* @brief 終了処理
	* @return void なし
	*/
	virtual void Finalize() override;

	/**
	* @brief 動作よう関数
	* @return void なし
	*/
	virtual void Move();

	/**
	* @brief パーツを消す関数
	* @return void なし
	*/
	virtual void DeleteParts();

	/**
	* @brief 当たり判定
	* @return void なし
	*/
	virtual void Collision();


	// ゲッター、セッター---------------------------------------------------------------------------
	/**
	* @brief 座標のゲッター
	* @return Vector3 オブジェクトの座標
	*/
	virtual DirectX::SimpleMath::Vector3 GetObjectPos() const override;
	/**
	* @brief 座標のセッター
	* @param (pos) 座標
	* @return void なし
	*/
	virtual void SetObjectPos(const DirectX::SimpleMath::Vector3& pos) override;

	/**
	* @brief 向きのゲッター
	* @return Vector3 オブジェクトの向き
	*/
	virtual DirectX::SimpleMath::Vector3 GetObjectDirection() const;
	/**
	* @brief 向きのセッター
	* @param (direction) 向き
	* @return void なし
	*/
	virtual void SetObjectDirection(const DirectX::SimpleMath::Vector3& direction);

	/**
	* @brief 速さのゲッター
	* @return Vector3 オブジェクトの速さ
	*/
	virtual DirectX::SimpleMath::Vector3 GetObjectSpeed() const;
	/**
	* @brief 速さのセッター
	* @param (speed) 速さ
	* @return void なし
	*/
	virtual void SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed);

	/**
	* @brief 使用状態のゲッター
	* @return bool 使用状態
	*/
	virtual bool GetActive() const;
	/**
	* @brief 使用状態のセッター
	* @param (active) 使用状態
	* @return void なし
	*/
	virtual void SetActive(const bool& active);

private:
	//! オブジェクトの向き
	DirectX::SimpleMath::Vector3 mDirection;

	//! オブジェクトの速さ
	DirectX::SimpleMath::Vector3 mSpeed;

	//! 使用状態
	bool mIsActive;
};