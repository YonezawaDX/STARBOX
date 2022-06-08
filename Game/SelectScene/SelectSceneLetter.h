/**
* @file SelectSceneLetter.h
* @brief �Z���N�g�V�[���̕������Ǘ�
* @author ���V�x��
* @date 2022/04/26
* @details �{�^����V�[���̕������Ǘ��A�`��
*/
#pragma once
#include "StepTimer.h"
#include "Libraries/MyLibraries/Letter.h"
#include <SpriteBatch.h>
#include <CommonStates.h>
#include <vector>

/**
* @brief �Z���N�g�V�[���̕������Ǘ�����    �N���X
* @details �{�^����V�[���̕������Ǘ��A�`��
*/
class SelectSceneLetter
{
public:
    /**
    * @enum SELECT_TYPE
    * �I�������{�^��
    */
    enum class SELECT_TYPE
    {
        NONE,       // �Ȃɂ��Ȃ�
        OPERATE,    // ������
        BOSS01,     // �{�X01�{�^��
        BOSS02      // �{�X02�{�^��
    };

public:
    /**
    * @brief �R���X�g���N�^
    */
    SelectSceneLetter();
    /**
    * @brief �f�X�g���N�^
    */
    ~SelectSceneLetter() = default;

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
    * @param (num) �Z���N�g���Ă�����̂��擾
    * @return �Ȃ�
    */
    void SetSelectType(int num);
private:

    //! ������`�悷��ϐ�
    std::vector<std::unique_ptr<Letter>> mLetter;

    //! �Z���N�g�^�C�v��ۑ�
    int mSelectType;
};