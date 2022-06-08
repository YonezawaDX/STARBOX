/**
* @file Bullet.h
* @brief 弾のクラス
* @author 米澤駿介
* @date 2021/12/01
* @details 弾
*/
#pragma once
#include "MoveObject.h"
#include "../Collision.h"

/**
* @brief 弾のクラス
* @details １つの弾を生成する
*/
class Bullet : public MoveObject
{
public:

    /**
    * @enum eShooterType
    * 発射するエンティティ
    */
    enum class eShooterType : int
    {
        PLAYER_SHOT,        //! 0
        ENEMY_SHOT,         //! 1
        BOSS_SHOT           //! 2
    };
public:

	/**
	* @brief コンストラクタ
	*/
	Bullet();

    /**
	* @brief デストラクタ
	*/
	~Bullet();

    // 基本処理---------------------------------------------------
   
    /**
    * @brief 初期化
    * @return void なし
    */
    void Initialize() override;
    
    /**
	* @brief 初期化
	* @param (bulletType) 弾のタイプ
    * @param (shooterType) 弾を使う者の種類
    * @param (pos) 座標
    * @param (angle) 角度
	* @return void なし
	*/
    void Initialize(
        Model3D* bulletType,
        int shooterType,
        DirectX::SimpleMath::Vector3 pos,
        DirectX::SimpleMath::Vector3 angle
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
    * @brief 弾の種類のゲッター
    * @return int 弾の種類
    */
    eShooterType GetShooterType() const;
    /**
    * @brief 弾の種類のセッター
    * @param (type) 弾の種類
    * @return void なし
    */
    void SetShooterType(const eShooterType type);

private:
    //! モデルのポインタ格納用
    Model3D* mpBulletModel3D;

    //! ShooterType格納用
    eShooterType mShooterType;

    //! 発射時の角度を保存する
    DirectX::SimpleMath::Vector3 mBulletAnglePos;

    //! 使用中フラグ
    bool mIsActive;
};