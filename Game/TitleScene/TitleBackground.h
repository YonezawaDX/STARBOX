/**
* @file	TitleBackground.h
* @brief タイトルの背景
* @author 米澤駿介
* @date 2022/04/26
* @details 回転しているタイトルの背景
*/
#pragma once
#include "Game/PlayScene/Object/MoveObject.h"

/**
* @brief タイトルの背景クラス
* @details 回転しているタイトルの背景
*/
class TitleBackground : public MoveObject
{
public:
	// 定数------------------------------------------
	
	//! 動く速さ
	static const float MOVE_SPEED;
public:
	/**
	* @brief コンストラクタ
	*/
	TitleBackground();

	/**
	* @brief デストラクタ
	*/
	virtual ~TitleBackground() override;

	// 基本処理

	/**
	* @brief 初期化
	* @return void なし
	*/
	void Initialize() override;
	/**
    * @brief 更新
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
	* @brief 動き
	* @return void なし
	*/
	void Move() override;

	// ゲッター、セッター---------------------------------------------------------------------------
	
	/**
	* @brief 座標のゲッター
	* @return Vector3 オブジェクトの座標
	*/
	DirectX::SimpleMath::Vector3 GetObjectPos() const override;
	/**
	* @brief 座標のセッター
	* @param (pos) 座標
	* @return void なし
	*/
	void SetObjectPos(const DirectX::SimpleMath::Vector3& pos) override;

	/**
	* @brief 向きのゲッター
	* @return Vector3 オブジェクトの向き
	*/
	DirectX::SimpleMath::Vector3 GetObjectDirection() const;
	/**
	* @brief 向きのセッター
	* @param (direction) 向き
	* @return void なし
	*/
	void SetObjectDirection(const DirectX::SimpleMath::Vector3& direction);

	/**
	* @brief 速さのゲッター
	* @return Vector3 オブジェクトの速さ
	*/
	DirectX::SimpleMath::Vector3 GetObjectSpeed() const;
	/**
	* @brief 速さのセッター
	* @param (speed) 速さ
	* @return void なし
	*/
	void SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed);

private:
	//! モデル保存用
	DirectX::Model* mpModel;
};