/**
* @file Boss.cpp
* @brief ボスのクラス
* @author 米澤駿介
* @date 2022/04/26
* @details ボス01のクラス
*/
#include "pch.h"
#include "Boss.h"
#include "../BossFactory.h"
#include "Game/PlayScene/Collision.h"
#include <random>


// 定数のパラメータを決める
const DirectX::SimpleMath::Vector3 Boss::SPEED = DirectX::SimpleMath::Vector3(2.0f, 2.0f, 2.0f);
const DirectX::SimpleMath::Vector3 Boss::START_POS = DirectX::SimpleMath::Vector3(0.0f, 20.0f, 50.0f);
const DirectX::SimpleMath::Vector3 Boss::MOVE_POS = DirectX::SimpleMath::Vector3(0.0f, 2.0f, -50.0f);

// それぞれのパーツの座標
const DirectX::SimpleMath::Vector3 Boss::ARM_OFFSET_01 = DirectX::SimpleMath::Vector3(-10.0f, 8.0f, 0.0f);
const DirectX::SimpleMath::Vector3 Boss::ARM_OFFSET_02 = DirectX::SimpleMath::Vector3(-10.0f, 0.0f, 0.0f);
const DirectX::SimpleMath::Vector3 Boss::ARM_OFFSET_03 = DirectX::SimpleMath::Vector3( 10.0f, 0.0f, 0.0f);

// 動きの定数
const DirectX::SimpleMath::Vector3 Boss::BOSS_MOVE_01 = DirectX::SimpleMath::Vector3(-15.0f, 2.0f, -50.0f);
const DirectX::SimpleMath::Vector3 Boss::BOSS_MOVE_02 = DirectX::SimpleMath::Vector3(15.0f, 2.0f, -50.0f);

// ボスのアングルの定数
const float Boss::RESULT_ANGLE = 20.0f;
const float Boss::RESULT_COUNT = 10.0f;

//-------------------------------------------------------------------
// 概要：コンストラクタ
// 引数(pBulletManager)：弾の発射管理情報
// 引数(pEnemyManager)：敵の管理情報
// 戻り値：なし
//-------------------------------------------------------------------
Boss::Boss(
	BulletManager* pBulletManager,
	EnemyManager* pEnemyManager
):
	mpBody(nullptr),
	mBossState(BOSS_STATE::NONE),
	mCount(0.0f),
	mTempPos(DirectX::SimpleMath::Vector3::Zero),
	mResultPos(DirectX::SimpleMath::Vector3::Zero),
	mTempAngle(0.0f),
	mResultAngle(0.0f),
	mpBullets(pBulletManager),
	mpEnemies(pEnemyManager)
{
	SetObjectPos(Boss::START_POS);
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);
	SetActive(true);
}

//---------------------------------------------------------
// 概要：デストラクタ
//---------------------------------------------------------
Boss::~Boss()
{
	// Finalizeを呼び出す
	Finalize();
}

//----------------------------------------------------------
// 概要：初期化
// 引数()：なし
// 戻り値：なし
//----------------------------------------------------------
void Boss::Initialize()
{
	// BossFactoryオブジェクトを生成する
	BossFactory bossFactory(mpBullets, mpEnemies);
	// BossFactoryオブジェクトを初期化する
	bossFactory.Initialize();

	// bodyオブジェクトを生成する
	mpBody = bossFactory.Create(BOSS_PARTS_ID::BODY, DirectX::SimpleMath::Vector3::Zero);
	
	// bodyオブジェクトにSmallArm1を追加する
	mpBody->AddBossParts(bossFactory.Create(BOSS_PARTS_ID::SMALL_ARM, ARM_OFFSET_01));
	// bodyオブジェクトにSmallArm2を追加する
	mpBody->AddBossParts(bossFactory.Create(BOSS_PARTS_ID::SMALL_ARM, ARM_OFFSET_02));
	// bodyオブジェクトにBigArmを追加する
	mpBody->AddBossParts(bossFactory.Create(BOSS_PARTS_ID::BIG_ARM, ARM_OFFSET_03));

	// 登場シーンに変更する
	mBossState = BOSS_STATE::ADMISSION;
}

//-----------------------------------------------------------
// 概要：更新
// 引数()：なし
// 戻り値：なし
//-----------------------------------------------------------
void Boss::Update()
{
	// 車体を更新
	//mpBody->Update(GetObjectPos(), GetObjectDirection(), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	// 動き
	Move();
	Collision();

}

//------------------------------------------------------------
// 概要：更新
// 引数(playerPos)：プレイヤーの座標
// 戻り値：なし
//------------------------------------------------------------
void Boss::Update(DirectX::SimpleMath::Vector3 playerPos)
{
	// 車体を更新
	mpBody->Update(
		GetObjectPos(),
		GetObjectDirection(),
		DirectX::SimpleMath::Vector3::Zero,
		playerPos,
		static_cast<int>(mBossState)
	);
	// 動き
	Move();
	Collision();

	if (!mpBody->GetActive())
	{
		SetActive(false);
	}
}

