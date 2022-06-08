/**
* @file Model3D.h
* @brief ���f��3D�̃N���X
* @author ���V�x��
* @date 
* @details ���f�����ȈՓI�ɏo����悤�ɂ���
*/
#pragma once
#include <SimpleMath.h>
#include "StepTimer.h"
#include <CommonStates.h>
#include <Model.h>

// �O���錾
class Camera;
class FollowCamera;

/**
* @brief Model3D�̃N���X
* @details ���f�����ȈՓI�ɏo����悤�ɂ���
*/
class Model3D
{
public:
	// �֐�------------------------------------
	/**
	* @brief �R���X�g���N�^
	*/
	Model3D();
	/**
	* @brief �f�X�g���N�^
	*/
	~Model3D() = default;

	/**
	* @brief ������
	* @param (fileName) ���f���̃t�@�C����
	* @return void �Ȃ�
	*/
	void Initialize(const wchar_t* fileName);

	/**
	* @brief �`��
	* @param (commonStates) �R�����X�e�C�g
	* @param (world) ���[���h���W
	* @param (camera) �J����
	* @return void �Ȃ�
	*/
	void Draw(
		DirectX::CommonStates* commonStates,
		DirectX::SimpleMath::Matrix* world,
		Camera* camera
	);

	/**
	* @brief �I������
	* @return void �Ȃ�
	*/
	void Finalize();

	/**
	* @brief ���f����X��]�Z�b�g
	* @param (rotate) ��]��
	* @return void �Ȃ�
	*/
	void SetModelRotationX(float rotate) { mRotateX = rotate; }
	
	/**
	* @brief ���f����Y��]�Z�b�g
	* @param (rotate) ��]��
	* @return void �Ȃ�
	*/
	void SetModelRotationY(float rotate) { mRotateY = rotate; }
	
	/**
	* @brief ���f����Z��]�Z�b�g
	* @param (rotate) ��]��
	* @return void �Ȃ�
	*/
	void SetModelRotationZ(float rotate) { mRotateZ = rotate; }

	/**
	* @brief ���f����XYZ��]�Z�b�g
	* @param (rotate) ��]��
	* @return void �Ȃ�
	*/
	void SetModelRotation(DirectX::SimpleMath::Vector3 rotate) 
	{
		mRotateX = rotate.x;
		mRotateY = rotate.y;
		mRotateZ = rotate.z;
	}
	/**
	* @brief ���f���̉�]�����Z�b�g
	* @param (axis) ��
	* @return void �Ȃ�
	*/
	void SetModelAxis(DirectX::SimpleMath::Vector3 axis) { mAxis = axis; }
private:
	//! ���f��
	std::unique_ptr<DirectX::Model> mModel;

	//! ��]���̕ϐ�X
	float mRotateX;
	//! ��]���̕ϐ�Y
	float mRotateY;
	//! ��]���̕ϐ�Z
	float mRotateZ;

	//! ���f���̉�]��
	DirectX::SimpleMath::Vector3 mAxis;
};