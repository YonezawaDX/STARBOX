/**
* @file Floor.h
* @brief 動く床のクラス
* @author 米澤駿介
* @date 2022/04/26
* @details 見た目だけ動く床
*/
#pragma once
#include "MoveObject.h"

/**
* @brief 動く床のクラス
* @details 動く床を生成する
*/
class Floor : public MoveObject
{
public:
    // 定数---------------------------------------------
    
    //! 動く速さ
    static const float MOVE_SPEED;

    //! 限界の座標
    static const float LIMIT_POS;

    //! 間の座標
    static const float OFFSET;


public:
    /**
    * @brief コンストラクタ
    */
    Floor();

    /**
    * @brief デストラクタ
    */
    ~Floor();

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

    /**
    * @brief 動き
    * @param なし
    * @return void なし
    */
    void Move() override;
    
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
    std::vector<std::unique_ptr<Model3D>> mpFloorModel3D;
};