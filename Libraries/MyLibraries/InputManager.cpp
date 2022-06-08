/**
* @file InputManager.cpp
* @brief インプットマネージャー
* @author 米澤駿介
* @date
* @details マウス、キーボードの入力を請け負う
*/
#include "pch.h"
#include "InputManager.h"

//------------------------------------------------------------------
// 概要：コンストラクタ
// 引数：なし
//------------------------------------------------------------------
void InputManager::Initialize(const HWND& window)
{
	// キーボード関連
	mKeyboard = std::make_unique<DirectX::Keyboard>();
	mKeyboardStateTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	
	// マウス関連
	mMouse = std::make_unique<DirectX::Mouse>();
	mMouse->SetWindow(window);
	mButtonStateTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();

}

//------------------------------------------------------------------
// 概要：更新
// 引数：なし
// 戻り値：なし
//-------------------------------------------------------------------
void InputManager::Update()
{
	// キーボードの状態更新
	mKeyboardState = mKeyboard->GetState();
	// キーボードトラッカーの更新
	mKeyboardStateTracker->Update(mKeyboardState);

	// マウスの状態更新
	mMouseState = mMouse->GetState();
	// マウスボタントラッカーの更新
	mButtonStateTracker->Update(mMouseState);
}
