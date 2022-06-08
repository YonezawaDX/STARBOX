/**
* @file BigArm.h
* @brief 大きな腕のクラス
* @author 米澤駿介
* @date 2022/04/26
* @details 敵を射出する大きい腕
*/

#pragma once
#include "HeartObject.h"
#include "Boss.h"
#include "Game/PlayScene/EnemyManager.h"

/**
* @brief ボスパーツの大きな腕のクラス
* @details 大きな腕、敵を射出する
*/
class BigArm : public HeartObject
{
public:

	/**
	* @brief ボスパーツを追加する関数
	* @param (bossParts) 追加したいボスのパーツ
	* @return void なし
	* @details ファクトリの関係で各パーツに追加なければいけない
	*/
	void AddBossParts(std::unique_ptr<HeartObject> bossParts) override;

	/**
	* @brief コンストラクタ
	* @param (offset) 親パーツとの距離
	* @param (pEnemies) 細かい敵のポインタ
	* @param (pBulletManager) 弾の発射用
	*/
	BigArm(
		const DirectX::SimpleMath::Vector3& offset,
		EnemyManager* pEnemies,
		BulletManager* pBulletManager
	);

	/**
	* @brief デストラクタ
	*/
	~BigArm();

	// 基本処理-----------------------------------------------------------------------

	/**
	* @brief 初期化
	* @param (bossFactory) ボスの作成をする
	* @return void なし
	*/
	void Initialize(BossFactory* bossFactory) override;
	
	/**
	* @brief 更新
	* @param (position) 座標
	* @param (angle) 角度
	* @param (offset) 親パーツとの距離
	* @param (playerPos) プレイヤーの座標　
	* @param (stateNum) ボスの状態
	* @return void なし
	*/
	void Update(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& angle,
		const DirectX::SimpleMath::Vector3& offset,
		const DirectX::SimpleMath::Vector3& playerPos,
		const int& stateNum
		) override;

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

	/**
	* @brief 当たり判定
	* @return void なし
	*/
	void Collision() override;

	/**
	* @brief 弾発射関数
	* @return void なし
	*/
	void BulletFire(DirectX::SimpleMath::Vector3 pos);
	
	
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
	DirectX::SimpleMath::Vector3 GetObjectDirection() const override;
	/**
	* @brief 向きのセッター
	* @param (direction) 向き
	* @return void なし
	*/
	void SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)override;

	/**
	* @brief 速さのゲッター
	* @return Vector3 オブジェクトの速さ
	*/
	DirectX::SimpleMath::Vector3 GetObjectSpeed() const override;
	/**
	* @brief 速さのセッター
	* @param (speed) 速さ
	* @return void なし
	*/
	void SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)override;

	/**
	* @brief 使用状態のゲッター
	* @return bool 使用状態
	*/
	bool GetActive() const override;
	/**
	* @brief 使用状態のセッター
	* @param (active) 使用状態
	* @return void なし
	*/
	void SetActive(const bool& active) override;
	
	/**
	* @brief HPのゲッター
	* @return int HPの値
	*/
	int GetHP() const override;
	/**
	* @brief HPのセッター
	* @param (hp) HPの値 
	* @return void なし
	*/
	void SetHP(const int& hp) override;

private:
	//! ボスへのポインタ
	Boss* mpBoss;

	//! 敵生成用
	EnemyManager* mpEnemies;

	//! 弾の管理者
	BulletManager* mpBullets;

	//! 位置オフセット
	DirectX::SimpleMath::Vector3 mPosOffset;

	//! 回転角オフセット
	DirectX::SimpleMath::Vector3 mAngleOffset;

	//! ボスの状態を保存する
	int mBossState;

	//! パーツが外れて下降していくか
	bool mIsDown;

};