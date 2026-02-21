#include "HelpScene.h"
#include "../../Input/InputManager.h"
#include"../../../Utility/PadInputManager.h"
#include <DxLib.h>


HelpScene::HelpScene()
{

}
HelpScene::~HelpScene()
{
}
void HelpScene::Initialize()
{
}
eSceneType HelpScene::Update(const float& delta_second)
{
	InputManager* input = InputManager::GetInstance();
	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed)
	{
		return eSceneType::eInGame;
	}

	PadInputManager* pad = PadInputManager::GetInstance();
	if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
	{
		return eSceneType::eInGame;
	}

	return GetNowSceneType();
}
void HelpScene::Draw() 
{
	DrawString(10, 10, "ƒwƒ‹ƒv‰æ–Ê", GetColor(255, 255, 255));
}
void HelpScene::Finalize()
{
}