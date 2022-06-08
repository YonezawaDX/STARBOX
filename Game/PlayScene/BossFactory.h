/**
* @file BossFactory.h
* @brief ボスの工場
* @author 米澤駿介
* @date 2022/04/26
* @details ボスの各パーツを生成する
*/
#pragma once
#include <memory>
#include "Libraries/MyLibraries/Model3D.h"
#include "BulletManager.h"
#include "EnemyManager.h"

class Boss;
class HeartObject;

/**
* @enum BOSS_PARTS_ID
* ボスのパーツの列挙
*/
enum class BOSS_PARTS_ID
{
	//! 体
	BODY,
	//! 小さい腕
	SMALL_ARM,			
	//! 大きい腕
	BIG_ARM,			
	//! ボス02の体
	PRIME,				
	//! キャタピラ右
	CATERPILLER_RIGHT,	
	//! キャタピタ左
	CATERPILLER_LEFT,	
	//! コア
	CORE,				
	//! カバー
	COVER,
	//! タイヤ
	TIRE
};

/**
* @brief ボスの工場のクラス
* @details ボスの工場
*/
class BossFactory
{
public:
	/**
	* @brief コンストラクタ
	* @param (pBulletManager) 弾発射用
	* @param (pEnemyManager) 敵発射用
	*/
	BossFactory(BulletManager* pBullets, EnemyManager* pEnemies);

	/**
	* @brief 初期化
	* @return void なし
	*/
	void Initialize();

	/**
	* @brief ボスパーツの生成
	* @param (bossPartsID) ボスパーツのID
	* @param (offset) パーツの座標、親パーツからの距離 
	* @return unique_ptr<HeartObject> オブジェクトを生成して返す
	*/
	std::unique_ptr<HeartObject> BossFactory::Create(
		BOSS_PARTS_ID bossPartsID,
		const DirectX::SimpleMath::Vector3& offset
	);

	/**
	* @brief 終了処理
	* @return void なし
	*/
	void Finalize();

private:

	//! 弾丸の管理者ポインタ
	BulletManager* mpBullets;
	
	//! 敵の管理者ポインタ
	EnemyManager* mpEnemies;
};