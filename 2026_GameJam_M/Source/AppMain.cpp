#include <DxLib.h>

#include "Scene/SceneManager.h"
#include "../Utility/PadInputManager.h"
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	/*ChangeWindowMode(FALSE);
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
	SetGraphMode(1920, 1080, 32);*/

	ChangeWindowMode(TRUE); // TRUE → ウィンドウ起動
	SetGraphMode(1280, 720, 32);


	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SceneManager* scene_manager = SceneManager::GetInstance();
	PadInputManager* pad = PadInputManager::GetInstance();
	scene_manager->Initialize();
	int prev_time = GetNowCount();
	while (ProcessMessage() != -1)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		int now_time = GetNowCount();
		const float delta = (now_time - prev_time) / 1000.0f;
		prev_time = now_time;

		pad->Update();

		scene_manager->Update(delta);   

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