/**
* @file BinaryFile.cpp
* @brief バイナリファイル
* @author 米澤駿介
* @date
* @details バイナリファイルを管理
*/
#include "pch.h"
#include "BinaryFile.h"

#include <fstream>
#include <assert.h>

//-------------------------------------------------
// 概要:ファイルをロード
// 引数(fileName):ファイル名
// 戻り値 BinaryFile：バイナリファイル
//--------------------------------------------------
BinaryFile BinaryFile::LoadFile(const wchar_t* fileName)
{
	BinaryFile bin;

	std::ifstream ifs;

	// ファイルオープン
	ifs.open(fileName, std::ios::in | std::ios::binary);

	// 読み込み失敗時、強制終了
	assert(ifs);

	// ファイルサイズを取得
	ifs.seekg(0, std::fstream::end);
	std::streamoff eofPos = ifs.tellg();
	ifs.clear();
	ifs.seekg(0, std::fstream::beg);
	std::streamoff begPos = ifs.tellg();
	bin.mSize = (unsigned int)(eofPos - begPos);

	// 読み込むためのメモリを確保
	bin.mData.reset(new char[bin.mSize]);

	// ファイル先頭からバッファへコピー 
	ifs.read(bin.mData.get(), bin.mSize);

	// ファイルクローズ
	ifs.close();

	return std::move(bin);
}

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
BinaryFile::BinaryFile()
{
	mSize = 0;
}

//------------------------------------------------------------------
// 概要：ムーブコンストラクタ
// 引数(in)：動かす
//------------------------------------------------------------------
BinaryFile::BinaryFile(BinaryFile&& in)
{
	mData = std::move(in.mData);
	mSize = in.mSize;
}
