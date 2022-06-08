/**
* @file UI.h
* @brief ユーザーインターフェース
* @author 米澤駿介
* @date
* @details UI(HP)を描画するクラス
*/
#pragma once
#include <CommonStates.h>
#include <SpriteBatch.h>

// 前方宣言
class Camera;

/**
* @brief ユーザーインターフェース
* @details UI(HP)を描画するクラス
*/
class UI
{
public:
	/**
	* @brief コンストラクタ
	*/
	UI();
	
	/**
	* @brief デストラクタ
	*/
	~UI();

	/**
	* @brief 初期化
	* @param (playerHP) プレイヤーの体力
	* @param (bossHP) ボスの体力
	* @return void なし
	*/
	void Initialize(int playerHp, int bossHp, int score);
	/**
	* @brief 更新
	* @param (playerHP) プレイヤーの体力
	* @param (bossHP) ボスの体力
	* @return void なし
	*/
	void Update(int playerHp, int bossHp, int score);

	/**
	* @brief 描画
	* @param (commonStates) コモンステイト
	* @param (camera) カメラ
	* @return void なし
	*/
	void Draw(DirectX::CommonStates* commonStates,DirectX::SpriteBatch* spriteBatch, Camera* camera);

	/**
	* @brief 終了処理
	* @return void なし
	*/
	void Finalize();

private:
	/**
	* @brief スコアの描画
	* @param (spriteBatch) 画像情報
	* @return void なし
	*/
	void DrawScore(DirectX::SpriteBatch* spriteBatch);
	
	/**
	* @brief ボスの体力の描画
	* @param (spriteBatch) 画像情報
	* @return void なし
	*/
	void DrawBossHP(DirectX::SpriteBatch* spriteBatch);
	
	/**
	* @brief プレイヤーの体力の描画
	* @param (spriteBatch) 画像情報
	* @return void なし
	*/
	void DrawPlayerHP(DirectX::SpriteBatch* spriteBatch);

private:
	//! プレイヤーのHP
	int mPlayerHP;
	//! ボスのHP
	int mBossHP;
	//! スコア
	int mScore;

	// ボスのパーツ画像(これはリソースマネージャーで持ってくる)
	// 各自リソースマネージャで持ってきた画像を表示
	// HPバー×２、スコアの数字(score0000010)←こんな感じ
};