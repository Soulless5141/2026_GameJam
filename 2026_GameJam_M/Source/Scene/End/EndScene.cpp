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
	End_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Goal.png");
	EndBGM_handle = LoadSoundMem("Resource/Image/BGM SE/エンディングBGM.mp3");
	PlaySoundMem(EndBGM_handle, DX_PLAYTYPE_LOOP);
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
	int screenWidth, screenHeight;
	GetDrawScreenSize(&screenWidth, &screenHeight);

	DrawExtendGraph(0, 0, screenWidth, screenHeight, End_image, TRUE);
	DrawString(10, 10, "エンド画面", GetColor(255, 255, 255));
}
void EndScene::Finalize()
{
	StopSoundMem(EndBGM_handle);
	DeleteGraph(End_image);
	DeleteSoundMem(EndBGM_handle);

}