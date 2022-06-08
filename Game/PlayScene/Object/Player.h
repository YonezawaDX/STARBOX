/**
* @file Player.h
* @brief プレイヤーのクラス
* @author 米澤駿介
* @date 2022/04/26
* @details プレイヤー、移動したり弾撃ったり
*/
#pragma once
#include "HeartObject.h"

#include "Game/PlayScene/BulletManager.h"
#include "../Collision.h"

/**
* @brief Playerのクラス
* @details Player
*/
class Player : public HeartObject
{
public:
    // 定数-------------------------------------------------
    
    //! 初期座標
    static const DirectX::SimpleMath::Vector3 START_POS;
    //! 体力
    static const int HP;
    //! 加速度
    static const float ACCELERATION;
    //! 向き
    static const float ANGLE;
    //! プレイヤーを止める速度
    static const float STOP_PLAYER;

    //! 向きの最小値
    static const DirectX::SimpleMath::Vector3 LIMIT_SPEED_MIN;
    //! 向きの最大値
    static const DirectX::SimpleMath::Vector3 LIMIT_SPEED_MAX;

    //! 位置の最小値
    static const DirectX::SimpleMath::Vector3 LIMIT_POS_MIN;
    //! 位置の最大値
    static const DirectX::SimpleMath::Vector3 LIMIT_POS_MAX;

    //! ショットのインターバル
    static const int SHOT_INTERVAL;

public:

    /**
    * @enum PLAYER_MOVE
    * プレイヤーが今どうしているかをとる
    */
    enum class PLAYER_MOVE
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

public:
    
    /**
	* @brief コンストラクタ
    * @param (pBulletManager) 弾の管理者
	*/
	Player(BulletManager* pBulletManager);
	
    /**
	* @brief デストラクタ
	*/
    ~Player();

    // 基本処理---------------------------------------------------
    
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
    void Draw(DirectX::CommonStates* commonStates,Camera* camera) override;

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
    * @brief 動作よう関数
    * @param (damage) ダメージの値
    * @return void なし
    */
    void Damage(int damage);

    /**
    * @brief 弾発射用
    * @return void なし
    */
    void Shot();

    // セッターゲッター--------------------------------------------
    
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
    void SetObjectDirection(const DirectX::SimpleMath::Vector3& direction) override;

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
    void SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed) override;

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

private:// 変数---------------------------------------------------------------
    //! プレイヤーの移動スピード
    DirectX::SimpleMath::Vector3 mPlayerSpeed;

    //! プレイヤーの角度
    DirectX::SimpleMath::Vector3 mPlayerAngle;

    //! 移動しているフラグ
    bool mPlayerMoveFlag;

    //! 弾丸の管理者へのポインタ
    BulletManager* mpBulletManager;

    //! 弾丸の発射間隔
    int mShootIntervalTimer;

    //! プレイヤーの座標保存用
    DirectX::SimpleMath::Vector3 mPlayerPos;
};