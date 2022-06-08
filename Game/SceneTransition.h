/**
* @file SceneTransition.h
* @brief シーン遷移
* @author 米澤駿介
* @date 2022/05/11
* @details シーン遷移用のシングルトン
*/
#pragma once
#include <StepTimer.h>

// 前方宣言
class Fade;

/**
* @brief シーン遷移用
* @details シーン遷移を管理するシングルトン
*/
class SceneTransition
{
public:
	/**
	* @brief シーン遷移を生成する
	* @return SceneTransition* シーン遷移のポインタ
	*/
	static SceneTransition* GetInstance()
	{
		static SceneTransition instance;
		return &instance;
	}

private:
	/**
	* @brief コンストラクタ
	*/
	SceneTransition();
	
	/**
	* @brief デストラクタ
	*/
	~SceneTransition() = default;

private:
	//! フェード用
	std::unique_ptr<Fade> mFade;

private:
	/**
	* @brief コピーコンストラクタ
	* @param (SceneTransition&) 参照
	*/
	SceneTransition(const SceneTransition&) = delete;
	SceneTransition& operator=(const SceneTransition&) = delete;
	
	/**
	* @brief ムーブコンストラクタ
	* @param (SceneTransition&&) 参照
	*/
	SceneTransition(const SceneTransition&&) = delete;
	SceneTransition&& operator=(const SceneTransition&&) = delete;


public:
	/**
	* @brief 初期化
	* @return void なし
	*/
	void Initialize();
	/**
	* @brief 更新
	* @return void なし
	*/
	void Update(const DX::StepTimer& timer);
};