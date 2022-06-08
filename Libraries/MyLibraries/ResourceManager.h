/**
* @file ResourceManager.h
* @brief ���\�[�X�}�l�[�W���[
* @author ���V�x��
* @date
* @details ���f����摜���Ǘ�����
*/
#pragma once
#include <string>
#include <unordered_map>
#include <Model.h>

/**
* @brief ���\�[�X�}�l�[�W���[�̃N���X
* @details ���f����摜���Ǘ�����
*/
class ResourceManager
{
public:
	/**
	* @brief �C���X�^���X�̎擾
	* @return ResourceManager ���\�[�X�}�l�[�W���̃|�C���^
	*/
	static ResourceManager* GetInstance()
	{
		static ResourceManager instance;
		return &instance;
	}

private:
	//! �e�N�X�`���ێ��p�}�b�v
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mTextureDB;
	//! CMO�ێ��p�}�b�v
	std::unordered_map<std::string, std::unique_ptr<DirectX::Model>> mCmoModelDB;

private:
	/**
	* @brief �R���X�g���N�^
	*/
	ResourceManager();
	/**
	* @brief �f�X�g���N�^
	*/
	~ResourceManager();

	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param (InputManager&) �Q��
	*/
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;

	/**
	* @brief ���[�u�R���X�g���N�^
	* @param (InputManager&&) �Q��
	*/
	ResourceManager(const ResourceManager&&) = delete;
	ResourceManager& operator= (const ResourceManager&&) = delete;

public:
	/**
	* @brief ������
	* @return void �Ȃ�
	*/
	void Initialize();

    /**
    * @brief �I������
    * @return void �Ȃ�
    */
	void Finalize();

	/**
    * @brief �摜�̃Q�b�^�[
	* @param (key) ���\�[�X�̌�
	* @return ID3D11ShaderResourceView* �V�F�[�_���\�[�X
    */
	ID3D11ShaderResourceView* GetTexture(const std::string& key);

	/**
    * @brief ���f���̃Q�b�^�[
	* @param (key) ���\�[�X�̌�
	* @return Model* ���f��
    */
	DirectX::Model* GetCmoModel(const std::string& key);

	/**
	* @brief �摜�̓o�^
	* @param (path) ���\�[�X�̏ꏊ�̃p�X
	* @param (key) ���\�[�X�̌�
	* @return void �Ȃ�
	*/
	void RegisterTexture(const wchar_t* path, const std::string& key);

	/**
    * @brief ���f���̓o�^
	* @param (path) ���\�[�X�̏ꏊ�̃p�X
	* @param (key) ���\�[�X�̌�
	* @return void �Ȃ�
    */
	void RegisterCmoModel(const wchar_t* path, const std::string& key);

private:
	/**
	* @brief ���ׂẴ��\�[�X�̍폜
	* @return void �Ȃ�
	*/
	void DeleteAllData();
};