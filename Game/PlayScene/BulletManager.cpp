/**
* @file BulletManager.cpp
* @brief 弾の管理者クラス
* @author 米澤駿介
* @date 2022/04/26
* @details 弾の管理をする、発射など
*/
#include "pch.h"
#include "BulletManager.h"
#include "Game/PlayScene/Object/Enemy.h"
#include "Game/PlayScene/Object/Player.h"

#include "Libraries/MyLibraries/Model3D.h"
#include "Game/PlayScene/Object/Boss.h"

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
BulletManager::BulletManager()
	: mBullets{}
	, mBulletModel3D{}
{
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
BulletManager::~BulletManager()
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void BulletManager::Initialize()
{
	// 弾丸の量の確定
	mBullets.resize(512);

	// 弾丸のモデルをロード
	mBulletModel3D = std::make_unique<Model3D>();
	mBulletModel3D->Initialize(L"Resources/Models/Bullet.cmo");

	// すべての弾を未使用状態にする
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i] = std::make_unique<Bullet>();
		mBullets[i]->SetActive(false);
	}
}

//----------------------------------------------------
// 概要：更新
// 引数:なし
// 戻り値：なし
//----------------------------------------------------
void BulletManager::Update()
{
	// プレイヤーの弾の更新
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->Update();
	}
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void BulletManager::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	// プレイヤーの弾の更新
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->Draw(commonStates,camera);
	}
}

//----------------------------------------------------------------------
// 概要：弾の発射
// 引数(shooterType)：発射するエンティティ
// 引数(pos)：座標
// 引数(angle)：角度
// 戻り値(bool)：撃っているか確認
//---------------------------------------------------------------------
bool BulletManager::Shot(int shooterType, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 angle)
{
	bool res = false;

	// 発射可能な弾を探す
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		// アクティブ(使用中)なら次へ
		if (mBullets[i]->GetActive() == true)
		{
			continue;
		}

		// 使用されていないなら初期化
		mBullets[i]->Initialize(mBulletModel3D.get(), shooterType, pos, angle);

		// 弾の発射に成功
		res = true;

		// 処理を中断する
		break;
	}

	return res;
}

//------------------------------------------------------------------
// 概要：敵との当たり判定
// 引数 (pEnemy)：敵のポインタ
// 戻り値：なし
//------------------------------------------------------------------
void BulletManager::CheckHitEnemy(Enemy* pEnemy)
{
	// すべての弾と渡された対象との判定を取る
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		// 特定の条件ならば判定しない
		if (
			!mBullets[i]->GetActive() ||			// 弾が発射状態でない
			pEnemy->GetHP() <= 0 ||				// 敵の体力がない
			mBullets[i]->GetShooterType() == Bullet::eShooterType::ENEMY_SHOT
			)
		{
			continue;
		}


		// 当たり判定用の一時変数
		Collision::Sphere bullet;
		Collision::Sphere enemy;

		bullet.center = mBullets[i]->GetObjectPos();
		bullet.radius = 1.0f;

		enemy.center = pEnemy->GetObjectPos();
		enemy.radius = 1.0f;

		// あたっていなければ次へ
		if (!Collision::HitCheckSphereToSphere(bullet,enemy))
		{
			continue;
		}

		// ダメージ処理エネミー
		pEnemy->Damage(1);

		// 弾を未使用状態にする
		mBullets[i]->SetActive(false);
	}
}

//------------------------------------------------------------------
// 概要：プレイヤーとの当たり判定
// 引数 (pEnemy)：プレイヤーのポインタ
// 戻り値：なし
//------------------------------------------------------------------
void BulletManager::CheckHitPlayer(IObject* pPlayer)
{
	// すべての弾と渡された対象との判定を取る
	for (unsigned int i = 0; i < mBullets.size(); i++)
	{
		// 特定の条件ならば判定しない
		if (
			!mBullets[i]->GetActive() ||			// 弾が発射状態でない
			mBullets[i]->GetShooterType() == Bullet::eShooterType::PLAYER_SHOT
			// プレイヤーが被弾中
			)
		{
			continue;
		}
		// 当たり判定用の一時変数
		Collision::Sphere bullet;
		Collision::Sphere player;

		bullet.center = mBullets[i]->GetObjectPos();
		bullet.radius = 3.0f;

		player.center = pPlayer->GetObjectPos();
		player.radius = 5.0f;

		// あたっていなければ次へ
		if (Collision::HitCheckSphereToSphere(bullet, player))
		{
			continue;
		}
		// ダメージ処理エネミー
		//pPlayer->Damage(1);

		// 弾を未使用状態にする
		mBullets[i]->SetActive(false);
	}
}