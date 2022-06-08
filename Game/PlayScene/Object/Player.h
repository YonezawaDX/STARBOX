/**
* @file Player.h
* @brief �v���C���[�̃N���X
* @author ���V�x��
* @date 2022/04/26
* @details �v���C���[�A�ړ�������e��������
*/
#pragma once
#include "HeartObject.h"

#include "Game/PlayScene/BulletManager.h"
#include "../Collision.h"

/**
* @brief Player�̃N���X
* @details Player
*/
class Player : public HeartObject
{
public:
    // �萔-------------------------------------------------
    
    //! �������W
    static const DirectX::SimpleMath::Vector3 START_POS;
    //! �̗�
    static const int HP;
    //! �����x
    static const float ACCELERATION;
    //! ����
    static const float ANGLE;
    //! �v���C���[���~�߂鑬�x
    static const float STOP_PLAYER;

    //! �����̍ŏ��l
    static const DirectX::SimpleMath::Vector3 LIMIT_SPEED_MIN;
    //! �����̍ő�l
    static const DirectX::SimpleMath::Vector3 LIMIT_SPEED_MAX;

    //! �ʒu�̍ŏ��l
    static const DirectX::SimpleMath::Vector3 LIMIT_POS_MIN;
    //! �ʒu�̍ő�l
    static const DirectX::SimpleMath::Vector3 LIMIT_POS_MAX;

    //! �V���b�g�̃C���^�[�o��
    static const int SHOT_INTERVAL;

public:

    /**
    * @enum PLAYER_MOVE
    * �v���C���[�����ǂ����Ă��邩���Ƃ�
    */
    enum class PLAYER_MOVE
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

public:
    
    /**
	* @brief �R���X�g���N�^
    * @param (pBulletManager) �e�̊Ǘ���
	*/
	Player(BulletManager* pBulletManager);
	
    /**
	* @brief �f�X�g���N�^
	*/
    ~Player();

    // ��{����---------------------------------------------------
    
    /**
    * @brief ������
    * @return void �Ȃ�
    */
    void Initialize() override;

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
    void Draw(DirectX::CommonStates* commonStates,Camera* camera) override;

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
    * @brief ����悤�֐�
    * @param (damage) �_���[�W�̒l
    * @return void �Ȃ�
    */
    void Damage(int damage);

    /**
    * @brief �e���˗p
    * @return void �Ȃ�
    */
    void Shot();

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
    void SetObjectDirection(const DirectX::SimpleMath::Vector3& direction) override;

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
    void SetObjectSpeed(const DirectX::SimpleMath::Vector3& speed) override;

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

private:// �ϐ�---------------------------------------------------------------
    //! �v���C���[�̈ړ��X�s�[�h
    DirectX::SimpleMath::Vector3 mPlayerSpeed;

    //! �v���C���[�̊p�x
    DirectX::SimpleMath::Vector3 mPlayerAngle;

    //! �ړ����Ă���t���O
    bool mPlayerMoveFlag;

    //! �e�ۂ̊Ǘ��҂ւ̃|�C���^
    BulletManager* mpBulletManager;

    //! �e�ۂ̔��ˊԊu
    int mShootIntervalTimer;

    //! �v���C���[�̍��W�ۑ��p
    DirectX::SimpleMath::Vector3 mPlayerPos;
};