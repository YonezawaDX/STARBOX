/**
* @file File.h
* @brief �t�@�C���Ǘ�
* @author ���V�x��
* @date 
* @details �t�@�C�����Ǘ�
*/
#pragma once

#include <fstream>
/**
* @brief �t�@�C���Ǘ��̃N���X
* @details File
*/
class File
{
private:
	//! �T�C�Y
	int length;

	//! �ǂݍ��ݐ�̃o�b�t�@
	char* data;

public:
	/**
	* @brief �R���X�g���N�^
	* @param (fname) �t�@�C����
	*/
	File(const wchar_t* fname);
	/**
	* @brief �f�X�g���N�^
	*/
	~File();
};
