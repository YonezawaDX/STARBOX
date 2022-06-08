/**
* @file BinaryFile.cpp
* @brief �o�C�i���t�@�C��
* @author ���V�x��
* @date
* @details �o�C�i���t�@�C�����Ǘ�
*/
#include "pch.h"
#include "BinaryFile.h"

#include <fstream>
#include <assert.h>

//-------------------------------------------------
// �T�v:�t�@�C�������[�h
// ����(fileName):�t�@�C����
// �߂�l BinaryFile�F�o�C�i���t�@�C��
//--------------------------------------------------
BinaryFile BinaryFile::LoadFile(const wchar_t* fileName)
{
	BinaryFile bin;

	std::ifstream ifs;

	// �t�@�C���I�[�v��
	ifs.open(fileName, std::ios::in | std::ios::binary);

	// �ǂݍ��ݎ��s���A�����I��
	assert(ifs);

	// �t�@�C���T�C�Y���擾
	ifs.seekg(0, std::fstream::end);
	std::streamoff eofPos = ifs.tellg();
	ifs.clear();
	ifs.seekg(0, std::fstream::beg);
	std::streamoff begPos = ifs.tellg();
	bin.mSize = (unsigned int)(eofPos - begPos);

	// �ǂݍ��ނ��߂̃��������m��
	bin.mData.reset(new char[bin.mSize]);

	// �t�@�C���擪����o�b�t�@�փR�s�[ 
	ifs.read(bin.mData.get(), bin.mSize);

	// �t�@�C���N���[�Y
	ifs.close();

	return std::move(bin);
}

//------------------------------------------------------------------
// �T�v�F�R���X�g���N�^
// �����F�Ȃ�
//------------------------------------------------------------------
BinaryFile::BinaryFile()
{
	mSize = 0;
}

//------------------------------------------------------------------
// �T�v�F���[�u�R���X�g���N�^
// ����(in)�F������
//------------------------------------------------------------------
BinaryFile::BinaryFile(BinaryFile&& in)
{
	mData = std::move(in.mData);
	mSize = in.mSize;
}
