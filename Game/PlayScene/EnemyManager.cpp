/**
* @file EnemyManager.cpp
* @brief 敵の管理者
* @author 米澤駿介
* @date 2022/04/26
* @details 細かい敵を管理する
*/
#include "pch.h"
#include <cassert>
#include <fstream>
#include <sstream>

#include "Libraries/MyLibraries/Model3D.h"
#include "EnemyManager.h"
#include "Object/Player.h"

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
EnemyManager::EnemyManager()
	: mEnemies{}
	, mEnemyData{}
	, mEnemyNum(0)
	, mpBulletManager{}
	, mTimer(0)
	, mpEnemyModel3D{}
{
	LoadCSV(L"Resources/CSV/EnemyData.csv");
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
EnemyManager::~EnemyManager()
{
}

//----------------------------------------------------
// 概要：初期化
// 引数 (pBulletManager):弾の管理者
// 戻り値：なし
//----------------------------------------------------
void EnemyManager::Initialize(BulletManager* pBulletManager)
{
	// モデルのロード
	mpEnemyModel3D = std::make_unique<Model3D>();
	mpEnemyModel3D->Initialize(L"Resources/Models/dice.cmo");

	// タイマーの初期化
	mTimer = 0;

	// 弾の管理者格納
	mpBulletManager = pBulletManager;

	// すべての敵を未使用の状態にする
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->SetActive(false);
	}
}

//----------------------------------------------------
// 概要：更新
// 引数:なし
// 戻り値：なし
//----------------------------------------------------
void EnemyManager::Update()
{
	// タイマーの更新
	mTimer++;

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		// すでに動いている敵は無視
		if (mEnemies[i]->GetActive())
		{
			continue;
		}

		// 時間が立っていなかったら無視
		if (mEnemyData[i].mCount > mTimer)
		{
			continue;
		}

		// 敵の生成
		mEnemies[i]->Initialize(
			mpEnemyModel3D.get(),
			mEnemyData[i].mEnemyNum,
			DirectX::SimpleMath::Vector3(mEnemyData[i].mPosX, mEnemyData[i].mPosY, -100.0f),
			DirectX::SimpleMath::Vector3::Zero,
			mEnemyData[i].mHP,
			mpBulletManager
		);
	}

	// 敵を更新
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Update();
	}

}

//---------------------------------------------
// 概要：ボスの更新
// 引数 (enemyNum)：敵の種類
// 引数 (pos)：座標
// 引数 (angle)：角度
// 引数 (hp)：体力　
// 引数 (move)：動いているか
// 戻り値：void なし
//---------------------------------------------
void EnemyManager::BossUpdate(
	int enemyNum,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 angle,
	int hp,
	bool move
)
{
	// タイマーの更新
	mTimer++;


	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		// すでに動いている敵は無視
		if (mEnemies[i]->GetActive())
		{
			continue;
		}

		// 時間が立っていなかったら無視
		if (mEnemyData[i].mCount > mTimer)
		{
			continue;
		}
		if (move)
		{
			// 敵の生成
			mEnemies[i]->Initialize(
				mpEnemyModel3D.get(),
				enemyNum,
				pos,
				angle,
				hp,
				mpBulletManager
			);
		}
	}

	// 敵を更新
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Update();
	}
}

//----------------------------------------------------------------------
// 概要：描画
// 引数(commonStates)：コモンステイトのポインタ
// 引数(camera)：カメラのポインタ
// 戻り値：なし
//---------------------------------------------------------------------
void EnemyManager::Draw(DirectX::CommonStates* commonStates, Camera* camera)
{
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Draw(commonStates,camera);
	}
}

//------------------------------------------------------------------
// 概要：終了
// 引数：なし
// 戻り値 (bool)：終了したか
//------------------------------------------------------------------
bool EnemyManager::IsEnd()
{
	return false;
}

//-----------------------------------------------------------------------
// 概要：プレイヤーとの当たり判定
// 引数 (pPlayer)：プレイヤーのポインタ
// 戻り値：なし
//-----------------------------------------------------------------------
void EnemyManager::CheckHitPlayer(IObject* pPlayer)
{
	// すべての敵との判定
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		// 特定の条件ならば処理をしない
		if (
			!mEnemies[i]->GetActive() 	// 弾が使用状態でない
			// プレイヤーが被弾状態でない
			)
		{
			continue;
		}

		// あたっていなければ次へ
		// 当たり判定用の一時変数
		Collision::Sphere enemy;
		Collision::Sphere player;

		enemy.center = mEnemies[i]->GetObjectPos();
		enemy.radius = 100.0f;

		player.center = pPlayer->GetObjectPos();
		player.radius = 5.0f;

		if (!Collision::HitCheckSphereToSphere(enemy,player))
		{
			continue;
		}

		//pPlayer->Damage(1);
	}
}

//--------------------------------------------------
// 概要：csvを読み込む
// 引数(mapFile)：ファイルの名前
// 戻り値(bool)： 読み込みができたか
//---------------------------------------------------
bool EnemyManager::LoadCSV(const wchar_t* mapFile)
{
	// ローカル変数
	std::ifstream ifs;		// 入力ファイルストリーム
	std::istringstream iss;	// 入力文字列ストリーム
	std::string line;		// 1行分の文字列
	std::string data;		// (カンマで区切られた)1データ分の文字列

	ifs.open(mapFile);
	// ファイルを開かなければ、失敗
	if (ifs.fail()) { return false; }

	// 最初の行は読み飛ばす
	std::getline(ifs, line);

	// 敵の数を読み込む
	std::getline(ifs, line);
	mEnemyNum = std::stoi(line);

	// 敵の数を確定する
	mEnemies.resize(mEnemyNum);
	mEnemyData.resize(mEnemyNum);
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		// 一行分の文字列を読み込む
		std::getline(ifs, line);
		// issの状態をクリア -> しないとハマる
		iss.clear(std::istringstream::goodbit);
		// 文字列から文字列ストリームに変換
		iss.str(line);

		// カンマ区切りで文字列をint型に変換し、配列に格納する
		for (int j = 0; j < 5; j++)
		{
			std::getline(iss, data, ',');

			// それぞれのデータを格納する
			switch (j)
			{
				case 0:
				{
					mEnemyData[i].mCount = std::stoi(data);
					break;
				}
				case 1:
				{
					mEnemyData[i].mEnemyNum = std::stoi(data);
					break;
				}
				case 2:
				{
					mEnemyData[i].mPosX = (float)std::stoi(data);
					break;
				}
				case 3:
				{
					mEnemyData[i].mPosY = (float)std::stoi(data);
					break;
				}
				case 4:
				{
					mEnemyData[i].mHP = std::stoi(data);
					break;
				}
				default:
					break;
			}
		}
	}

	// ファイルを閉じる
	ifs.close();

	// 敵の作成
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i] = std::make_unique<Enemy>();
	}

	// ファイルの読み込み成功
	return true;
}

//----------------------------------------------
// 概要：敵の情報を渡す
// 引数(i)：１つの敵の番号を取得
// 戻り値 (Enemy*)：１つの敵のポインタ
//--------------------------------------------------
Enemy* EnemyManager::GetEnemies(int i)
{
	return mEnemies[i].get();
}

//----------------------------------------------
// 概要：敵の数を渡す
// 戻り値(int)：敵の数
//-----------------------------------------------
int EnemyManager::GetEnemyNum() const
{
	return mEnemyNum;
}
