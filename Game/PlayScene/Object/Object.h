/**
* @file Object.h
* @brief オブジェクトのクラス
* @author 米澤駿介
* @date 2022/04/26
* @details オブジェクトIObjectを継承している
*/
#pragma once
#include "IObject.h"

#include "Libraries/MyLibraries/Model3D.h"

#include "Libraries/MyLibraries/ResourceManager.h"
#include "DeviceResources.h"

/**
* @brief オブジェクトのクラス
* @details オブジェクトの基盤
*/
class Object : public IObject
{
public:
    /**
    * @brief コンストラクタ
    */
    Object();

    /**
    * @brief デストラクタ
    */
    virtual ~Object() override;

    // 基本処理---------------------------------------------------
    
    /**
    * @brief 初期化
    * @return void なし
    */
    virtual void Initialize() override;
    
    /**
    * @brief 更新
    * @return void なし
    */
    virtual void Update() override;
    
    /**
    * @brief 描画
    * @param (commonStates) コモンステイト
    * @param (camera) カメラ
    * @return void なし
    */
    virtual void Draw(DirectX::CommonStates* commonStates, Camera* camera) override;
    
    /**
    * @brief 終了処理
    * @return void なし
    */
    virtual void Finalize() override;
    // セッターゲッター--------------------------------------------
    /**
    * @brief 座標のゲッター
    * @return Vector3 オブジェクトの座標
    */
    virtual DirectX::SimpleMath::Vector3 GetObjectPos() const override;
    /**
    * @brief 座標のセッター
    * @param (pos) 座標
    * @return void なし
    */
    virtual void SetObjectPos(const DirectX::SimpleMath::Vector3& pos) override;
private: // 変数---------------------------------------------------
    
    //! オブジェクトの座標
    DirectX::SimpleMath::Vector3 mPos;
};

