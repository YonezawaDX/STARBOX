/**
* @file SelectButton.h
* @brief 選択されるボタン
* @author 米澤駿介
* @date 2022/04/26
* @details 選択されるボタンの描画と処理
*/
#pragma once
#include <SpriteBatch.h>
#include <StepTimer.h>
#include <CommonStates.h>
#include <vector>
#include "Libraries/MyLibraries/Letter.h"

/**
* @brief 選択されるボタンクラス
* @details 選択されるボタンの描画と処理
*/
class SelectButton
{
public:
    // 定数-----------------------------------------------------------------

    //! 小さいボタンのサイズ
    static const float BUTTON_SIZE_NORMAL;
    //! 大きいボタンのサイズ
    static const float BUTTON_SIZE_BIG;

    //! ボタンのX座標
    static const int BUTTON_POS_X;
    //! ボタン１のY座標
    static const int BUTTON_POS_Y_01;
    //! ボタン２のY座標
    static const int BUTTON_POS_Y_02;

    //----------------------------------------------------------------------
public:
    /**
    * @enum SELECT_TYPE
    * 選択されるボタン
    */
    enum class SELECT_TYPE
    {
        NONE,       //! なにもない
        OPERATE,    //! 操作状態
        BOSS01,     //! ボス01ボタン
        BOSS02      //! ボス02ボタン
    };

public:
    /**
    * @brief コンストラクタ
    */
    SelectButton();
    /**
    * @brief デストラクタ
    */
    ~SelectButton() = default;

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
    * @return SELECT_TYPE ボタンの選択状態
    */
    SELECT_TYPE GetSelectType() const;
private:
    //! セレクトタイプを取得
    SELECT_TYPE mSelectType;

    //! 文字を描画する変数
    std::vector<std::unique_ptr<Letter>> mBossLetter;
    
    //! ボタン1の拡大率
    float mButtonSize01;
    
    //! ボタン２の拡大率
    float mButtonSize02;
};