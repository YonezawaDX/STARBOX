/**
* @file Hatch.h
* @brief 昇降口のクラス
* @author 米澤駿介
* @date 2022/04/26
* @details ボスの弱点のカバーのクラス
*/
#pragma once
#include "HeartObject.h"

/**
* @brief カバー
* @details  カバー
*/
class Hatch : public HeartObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Hatch();
	/**
	* @brief デストラクタ
	*/
	~Hatch();

	// 基本処理------------------------------------------------------------------------
	
	/**
	* @brief 初期化
	* @return void なし
	*/
	void Initialize() override;
	
	/**
	* @brief 更新
	* @param (position) 座標
	* @return void なし
	*/
	void Update() override;
	
	/**
	* @brief 描画
	* @param (commonStates) コモンステイト
	* @param (camera) カメラ
	* @return void なし
	*/
	void Draw(DirectX::CommonStates* commonStates, Camera* camera) override;
	
	/**
	* @brief 終了処理
	* @return void なし
	*/
	void Finalize() override;

	/**
	* @brief 動作よう関数
	* @return void なし
	*/
	void Move() override;
	
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

	/**
	* @brief ハッチの開閉のゲッター
	* @return bool 開いているか
	*/
	void GetIsOpen() const;

private:

	//! 昇降口の状態
	bool mIsHatchOpen;
};