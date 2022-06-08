/**
* @file Bullet.h
* @brief �e�̃N���X
* @author ���V�x��
* @date 2021/12/01
* @details �e
*/
#pragma once
#include "MoveObject.h"
#include "../Collision.h"

/**
* @brief �e�̃N���X
* @details �P�̒e�𐶐�����
*/
class Bullet : public MoveObject
{
public:

    /**
    * @enum eShooterType
    * ���˂���G���e�B�e�B
    */
    enum class eShooterType : int
    {
        PLAYER_SHOT,        //! 0
        ENEMY_SHOT,         //! 1
        BOSS_SHOT           //! 2
    };
public:

	/**
	* @brief �R���X�g���N�^
	*/
	Bullet();

    /**
	* @brief �f�X�g���N�^
	*/
	~Bullet();

    // ��{����---------------------------------------------------
   
    /**
    * @brief ������
    * @return void �Ȃ�
    */
    void Initialize() override;
    
    /**
	* @brief ������
	* @param (bulletType) �e�̃^�C�v
    * @param (shooterType) �e���g���҂̎��
    * @param (pos) ���W
    * @param (angle) �p�x
	* @return void �Ȃ�
	*/
    void Initialize(
        Model3D* bulletType,
        int shooterType,
        DirectX::SimpleMath::Vector3 pos,
        DirectX::SimpleMath::Vector3 angle
    );

    /**
    * @brief �X�V
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
    * @return void �Ȃ�
    */
    void Finalize() override;

    /**
    * @brief ����悤�֐�
    * @return void �Ȃ�
    */
    void Move() override;

    /**
    * @brief �_���[�W�֐�
    * @param (damage) �_���[�W�̒l
    * @return void �Ȃ�
    */
    void Damage(int damage);

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

    /**
    * @brief �g�p��Ԃ̃Q�b�^�[
    * @return bool �g�p���
    */
    bool GetActive() const override;
    /**
    * @brief �g�p��Ԃ̃Z�b�^�[
    * @param (active) �g�p���
    * @return void �Ȃ�
    */
    void SetActive(const bool& active) override;

    /**
    * @brief �e�̎�ނ̃Q�b�^�[
    * @return int �e�̎��
    */
    eShooterType GetShooterType() const;
    /**
    * @brief �e�̎�ނ̃Z�b�^�[
    * @param (type) �e�̎��
    * @return void �Ȃ�
    */
    void SetShooterType(const eShooterType type);

private:
    //! ���f���̃|�C���^�i�[�p
    Model3D* mpBulletModel3D;

    //! ShooterType�i�[�p
    eShooterType mShooterType;

    //! ���ˎ��̊p�x��ۑ�����
    DirectX::SimpleMath::Vector3 mBulletAnglePos;

    //! �g�p���t���O
    bool mIsActive;
};