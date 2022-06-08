/**
* @file FollowCamera.h
* @brief �Ǐ]�J����
* @author
* @date
* @details �Ǐ]�J����
*/
#pragma once
#include "Camera.h"
#include <SimpleMath.h>

/**
* @brief �Ǐ]�J�����̃N���X
* @details �Ǐ]�J����
*/
class FollowCamera :public Camera
{
public:
	//! �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;	
	
	//! ���_�ƒ����_
	static const DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC; 

	//! �v���C���[���n�ʂɂ���Ƃ��̎��_
	static const float POINT_OF_VIEW_WORK;		
	
	//! �v���C���[�����ł���Ƃ��̎��_
	static const float POINT_OF_VIEW_BOOST;		

public:
	/**
	* @brief �R���X�g���N�^
	*/
	FollowCamera();

	/**
	* @brief �f�X�g���N�^
	*/
	~FollowCamera();

	/**
	* @brief �X�V
	* @return void �Ȃ�
	*/
	void Update() override;

	//-------------------------------------------------------

	/**
	* @brief �r���[�s��̃Z�b�^�[
	* @param (view) �r���[�s��
	* @return void �Ȃ�
	*/
	void SetViewMatrix(const DirectX::SimpleMath::Matrix &view) override { Camera::SetViewMatrix(view); }
	/**
    * @brief �r���[�s��̃Q�b�^�[
    * @return Matrix �r���[�s��
    */
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return Camera::GetViewMatrix(); }

	/**
	* @brief �v���W�F�N�V�����s��̃Z�b�^�[
	* @param (view) �v���W�F�N�V�����s��
	* @return void �Ȃ�
	*/
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix &projection) override { Camera::SetProjectionMatrix(projection); }
	/**
	* @brief �v���W�F�N�V�����s��̃Q�b�^�[
	* @return Matrix �v���W�F�N�V�����s��
	*/
	DirectX::SimpleMath::Matrix GetProjectionMatrix() const override { return Camera::GetProjectionMatrix(); }

	/**
	* @brief Eye���W�̃Z�b�^�[
	* @param (eye) Eye���W
	* @return void �Ȃ�
	*/
	void SetEyePosition(const DirectX::SimpleMath::Vector3 &eye) override { Camera::SetEyePosition(eye); }
	/**
	* @brief Eye���W�̃Q�b�^�[
	* @return Vector3 �A�C���W
	*/
	DirectX::SimpleMath::Vector3 GetEyePosition() const override { return Camera::GetEyePosition(); }

	/**
	* @brief �^�[�Q�b�g���W�̃Z�b�^�[
	* @param (target) �^�[�Q�b�g���W
	* @return void �Ȃ�
	*/
	void SetTargetPosition(const DirectX::SimpleMath::Vector3 &target) override { Camera::SetTargetPosition(target); }
	/**
	* @brief �^�[�Q�b�g���W�̃Q�b�^�[
	* @return Vector3 �^�[�Q�b�g���W
	*/
	DirectX::SimpleMath::Vector3 GetTargetPosition() const override { return Camera::GetTargetPosition(); }

	/**
	* @brief ������x�N�g���̃Z�b�^�[
	* @param (up) ������x�N�g��
	* @return void �Ȃ�
	*/
	void SetUpVector(const DirectX::SimpleMath::Vector3 &up) override { Camera::SetUpVector(up); }
	/**
	* @brief ������x�N�g���̃Q�b�^�[
	* @return Vector3 ������x�N�g��
	*/
	DirectX::SimpleMath::Vector3 GetUpVector() const override { return Camera::GetUpVector(); }

	/**
	* @brief �Q�Ǝ��_�̃Z�b�^�[
	* @param (refeye) �Q�Ǝ��_
	* @return void �Ȃ�
	*/
	void SetRefEyePosition(const DirectX::SimpleMath::Vector3 &refeye){ mRefEye = refeye; }
	/**
	* @brief �Q�Ǝ��_�̃Q�b�^�[
	* @return Vector3 �Q�Ǝ��_
	*/
	void SetRefTargetPosition(const DirectX::SimpleMath::Vector3 &reftarget) { mRefTarget = reftarget; }

	/**
	* @brief �J�����̊p�x�̃Q�b�^�[
	* @return float �J�����̊p�x
	*/
	float GetCameraRot() const { return mCameraRot; }

protected:

	/**
	* @brief �r���[�s��̎Z�o
	* @return void �Ȃ�
	*/
	virtual void CalculateViewMatrix();

	/**
	* @brief �v���W�F�N�V�����s��̎Z�o
	* @return void �Ȃ�
	*/
	virtual void CalculateProjectionMatrix();
private:

	//! �Q�Ǝ��_
	DirectX::SimpleMath::Vector3 mRefEye;

	//! �Q�ƒ����_
	DirectX::SimpleMath::Vector3 mRefTarget;

	//! ��]�l
	float mCameraRot;
};
