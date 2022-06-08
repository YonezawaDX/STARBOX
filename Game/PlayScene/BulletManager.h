/**
* @file BulletManager.h
* @brief 弾の管理者クラス
* @author 米澤駿介
* @date 2022/04/26
* @details 弾の管理をする、発射など
*/
#pragma once
#include "Game/PlayScene/Object/Bullet.h"

// 前方宣言
class Model3D;
class Enemy;
class Player;

/**
* @brief 弾の管理者クラス
* @details 弾の管理をする、発射など
*/
class BulletManager
{
public:
	/**
	* @brief コンストラクタ
	*/
	BulletManager();

	/**
	* @brief デストラクタ
	*/
	~BulletManager();

	/**
	* @brief 初期化
	* @return void なし
	*/
	void Initialize();

	/**
	* @brief 更新
	* @return void なし
	*/
	void Update();

	/**
	* @brief 描画
	* @param (commonStates) コモンステイト
	* @param (camera) カメラ
	* @return void なし
	*/
	void Draw(DirectX::CommonStates* commonStates, Camera* camera);

	/**
	* @brief 弾の発射
	* @param (shooterType) 発射するエンティティ
	* @param (pos) 座標
	* @param (angle) 角度
	* @return bool 撃っているか確認
	*/
	bool Shot(int shooterType, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 angle);

	/**
	* @brief 敵との当たり判定
	* @param (pEnemy) 敵のポインタ
	* @return void なし
	*/
	void CheckHitEnemy(Enemy* pEnemy);

	/**
	* @brief プレイヤーとの当たり判定
	* @param (pEnemy) プレイヤーのポインタ
	* @return void なし
	*/
	void CheckHitPlayer(IObject* pPlayer);

	/**
	* @brief 一つの弾を取得する
	* @param (i) 一つの弾のが格納されている番号
	* @return Bullet* 弾のポインタ
	*/
	Bullet* GetBullet(int i) { return mBullets[i].get(); }

private:// 変数-------------------------------------------------------------------------------------------
	//! 弾
	std::vector<std::unique_ptr<Bullet>> mBullets;

	//! 弾のモデル
	std::unique_ptr<Model3D> mBulletModel3D;
};