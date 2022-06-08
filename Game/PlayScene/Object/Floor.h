/**
* @file Floor.h
* @brief �������̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �����ڂ���������
*/
#pragma once
#include "MoveObject.h"

/**
* @brief �������̃N���X
* @details �������𐶐�����
*/
class Floor : public MoveObject
{
public:
    // �萔---------------------------------------------
    
    //! ��������
    static const float MOVE_SPEED;

    //! ���E�̍��W
    static const float LIMIT_POS;

    //! �Ԃ̍��W
    static const float OFFSET;


public:
    /**
    * @brief �R���X�g���N�^
    */
    Floor();

    /**
    * @brief �f�X�g���N�^
    */
    ~Floor();

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

    /**
    * @brief ����
    * @param �Ȃ�
    * @return void �Ȃ�
    */
    void Move() override;
    
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
    std::vector<std::unique_ptr<Model3D>> mpFloorModel3D;
};