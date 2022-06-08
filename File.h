/**
* @file File.h
* @brief ファイル管理
* @author 米澤駿介
* @date 
* @details ファイルを管理
*/
#pragma once

#include <fstream>
/**
* @brief ファイル管理のクラス
* @details File
*/
class File
{
private:
	//! サイズ
	int length;

	//! 読み込み先のバッファ
	char* data;

public:
	/**
	* @brief コンストラクタ
	* @param (fname) ファイル名
	*/
	File(const wchar_t* fname);
	/**
	* @brief デストラクタ
	*/
	~File();
};
