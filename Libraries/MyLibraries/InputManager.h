/**
* @file InputManager.h
* @brief インプットマネージャー
* @author 米澤駿介
* @date
* @details マウス、キーボードの入力を請け負う
*/
#pragma once
#include <Mouse.h>
#include <Keyboard.h>

/**
* @brief インプットマネージャーのクラス
* @details マウス、キーボードの入力を請け負う
*/
class InputManager
{
public:
	/**
	* @brief インプットマネージャーを生成する
	* @return InputManager* インプットマネージャーのポインタ
	*/
	static InputManager* GetInstance()
	{
		static InputManager instance;
		return &instance;
	}
private:
	//! マウス関連
	std::unique_ptr<DirectX::Mouse> mMouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> mButtonStateTracker;
	DirectX::Mouse::State mMouseState;
	//! キーボード関連
	std::unique_ptr<DirectX::Keyboard> mKeyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> mKeyboardStateTracker;
	DirectX::Keyboard::State mKeyboardState;

private:
	/**
	* @brief コンストラクタ
	*/
	InputManager() : mKeyboardState(), mMouseState() {};
	/**
	* @brief デストラクタ
	*/
	~InputManager() = default;

private:
	/**
	* @brief コピーコンストラクタ
	* @param (InputManager&) 参照
	*/
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	
	/**
	* @brief ムーブコンストラクタ
	* @param (InputManager&&) 参照
	*/
	InputManager(const InputManager&&) = delete;
	InputManager&& operator=(const InputManager&&) = delete;

public:
	/**
	* @brief 初期化
	* @param (window) 画面の大きさを取得
	* @return void なし
	*/
	void Initialize(const HWND& window);
	/**
	* @brief 更新
	* @return void なし
	*/
	void Update();
	// 各種ゲッタ
	
	/**
	* @brief マウスの状態のゲッター
	* @return Mouse::State& マウスの状態
	*/
	DirectX::Mouse::State& GetMouseState() { return mMouseState; }
	
	/**
	* @brief キーボードの状態のゲッター
	* @return Keyboard::State& キーボードの状態
	*/
	DirectX::Keyboard::State& GetKeyboardState() { return mKeyboardState; }

	/**
	* @brief ボタンの状態のゲッター
	* @return ButtonStateTracker* ボタンの状態ポインタ
	*/
	DirectX::Mouse::ButtonStateTracker* GetButtonStateTracker() const { return mButtonStateTracker.get(); }
	
	/**
	* @brief キーボードの状態のゲッター
	* @return KeyboardStateTracker* キーボードの状態ポインタ
	*/
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker()const { return mKeyboardStateTracker.get(); }

};