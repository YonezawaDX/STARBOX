/**
* @file BinaryFile.h
* @brief バイナリファイル
* @author 米澤駿介
* @date
* @details バイナリファイルを管理
*/
#pragma once

#include <memory>

/**
* @brief バイナリファイルのクラス
* @details バイナリファイル
*/
class BinaryFile
{
protected:

	//! データ
	std::unique_ptr<char[]> mData;

	//! サイズ
	unsigned int mSize;

public:

	/**
	* @brief ファイルをロード
	* @param (fileName) ファイル名
	* @return BinaryFile バイナリファイル
	*/
	static BinaryFile LoadFile(const wchar_t* fileName);

	/**
	* @brief コンストラクタ
	*/
	BinaryFile();

	/**
	* @brief ムーブコンストラクタ
	* @param (in) ムーブする
	*/
	BinaryFile(BinaryFile&& in);

	/**
	* @brief データを取得
	* @return char* データ
	*/
	char* GetData() { return mData.get(); }

	/**
	* @brief サイズを取得
	* @return unsigned int サイズ
	*/
	unsigned int GetSize() { return mSize; }
};