//-------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイト
// 引数(camera)：カメラ
// 戻り値：なし
//-------------------------------------------------------------
void Boss::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	//車体を描画する
	mpBody->Draw(commonStates, camera);
}

//--------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//--------------------------------------------------------------
void Boss::Finalize()
{
	// 車体をリセットする
	//mpBody.reset();
}

//--------------------------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//--------------------------------------------------------------
void Boss::Move()
{
	// 座標
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;

	// 角度
	DirectX::SimpleMath::Vector3 angle = DirectX::SimpleMath::Vector3::Zero;

	float resultCount = 0.0f;

	// ボスの状態に応じて動く
	switch (mBossState)
	{
		case BOSS_STATE::ADMISSION:
			mResultPos = MOVE_POS;
			resultCount = RESULT_COUNT;
			break;
		case BOSS_STATE::ADMISSION_AFTER:
			mBossState = static_cast<BOSS_STATE>((rand() % 2) + 3);
			return;
		case BOSS_STATE::LEFT_MOVE:
			mResultPos = BOSS_MOVE_01;
			mResultAngle = RESULT_ANGLE;
			resultCount = RESULT_COUNT;
			break;
		case BOSS_STATE::RIGHT_MOVE:
			mResultPos = BOSS_MOVE_02;
			mResultAngle = -RESULT_ANGLE;
			resultCount = RESULT_COUNT;
			break;
		case BOSS_STATE::ROLL_MOVE:
			break;
		default:
			break;
	}

	// 動く前の座標を入れ込む
	if (mCount <= 0.0f)
	{
		mTempPos = GetObjectPos();
		mTempAngle = GetObjectDirection().y;
	}

	// 1秒間1/60秒
	mCount += 1.0f / (resultCount * 60.0f);

	// 座標を計算する
	pos = DirectX::SimpleMath::Vector3::SmoothStep(mTempPos, mResultPos, mCount);
	
	// 角度を計算する
	angle = DirectX::SimpleMath::Vector3::SmoothStep(
		DirectX::SimpleMath::Vector3(0.0f,mTempAngle,0.0f),
		DirectX::SimpleMath::Vector3(0.0f, mResultAngle, 0.0f),
		mCount
	);
	// 座標をセットする
	SetObjectPos(pos);
	SetObjectDirection(angle);

	// 最後まで動いたら入場後に切り替える
	if (mResultPos == GetObjectPos())
	{
		mCount = 0.0f;
		mBossState = BOSS_STATE::ADMISSION_AFTER;
	}
}

//--------------------------------------------------------------------------
// 概要：当たり判定
// 引数：なし
// 戻り値：なし
//--------------------------------------------------------------------------
void Boss::Collision()
{
		// すべての弾と渡された対象との判定を取る
	for (unsigned int i = 0; i < 512; i++)
	{
		// 特定の条件ならば判定しない
		if (
			!mpBullets->GetBullet(i)->GetActive() ||			// 弾が発射状態でない
			mpBullets->GetBullet(i)->GetShooterType() == Bullet::eShooterType::ENEMY_SHOT
			)
		{
			continue;
		}
		// 当たり判定用の一時変数
		Collision::Sphere bullet;
		Collision::Sphere enemy;

		bullet.center = mpBullets->GetBullet(i)->GetObjectPos();
		bullet.radius = 1.0f;

		enemy.center = GetObjectPos();
		enemy.center.y += 5.0f;
		enemy.radius = 15.0f;

		// あたっていなければ次へ
		if (!Collision::HitCheckSphereToSphere(bullet, enemy))
		{
			continue;
		}

		// ダメージ処理エネミー
		// 各パーツに移行する
		mpBody->Collision();
	}
}

// ゲッター、セッター----------------------------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Boss::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}

//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void Boss::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// 概要：向きのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Boss::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}

//---------------------------------------
// 概要：向きのセッター
// 引数(direction)：オブジェクトの向き
// 戻り値：なし
//---------------------------------------
void Boss::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// 概要：速さのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの速さ
//---------------------------------------
DirectX::SimpleMath::Vector3 Boss::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}

//---------------------------------------
// 概要：速さのセッター
// 引数(speed)：オブジェクトの速さ
// 戻り値：なし
//---------------------------------------
void Boss::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// 概要：使用状態のゲッター
// 引数：なし
// 戻り値(bool)：オブジェクトの使用状態
//---------------------------------------
bool Boss::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// 概要：使用状態のセッター
// 引数(active)：オブジェクトの使用状態
// 戻り値：なし
//---------------------------------------
void Boss::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// 概要：HPのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトのHP
//---------------------------------------
int Boss::GetHP() const
{
	return mpBody->GetHP();
}

//---------------------------------------
// 概要：HPのセッター
// 引数(hp)：オブジェクトのHP
// 戻り値：なし
//---------------------------------------
void Boss::SetHP(const int& hp)
{
	UNREFERENCED_PARAMETER(hp);
	HeartObject::SetHP(mpBody->GetHP());
}
