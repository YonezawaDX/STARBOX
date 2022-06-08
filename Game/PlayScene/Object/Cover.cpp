/**
* @file Cover.cpp
* @brief コアカバーのクラス
* @author 米澤駿介
* @date 2022/05/01
* @details ボス02のコアの上をくるくる回っているオブジェクト
*/
#include "pch.h"

#include "pch.h"
#include "Cover.h"
#include "../BossFactory.h"

//------------------------------------------------------------------
// 概要：ボスパーツを追加する
// 引数 (bossParts)：HeartObjectのユニークポインタ 
// 戻り値：なし
//-------------------------------------------------------------------
void Cover::AddBossParts(std::unique_ptr<HeartObject> bossParts)
{
	UNREFERENCED_PARAMETER(bossParts);
}

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数(offset)：素体との距離
// 引数(pBulletManager)：弾の発射管理情報
//------------------------------------------------------------------
Cover::Cover(
	const DirectX::SimpleMath::Vector3& offset,
	BulletManager* pBulletmanager
) :
	mPosOffset(offset),
	mAngleOffset(DirectX::SimpleMath::Vector3::Zero),
	mBossState(0),
	mpBulletManager(pBulletmanager),
	mShootIntervalTimer(0),
	mIsDown(false)
{
	SetObjectPos(DirectX::SimpleMath::Vector3::Zero);
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);
	SetObjectSpeed(DirectX::SimpleMath::Vector3(-0.2f, -0.2f, 0.2f));
	SetHP(3);
	SetActive(true);
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
Cover::~Cover()
{
	Finalize();
}

//----------------------------------------------------
// 概要：初期化
// 引数 (bossFactory):ボスの生成クラス
// 戻り値：なし
//----------------------------------------------------
void Cover::Initialize(BossFactory* bossFactory)
{
	UNREFERENCED_PARAMETER(bossFactory);
}

//------------------------------------------------------
// 概要：更新
// 引数 (position)：座標
// 引数 (angle)：角度
// 引数 (offset)：素体との距離
// 引数 (playerPos)：プレイヤーの座標
// 引数 (stateNum)：ボスの状態
// 戻り値：なし
//-------------------------------------------------------
void Cover::Update(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& angle,
	const DirectX::SimpleMath::Vector3& offset,
	const DirectX::SimpleMath::Vector3& playerPos,
	const int& stateNum
)
{
	UNREFERENCED_PARAMETER(playerPos);

	Move();
	// ボスの状態を格納
	mBossState = stateNum;

	if (GetObjectPos().y <= -10.0f)
	{
		SetActive(false);
	}

	if (mIsDown)
	{
		return;
	}
	// 位置を設定する
	SetObjectPos(position + mPosOffset);

	// 向きを設定する
	SetObjectDirection(angle + offset);

	// 向きのオフセット
	mAngleOffset = offset;
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void Cover::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	auto pRM = ResourceManager::GetInstance();
	//デバイスコンテキストの取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// 射影行列の取得
	DirectX::SimpleMath::Matrix projection = camera->GetProjectionMatrix();
	// ビュー行列の取得
	DirectX::SimpleMath::Matrix view = camera->GetViewMatrix();

	// ワールド座標の取得
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(GetObjectPos());

	// モデルの回転
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		GetObjectDirection().y * 0.05f,
		GetObjectDirection().x * 0.05f,
		GetObjectDirection().z * 0.05f
	);


	pRM->GetCmoModel("Cover")->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(q) * world,
		view,
		projection
	);
}

//------------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void Cover::Finalize()
{
}

//------------------------------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void Cover::Move()
{
	DirectX::SimpleMath::Vector3 downVel = GetObjectPos();
	if (GetHP() <= 0)
	{
		downVel += GetObjectSpeed();
		mIsDown = true;
	}
	SetObjectPos(downVel);
}

//-----------------------------------------------------------------------
// 概要：当たり判定
// 引数：なし
// 戻り値：なし
//-----------------------------------------------------------------------
void Cover::Collision()
{
	// すべての弾と渡された対象との判定を取る
	for (unsigned int i = 0; i < 512; i++)
	{
		// 特定の条件ならば判定しない
		if (
			!mpBulletManager->GetBullet(i)->GetActive() ||			// 弾が発射状態でない
			mpBulletManager->GetBullet(i)->GetShooterType() == Bullet::eShooterType::ENEMY_SHOT
			)
		{
			continue;
		}


		// 当たり判定用の一時変数
		Collision::Sphere bullet;
		Collision::Sphere enemy;

		bullet.center = mpBulletManager->GetBullet(i)->GetObjectPos();
		bullet.radius = 1.0f;

		enemy.center = GetObjectPos();
		enemy.center.y += 5.0f;
		enemy.radius = 5.0f;

		// あたっていなければ次へ
		if (!Collision::HitCheckSphereToSphere(bullet, enemy))
		{
			continue;
		}

		// ダメージ処理エネミー
		mpBulletManager->GetBullet(i)->SetActive(false);

		int hp = GetHP();
		hp -= 1;
		SetHP(hp);
	}
}

//---------------------------------------
// 概要：弾発射
// 引数(pos)：座標
// 戻り値：なし
//---------------------------------------
void Cover::BulletFire(DirectX::SimpleMath::Vector3 pos)
{
	++mShootIntervalTimer %= 20;
	//発射角を計算する
	DirectX::SimpleMath::Vector3 myPos = GetObjectPos();
	myPos.y += 5.0f;
	myPos.z += 15.0f;
	DirectX::SimpleMath::Vector3 launch = myPos - pos;
	mpBulletManager->Shot(2, myPos, launch);

	if (mShootIntervalTimer == 0)
	{

	}
}

// ゲッター、セッター------------------------------------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Cover::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}
//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void Cover::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// 概要：向きのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Cover::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}
//---------------------------------------
// 概要：向きのセッター
// 引数(direction)：オブジェクトの向き
// 戻り値：なし
//---------------------------------------
void Cover::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// 概要：速さのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの速さ
//---------------------------------------
DirectX::SimpleMath::Vector3 Cover::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}
//---------------------------------------
// 概要：速さのセッター
// 引数(speed)：オブジェクトの速さ
// 戻り値：なし
//---------------------------------------
void Cover::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// 概要：使用状態のゲッター
// 引数：なし
// 戻り値(bool)：オブジェクトの使用状態
//---------------------------------------
bool Cover::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// 概要：使用状態のセッター
// 引数(active)：オブジェクトの使用状態
// 戻り値：なし
//---------------------------------------
void Cover::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// 概要：HPのゲッター
// 引数：なし
// 戻り値(int)：オブジェクトのHP
//---------------------------------------
int Cover::GetHP() const
{
	return HeartObject::GetHP();
}
//---------------------------------------
// 概要：HPのセッター
// 引数(hp)：オブジェクトのHP
// 戻り値：なし
//---------------------------------------
void Cover::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}