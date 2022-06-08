/**
* @file Object.h
* @brief �I�u�W�F�N�g�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �I�u�W�F�N�gIObject���p�����Ă���
*/
#pragma once
#include "IObject.h"

#include "Libraries/MyLibraries/Model3D.h"

#include "Libraries/MyLibraries/ResourceManager.h"
#include "DeviceResources.h"

/**
* @brief �I�u�W�F�N�g�̃N���X
* @details �I�u�W�F�N�g�̊��
*/
class Object : public IObject
{
public:
    /**
    * @brief �R���X�g���N�^
    */
    Object();

    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Object() override;

    // ��{����---------------------------------------------------
    
    /**
    * @brief ������
    * @return void �Ȃ�
    */
    virtual void Initialize() override;
    
    /**
    * @brief �X�V
    * @return void �Ȃ�
    */
    virtual void Update() override;
    
    /**
    * @brief �`��
    * @param (commonStates) �R�����X�e�C�g
    * @param (camera) �J����
    * @return void �Ȃ�
    */
    virtual void Draw(DirectX::CommonStates* commonStates, Camera* camera) override;
    
    /**
    * @brief �I������
    * @return void �Ȃ�
    */
    virtual void Finalize() override;
    // �Z�b�^�[�Q�b�^�[--------------------------------------------
    /**
    * @brief ���W�̃Q�b�^�[
    * @return Vector3 �I�u�W�F�N�g�̍��W
    */
    virtual DirectX::SimpleMath::Vector3 GetObjectPos() const override;
    /**
    * @brief ���W�̃Z�b�^�[
    * @param (pos) ���W
    * @return void �Ȃ�
    */
    virtual void SetObjectPos(const DirectX::SimpleMath::Vector3& pos) override;
private: // �ϐ�---------------------------------------------------
    
    //! �I�u�W�F�N�g�̍��W
    DirectX::SimpleMath::Vector3 mPos;
};

