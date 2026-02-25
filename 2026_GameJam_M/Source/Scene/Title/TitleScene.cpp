#include "TitleScene.h"
#include "../../Input/InputManager.h"
#include "../../../Utility/PadInputManager.h"
#include "math.h"
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

    Title_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Title_Help.png");
	Rogo_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/TitleRogo.png");
    //Box_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/TitleFrame.png");
    Arrow_image[0] = LoadGraph("Resource/Image/2026_Gamejam_sozai/donut1.png");
    Arrow_image[1] = LoadGraph("Resource/Image/2026_Gamejam_sozai/donut2.png");
    Arrow_image[2] = LoadGraph("Resource/Image/2026_Gamejam_sozai/donut3.png");
    random_donut = GetRand(2);
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
            return eSceneType::eInGame;
        case 1:
            return eSceneType::eHelp;
        case 2:
            is_result = true;

            DxLib_End();
            exit(0);
            break;;
        }
    }

    arrow_angle += 10.0f * delta_second;   // 回転速度（毎フレーム3度）
    if (arrow_angle >= 360.0f) arrow_angle -= 360.0f;


    SelectCursor();

    return GetNowSceneType();
}

void TitleScene::Draw()
{
    int screenWidth, screenHeight;
    GetDrawScreenSize(&screenWidth, &screenHeight);

    DrawExtendGraph(0, 0, screenWidth, screenHeight, Title_image, TRUE);
    DrawRotaGraphF(600, 250, 0.4, 0.0, Rogo_image, TRUE, 0);

    // ↓ メニュー位置を直接指定
    int baseX = screenWidth / 2 - -190;  
    int baseY = screenHeight / 2 - 25;
    int lineSpace = 130;

    int arrowW, arrowH;
    GetGraphSize(Arrow_image[random_donut], &arrowW, &arrowH);

    int smallW = arrowW / 7;
    int smallH = arrowH / 7;

    for (int i = 0; i < 3; i++)
    {
        int arrowY = baseY + lineSpace * i;

        if (i == cursor_number)
        {
            float scale = 0.15f;  // ← 25% の大きさに縮小（ここを調整）

            DrawRotaGraph(
                baseX + smallW / 2,        // 中心X
                arrowY + smallH / 2,       // 中心Y
                scale,                     // ← 大きさ
                arrow_angle * DX_PI / 180, // 回転角度（ラジアン）
                Arrow_image[random_donut],
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
    DeleteGraph(Arrow_image[random_donut]);

    DeleteSoundMem(cursor_se);       
    DeleteSoundMem(decide_se);       
    DeleteSoundMem(bgm_handle);
    DeleteGraph(Arrow_image[random_donut]);

    for (int i = 0; i < 3; i++)
    {
        DeleteGraph(Arrow_image[i]);
    }
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