/**
* @file Player.cpp
* @brief プレイヤーのクラス
* @author 米澤駿介
* @date 2022/04/26
* @details プレイヤー、移動したり弾撃ったり
*/
#include "pch.h"
#include "Player.h"
#include <Keyboard.h>
#include "Libraries/MyLibraries/ResourceManager.h"
#include "DeviceResources.h"
#include "Libraries/MyLibraries/InputManager.h"

// 定数-------------------------------------------------
// 初期座標
const DirectX::SimpleMath::Vector3 Player::START_POS = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
// 体力
const int Player::HP = 100;
// 加速度
const float Player::ACCELERATION = 0.005f;
// 向き
const float Player::ANGLE = 0.5f;
// プレイヤーを止める速度
const float Player::STOP_PLAYER = 0.01f;

// 向きの限界値
const DirectX::SimpleMath::Vector3 Player::LIMIT_SPEED_MIN = DirectX::SimpleMath::Vector3(-5.0f, -5.0f, -5.0f);
const DirectX::SimpleMath::Vector3 Player::LIMIT_SPEED_MAX = DirectX::SimpleMath::Vector3(5.0f, 5.0f, 5.0f);

// 位置の限界値
const DirectX::SimpleMath::Vector3 Player::LIMIT_POS_MIN = DirectX::SimpleMath::Vector3(-20.0f, 1.0f, 0.0f);
const DirectX::SimpleMath::Vector3 Player::LIMIT_POS_MAX = DirectX::SimpleMath::Vector3(20.0f, 10.0f, 0.0f);

// ショットのインターバル
const int Player::SHOT_INTERVAL = 20;

