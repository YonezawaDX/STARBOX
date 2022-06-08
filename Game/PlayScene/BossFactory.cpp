/**
* @file BossFactory.cpp
* @brief ボスの工場
* @author 米澤駿介
* @date 2022/04/26
* @details ボスの各パーツを生成する
*/
#include "pch.h"
#include "BossFactory.h"

#include "Object/Body.h"
#include "Object/SmallArm.h"
#include "Object/BigArm.h"
#include "Object/Prime.h"
#include "Object/CaterpillerRight.h"
#include "Object/CaterpillerLeft.h"
#include "Object/Core.h"
#include "Object/Cover.h"
#include "Object/Tire.h"

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数(pBoss)：ボスのポインタ
// 引数(pBulletManager)：弾発射用
// 引数(pEnemyManager)：敵発射用
//------------------------------------------------------------------
BossFactory::BossFactory(BulletManager* pBullets, EnemyManager* pEnemies)
	: mpBullets(pBullets)
	, mpEnemies(pEnemies)
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void BossFactory::Initialize()
{
	// 現在はリソースマネージャでの管理をしている
}

//---------------------------------------------------------------------
// 概要：ボスパーツの生成
// 引数(bossPartsID)：ボスパーツのID
// 引数(offset)：パーツの座標、親パーツからの距離
// 戻り値(unique_ptr<HeartObject>)：オブジェクトを生成して返す
//---------------------------------------------------------------------
std::unique_ptr<HeartObject> BossFactory::Create(
	BOSS_PARTS_ID bossPartsID,
	const DirectX::SimpleMath::Vector3& offset
)
{
	std::unique_ptr<HeartObject> bossParts;

	switch (bossPartsID)
	{
		case BOSS_PARTS_ID::BODY:
			// Bodyのオブジェクトを生成する
			bossParts.reset((HeartObject*)new Body(offset,mpBullets));
			break;
		case BOSS_PARTS_ID::SMALL_ARM:
			// SmallArmのオブジェクトを生成する
			bossParts.reset((HeartObject*)new SmallArm(offset , mpBullets));
			break;
		case BOSS_PARTS_ID::BIG_ARM:
			// BigArmのオブジェクトを生成する
			bossParts.reset((HeartObject*)new BigArm(offset,mpEnemies,mpBullets));
			break;
		case BOSS_PARTS_ID::PRIME:
			// Primeのオブジェクトを生成する
			bossParts.reset((HeartObject*)new Prime(offset,mpBullets));
			break;
		case BOSS_PARTS_ID::CORE:
			// Coreのオブジェクトを生成する
			bossParts.reset((HeartObject*)new Core(offset, mpBullets));
			break;
		case BOSS_PARTS_ID::COVER:
			// Coverのオブジェクトを生成する
			bossParts.reset((HeartObject*)new Cover(offset, mpBullets));
			break;
		case BOSS_PARTS_ID::TIRE:
			// Coverのオブジェクトを生成する
			bossParts.reset((HeartObject*)new Tire(offset));
			break;

		default:
			return nullptr;
	}

	// それぞれのボスパーツを初期化する
	bossParts->Initialize(this);
	return std::move(bossParts);
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void BossFactory::Finalize()
{
}
