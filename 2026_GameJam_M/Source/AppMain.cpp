#include <DxLib.h>

#include "Scene/SceneManager.h"
#include "../Utility/PadInputManager.h"
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	ChangeWindowMode(FALSE);
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
	//SetGraphMode(640, 480, 32);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SceneManager* scene_manager = SceneManager::GetInstance();
	PadInputManager* pad = PadInputManager::GetInstance();
	scene_manager->Initialize();
	while (ProcessMessage() != -1)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;	//ƒ‹[ƒv‚ð”²‚¯‚é
		}
		pad ->Update();
		scene_manager->Update();
		ClearDrawScreen();
		scene_manager->Draw();
		ScreenFlip();

	}
	scene_manager->Finalize();
	SceneManager::DeleteInstance();
	PadInputManager::DeleteInstance();
	DxLib_End();
	return 0;
}