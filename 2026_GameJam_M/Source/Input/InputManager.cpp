#include "InputManager.h"
#include <DxLib.h>

/// <summary>
/// 静的メンバー関数の定義
/// SingLetonパターンのインスタンスを保持する
/// </summary>
InputManager* InputManager::instance = nullptr;

/// <summary>
/// コンストラクト
/// キー入力の現在状態と前回状態を初期化
/// </summary>
InputManager::InputManager()
	:now_key{}
	, old_key{}
{

}

//Singltonインスタンスの取得
//インスタンスの生成
InputManager* InputManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new InputManager();
	}
	return instance;
}

//キー入力の更新処理
//戻り値
void InputManager::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

//1フレームごとに現在のキー状態
void InputManager::Update()
{
	//前回のキー
	memcpy(old_key, now_key, sizeof(char) * 256);
	//現在のキー
	GetHitKeyStateAll(now_key);
}

//キーの入力状態を調べる
eInputState InputManager::GetKeyState(int key) const
{
	if (CheckKeycodeRange(key))
	{
		if (old_key[key] == TRUE)
		{
			if (now_key[key] == TRUE)

			{
				return eInputState::eHeld;
			}

			else
			{
				return eInputState::eReleased;
			}
		}

		else
		{
			if (now_key[key] == TRUE)

			{
				return eInputState::ePressed;
			}
		}
	}
	return eInputState::eNone;
}


bool InputManager::CheckKeycodeRange(int key) const
{
	return (0 <= key && key < 256);
}


