/**
* @file Enemy.cpp
* @brief 敵のクラス
* @author 米澤駿介
* @date 2021/12/04
* @details 敵
*/
#include "pch.h"
#include "Enemy.h"

//----------------------------------------------------------
// 概要：コンストラクタ
//----------------------------------------------------------
Enemy::Enemy()
	: mpBulletManager{}
	, mEnemyType(0)
	, mShotTimer(0)
{
}

//--------------------------------------------
// 概要：デストラクタ
//--------------------------------------------
Enemy::~Enemy()
{
}

//-------------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//-------------------------------------------------------
void Enemy::Initialize()
{
}

//-------------------------------------------------------
// 概要：初期化
// 引数 (modelType)：敵のモデルのタイプ
// 引数 (enemyType)：敵の種類
// 引数 (pos)：座標
// 引数 (angle)：角度
// 引数 (hp)：体力
// 引数 (pBulletManager)：弾発射用
// 戻り値：なし
//-------------------------------------------------------
void Enemy::Initialize(
	Model3D* modelType,
	int enemyType,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 angle ,
	int hp,
	BulletManager* pBulletManager
)
{
	UNREFERENCED_PARAMETER(modelType);
	// 弾の管理者を保存
	mpBulletManager = pBulletManager;
	
	// 敵の種類を保存
	mEnemyType = enemyType;

	// 座標の保存
	SetObjectPos(pos);

	// 敵を使用状態とする
	SetActive(true);

	// 敵の向き
	SetObjectDirection(angle);

	// HPのセット
	this->SetHP(hp);
}

//------------------------------------------------------
// 概要：更新
// 引数：なし
// 戻り値：なし
//------------------------------------------------------
void Enemy::Update()
{
	// アクティブ状態でなければ処理をしない
	if (!this->GetActive())
	{
		return;
	}


	DirectX::SimpleMath::Vector3 enemyPos = GetObjectPos();

	switch (mEnemyType)
	{
		case static_cast<int>(eEnemyType::NORMAL):
		{

			enemyPos.z += 0.1f;

			// 発射間隔用タイマーを進める
			++mShotTimer %= 60;

			// 時間が来たら弾発射
			if (mShotTimer == 0)
			{
				//mpBulletManager->Shot(1,enemyPos, DirectX::SimpleMath::Vector3::Zero);
			}
			break;
		}
		case static_cast<int>(eEnemyType::ROTATE):
		{
			break;
		}
		case static_cast<int>(eEnemyType::TRACK):
		{
			//enemyPos.z += 0.2f;
			DirectX::SimpleMath::Vector3 vel = GetObjectDirection();
			vel.Normalize();

			enemyPos -= vel * 0.25f;
			
			// 発射間隔用タイマーを進める
			++mShotTimer %= 60;

			// 時間が来たら弾発射
			if (mShotTimer == 0)
			{
				//mpBulletManager->Shot(1,enemyPos, DirectX::SimpleMath::Vector3::Zero);
			}
			break;
		}
		default:
			break;
	}

	// 座標を決定する
	SetObjectPos(enemyPos);

	// 画面外に出たら未使用状態にする
	if (
		GetObjectPos().z > 50.0f ||
		GetObjectPos().z < -1000.0f
		)
	{
		SetActive(false);
	}

}

//---------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------
void Enemy::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	// アクティブ状態でなければ処理しない
	if (!this->GetActive())
	{
		return;
	}
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


	pRM->GetCmoModel("Enemy")->Draw(
		context,
		*commonStates,
		world,
		view,
		projection
	);

}

//----------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//----------------------------------------------
void Enemy::Finalize()
{
}

//----------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//----------------------------------------------
void Enemy::Move()
{
}
//----------------------------------------------
// 概要：ダメージ
// 引数(damage)：ダメージの値
// 戻り値：なし
//----------------------------------------------
void Enemy::Damage(int damage)
{
	damage;
	SetActive(false);
}

// ゲッター、セッター----------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Enemy::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}
//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void Enemy::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// 概要：向きのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Enemy::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}
//---------------------------------------
// 概要：向きのセッター
// 引数(direction)：オブジェクトの向き
// 戻り値：なし
//---------------------------------------
void Enemy::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// 概要：速さのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの速さ
//---------------------------------------
DirectX::SimpleMath::Vector3 Enemy::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}
//---------------------------------------
// 概要：速さのセッター
// 引数(speed)：オブジェクトの速さ
// 戻り値：なし
//---------------------------------------
void Enemy::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// 概要：使用状態のゲッター
// 引数：なし
// 戻り値(bool)：オブジェクトの使用状態
//---------------------------------------
bool Enemy::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// 概要：使用状態のセッター
// 引数(active)：オブジェクトの使用状態
// 戻り値：なし
//---------------------------------------
void Enemy::SetActive(const bool& act)
{
	HeartObject::SetActive(act);
}

//---------------------------------------
// 概要：HPのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトのHP
//---------------------------------------
int Enemy::GetHP() const
{
	return HeartObject::GetHP();
}
//---------------------------------------
// 概要：HPのセッター
// 引数(hp)：オブジェクトのHP
// 戻り値：なし
//---------------------------------------
void Enemy::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}
