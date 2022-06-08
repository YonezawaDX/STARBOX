/**
* @file ResourceManager.cpp
* @brief ���\�[�X�}�l�[�W���[
* @author ���V�x��
* @date
* @details ���f����摜���Ǘ�����
*/
#include "pch.h"
#include "ResourceManager.h"
#include <WICTextureLoader.h>
#include <Effects.h>
#include "DeviceResources.h"

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
ResourceManager::ResourceManager()
{
}
//------------------------------------------------------------------
// �T�v�F�f�X�g���N�^
// �����F�Ȃ�
//-------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
	// ���ׂẴ��\�[�X�̍폜
	this->DeleteAllData();
}

//----------------------------------------------------
// �T�v�F������
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void ResourceManager::Initialize()
{
	this->DeleteAllData();
}

//------------------------------------------------------------------
// �T�v�F�I������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//------------------------------------------------------------------
void ResourceManager::Finalize()
{
	this->DeleteAllData();
}

//------------------------------------------------------------------
// �T�v�F�摜�̎擾
// ����(key)�F��
// �߂�l ID3D11ShaderResourceView*�F�摜
//------------------------------------------------------------------
ID3D11ShaderResourceView* ResourceManager::GetTexture(const std::string& key)
{
	return mTextureDB[key].Get();
}

//------------------------------------------------------------------
// �T�v�F���f���̎擾
// ����(key)�F��
// �߂�l Model*�F���f��
//------------------------------------------------------------------
DirectX::Model* ResourceManager::GetCmoModel(const std::string& key)
{
	return mCmoModelDB[key].get();
}

//-----------------------------------------------------------------------------
// �T�v�F�e�N�X�`���̓o�^
// ����(path): �e�N�X�`���̑��΃p�X(���C�h������)
// ����(key) : �e�N�X�`���̎��ʖ�(������)
// �߂�l void�F�Ȃ�
//-----------------------------------------------------------------------------
void ResourceManager::RegisterTexture(const wchar_t* path, const std::string& key)
{
	// �f�o�C�X���\�[�X�̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// �e�N�X�`���̓ǂݍ���	: SRV�̍쐬
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	DirectX::CreateWICTextureFromFile(
		device,
		path,
		nullptr,
		texture.ReleaseAndGetAddressOf()
	);

	// DB(Map)�Ƀe�N�X�`����ǉ�
	mTextureDB[key] = std::move(texture);
}

//-----------------------------------------------------------------------------
// �T�v�FCMO���f���̓o�^
// ����(path): CMO���f���̑��΃p�X(���C�h������)
// ����(key) : CMO���f���̎��ʖ�(������)
// �߂�l void : �Ȃ�
//-----------------------------------------------------------------------------
void ResourceManager::RegisterCmoModel(const wchar_t* path, const std::string& key)
{
	// �f�o�C�X���\�[�X�̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// ���f���̕ۑ��ꏊ����ێ�����C���X�^���X�̐���
	std::unique_ptr<DirectX::EffectFactory> factory = std::make_unique<DirectX::EffectFactory>(device);
	factory->SetDirectory(L"Resources/Models");

	// ���f���̃��[�h
	std::unique_ptr<DirectX::Model> model = DirectX::Model::CreateFromCMO(device, path, *factory);

	// DB(Map)�Ƀ��f����o�^
	mCmoModelDB[key] = std::move(model);
}

//----------------------------------------------------
// �T�v�F���ׂẴ��\�[�X���폜
// ���� : �Ȃ�
// �߂�l�F�Ȃ�
//----------------------------------------------------
void ResourceManager::DeleteAllData()
{
	mTextureDB.clear();
	mCmoModelDB.clear();
}