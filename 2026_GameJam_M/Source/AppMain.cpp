#include <DxLib.h>

#include "Scene/SceneManager.h"
#include "Input/InputManager.h"
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(640, 480, 32);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SceneManager* scene_manager = SceneManager::GetInstance();
	InputManager* input_manager = InputManager::GetInstance();
	scene_manager->Initialize();
	while (ProcessMessage() != -1)
	{
		input_manager->Update();
		scene_manager->Update();
		ClearDrawScreen();
		scene_manager->Draw();
		ScreenFlip();
		if (input_manager->GetKeyState(KEY_INPUT_ESCAPE) ==
			eInputState::eReleased)
		{
			break;
		}
	}
	scene_manager->Finalize();
	SceneManager::DeleteInstance();
	InputManager::DeleteInstance();
	DxLib_End();
	return 0;
}