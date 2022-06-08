/**
* @file GameMain.h
* @brief �Q�[�����C��
* @author ���V�x��
* @date 
* @details �Q�[���S�̂��Ǘ�
*/
#pragma once

#include <Keyboard.h>
#include <Mouse.h>
#include "StepTimer.h"

/**
* @enum GAME_SCENE
* �Q�[���̃V�[�����
*/
enum class GAME_SCENE : int
{
    NONE,       //! �Ȃ�

    TITLE,      //! �^�C�g��
    SELECT,     //! �Z���N�g
    PLAY,       //! �v���C
};

// �O���錾
class DebugCamera;
class IScene;


/**
* @brief �Q�[�����C���N���X
* @details Game�N���X����A���[�U���������𔲂��o�����N���X
*/
class GameMain
{
public:
    /**
	* @brief �R���X�g���N�^
	*/
    GameMain();

    /**
    * @brief �f�X�g���N�^
    */
    ~GameMain();
    
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
    void Update(const DX::StepTimer& timer);
    /**
    * @brief �`��
    * @return void �Ȃ�
    */
    void Render();
    /**
    * @brief �I������
    * @return void �Ȃ�
    */
    void Finalize();

	// �V�[���֌W����

    /**
    * @brief �V�[���̍쐬
    * @return void �Ȃ�
    */
	void CreateScene();

    /**
    * @brief �V�[���̍폜
    * @return void �Ȃ�
    */
	void DeleteScene();
private:

    //! �L�[�{�[�h
    std::unique_ptr<DirectX::Keyboard> mKeybord;

    //! �}�E�X
    std::unique_ptr<DirectX::Mouse> mMouse;

    //! ���̃V�[���ԍ�
    GAME_SCENE mNextScene;

    //! �V�[��
    IScene* mpScene;

};