//------------------------------------------------------

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数(pBulletManager)：弾の管理者
//------------------------------------------------------------------
Player::Player(BulletManager* pBulletManager)
	: mPlayerSpeed(DirectX::SimpleMath::Vector3::Zero)
	, mPlayerAngle(DirectX::SimpleMath::Vector3::Zero)
	, mPlayerMoveFlag(false)
	, mpBulletManager(pBulletManager)
	, mShootIntervalTimer(0)
	, mPlayerPos(DirectX::SimpleMath::Vector3::Zero)
{
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
Player::~Player()
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 : なし
// 戻り値：なし
//----------------------------------------------------
void Player::Initialize()
{
	// 各種パラメータを初期化する
	SetObjectPos(START_POS);
	SetObjectDirection(DirectX::SimpleMath::Vector3::Zero);
	SetObjectSpeed(DirectX::SimpleMath::Vector3::Zero);
	SetActive(true);
	SetHP(HP);
}

//----------------------------------------------------
// 概要：更新
// 引数:なし
// 戻り値：なし
//----------------------------------------------------
void Player::Update()
{
	// プレイヤを動かす
	Move();

	// 弾を発射する
	Shot();
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void Player::Draw(DirectX::CommonStates* commonStates, Camera* camera)
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


	pRM->GetCmoModel("Player")->Draw(
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
void Player::Finalize()
{
}

//------------------------------------------------------------------
// 概要：動き
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void Player::Move()
{
	// キー入力情報を取得する
	auto keyState = InputManager::GetInstance();

	// プレイヤーの座標を取得
	DirectX::SimpleMath::Vector3 playerPos = DirectX::SimpleMath::Vector3::Zero;
	playerPos = GetObjectPos();

	// 加速度
	float acc = ACCELERATION;

	// フラグを下ろす
	mPlayerMoveFlag = false;

	// プレイヤーのスピードを宣言
	DirectX::SimpleMath::Vector3 playerSpeed = GetObjectSpeed();
	// プレイヤーのアングルを宣言
	DirectX::SimpleMath::Vector3 playerAngle = GetObjectDirection();

	// ボタンを押したとき
	if (keyState->GetKeyboardState().Left)
	{
		playerSpeed.x -= acc;
		playerAngle.z += ANGLE;
		playerAngle.y += ANGLE;
		mPlayerMoveFlag = true;
	}
	if (keyState->GetKeyboardState().Right)
	{
		playerSpeed.x += acc;
		playerAngle.z -= ANGLE;
		playerAngle.y -= ANGLE;

		mPlayerMoveFlag = true;
	}
	if (keyState->GetKeyboardState().Up)
	{
		playerSpeed.y += acc;
		playerAngle.x += 0.5f;
		mPlayerMoveFlag = true;
	}
	if (keyState->GetKeyboardState().Down)
	{
		playerSpeed.y -= acc;
		playerAngle.x -= 0.5f;
		mPlayerMoveFlag = true;
	}

	// プレイヤーが移動していないとき
	if (!mPlayerMoveFlag)
	{
		if (playerAngle.x > 0.0f)
		{
			playerAngle.x -= ANGLE;
		}
		else if (playerAngle.x < 0.0f)
		{
			playerAngle.x += ANGLE;
		}
		if (playerAngle.z > 0.0f)
		{
			playerAngle.z -= ANGLE;
		}
		else if (playerAngle.z < 0.0f)
		{
			playerAngle.z += ANGLE;
		}
		if (playerAngle.y > 0.0f)
		{
			playerAngle.y -= ANGLE;
		}
		else if (playerAngle.y < 0.0f)
		{
			playerAngle.y += ANGLE;
		}


		//プレイヤーを止める
		if (playerSpeed.x > 0.000000000f)
		{
			playerSpeed.x -= STOP_PLAYER;
		}
		else if (playerSpeed.x < 0.000000000f)
		{
			playerSpeed.x += STOP_PLAYER;
		}
		if (playerSpeed.y > 0.000000000f)
		{
			playerSpeed.y -= STOP_PLAYER;
		}
		else if (playerSpeed.y < 0.000000000f)
		{
			playerSpeed.y += STOP_PLAYER;
		}
	}


	playerAngle.Clamp(
		LIMIT_SPEED_MIN,
		LIMIT_SPEED_MAX
	);

	SetObjectDirection(playerAngle);
	SetObjectSpeed(playerSpeed);


	// スピードを加算する
	playerPos.x += GetObjectSpeed().x;
	playerPos.y += GetObjectSpeed().y;


	// 最小値と最大値を決める
	// todoこの段階で速度を戻しておく
	playerPos.Clamp(
		LIMIT_POS_MIN,
		LIMIT_POS_MAX
	);

	// プレイヤの座標をセットする
	SetObjectPos(playerPos);
}

//------------------------------------------------------------------
// 概要：ダメージ
// 引数 (damage)：ダメージの値
// 戻り値：なし
//------------------------------------------------------------------
void Player::Damage(int damage)
{
	int hp = GetHP();
	hp -= damage;
	SetHP(hp);
}

//------------------------------------------------------------------
// 概要：弾丸発射
// 引数：なし
// 戻り値：なし
//------------------------------------------------------------------
void Player::Shot()
{
	// キー入力情報を取得する
	auto keyState = DirectX::Keyboard::Get().GetState();

	++mShootIntervalTimer %= SHOT_INTERVAL;
	
	bool shootTime = mShootIntervalTimer == 0;
	if (shootTime && keyState.Space)
	{
		mpBulletManager->Shot(0,GetObjectPos(),GetObjectDirection());
	}
}

//ゲッタセッタ-------------------------------------------------------------------
//---------------------------------------
// 概要：座標のゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Player::GetObjectPos() const
{
	return HeartObject::GetObjectPos();
}
//---------------------------------------
// 概要：座標のセッター
// 引数(pos)：オブジェクトの座標
// 戻り値：なし
//---------------------------------------
void Player::SetObjectPos(const DirectX::SimpleMath::Vector3& pos)
{
	HeartObject::SetObjectPos(pos);
}

//---------------------------------------
// 概要：向きのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの座標
//---------------------------------------
DirectX::SimpleMath::Vector3 Player::GetObjectDirection() const
{
	return HeartObject::GetObjectDirection();
}
//---------------------------------------
// 概要：向きのセッター
// 引数(direction)：オブジェクトの向き
// 戻り値：なし
//---------------------------------------
void Player::SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)
{
	HeartObject::SetObjectDirection(direction);
}

//---------------------------------------
// 概要：速さのゲッター
// 引数：なし
// 戻り値(Vector3)：オブジェクトの速さ
//---------------------------------------
DirectX::SimpleMath::Vector3 Player::GetObjectSpeed() const
{
	return HeartObject::GetObjectSpeed();
}
//---------------------------------------
// 概要：速さのセッター
// 引数(speed)：オブジェクトの速さ
// 戻り値：なし
//---------------------------------------
void Player::SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)
{
	HeartObject::SetObjectSpeed(speed);
}

//---------------------------------------
// 概要：使用状態のゲッター
// 引数：なし
// 戻り値(bool)：オブジェクトの使用状態
//---------------------------------------
bool Player::GetActive() const
{
	return HeartObject::GetActive();
}
//---------------------------------------
// 概要：使用状態のセッター
// 引数(active)：オブジェクトの使用状態
// 戻り値：なし
//---------------------------------------
void Player::SetActive(const bool& active)
{
	HeartObject::SetActive(active);
}

//---------------------------------------
// 概要：HPのゲッター
// 引数：なし
// 戻り値(int)：オブジェクトのHP
//---------------------------------------
int Player::GetHP() const
{
	return HeartObject::GetHP();
}
//---------------------------------------
// 概要：HPのセッター
// 引数(hp)：オブジェクトのHP
// 戻り値：なし
//---------------------------------------
void Player::SetHP(const int& hp)
{
	HeartObject::SetHP(hp);
}
