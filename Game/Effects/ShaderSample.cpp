/**
* @file ShaderSample.cpp
* @brief �G�t�F�N�g
* @author ���V�x��
* @date
* @details �G�t�F�N�g
*/
#include "pch.h"
#include "ShaderSample.h"

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "BinaryFile.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//----------------------------------------------------------
// �T�v�F������
// ���� (life) :��������
// ���� (pos): ���W
// �߂�l void�F�Ȃ�
//---------------------------------------------------------
void ShaderSample::Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity)
{
	mStartPosition = mPosition = pos;
	mStartVelocity = mVelocity = velocity;
	mStartLife = mLife = life;
	mGravity = Vector3(0, 0.001f, 0);
}
//----------------------------------------------------------
// �T�v�F�X�V
// ���� (timer) :��������
// �߂�l void : �Ȃ�
//---------------------------------------------------------
void ShaderSample::Update(DX::StepTimer timer)
{
	mTimer = timer;
	mLife -= (float)mTimer.GetElapsedSeconds();
}


