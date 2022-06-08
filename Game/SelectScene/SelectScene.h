/**
* @file SelectScene.h
* @brief セレクトシーン
* @author 米澤駿介
* @date 2022/04/26
* @details セレクトシーン
*/
#pragma once
#include <SimpleMath.h>
#include <CommonStates.h>
#include <Model.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include "../IScene.h"
#include "Game/GameMain.h"

// 前方宣言
class FollowCamera;
class IObject;
class BulletManager;
class Player;
class Fade;
class PostEffect;
class SelectButton;
class SelectSceneLetter;

/**
* @brief セレクトシーンのクラス
* @details セレクトシーン
*/
class SelectScene : public IScene
{
public:
	// 定数
	//! カメラ座標
	static const DirectX::SimpleMath::Vector3 CAMERA_POS;
public:
	/**
	* @enum SELECT_TRANS
	* セレクトシーンの遷移
	*/
	enum class SELECT_TRANS
	{
		NONE,		//! 何もない
		PLAY,		//! プレイ状態
		SELECT,		//! セレクト状態
		ANIMATION	//! シーンが切り替わる
	};

	/**
	* @enum SELECT_STATE
	* フェード用の遷移
	*/
	enum class SELECT_STATE
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
	SelectScene();

	/**
	* @brief デストラクタ
	*/
	~SelectScene();

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
	//! 背景
	std::unique_ptr<IObject> mpBackGround;
	//! 床
	std::unique_ptr<IObject> mpFloor;
	//! Fade
	std::unique_ptr<Fade> mpFade;

	//! 現在のFPS
	unsigned int mFps;


	//! ポストエフェクト用
	std::unique_ptr<PostEffect> mPostEffect;

	//! ポストエフェクトのカメラ座標
	DirectX::SimpleMath::Vector3 mPostCamera;

	//! プレイ画面、最初の大きさ
	DirectX::SimpleMath::Matrix mStartWindow;
	//! プレイ画面、最後の大きさ
	DirectX::SimpleMath::Matrix mEndWindow;

	//! プレイシーンへのカウンタ
	float mPlayCount;

	//! セレクトシーン内の遷移
	SELECT_TRANS mSelectTrans;

	//! セレクトシーンのボタン
	std::unique_ptr<SelectButton> mSelectButton;

	//! セレクトシーンの文字
	std::unique_ptr<SelectSceneLetter> mSelectSceneLetter;

	SELECT_STATE mState;

};