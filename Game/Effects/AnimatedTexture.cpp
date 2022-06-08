/**
* @file AnimatedTexture.cpp
* @brief 画像の遷移
* @author SpriteBatch
* @date 0000/00/00
* @details 画像の遷移用
*/
#include "pch.h"
#include "AnimatedTexture.h"

//--------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
// 戻り値：なし
//--------------------------------------------------------
AnimatedTexture::AnimatedTexture() noexcept:
    mPaused(false),
    mFrame(0),
    mFrameCount(0),
    mTextureWidth(0),
    mTextureHeight(0),
    mTimePerFrame(0.f),
    mTotalElapsed(0.f),
    mDepth(0.f),
    mRotation(0.f),
    mOrigin{},
    mScale(1.f, 1.f)
{
}

//--------------------------------------------------------
// 概要：コンストラクタ
// 引数 (origin)：中心
// 引数 (rotation)：回転
// 引数 (scale)：大きさ
// 引数 (depth)：深度
// 戻り値：なし
//--------------------------------------------------------
AnimatedTexture::AnimatedTexture(
    const DirectX::SimpleMath::Vector2& origin,
    float rotation,
    float scale,
    float depth
):
    mPaused(false),
    mFrame(0),
    mFrameCount(0),
    mTextureWidth(0),
    mTextureHeight(0),
    mTimePerFrame(0.f),
    mTotalElapsed(0.f),
    mDepth(depth),
    mRotation(rotation),
    mOrigin(origin),
    mScale(scale, scale)
{
}

//--------------------------------------------------------
// 概要：画像をロードする
// 引数 (texture)：画像情報
// 引数 (frameCount)：フレーム数
// 引数 (framePerSecond)：１フレームあたりの時間
// 戻り値：なし
//--------------------------------------------------------
void AnimatedTexture::Load(ID3D11ShaderResourceView* texture, int frameCount, int framesPerSecond)
{
    if (frameCount < 0 || framesPerSecond <= 0)
        throw std::invalid_argument("AnimatedTexture");

    mPaused = false;
    mFrame = 0;
    mFrameCount = frameCount;
    mTimePerFrame = 1.f / float(framesPerSecond);
    mTotalElapsed = 0.f;
    mTexture = texture;

    if (texture)
    {
        Microsoft::WRL::ComPtr<ID3D11Resource> resource;
        texture->GetResource(resource.GetAddressOf());

        D3D11_RESOURCE_DIMENSION dim;
        resource->GetType(&dim);

        if (dim != D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            throw std::runtime_error("AnimatedTexture expects a Texture2D");

        Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D;
        resource.As(&tex2D);

        D3D11_TEXTURE2D_DESC desc;
        tex2D->GetDesc(&desc);

        mTextureWidth = int(desc.Width);
        mTextureHeight = int(desc.Height);
    }
}

//--------------------------------------------------------
// 概要：更新
// 引数 (elapsed)：秒数
// 戻り値：なし
//--------------------------------------------------------
void AnimatedTexture::Update(float elapsed)
{
    if (mPaused)
        return;

    mTotalElapsed += elapsed;

    if (mTotalElapsed > mTimePerFrame)
    {
        ++mFrame;
        mFrame = mFrame % mFrameCount;
        mTotalElapsed -= mTimePerFrame;
    }
}

//--------------------------------------------------------
// 概要：画像を描画する
// 引数 (batch)：スプライトバッチ
// 引数 (screenPos)：画像の位置
// 戻り値：なし
//--------------------------------------------------------
void AnimatedTexture::Draw(
    DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* batch,
    const DirectX::SimpleMath::Vector2& screenPos
) const
{
    Draw(batch, mFrame, screenPos);
}

//--------------------------------------------------------
// 概要：画像を描画する
// 引数 (batch)：スプライトバッチ
// 引数 (frame)：フレーム
// 引数 (screenPos)：画像の座標
// 戻り値：なし
//--------------------------------------------------------
void AnimatedTexture::Draw(
    DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* batch,
    int frame,
    const DirectX::SimpleMath::Vector2& screenPos
) const
{
    int frameWidth = mTextureWidth / mFrameCount;

    RECT sourceRect;
    sourceRect.left = frameWidth * frame;
    sourceRect.top = 0;
    sourceRect.right = sourceRect.left + frameWidth;
    sourceRect.bottom = mTextureHeight;

    //batch->Draw()

 /*   batch->Draw(mTexture.Get(), screenPos, &sourceRect, DirectX::Colors::White,
        mRotation, mOrigin, mScale, DirectX::SpriteEffects_None, mDepth);*/
}

//--------------------------------------------------------
// 概要：リセットする
// 戻り値：なし
//--------------------------------------------------------
void AnimatedTexture::Reset()
{
    mFrame = 0;
    mTotalElapsed = 0.f;
}

//--------------------------------------------------------
// 概要：アニメーションを止めて初期位置へ
// 戻り値：なし
//--------------------------------------------------------
void AnimatedTexture::Stop()
{
    mPaused = true;
    mFrame = 0;
    mTotalElapsed = 0.f;
}

//--------------------------------------------------------
// 概要：アニメーションを動かす
// 戻り値：なし
//--------------------------------------------------------
void AnimatedTexture::Play()
{
    mPaused = false;
}

//--------------------------------------------------------
// 概要：アニメーションを止める
// 戻り値：なし
//--------------------------------------------------------
void AnimatedTexture::Paused()
{
    mPaused = true;
}
//--------------------------------------------------------
// 概要：アニメーションは止まっているか
// 戻り値 bool：止まっているか
//--------------------------------------------------------
bool AnimatedTexture::IsPaused() const
{
    return mPaused;
}
