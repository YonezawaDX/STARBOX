/**
* @file Bullet.cpp
* @brief 弾クラス
* @author 米澤駿介
* @date 2021/12/01
* @details 弾
*/
#include "pch.h"
#include "Bullet.h"

//-------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
// 戻り値：なし
//-------------------------------------------------------------------
Bullet::Bullet()
	: mpBulletModel3D{}
	, mShooterType(eShooterType::PLAYER_SHOT)
	, mBulletAnglePos(DirectX::SimpleMath::Vector3::Zero)
	, mIsActive(true)
{
}

//---------------------------------------------------------
// 概要：デストラクタ
//---------------------------------------------------------
Bullet::~Bullet()
{
}

//----------------------------------------------------------
// 概要：初期化
// 引数()：なし
// 戻り値：なし
//----------------------------------------------------------
void Bullet::Initialize()
{
}

//----------------------------------------------------------
// 概要：初期化
// 引数(bulletType)：弾のタイプ
// 引数(shooterType)：弾を使う者の種類
// 引数(pos)：座標
// 引数(angle)：角度
// 戻り値：なし
//----------------------------------------------------------
void Bullet::Initialize(
	Model3D* bulletType,
	int shooterType, 
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 angle
)
{
	// モデルへのポインタを格納する
	mpBulletModel3D = bulletType;

	// 発射するキャラの保存
	mShooterType = static_cast<eShooterType>(shooterType);

	// 発射時の座標の保存
	SetObjectPos(pos);

	// 発射時の機体の角度を取得し発射角を計算する
	SetObjectDirection(angle);

	// 使用中にする
	SetActive(true);
}


//-----------------------------------------------------------
// 概要：更新
// 引数()：なし
// 戻り値：なし
//-----------------------------------------------------------
void Bullet::Update()
{
	// 使用中でなければ処理しない
	if (!GetActive())
	{
		return;
	}
	Move();

	// 画面外に出たら未使用状態にする
	if (
		GetObjectPos().z > 100.0f||
		GetObjectPos().z < -1000.0f
		)
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
void Bullet::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	// 使用中でなければ処理しない
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


	pRM->GetCmoModel("Bullet")->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(q) * world,
		view,
		projection
	);
}

//--------------------------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//--------------------------------------------------------------
void Bullet::Finalize()
{
}


//--------------------------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//--------------------------------------------------------------
void Bullet::Move()
{
	DirectX::SimpleMath::Vector3 bulletPos = GetObjectPos();
	switch (mShooterType)
	{
		case eShooterType::PLAYER_SHOT:
		{
			bulletPos.x -= atanf((DirectX::XMConvertToRadians(GetObjectDirection().y)) * 4.5f);
			bulletPos.y += atanf((DirectX::XMConvertToRadians(GetObjectDirection().x)) * 4.5f);

			bulletPos.z -= 1.5f;
			SetObjectPos(bulletPos);

			break;
		}
		case eShooterType::ENEMY_SHOT:
		{
			break;
		}
		case eShooterType::BOSS_SHOT:
		{
			DirectX::SimpleMath::Vector3 vel = GetObjectDirection();
			vel.Normalize();

			bulletPos -= vel * 0.25f;

			SetObjectPos(bulletPos);
			break;
		}
		default:
			assert("弾がありません");
			break;
	}
}


//--------------------------------------------------------------
// 概要：ダメージ
// 引数(damage)：ダメージの値
// 戻り値：なし
//--------------------------------------------------------------
void Bullet::Damage(int damage)
{
	UNREFERENCED_PARAMETER(damage);
}

// ゲッタセッタ---------------------------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Bullet::GetObjectPos() const
{
	return Object::GetObjectPos();
}
//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void Bullet::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	Object::SetObjectPos(pos);
}

//---------------------------------------
// 概要：使用状態のゲッター
// 引数()：なし
// 戻り値(bool)：使用状態
//---------------------------------------
bool Bullet::GetActive() const
{
	return MoveObject::GetActive();
}
//---------------------------------------
// 概要：使用状態のセッター
// 引数(act)：使用状態
// 戻り値：なし
//---------------------------------------
void Bullet::SetActive(const bool& act)
{
	MoveObject::SetActive(act);
}

//---------------------------------------
// 概要：発射タイプのゲッター
// 引数()：なし
// 戻り値(int)：発射するタイプ
//---------------------------------------
Bullet::eShooterType Bullet::GetShooterType() const
{
	return mShooterType;
}
//---------------------------------------
// 概要：発射タイプのセッター
// 引数(type)：発射するタイプ
// 戻り値：なし
//---------------------------------------
void Bullet::SetShooterType(const eShooterType type)
{
	mShooterType = type;
}
