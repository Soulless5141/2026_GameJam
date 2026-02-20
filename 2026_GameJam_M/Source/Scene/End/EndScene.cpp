#include "EndScene.h"
#include "../../Input/InputManager.h"
#include <DxLib.h>

EndScene::EndScene()
{

}
EndScene::~EndScene()
{
}
void EndScene::Initialize()
{
}
eSceneType EndScene::Update()
{
	InputManager* input = InputManager::GetInstance();
	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed)
	{
		return eSceneType::eTitle;
	}
	return GetNowSceneType();
}
void EndScene::Draw() const
{
	DrawString(10, 10, "ƒGƒ“ƒh‰æ–Ê", GetColor(255, 255, 255));
}
void EndScene::Finalize()
{
}