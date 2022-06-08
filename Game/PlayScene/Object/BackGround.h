/**
* @file BackGround.h
* @brief �����Șr�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �v���C�V�[���̔w�i
*/
#pragma once
#include "Object.h"

/**
* @brief �v���C�V�[���̔w�i�̃N���X
* @details �w�i��`�悷��i�j
*/
class BackGround : public Object
{
public:
    /**
    * @brief �R���X�g���N�^
    */
    BackGround();

    /**
    * @brief �f�X�g���N�^
    */
	~BackGround();

    // ��{����---------------------------------------------------
    
    /**
    * @brief ������
    * @param �Ȃ�
    * @return void �Ȃ�
    */
    void Initialize() override;
	
    /**
	* @brief �X�V
	* @param �Ȃ�
	* @return void �Ȃ�
	*/
    void Update() override;
    
    /**
    * @brief �`��
    * @param (commonStates) �R�����X�e�C�g
    * @param (camera) �J����
    * @return void �Ȃ�
    */
    void Draw(DirectX::CommonStates* commonStates, Camera* camera) override;

    /**
    * @brief �I������
    * @param �Ȃ�
    * @return void �Ȃ�
    */
    void Finalize() override;
    
    // �Z�b�^�[�Q�b�^�[--------------------------------------------
    
    /**
    * @brief ���W�̃Q�b�^�[
    * @return Vector3 �I�u�W�F�N�g�̍��W
    */
    DirectX::SimpleMath::Vector3 GetObjectPos() const override;
    /**
	* @brief ���W�̃Z�b�^�[
	* @param (pos) ���W
	* @return void �Ȃ�
	*/
    void SetObjectPos(const DirectX::SimpleMath::Vector3& pos) override;

private: // �ϐ�---------------------------------------------------
    
    //! ���f��
    DirectX::Model* mpModel;
};