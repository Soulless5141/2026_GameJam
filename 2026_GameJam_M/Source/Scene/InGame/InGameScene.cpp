#include "InGameScene.h"
#include "../../Input/InputManager.h"
#include"../../../Utility/PadInputManager.h"
#include <DxLib.h>

#define START_TIME (3) // 何秒からスタートかの初期設定

InGameScene::InGameScene() : time(0),time_count(0)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	// 
	time = START_TIME;
	// マップデータ読み込み生成処理
	//LoadStageMapCSV();
}

/// <summary>
/// 更新処理
/// </summary>
/// <returns>戻り値は</returns>
eSceneType InGameScene::Update(const float& delta_second)
{
	InputManager* input = InputManager::GetInstance();
	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed)
	{
		return eSceneType::eResult;
	}
	PadInputManager* pad = PadInputManager::GetInstance();
	if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
	{
		return eSceneType::eResult;
	}

	// 親クラスの更新処理を呼び出す
	__super::Update(delta_second);

	CountDwon(delta_second);

	return GetNowSceneType();
}


void InGameScene::Draw() 
{
	DrawString(10, 10, "インゲーム画面", GetColor(255, 255, 255));
	DrawString(10, 100, "時間制限", GetColor(255, 255, 255));
	if (time >= 0)
	{
		DrawFormatString(10, 200, GetColor(255, 255, 255), "%d", time);
	}
	else
	{
		DrawFormatString(10, 200, GetColor(255, 255, 255), "TIME UP!");
	}
}

void InGameScene::Finalize()
{

}

void InGameScene::CountDwon(float delta_second)
{
	if (time >= 0)
	{
		time_count = time_count + delta_second;
		if (time_count >= 1)
		{
			time_count = 0;
			time--;
		}
	}

}
