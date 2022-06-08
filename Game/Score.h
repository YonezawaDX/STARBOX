/**
* @file Score.h
* @brief スコア保存
* @author 米澤駿介
* @date
* @details スコア保存
*/
#pragma once

/**
* @brief スコアの保存クラス
* @details スコア保存
*/
class Score
{
public:
	/**
	* @brief インスタンス
	* @return Score* スコアのポインタ
	*/
	static Score* GetInstance()
	{
		static Score instance;
		return &instance;
	}

	// 使用関数---------------------------------------------------
	
	/**
	* @brief 初期化
	* @return void なし
	*/
	void Initialize();
	
	/**
	* @brief スコアの加算
	* @param (score) 追加されるスコア
	* @return void なし
	*/
	void AddScore(int score);

	/**
	* @brief スコアの加算
	* @return int スコアの取得
	*/
	int GetScore() const;

	/**
	* @brief ボスの種類
	* @return int ボスの種類
	*/
	int GetBossNum() const;

	/**
	* @brief ボスの種類
	* @param (num) ボスの種類
	*/
	void SetBossNum(int num);
private:
	/**
	* @brief コンストラクタ
	*/
	Score();
	/**
	* @brief デストラクタ
	*/
	~Score();
private:
	// 使用変数---------------------------------------------
	//! スコアの値
	int mScore;

	//! セレクトシーンで選んだボス
	int mBossNum;
};