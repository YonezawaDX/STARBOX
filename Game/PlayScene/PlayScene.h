/**
* @file PlayScene.h
* @brief プレイシーン
* @author 米澤駿介
* @date
* @details プレイシーン
*/
#pragma once

#include <CommonStates.h>
#include <Model.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include "../IScene.h"
#include "Game/GameMain.h"

// 前方宣言
class FollowCamera;
class Boss;
class Boss02;
class IObject;
class BulletManager;
class EnemyManager;
class Player;
class UI;
class Fade;

/**
* @brief プレイシーンのクラス
* @details プレイシーン
*/
class PlayScene : public IScene
{
public:
	/**
	* @enum PLAY_STATE
	* フェード用の遷移
	*/
	enum class PLAY_STATE
	{
		//! なし
		NONE,
		//! 画面が開ききるまでの間
		START,
		//! 操作待機
		PLAY,
		//! 次に行く
		NEXT_SCENE
	};
public:

	/**
	* @brief コンストラクタ
	*/
	PlayScene();

	/**
	* @brief デストラクタ
	*/
	~PlayScene();

	/**
	* @brief 初期化
	* @return void なし
	*/
	void Initialize() override;

	/**
	* @brief 更新
	* @param (timer) 時間
	* @return GAME_SCENE ゲームのシーンを返す、変更
	*/
	GAME_SCENE Update(const DX::StepTimer& timer) override;

	/**
	* @brief 描画
	* @return void なし
	*/
	void Draw() override;

	/**
	* @brief 終了処理
	* @return void なし
	*/
	void Finalize() override;

	/**
	* @brief リソース読み込み
	* @return void なし
	*/
	void ResourcesRegister();

private:

	//! コモンステート
	std::unique_ptr<DirectX::CommonStates> mCommonState;
	//! スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	//! スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> mSpriteFont;

	//! デバッグカメラ
	std::unique_ptr<FollowCamera> mCamera;

	//! プレイヤー
	std::unique_ptr<Player> mpPlayer;
	//! 弾丸の管理
	std::unique_ptr<BulletManager> mpBulletManager;
	//! 敵の管理
	std::unique_ptr<EnemyManager> mpEnemyManager;
	//! 背景
	std::unique_ptr<IObject> mpBackGround;
	//! 床
	std::unique_ptr<IObject> mpFloor;
	
	//! ボス
	std::unique_ptr<Boss> mpBoss;
	//! ボス
	std::unique_ptr<Boss02> mpBoss02;
	//! UI
	std::unique_ptr<UI> mpUI;

	//! Fade
	std::unique_ptr<Fade> mpFade;
	
	//! プレイシーンのステート
	PLAY_STATE mState;

	//! 現在のFPS
	unsigned int mFps;
};