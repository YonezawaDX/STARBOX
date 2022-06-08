/**
* @file Boss02.h
* @brief ボス02のクラス
* @author 米澤駿介
* @date 2022/05/01
* @details ボス02のクラス
*/
#pragma once
#include "HeartObject.h"
#include "Game/PlayScene/BulletManager.h"

class EnemyManager;

/**
* @brief ボス02
* @details  2体目のボス
*/
class Boss02 : public HeartObject
{
public:
	//! 速度
	static const DirectX::SimpleMath::Vector3 SPEED;
	//! 初期座標								  
	static const DirectX::SimpleMath::Vector3 START_POS;
	static const DirectX::SimpleMath::Vector3 MOVE_POS;
	
	//! パーツの初期座標（コアパーツ）					  
	static const DirectX::SimpleMath::Vector3 CORE_OFFSET;

	//! パーツの初期座標（カバー）
	static const DirectX::SimpleMath::Vector3 COVER_OFFSET;

	//! パーツの初期座標（タイヤ）
	static const DirectX::SimpleMath::Vector3 TIRE_OFFSET;

	//! コアパーツやカバーの間
	static const float PARTS_BETWEEN;

	//! 動きの定数01
	static const DirectX::SimpleMath::Vector3 BOSS_MOVE_01;
	//! 動きの定数02
	static const DirectX::SimpleMath::Vector3 BOSS_MOVE_02;

	//! ボスのアングル
	static const float RESULT_ANGLE;

	//! ボスの移動時間
	static const float RESULT_COUNT;

	//! パーツの回転
	static const float PARTS_ROTATE;

public:
	/**
	* @enum BOSS_STATE
	* ボスの移動状態
	*/
	enum class BOSS_STATE
	{
		//! 初期値	
		NONE,
		//! 入場
		ADMISSION,
		//! 入場後
		ADMISSION_AFTER,
		//! 左に動く
		LEFT_MOVE,
		//! 右に動く
		RIGHT_MOVE,
		//! 回る
		ROLL_MOVE
	};

public:
	
	/**
	* @brief コンストラクタ
	* @param (pBulletManager) 弾の管理者
	* @param (pEnemyManager) 敵のポインタ
	*/
	Boss02(BulletManager* pBulletManager, EnemyManager* pEnemyManager);

	/**
	* @brief デストラクタ
	*/
	~Boss02();

	// 基本処理-----------------------------------------------------------------------

/**
* @brief 初期化
* @param なし
* @return void なし
*/
	virtual void Initialize() override;

	/**
	* @brief 更新
	* @param なし
	* @return void なし
	*/
	virtual void Update() override;

	// @brief 更新
	// @param (playerPos) プレイヤーの座標
	// @return void なし
	virtual void Update(DirectX::SimpleMath::Vector3 playerPos);

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
	void Move() override;

	/**
	* @brief 当たり判定
	* @return void なし
	*/
	void Collision() override;
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
	//! 車体オブジェクト
	std::unique_ptr<HeartObject> mpPrime;

	//! ボスのステート
	BOSS_STATE mBossState;

	//! カウンタ
	float mCount;

	//! 最初の角度変更用
	float mTempAngle;

	//! 最後の角度変更用
	float mResultAngle;

	//! ボスが行動する時点での座標
	DirectX::SimpleMath::Vector3 mTempPos;

	//! ボスが行動し終わる時点での座標
	DirectX::SimpleMath::Vector3 mResultPos;

	//! 弾発射用
	BulletManager* mpBullets;

	//! 敵出現用
	EnemyManager* mpEnemies;
};
