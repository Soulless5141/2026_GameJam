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
	Help_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/setumei.png");
	HelpeBGM_handle = LoadSoundMem("Resource/Image/BGM SE/ランキングリザルト画面BGM.mp3");
	PlaySoundMem(HelpeBGM_handle, DX_PLAYTYPE_LOOP);
}
eSceneType HelpScene::Update(const float& delta_second)
{
	InputManager* input = InputManager::GetInstance();
	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed)
	{
		return eSceneType::eInGame;
	}

	PadInputManager* pad = PadInputManager::GetInstance();
	if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::ePressed)
	{
		return eSceneType::eInGame;
	}

	if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
	{
		return eSceneType::eTitle;
	}

	return GetNowSceneType();
}
void HelpScene::Draw() 
{
	int screenWidth, screenHeight;
	GetDrawScreenSize(&screenWidth, &screenHeight);

	DrawExtendGraph(0, 0, screenWidth, screenHeight, Help_image, TRUE);

	//DrawString(10, 10, "ヘルプ画面", GetColor(255, 255, 255));
}
void HelpScene::Finalize()
{

	StopSoundMem(HelpeBGM_handle);
	DeleteGraph(Help_image);
	DeleteSoundMem(HelpeBGM_handle);
}