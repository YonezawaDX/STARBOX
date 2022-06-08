/**
* @file GameMain.h
* @brief ゲームメイン
* @author 米澤駿介
* @date 
* @details ゲーム全体を管理
*/
#pragma once

#include <Keyboard.h>
#include <Mouse.h>
#include "StepTimer.h"

/**
* @enum GAME_SCENE
* ゲームのシーンを列挙
*/
enum class GAME_SCENE : int
{
    NONE,       //! なし

    TITLE,      //! タイトル
    SELECT,     //! セレクト
    PLAY,       //! プレイ
};

// 前方宣言
class DebugCamera;
class IScene;


/**
* @brief ゲームメインクラス
* @details Gameクラスから、ユーザ処理部分を抜き出したクラス
*/
class GameMain
{
public:
    /**
	* @brief コンストラクタ
	*/
    GameMain();

    /**
    * @brief デストラクタ
    */
    ~GameMain();
    
    /**
    * @brief 初期化
    * @return void なし
    */
    void Initialize();
    /**
    * @brief 更新
    * @param (timer) 時間
    * @return void なし
    */
    void Update(const DX::StepTimer& timer);
    /**
    * @brief 描画
    * @return void なし
    */
    void Render();
    /**
    * @brief 終了処理
    * @return void なし
    */
    void Finalize();

	// シーン関係処理

    /**
    * @brief シーンの作成
    * @return void なし
    */
	void CreateScene();

    /**
    * @brief シーンの削除
    * @return void なし
    */
	void DeleteScene();
private:

    //! キーボード
    std::unique_ptr<DirectX::Keyboard> mKeybord;

    //! マウス
    std::unique_ptr<DirectX::Mouse> mMouse;

    //! 次のシーン番号
    GAME_SCENE mNextScene;

    //! シーン
    IScene* mpScene;

};
