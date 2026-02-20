#include "TitleScene.h"
#include "../../Input/InputManager.h"
#include "../../../Utility/PadInputManager.h"
#include <DxLib.h>

TitleScene::TitleScene()
{

}
TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{
}
eSceneType TitleScene::Update()
{
	InputManager* input = InputManager::GetInstance();
	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed)
	{
		return eSceneType::eHelp;
	}

	PadInputManager* pad = PadInputManager::GetInstance();
	if(pad ->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
	{
		return eSceneType::eHelp;
	}
	return GetNowSceneType();
}
void TitleScene::Draw() const
{
	DrawString(10, 10, "ƒ^ƒCƒgƒ‹‰æ–Ê", GetColor(255, 255, 255));
}
void TitleScene::Finalize()
{
}