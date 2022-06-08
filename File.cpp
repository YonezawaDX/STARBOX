/**
* @file File.cpp
* @brief ファイル管理
* @author 米澤駿介
* @date
* @details ファイルを管理
*/
#include "pch.h"
#include "File.h"
#include <limits>

using namespace std;

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数(fname)：ファイル名
//------------------------------------------------------------------
File::File(const wchar_t* fname)
	: length(0)
	, data(nullptr)
{
	ifstream in(fname, ios::in | ios::binary);

	// オープン成功？
	_ASSERT(in);

	// ファイルサイズを取得
	ios::pos_type tmp = in.tellg();
	ios::off_type size_ = in.seekg(0, ios::end).tellg() - in.seekg(0, ios::beg).tellg();
	in.seekg(tmp);

	// ファイルサイズがintで表せる最大値を超えていない？
	_ASSERT(!(std::numeric_limits<int>::max() < size_));
	length = static_cast<int>(size_);

	//メモリを確保して読み込む
	data = new char[length];
	in.read(data, length);

	// クローズ
	in.close();
}

//------------------------------------------------------------------
// 概要：デストラクタ
// 引数：なし
//-------------------------------------------------------------------
File::~File()
{
	if (data)
	{
		delete[] data;
	}
}

