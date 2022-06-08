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
* @brief �摜�̑J��
* @author SpriteBatch
* @date 0000/00/00
* @details �摜�̑J�ڗp
*/

#pragma once
#include <stdexcept>
#include <PrimitiveBatch.h>
#include <wrl/client.h>
#include <SimpleMath.h>
#include <VertexTypes.h>

/**
* @brief AnimatedTexture�̃N���X
* @details �摜�̑J�ڂ̃N���X
*/
class AnimatedTexture
{
public:
    /**
    * @brief �R���X�g���N�^
    * @details �摜�J�ڃN���X�̃R���X�g���N�^
    */
    AnimatedTexture() noexcept;

    /**
    * @brief �R���X�g���N�^
    * @param (rotation) ��]
    * @param (scale) �傫��
    * @param (depth) �[�x
    * @details �摜�J�ڃN���X�̃R���X�g���N�^
    */
    AnimatedTexture(
        const DirectX::SimpleMath::Vector2& origin,
        float rotation,
        float scale,
        float depth
    );

    /**
    * @brief �R�s�[�R���X�g���N�^
    * @details �摜�J�ڃN���X�̃R���X�g���N�^
    */
    AnimatedTexture(AnimatedTexture&&) = default;
    AnimatedTexture& operator= (AnimatedTexture&&) = default;
    
    /**
    * @brief �R�s�[�R���X�g���N�^
    * @details �摜�J�ڃN���X�̃R���X�g���N�^
    */
    AnimatedTexture(AnimatedTexture const&) = default;
    AnimatedTexture& operator= (AnimatedTexture const&) = default;

    /**
    * @brief �摜�����[�h����
    * @param (texture) �摜���
    * @param (frameCount) �t���[����
    * @param (framePerSecond) �P�t���[��������̕b��
    */
    void Load(ID3D11ShaderResourceView* texture, int frameCount, int framesPerSecond);

    /**
    * @brief �摜�̍X�V
    * @param (elapsed) �b��
    */
    void Update(float elapsed);

    /**
    * @brief �摜��`�悷��
    * @param (batch) �X�v���C�g�o�b�`
    * @param (screenPos) �摜���o���ꏊ
    */
    void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* batch, const DirectX::SimpleMath::Vector2& screenPos) const;

    /**
    * @brief �摜��`�悷��
    * @param (batch) �X�v���C�g�o�b�`
    * @param (frame) �t���[��
    * @param (screenPos) �摜���o���ꏊ
    */
    void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* batch, int frame, const DirectX::SimpleMath::Vector2& screenPos) const;
  
    /**
    * @brief ���Z�b�g����
    */
    void Reset();

    /**
    * @brief �~�߂�
    */
    void Stop();

    /**
    * @brief ������
    */
    void Play();
    /**
    * @brief �~�߂�
    */
    void Paused();

    /**
    * @brief �~�܂��Ă��邩
    */
    bool IsPaused() const;

private:
    //! �~�߂�
    bool mPaused;
    
    //! �t���[��
    int mFrame;
    
    //! �t���[����
    int mFrameCount;

    //! �摜�̉���
    int mTextureWidth;
    
    //! �摜�̏c��
    int mTextureHeight;

    //! 1�t���[��������̎���
    float mTimePerFrame;

    //! ���o�ߎ���
    float mTotalElapsed;
    
    //! �[�x
    float mDepth;
    
    //! ��]
    float mRotation;
    
    //! ���S���W
    DirectX::SimpleMath::Vector2 mOrigin;
    
    //! �傫��
    DirectX::SimpleMath::Vector2 mScale;
    
    //! �摜���
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;
};