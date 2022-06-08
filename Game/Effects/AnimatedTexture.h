//--------------------------------------------------------------------------------------
// File: AnimatedTexture.h
//
// C++ version of the C# example on how to animate a 2D sprite using SpriteBatch
// http://msdn.microsoft.com/en-us/library/bb203866.aspx
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------

/**
* @file AnimatedTexture.h
* @brief 画像の遷移
* @author SpriteBatch
* @date 0000/00/00
* @details 画像の遷移用
*/

#pragma once
#include <stdexcept>
#include <PrimitiveBatch.h>
#include <wrl/client.h>
#include <SimpleMath.h>
#include <VertexTypes.h>

/**
* @brief AnimatedTextureのクラス
* @details 画像の遷移のクラス
*/
class AnimatedTexture
{
public:
    /**
    * @brief コンストラクタ
    * @details 画像遷移クラスのコンストラクタ
    */
    AnimatedTexture() noexcept;

    /**
    * @brief コンストラクタ
    * @param (rotation) 回転
    * @param (scale) 大きさ
    * @param (depth) 深度
    * @details 画像遷移クラスのコンストラクタ
    */
    AnimatedTexture(
        const DirectX::SimpleMath::Vector2& origin,
        float rotation,
        float scale,
        float depth
    );

    /**
    * @brief コピーコンストラクタ
    * @details 画像遷移クラスのコンストラクタ
    */
    AnimatedTexture(AnimatedTexture&&) = default;
    AnimatedTexture& operator= (AnimatedTexture&&) = default;
    
    /**
    * @brief コピーコンストラクタ
    * @details 画像遷移クラスのコンストラクタ
    */
    AnimatedTexture(AnimatedTexture const&) = default;
    AnimatedTexture& operator= (AnimatedTexture const&) = default;

    /**
    * @brief 画像をロードする
    * @param (texture) 画像情報
    * @param (frameCount) フレーム数
    * @param (framePerSecond) １フレームあたりの秒数
    */
    void Load(ID3D11ShaderResourceView* texture, int frameCount, int framesPerSecond);

    /**
    * @brief 画像の更新
    * @param (elapsed) 秒数
    */
    void Update(float elapsed);

    /**
    * @brief 画像を描画する
    * @param (batch) スプライトバッチ
    * @param (screenPos) 画像を出す場所
    */
    void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* batch, const DirectX::SimpleMath::Vector2& screenPos) const;

    /**
    * @brief 画像を描画する
    * @param (batch) スプライトバッチ
    * @param (frame) フレーム
    * @param (screenPos) 画像を出す場所
    */
    void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* batch, int frame, const DirectX::SimpleMath::Vector2& screenPos) const;
  
    /**
    * @brief リセットする
    */
    void Reset();

    /**
    * @brief 止める
    */
    void Stop();

    /**
    * @brief 動かす
    */
    void Play();
    /**
    * @brief 止める
    */
    void Paused();

    /**
    * @brief 止まっているか
    */
    bool IsPaused() const;

private:
    //! 止める
    bool mPaused;
    
    //! フレーム
    int mFrame;
    
    //! フレーム数
    int mFrameCount;

    //! 画像の横幅
    int mTextureWidth;
    
    //! 画像の縦幅
    int mTextureHeight;

    //! 1フレームあたりの時間
    float mTimePerFrame;

    //! 総経過時間
    float mTotalElapsed;
    
    //! 深度
    float mDepth;
    
    //! 回転
    float mRotation;
    
    //! 中心座標
    DirectX::SimpleMath::Vector2 mOrigin;
    
    //! 大きさ
    DirectX::SimpleMath::Vector2 mScale;
    
    //! 画像情報
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;
};