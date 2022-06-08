/**
* @file SelectButton.h
* @brief �I�������{�^��
* @author ���V�x��
* @date 2022/04/26
* @details �I�������{�^���̕`��Ə���
*/
#pragma once
#include <SpriteBatch.h>
#include <StepTimer.h>
#include <CommonStates.h>
#include <vector>
#include "Libraries/MyLibraries/Letter.h"

/**
* @brief �I�������{�^���N���X
* @details �I�������{�^���̕`��Ə���
*/
class SelectButton
{
public:
    // �萔-----------------------------------------------------------------

    //! �������{�^���̃T�C�Y
    static const float BUTTON_SIZE_NORMAL;
    //! �傫���{�^���̃T�C�Y
    static const float BUTTON_SIZE_BIG;

    //! �{�^����X���W
    static const int BUTTON_POS_X;
    //! �{�^���P��Y���W
    static const int BUTTON_POS_Y_01;
    //! �{�^���Q��Y���W
    static const int BUTTON_POS_Y_02;

    //----------------------------------------------------------------------
public:
    /**
    * @enum SELECT_TYPE
    * �I�������{�^��
    */
    enum class SELECT_TYPE
    {
        NONE,       //! �Ȃɂ��Ȃ�
        OPERATE,    //! ������
        BOSS01,     //! �{�X01�{�^��
        BOSS02      //! �{�X02�{�^��
    };

public:
    /**
    * @brief �R���X�g���N�^
    */
    SelectButton();
    /**
    * @brief �f�X�g���N�^
    */
    ~SelectButton() = default;

	// ��{����---------------------------------------------------
    
    /**
    * @brief ������
    * @return void �Ȃ�
    */
    void Initialize();

    /**
    * @brief �X�V
    * @param (timer) ����
    * @return void �Ȃ�
    */
    void Update(DX::StepTimer timer);

    /**
    * @brief �`��
    * @param (commonStates) �R�����X�e�C�g
    * @param (camera) �J����
    * @return void �Ȃ�
    */
    void Draw(DirectX::CommonStates* commStates, DirectX::SpriteBatch* spriteBatch);

    /**
    * @brief �I������
    * @return void �Ȃ�
    */
    void Finalize();

    // �Q�b�^�[�A�Z�b�^�[-------------------------------------------
    
    /**
    * @brief �{�^���̑I����Ԃ̃Q�b�^�[
    * @return SELECT_TYPE �{�^���̑I�����
    */
    SELECT_TYPE GetSelectType() const;
private:
    //! �Z���N�g�^�C�v���擾
    SELECT_TYPE mSelectType;

    //! ������`�悷��ϐ�
    std::vector<std::unique_ptr<Letter>> mBossLetter;
    
    //! �{�^��1�̊g�嗦
    float mButtonSize01;
    
    //! �{�^���Q�̊g�嗦
    float mButtonSize02;
};