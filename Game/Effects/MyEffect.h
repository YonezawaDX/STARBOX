/**
* @file MyEffect.h
* @brief �G�t�F�N�g
* @author ���V�x��
* @date
* @details �G�t�F�N�g	
*/
#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

/**
* @brief �G�t�F�N�g�̃N���X
* @details �G�t�F�N�g
*/
class MyEffect
{
public:
	/**
	* @brief ������
	* @param (life) ��������
	* @param (pos) ���W
	* @return void �Ȃ�
	*/
	void Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity);
	/**
	* @brief �X�V
	* @param (timer) ����
	* @return void �Ȃ�
	*/
	void Update(DX::StepTimer timer);

	/**
	* @brief ���W�̃Q�b�^�[
	* @return Vector3 ���W
	*/
	DirectX::SimpleMath::Vector3 GetPosition() { return mPosition; }
	
	/**
	* @brief �x���V�e�B�̃Q�b�^�[
	* @return Vector3 �x���V�e�B
	*/
	DirectX::SimpleMath::Vector3 GetVelocity() { return mVelocity; }
private:

	//! ����
	DX::StepTimer                           mTimer;

	//! �d��
	DirectX::SimpleMath::Vector3		mGravity;
	//! ���W
	DirectX::SimpleMath::Vector3		mPosition;
	
	//! �x���V�e�B
	DirectX::SimpleMath::Vector3		mVelocity;
	
	//! ��������
	float								mLife;

	//! �J�n�ʒu
	DirectX::SimpleMath::Vector3		mStartPosition;
	
	//! �J�n�x���V�e�B
	DirectX::SimpleMath::Vector3		mStartVelocity;
	
	//! �J�n��������
	float								mStartLife;

};