/**
* @file HeartObject.h
* @brief HPがあるオブジェクトのクラス
* @author 米澤駿介
* @date 2022/04/26
* @details HPがあるオブジェクトMoveObjectを継承している
*/
#pragma once
#include "MoveObject.h"
class BossFactory;

/**
* @brief HPがあるオブジェクトのクラス
* @details HPがあるオブジェクトの基盤
*/
class HeartObject : public MoveObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	HeartObject();
	
	/**
	* @brief デストラクタ
	*/
	virtual ~HeartObject() override;

	/**
	* @brief ボスパーツを追加する関数
	* @param (bossParts) 追加したいボスのパーツ
	* @return void なし
	*/
	virtual void AddBossParts(std::unique_ptr<HeartObject> bossParts);

	// 基本処理

	/**
	* @brief 初期化
	* @return void なし
	*/
	virtual void Initialize() override;

	/**
	* @brief 初期化
	* @param (bossFactory) ボスの作成をする
	* @return void なし
	*/
	virtual void Initialize(BossFactory* bossFactory);

	/**
	* @brief 更新
	* @return void なし
	*/
	virtual void Update() override;

	/**
	* @brief 更新
	* @param (position) 座標
	* @param (angle) 角度
	* @param (offset) 親パーツとの距離
	* @param (playerPos) プレイヤーの座標　
	* @param (stateNum) ボスの状態
	* @return void なし
	*/
	virtual void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& angle,
		const DirectX::SimpleMath::Vector3& offset,
		const DirectX::SimpleMath::Vector3& playerPos,
		const int& stateNum
	);

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

	/**
	* @brief HPのゲッター
	* @return int HPの値
	*/
	virtual int GetHP() const;
	/**
	* @brief HPのセッター
	* @param (hp) HPの値
	* @return void なし
	*/
	virtual void SetHP(const int& hp);

private:

	//! オブジェクトの体力
	int mHP;
};
