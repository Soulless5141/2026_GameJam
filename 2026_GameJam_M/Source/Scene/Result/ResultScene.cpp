#include "ResultScene.h"
#include "../../Input/InputManager.h"
#include "../../../Utility/PadInputManager.h"
#include <DxLib.h>
ResultScene::ResultScene()
{

}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <returns>戻り値は</returns>
eSceneType ResultScene::Update(const float& delta_second)
{
	//InputManager* input = InputManager::GetInstance();
	//if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed)
	//{
	//	return eSceneType::eEnd;
	//}

	PadInputManager* pad = PadInputManager::GetInstance();
	if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
	{
		return eSceneType::eEnd;
	}

	else if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::ePressed)
	{
		return eSceneType::eInGame;
	}
	else if (pad->GetKeyInputState(XINPUT_BUTTON_X) == eInputState::ePressed)
	{
		return eSceneType::eTest;
	}
	
	//else if (input->GetKeyState(KEY_INPUT_TAB) == eInputState::ePressed)
	//{
	//	return eSceneType::eInGame;
	//}


	return GetNowSceneType();
}


void ResultScene::Draw() 
{
	DrawString(10, 10, "リザルト画面", GetColor(255, 255, 255));
	DrawString(10, 50, "TABKeyでインゲーム画面", GetColor(255, 255, 255));
}

void ResultScene::Finalize()
{

}