/**
* @file Enemy.h
* @brief 敵のクラス
* @author 米澤駿介
* @date 2021/12/04
* @details 敵
*/
#pragma once
#include "HeartObject.h"
#include "../BulletManager.h"
#include "../Collision.h"

/**
* @brief 敵のクラス
* @details １つの敵を生成する
*/
class Enemy : public HeartObject
{
public:
    /**
    * @enum eEnemyrType
    * 敵のタイプ
    */
    enum class eEnemyType : int
    {
        NORMAL,		//! 普通
        TRACK,		//! 追尾
        ROTATE		//! 回転
    };

public:
    /**
    * @brief コンストラクタ
    */
	Enemy();

       /**
	* @brief デストラクタ
	*/
	~Enemy();

    // 基本処理---------------------------------------------------
    
    /**
    * @brief 初期化
    * @return void なし
    */
    void Initialize() override;

    /**
	* @brief 初期化
	* @param (modelType) 敵のモデルのタイプ
    * @param (enemyType) 敵の種類
    * @param (pos) 座標
    * @param (angle) 角度
    * @param (hp) 体力
    * @param (pBulletManager) 弾発射用
	* @return void なし
	*/
    void Initialize(
        Model3D* modelType,
        int enemyType,
        DirectX::SimpleMath::Vector3 pos,
        DirectX::SimpleMath::Vector3 angle,
        int hp,
        BulletManager* pBulletManager
    );

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

    /**
    * @brief ダメージ関数
    * @param (damage) ダメージの値
    * @return void なし
    */
    void Damage(int damage);

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

    //! 弾の管理者格納用
    BulletManager* mpBulletManager;

    //! 敵の種類を格納
    int mEnemyType;

    //! 弾の発射間隔
    int mShotTimer;

};