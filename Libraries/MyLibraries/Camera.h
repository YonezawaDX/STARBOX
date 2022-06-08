/**
* @file Camera.h
* @brief �J����
* @author 
* @date 
* @details �J����
*/
#pragma once

#include <SimpleMath.h>

/**
* @brief �J�����̃N���X
* @details �J����
*/
class Camera
{
public:
	
	//! �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;	

public:
	/**
	* @brief �R���X�g���N�^
	*/
	Camera();

	/**
	* @brief �f�X�g���N�^
	*/
	~Camera();

	/**
	* @brief �X�V
	* @return void �Ȃ�
	*/
	virtual void Update();
	
	//----------------------------------------------------------------------------------------------------

	/**
	* @brief �r���[�s��̃Z�b�^�[
	* @param (view) �r���[�s��
	* @return void �Ȃ�
	*/
	virtual void SetViewMatrix(const DirectX::SimpleMath::Matrix &view) { mView = view; }
	/**
    * @brief �r���[�s��̃Q�b�^�[
    * @return Matrix �r���[�s��
    */
	virtual DirectX::SimpleMath::Matrix GetViewMatrix() const { return mView; }

	/**
	* @brief �v���W�F�N�V�����s��̃Z�b�^�[
	* @param (view) �v���W�F�N�V�����s��
	* @return void �Ȃ�
	*/
	virtual void SetProjectionMatrix(const DirectX::SimpleMath::Matrix &projection) { mProjection = projection; }
	/**
	* @brief �v���W�F�N�V�����s��̃Q�b�^�[
	* @return Matrix �v���W�F�N�V�����s��
	*/
	virtual DirectX::SimpleMath::Matrix GetProjectionMatrix() const { return mProjection; }

	/**
	* @brief Eye���W�̃Z�b�^�[
	* @param (eye) Eye���W
	* @return void �Ȃ�
	*/
	virtual void SetEyePosition(const DirectX::SimpleMath::Vector3 &eye) { mEye = eye; }
	/**
	* @brief Eye���W�̃Q�b�^�[
	* @return Vector3 �A�C���W
	*/
	virtual DirectX::SimpleMath::Vector3 GetEyePosition() const { return mEye; }

	/**
	* @brief �^�[�Q�b�g���W�̃Z�b�^�[
	* @param (target) �^�[�Q�b�g���W
	* @return void �Ȃ�
	*/
	virtual void SetTargetPosition(const DirectX::SimpleMath::Vector3 &target) { mTarget = target; }
	/**
	* @brief �^�[�Q�b�g���W�̃Q�b�^�[
	* @return Vector3 �^�[�Q�b�g���W
	*/
	virtual DirectX::SimpleMath::Vector3 GetTargetPosition() const { return mTarget; }

	/**
	* @brief ������x�N�g���̃Z�b�^�[
	* @param (up) ������x�N�g��
	* @return void �Ȃ�
	*/
	virtual void SetUpVector(const DirectX::SimpleMath::Vector3 &up) { mUp = up; }
	/**
	* @brief ������x�N�g���̃Q�b�^�[
	* @return Vector3 ������x�N�g��
	*/
	virtual DirectX::SimpleMath::Vector3 GetUpVector() const { return mUp; }

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

	//! �r���[�s��
	DirectX::SimpleMath::Matrix mView;

	//! �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix mProjection;

	//! �J�������W
	DirectX::SimpleMath::Vector3 mEye;

	//! �����_
	DirectX::SimpleMath::Vector3 mTarget;

	//! ������x�N�g��
	DirectX::SimpleMath::Vector3 mUp;

};
