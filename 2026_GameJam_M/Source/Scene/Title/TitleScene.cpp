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
	cursor_number = 0;
	cursor_y = 360;
	Title_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Haikei1.png");
	Box_image = LoadGraph("Resource/Image/Title/BOX.png");
}
eSceneType TitleScene::Update()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (is_result == false) {


		//Bボタンが押されたら
		if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
		{
			
			switch (cursor_number)
			{
			case 0:
				//インゲーム画面に移動
				return eSceneType::eInGame;
			case 1:

				return eSceneType::eHelp;
			case 2:
				//return eSceneType::eEnd;
				is_result = true;
			default:
				break;
			}
		}
		SelectCursor();
	}
	else
	{
		if (end_frame_cnt++ > 60)
		{
			end_frame_cnt = 0;
			end_count++;
		}
		if (end_count > 5)
		{
			return eSceneType::eEnd;

		}

	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{

	DrawGraph(0, 0, Title_image, TRUE);

	int boxWidth;
	int boxHeight;
	GetGraphSize(Box_image, &boxWidth, &boxHeight);

	int screenWidth, screenHeight;
	GetDrawScreenSize(&screenWidth, &screenHeight);
	int screenWidth = 1280;				// サイズに合わせる
	int x = screenWidth - boxWidth - 50; // 右から50px余白
	int y = 200;

	DrawGraph(x, y, Box_image, TRUE);

	DrawString(10, 10, "タイトル画面", GetColor(255, 255, 255));
}
void TitleScene::Finalize()
{
	DeleteGraph(Title_image);
	DeleteGraph(Box_image);

}

void TitleScene::SelectCursor()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetKeyInputState(XINPUT_BUTTON_DPAD_UP) == eInputState::ePressed)
	{
		cursor_number--;
		if (cursor_number < 0)
		{
			cursor_number = 2;
		}
		PlaySoundMem(SE1, DX_PLAYTYPE_BACK, TRUE);

	}
	if (pad_input->GetKeyInputState(XINPUT_BUTTON_DPAD_DOWN) == eInputState::ePressed)
	{
		cursor_number++;
		cursor_number = cursor_number % 3;

		PlaySoundMem(SE1, DX_PLAYTYPE_BACK, TRUE);
	}

	cursor_y = 160 + (cursor_number * 80);


}

