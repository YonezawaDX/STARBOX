/**
* @file BackGround.h
* @brief 小さな腕のクラス
* @author 米澤駿介
* @date 2022/04/26
* @details プレイシーンの背景
*/
#pragma once
#include "Object.h"

/**
* @brief プレイシーンの背景のクラス
* @details 背景を描画する（）
*/
class BackGround : public Object
{
public:
    /**
    * @brief コンストラクタ
    */
    BackGround();

    /**
    * @brief デストラクタ
    */
	~BackGround();

    // 基本処理---------------------------------------------------
    
    /**
    * @brief 初期化
    * @param なし
    * @return void なし
    */
    void Initialize() override;
	
    /**
	* @brief 更新
	* @param なし
	* @return void なし
	*/
    void Update() override;
    
    /**
    * @brief 描画
    * @param (commonStates) コモンステイト
    * @param (camera) カメラ
    * @return void なし
    */
    void Draw(DirectX::CommonStates* commonStates, Camera* camera) override;

    /**
    * @brief 終了処理
    * @param なし
    * @return void なし
    */
    void Finalize() override;
    
    // セッターゲッター--------------------------------------------
    
    /**
    * @brief 座標のゲッター
    * @return Vector3 オブジェクトの座標
    */
    DirectX::SimpleMath::Vector3 GetObjectPos() const override;
    /**
	* @brief 座標のセッター
	* @param (pos) 座標
	* @return void なし
	*/
    void SetObjectPos(const DirectX::SimpleMath::Vector3& pos) override;

private: // 変数---------------------------------------------------
    
    //! モデル
    DirectX::Model* mpModel;
};