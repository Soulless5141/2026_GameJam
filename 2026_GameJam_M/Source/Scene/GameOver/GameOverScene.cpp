#include "GameOverScene.h"
#include "../../Input/InputManager.h"
#include"../../../Utility/PadInputManager.h"
#include <DxLib.h>

GameOverScene::GameOverScene()
{

}
GameOverScene::~GameOverScene()
{
}
void GameOverScene::Initialize()
{
	End_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Gameovera.png");
	EndBGM_handle = LoadSoundMem("Resource/Image/BGM SE/ゲームオーバーSE.mp3");
	PlaySoundMem(EndBGM_handle, DX_PLAYTYPE_LOOP);
}
eSceneType GameOverScene::Update(const float& delta_second)
{
	PadInputManager* pad = PadInputManager::GetInstance();
	if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
	{
		return eSceneType::eTitle;
	}
	return GetNowSceneType();
}
void GameOverScene::Draw()
{
	int screenWidth, screenHeight;
	GetDrawScreenSize(&screenWidth, &screenHeight);

	DrawExtendGraph(0, 0, screenWidth, screenHeight, End_image, TRUE);
}
void GameOverScene::Finalize()
{
	StopSoundMem(EndBGM_handle);
	DeleteGraph(End_image);
	DeleteSoundMem(EndBGM_handle);

}