/**
* @file BinaryFile.h
* @brief �o�C�i���t�@�C��
* @author ���V�x��
* @date
* @details �o�C�i���t�@�C�����Ǘ�
*/
#pragma once

#include <memory>

/**
* @brief �o�C�i���t�@�C���̃N���X
* @details �o�C�i���t�@�C��
*/
class BinaryFile
{
protected:

	//! �f�[�^
	std::unique_ptr<char[]> mData;

	//! �T�C�Y
	unsigned int mSize;

public:

	/**
	* @brief �t�@�C�������[�h
	* @param (fileName) �t�@�C����
	* @return BinaryFile �o�C�i���t�@�C��
	*/
	static BinaryFile LoadFile(const wchar_t* fileName);

	/**
	* @brief �R���X�g���N�^
	*/
	BinaryFile();

	/**
	* @brief ���[�u�R���X�g���N�^
	* @param (in) ���[�u����
	*/
	BinaryFile(BinaryFile&& in);

	/**
	* @brief �f�[�^���擾
	* @return char* �f�[�^
	*/
	char* GetData() { return mData.get(); }

	/**
	* @brief �T�C�Y���擾
	* @return unsigned int �T�C�Y
	*/
	unsigned int GetSize() { return mSize; }
};
