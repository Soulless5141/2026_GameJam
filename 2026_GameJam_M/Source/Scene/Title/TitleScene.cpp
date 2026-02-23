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
    cursor_y = 0;

    Title_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Title.png");
    //Box_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/TitleFrame.png");
    Arrow_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/donut1.png");
    font_handle = CreateFontToHandle(NULL, 40, 3);

    cursor_se = LoadSoundMem("Resource/Image/BGM SE/カーソル移動SE.mp3");   
    decide_se = LoadSoundMem("Resource/Image/BGM SE/決定SE.mp3");          
    bgm_handle = LoadSoundMem("Resource/Image/BGM SE/タイトルBGM.mp3");    
    PlaySoundMem(bgm_handle, DX_PLAYTYPE_LOOP);
}

eSceneType TitleScene::Update(const float& delta_second)
{
    PadInputManager* pad_input = PadInputManager::GetInstance();

    if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
    {
        PlaySoundMem(decide_se, DX_PLAYTYPE_BACK);   

        switch (cursor_number)
        {
        case 0:
            return eSceneType::eHelp;
        case 1:
            return eSceneType::eResult;
        case 2:
            return eSceneType::eEnd;
        }
    }

    SelectCursor();

    return GetNowSceneType();
}

void TitleScene::Draw()
{
    int screenWidth, screenHeight;
    GetDrawScreenSize(&screenWidth, &screenHeight);

    DrawExtendGraph(0, 0, screenWidth, screenHeight, Title_image, TRUE);

    // ↓ メニュー位置を直接指定
    int baseX = screenWidth / 2 - -100;  
    int baseY = screenHeight / 2 - 30;
    int lineSpace = 90;

    int arrowW, arrowH;
    GetGraphSize(Arrow_image, &arrowW, &arrowH);

    int smallW = arrowW / 10;
    int smallH = arrowH / 10;

    for (int i = 0; i < 3; i++)
    {
        int arrowY = baseY + lineSpace * i;

        if (i == cursor_number)
        {
            DrawExtendGraph(
                baseX,
                arrowY,
                baseX + smallW,
                arrowY + smallH,
                Arrow_image,
                TRUE
            );
        }
    }
}

void TitleScene::Finalize()
{
    StopSoundMem(bgm_handle);

    DeleteGraph(Title_image);
    DeleteGraph(Box_image);
    DeleteGraph(Arrow_image);

    DeleteSoundMem(cursor_se);       
    DeleteSoundMem(decide_se);       
    DeleteSoundMem(bgm_handle);
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
        PlaySoundMem(cursor_se, DX_PLAYTYPE_BACK);
    }

    if (pad_input->GetKeyInputState(XINPUT_BUTTON_DPAD_DOWN) == eInputState::ePressed)
    {
        cursor_number++;
        cursor_number %= 3;
        PlaySoundMem(cursor_se, DX_PLAYTYPE_BACK);   
    }
}