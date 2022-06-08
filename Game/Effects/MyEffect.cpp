/**
* @file MyEffect.cpp
* @brief エフェクト
* @author 米澤駿介
* @date
* @details エフェクト
*/
#include "pch.h"
#include "MyEffect.h"

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "Game/BinaryFile.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//----------------------------------------------------------
// 概要：初期化
// 引数 (life) :生存時間
// 引数 (pos): 座標
// 戻り値 void：なし
//---------------------------------------------------------
void MyEffect::Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity)
{
	mStartPosition = mPosition = pos;
	mStartVelocity = mVelocity = velocity;
	mStartLife = mLife = life;
	mGravity = Vector3(0, 0.001f, 0);
}
//----------------------------------------------------------
// 概要：更新
// 引数 (timer) :生存時間
// 戻り値 void : なし
//---------------------------------------------------------
void MyEffect::Update(DX::StepTimer timer)
{
	mTimer = timer;
	mLife -= (float)mTimer.GetElapsedSeconds();
}


