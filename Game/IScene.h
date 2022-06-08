/**
* @file IScene.h
* @brief シーンのインターフェース
* @author 
* @date
* @details シーンのインターフェース
*/
#pragma once

#include "StepTimer.h"
#include "GameMain.h"

/**
* @brief シーンのインターフェースのクラス
* @details シーンのインターフェース
*/
class IScene
{
public:
	/**
	* @brief デストラクタ
	*/
	virtual ~IScene() = default;

	/**
	* @brief 初期化
	* @return void なし
	*/
	virtual void Initialize() = 0;

	/**
	* @brief 更新
	* @param (timer) 時間
	* @return GAME_SCENE ゲームのシーンを返す、変更
	*/
	virtual GAME_SCENE Update(const DX::StepTimer& timer) = 0;

	/**
	* @brief 描画
	* @return void なし
	*/
	virtual void Draw() = 0;

	/**
	* @brief 終了処理
	* @return void なし
	*/
	virtual void Finalize() = 0;
};