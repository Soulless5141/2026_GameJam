#include "InGameScene.h"
#include "../../Input/InputManager.h"
#include"../../../Utility/PadInputManager.h"
#include <DxLib.h>
InGameScene::InGameScene() : time(0)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	time = 123;
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
	return GetNowSceneType();
}


void InGameScene::Draw() 
{
	DrawString(10, 10, "インゲーム画面", GetColor(255, 255, 255));
	DrawString(10, 100, "時間制限", GetColor(255, 255, 255));
	DrawFormatString(10, 200, GetColor(255, 255, 255), "%d", time);
}

void InGameScene::Finalize()
{

}