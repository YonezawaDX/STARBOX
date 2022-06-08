/**
* @file CaterpillerLeft.cpp
* @brief キャタピタのクラス
* @author 米澤駿介
* @date 2022/05/01
* @details ボス02のタイヤ左のクラス
*/
#include "pch.h"

#include "CaterpillerLeft.h"
#include "../BossFactory.h"

//--------------------------------------------------------
// 概要：ボスパーツを追加する
// 引数 (bossParts)：HeartObjectのユニークポインタ 
// 戻り値：なし
//--------------------------------------------------------
void CaterpillerLeft::AddBossParts(std::unique_ptr<HeartObject> bossParts)
{
	// タンクパーツを追加する
	mpBossParts.push_back(std::move(bossParts));
}

//----------------------------------------------------------
// 概要：コンストラクタ
// 引数(offset)：素体との距離
// 引数(pBulletManager)：弾の発射管理情報
// 戻り値：なし
//----------------------------------------------------------
CaterpillerLeft::CaterpillerLeft(
	const DirectX::SimpleMath::Vector3& offset,
	BulletManager* pBulletManager
) :
	mpBossParts{},
	mPosOffset(offset),
	mAngleOffset(DirectX::SimpleMath::Vector3::Zero),
	mpBullets(pBulletManager)
{
	SetObjectPos(DirectX::SimpleMath::Vector3::Zero);
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);
	SetObjectSpeed(DirectX::SimpleMath::Vector3::Zero);
	SetActive(true);
	SetHP(10);
}

//--------------------------------------------
// 概要：デストラクタ
//--------------------------------------------
CaterpillerLeft::~CaterpillerLeft()
{
	// 終了処理を呼ぶ
	Finalize();
}

//-------------------------------------------------------
// 概要：初期化
// 引数 (bossFactory):ボスの生成クラス
// 戻り値：なし
//-------------------------------------------------------
void CaterpillerLeft::Initialize(BossFactory* bossFactory)
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
//------------------------------------------------------
void CaterpillerLeft::Update(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& angle,
	const DirectX::SimpleMath::Vector3& offset,
	const DirectX::SimpleMath::Vector3& playerPos,
	const int& stateNum
)
{
	// 位置を設定する
	SetObjectPos(position);

	// 向きを設定する
	SetObjectDirection(angle);

	// 向きのオフセットを指定する
	mAngleOffset = offset;
	if (GetHP() <= 0)
	{
		SetActive(false);
	}

	// 再帰的にタンクパーツのUpdate関数を呼び出す
	for (auto& bossParts : mpBossParts)
	{
		// Update関数を呼び出す
		bossParts->Update(position, angle, offset, playerPos, stateNum);
	}
}

//---------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------
void CaterpillerLeft::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	mCamera = camera;
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

	pRM->GetCmoModel("CaterpillerLeft")->Draw(
		context,
		*commonStates,
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(q) * world,
		view,
		projection
	);

	// 再帰的にタンクパーツのUpdate関数を呼び出す
	for (auto& bossParts : mpBossParts)
	{
		// Update関数を呼び出す
		bossParts->Draw(commonStates, camera);
	}
}

//----------------------------------------------
// 概要：終了処理
// 引数：なし
// 戻り値：なし
//----------------------------------------------
void CaterpillerLeft::Finalize()
{
}

//----------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//----------------------------------------------
void CaterpillerLeft::Move()
{
}

//-----------------------------------------------
// 概要：当たり判定
// 引数：なし
// 戻り値：なし
//-----------------------------------------------
void CaterpillerLeft::Collision()
{
	// パーツが一つでも生きているなら処理しない
	bool enp = true;
	for (unsigned int i = 0; i < mpBossParts.size(); i++)
	{
		if (mpBossParts[i]->GetActive())
		{
			enp = false;
		}
	}

	if (enp)
	{
		// すべての弾と渡された対象との判定を取る
		for (unsigned int i = 0; i < 512; i++)
		{
			// 特定の条件ならば判定しない
			if (
				!mpBullets->GetBullet(i)->GetActive() ||			// 弾が発射状態でない
				mpBullets->GetBullet(i)->GetShooterType() == static_cast<int>(Bullet::eShooterType::ENEMY_SHOT)
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
			enemy.radius = 5.0f;

			// あたっていなければ次へ
			if (!Collision::HitCheckSphereToSphere(bullet, enemy))
			{
				continue;
			}

			// ダメージ処理エネミー
			mpBullets->GetBullet(i)->SetActive(false);

			DirectX::SimpleMath::Vector3 a = mpBullets->GetBullet(i)->GetObjectPos();
			a.z -= -5.0f;

			int hp = GetHP();
			hp -= 1;
			SetHP(hp);
		}
		return;
	}

	// 再帰的にタンクパーツのUpdate関数を呼び出す
	for (auto& bossParts : mpBossParts)
	{
		// Update関数を呼び出す
		bossParts->Collision();
	}
}

//-------------------------------------------------------
// 概要：パーツを消す
// 引数：なし
// 戻り値：なし
//--------------------------------------------------------
void CaterpillerLeft::DeleteParts()
{
	//mpBossParts.pop_back();
}

// ゲッター、セッター------------------------------------------------------------------------------------------

//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 CaterpillerLeft::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}

//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void CaterpillerLeft::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// 概要：向きのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 CaterpillerLeft::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}

//---------------------------------------
// 概要：向きのセッター
// 引数(direction)：オブジェクトの向き
// 戻り値：なし
//---------------------------------------
void CaterpillerLeft::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// 概要：速さのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの速さ
//---------------------------------------
DirectX::SimpleMath::Vector3 CaterpillerLeft::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}

//---------------------------------------
// 概要：速さのセッター
// 引数(speed)：オブジェクトの速さ
// 戻り値：なし
//---------------------------------------
void CaterpillerLeft::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// 概要：使用状態のゲッター
// 引数：なし
// 戻り値(bool)：オブジェクトの使用状態
//---------------------------------------
bool CaterpillerLeft::GetActive() const
{
	return HeartObject::GetActive();
}

//---------------------------------------
// 概要：使用状態のセッター
// 引数(active)：オブジェクトの使用状態
// 戻り値：なし
//---------------------------------------
void CaterpillerLeft::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// 概要：HPのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトのHP
//---------------------------------------
int CaterpillerLeft::GetHP() const
{
	return HeartObject::GetHP();
}

//---------------------------------------
// 概要：HPのセッター
// 引数(hp)：オブジェクトのHP
// 戻り値：なし
//---------------------------------------
void CaterpillerLeft::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}
