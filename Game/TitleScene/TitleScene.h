/**
* @file TitleScene.h
* @brief タイトルシーン
* @author 米澤駿介
* @date 
* @details タイトルシーン
*/
#pragma once

#include <CommonStates.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include "../IScene.h"
#include "Game/GameMain.h"

#include "Game/Effects/Fade.h"

// 前方宣言
class Fade;
class Camera;
class TitlePlane;
class TitleObject;
class TitleBackground;

/**
* @brief タイトルシーンのクラス
* @details タイトルシーン
*/
class TitleScene : public IScene
{
public:
	/**
    * @enum TITLE_STATE
    * タイトルシーンの状態
    */
	enum class TITLE_STATE
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
	TitleScene();

	/**
	* @brief デストラクタ
	*/
	~TitleScene();

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
private:

	//! コモンステート
	std::unique_ptr<DirectX::CommonStates> mCommonState;
	//! スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	//! スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> mSpriteFont;
	//! カメラ
	std::unique_ptr<Camera> mCamera;
	//! テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;


	//! 飛行機モデル
	std::unique_ptr<TitlePlane> mpPlane;
	//! タイトルモデル
	std::unique_ptr<TitleObject> mpTitleObject;
	//! 背景モデル
	std::unique_ptr<TitleBackground> mpTitleBackground;

	//! フェードイン用クラス
	std::unique_ptr<Fade> mFade;

	//! タイトルの状態
	TITLE_STATE mState;
};