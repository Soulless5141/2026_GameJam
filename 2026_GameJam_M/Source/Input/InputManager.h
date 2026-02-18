#pragma once

#include "InputSate.h"

/// <summary>
/// 入力管理クラス
/// </summary>
class InputManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static InputManager* instance;

private:
	//キー入力の状態
	char now_key[256];	//今
	char old_key[256];	//一フレーム前

private:
	InputManager();	//コンストラクト
	~InputManager() = default;	//デストラクタ
	InputManager(const InputManager&) = delete;	//NOコピー
	InputManager& operator=(const InputManager&) = delete;	//NO代入演算

public:
	static InputManager* GetInstance();	//インスタンス取得関数
	static void DeleteInstance();		//インスタンス削除

public:
	void Update();								//状態更新
	eInputState GetKeyState(int key) const;		//状態の取得


private:
	bool CheckKeycodeRange(int key) const;

};
