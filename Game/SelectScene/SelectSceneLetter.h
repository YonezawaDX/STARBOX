/**
* @file SelectSceneLetter.h
* @brief セレクトシーンの文字を管理
* @author 米澤駿介
* @date 2022/04/26
* @details ボタンやシーンの文字を管理、描画
*/
#pragma once
#include "StepTimer.h"
#include "Libraries/MyLibraries/Letter.h"
#include <SpriteBatch.h>
#include <CommonStates.h>
#include <vector>

/**
* @brief セレクトシーンの文字を管理する    クラス
* @details ボタンやシーンの文字を管理、描画
*/
class SelectSceneLetter
{
public:
    /**
    * @enum SELECT_TYPE
    * 選択されるボタン
    */
    enum class SELECT_TYPE
    {
        NONE,       // なにもない
        OPERATE,    // 操作状態
        BOSS01,     // ボス01ボタン
        BOSS02      // ボス02ボタン
    };

public:
    /**
    * @brief コンストラクタ
    */
    SelectSceneLetter();
    /**
    * @brief デストラクタ
    */
    ~SelectSceneLetter() = default;

    // 基本処理---------------------------------------------------
    
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
    void Update(DX::StepTimer timer);

    /**
    * @brief 描画
    * @param (commonStates) コモンステイト
    * @param (camera) カメラ
    * @return void なし
    */
    void Draw(DirectX::CommonStates* commStates, DirectX::SpriteBatch* spriteBatch);

    /**
    * @brief 終了処理
    * @return void なし
    */
    void Finalize();

    // ゲッター、セッター-------------------------------------------
    
    /**
    * @brief ボタンの選択状態のゲッター
    * @param (num) セレクトしているものを取得
    * @return なし
    */
    void SetSelectType(int num);
private:

    //! 文字を描画する変数
    std::vector<std::unique_ptr<Letter>> mLetter;

    //! セレクトタイプを保存
    int mSelectType;
};