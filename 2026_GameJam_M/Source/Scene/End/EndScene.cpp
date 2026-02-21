#include "EndScene.h"
#include "../../Input/InputManager.h"
#include"../../../Utility/PadInputManager.h"
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
eSceneType EndScene::Update(const float& delta_second)
{
	PadInputManager* pad = PadInputManager::GetInstance();
	if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
	{
		return eSceneType::eTitle;
	}
	return GetNowSceneType();
}
void EndScene::Draw() 
{
	DrawString(10, 10, "ƒGƒ“ƒh‰æ–Ê", GetColor(255, 255, 255));
}
void EndScene::Finalize()
{
}