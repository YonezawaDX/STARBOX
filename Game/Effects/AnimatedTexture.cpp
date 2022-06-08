/**
* @file AnimatedTexture.cpp
* @brief �摜�̑J��
* @author SpriteBatch
* @date 0000/00/00
* @details �摜�̑J�ڗp
*/
#include "pch.h"
#include "AnimatedTexture.h"

//--------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
// �߂�l�F�Ȃ�
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
// �T�v�F�R���X�g���N�^
// ���� (origin)�F���S
// ���� (rotation)�F��]
// ���� (scale)�F�傫��
// ���� (depth)�F�[�x
// �߂�l�F�Ȃ�
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
// �T�v�F�摜�����[�h����
// ���� (texture)�F�摜���
// ���� (frameCount)�F�t���[����
// ���� (framePerSecond)�F�P�t���[��������̎���
// �߂�l�F�Ȃ�
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
// �T�v�F�X�V
// ���� (elapsed)�F�b��
// �߂�l�F�Ȃ�
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
// �T�v�F�摜��`�悷��
// ���� (batch)�F�X�v���C�g�o�b�`
// ���� (screenPos)�F�摜�̈ʒu
// �߂�l�F�Ȃ�
//--------------------------------------------------------
void AnimatedTexture::Draw(
    DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* batch,
    const DirectX::SimpleMath::Vector2& screenPos
) const
{
    Draw(batch, mFrame, screenPos);
}

//--------------------------------------------------------
// �T�v�F�摜��`�悷��
// ���� (batch)�F�X�v���C�g�o�b�`
// ���� (frame)�F�t���[��
// ���� (screenPos)�F�摜�̍��W
// �߂�l�F�Ȃ�
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
// �T�v�F���Z�b�g����
// �߂�l�F�Ȃ�
//--------------------------------------------------------
void AnimatedTexture::Reset()
{
    mFrame = 0;
    mTotalElapsed = 0.f;
}

//--------------------------------------------------------
// �T�v�F�A�j���[�V�������~�߂ď����ʒu��
// �߂�l�F�Ȃ�
//--------------------------------------------------------
void AnimatedTexture::Stop()
{
    mPaused = true;
    mFrame = 0;
    mTotalElapsed = 0.f;
}

//--------------------------------------------------------
// �T�v�F�A�j���[�V�����𓮂���
// �߂�l�F�Ȃ�
//--------------------------------------------------------
void AnimatedTexture::Play()
{
    mPaused = false;
}

//--------------------------------------------------------
// �T�v�F�A�j���[�V�������~�߂�
// �߂�l�F�Ȃ�
//--------------------------------------------------------
void AnimatedTexture::Paused()
{
    mPaused = true;
}
//--------------------------------------------------------
// �T�v�F�A�j���[�V�����͎~�܂��Ă��邩
// �߂�l bool�F�~�܂��Ă��邩
//--------------------------------------------------------
bool AnimatedTexture::IsPaused() const
{
    return mPaused;
}
