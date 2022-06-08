/**
* @file TitlePlane.h
* @brief タイトルシーンの飛行機
* @author 米澤駿介
* @date 2022/04/26
* @details タイトルシーンの回転している飛行機
*/
#pragma once
#include "Game/PlayScene/Object/MoveObject.h"

/**
* @brief タイトルシーンの飛行機
* @details タイトルシーンの回転している飛行機
*/
class TitlePlane : public MoveObject
{
public:
	// 定数--------------------------------------------------
	//! 最初の位置
	static const DirectX::SimpleMath::Vector3 START_POS;
	//! 最初のアングル
	static const DirectX::SimpleMath::Vector3 START_ANGLE;

	//! 回転する速さ
	static const float MOVE_SPEED;
	//-------------------------------------------------------
public:
	/**
	* @brief コンストラクタ
	*/
	TitlePlane();

	/**
	* @brief デストラクタ
	*/
	virtual ~TitlePlane() override;

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
	* @brief 動作よう関数
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
};