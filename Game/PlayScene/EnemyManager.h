/**
* @file EnemyManager.h
* @brief 敵の管理者
* @author 米澤駿介
* @date 2022/04/26
* @details 細かい敵を管理する
*/
#pragma once
#include "Game/PlayScene/Object/Enemy.h"
#include "Game/PlayScene/BulletManager.h"

/**
* @struct 敵のデータ
*/
struct EnemyData
{
	int mCount;				//! 出現時間
	int mEnemyNum;			//! 敵の種類
	
	float mPosX;			//! X座標
	float mPosY;			//! Y座標

	int mHP;				//! 体力
};

// 前方宣言
class Model3D;
class IObject;

/**
* @brief 敵の管理者クラス
* @details 細かい敵を管理する
*/
class EnemyManager
{
public:
	/**
	* @brief コンストラクタ
	*/
	EnemyManager();

	/**
	* @brief デストラクタ
	*/
	~EnemyManager();

	/**
	* @brief 初期化
	* @param (pBulletManager) 弾発射用
	* @return void なし
	*/
	void Initialize(BulletManager* pBulletManager);

	/**
	* @brief 更新
	* @return void なし
	*/
	void Update();

	/**
	* @brief ボスの更新
	* @param (enemyNum) 敵の種類
	* @param (pos) 座標
	* @param (angle) 角度
	* @param (hp) 体力　
	* @param (move) 動いているか
	* @return void なし
	*/
	void BossUpdate(
		int enemyNum,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 angle,
		int hp,
		bool move
		);

	/**
	* @brief 描画
	* @param (commonStates) コモンステイト
	* @param (camera) カメラ
	* @return void なし
	*/
	void Draw(DirectX::CommonStates* commonStates, Camera* camera);

	/**
	* @brief 終了
	* @return bool 終了しているか
	*/
	bool IsEnd();

	/**
	* @brief プレイヤーとの当たり判定
	* @param (pPlayer) プレイヤーのポインタ
	* @return void なし
	*/
	void CheckHitPlayer(IObject* pPlayer);

	/**
	* @brief csvを読み込む
	* @param (mapFile) ファイルの名前
	* @return bool 読み込みができたか
	*/
	bool LoadCSV(const wchar_t* mapFile);

	/**
	* @brief 敵の情報を渡す
	* @param (i) １つの敵の番号を取得
	* @return Enemy* １つの敵のポインタ
	*/
	Enemy* GetEnemies(int i);

	/**
	* @brief 敵の数を渡す
	* @return int 敵の数
	*/
	int GetEnemyNum() const;
private:
	//! 敵の配列
	std::vector<std::unique_ptr<Enemy>> mEnemies;

	//! 敵の数
	int mEnemyNum;

	//! 敵の数値を格納する配列
	std::vector<EnemyData> mEnemyData;

	//! 弾の管理者格納用
	BulletManager* mpBulletManager;

	//! 敵の出現時間
	int mTimer;

	//! 敵のモデル
	std::unique_ptr<Model3D> mpEnemyModel3D;
};