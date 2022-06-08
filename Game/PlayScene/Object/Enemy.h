/**
* @file Enemy.h
* @brief �G�̃N���X
* @author ���V�x��
* @date 2021/12/04
* @details �G
*/
#pragma once
#include "HeartObject.h"
#include "../BulletManager.h"
#include "../Collision.h"

/**
* @brief �G�̃N���X
* @details �P�̓G�𐶐�����
*/
class Enemy : public HeartObject
{
public:
    /**
    * @enum eEnemyrType
    * �G�̃^�C�v
    */
    enum class eEnemyType : int
    {
        NORMAL,		//! ����
        TRACK,		//! �ǔ�
        ROTATE		//! ��]
    };

public:
    /**
    * @brief �R���X�g���N�^
    */
	Enemy();

       /**
	* @brief �f�X�g���N�^
	*/
	~Enemy();

    // ��{����---------------------------------------------------
    
    /**
    * @brief ������
    * @return void �Ȃ�
    */
    void Initialize() override;

    /**
	* @brief ������
	* @param (modelType) �G�̃��f���̃^�C�v
    * @param (enemyType) �G�̎��
    * @param (pos) ���W
    * @param (angle) �p�x
    * @param (hp) �̗�
    * @param (pBulletManager) �e���˗p
	* @return void �Ȃ�
	*/
    void Initialize(
        Model3D* modelType,
        int enemyType,
        DirectX::SimpleMath::Vector3 pos,
        DirectX::SimpleMath::Vector3 angle,
        int hp,
        BulletManager* pBulletManager
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
    * @brief �����̃Q�b�^�[
    * @return Vector3 �I�u�W�F�N�g�̌���
    */
    DirectX::SimpleMath::Vector3 GetObjectDirection() const override;
    /**
	* @brief �����̃Z�b�^�[
	* @param (direction) ����
	* @return void �Ȃ�
	*/
    void SetObjectDirection(const DirectX::SimpleMath::Vector3& direction)override;

    /**
    * @brief �����̃Q�b�^�[
    * @return Vector3 �I�u�W�F�N�g�̑���
    */
    DirectX::SimpleMath::Vector3 GetObjectSpeed() const override;
    /**
	* @brief �����̃Z�b�^�[
	* @param (speed) ����
	* @return void �Ȃ�
	*/
    void SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed)override;

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
    * @brief HP�̃Q�b�^�[
    * @return int HP�̒l
    */
    int GetHP() const override;
    /**
    * @brief HP�̃Z�b�^�[
    * @param (hp) HP�̒l
    * @return void �Ȃ�
    */
    void SetHP(const int& hp) override;
private:

    //! �e�̊Ǘ��Ҋi�[�p
    BulletManager* mpBulletManager;

    //! �G�̎�ނ��i�[
    int mEnemyType;

    //! �e�̔��ˊԊu
    int mShotTimer;

};