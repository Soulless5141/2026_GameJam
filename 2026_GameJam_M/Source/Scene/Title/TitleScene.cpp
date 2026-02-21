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

    Title_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Haikei1.png");
    Box_image = LoadGraph("Resource/Image/Title/BOX.png");
    Arrow_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/donut1.png");
}

eSceneType TitleScene::Update(const float& delta_second)
{
    PadInputManager* pad_input = PadInputManager::GetInstance();

    if (pad_input->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
    {
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

    // 背景（全画面）
    DrawExtendGraph(0, 0, screenWidth, screenHeight, Title_image, TRUE);

    // Box（右中央）
    int boxW, boxH;
    GetGraphSize(Box_image, &boxW, &boxH);

    int boxX = screenWidth - boxW - 80;
    int boxY = screenHeight / 2 - boxH / 2;

    DrawGraph(boxX, boxY, Box_image, TRUE);

    // メニュー文字
    int textStartY = boxY + 80;
    int lineSpace = 80;

    DrawString(boxX + 120, textStartY + lineSpace * 0, "START", GetColor(255, 255, 255));
    DrawString(boxX + 120, textStartY + lineSpace * 1, "HELP", GetColor(255, 255, 255));
    DrawString(boxX + 120, textStartY + lineSpace * 2, "END", GetColor(255, 255, 255));

    // Arrow（縮小表示）
    int arrowW, arrowH;
    GetGraphSize(Arrow_image, &arrowW, &arrowH);

    int smallW = arrowW / 9;
    int smallH = arrowH / 9;
    
    //矢印のXの位置（文字の左）
    int arrowX = boxX + 60;
    int arrowY = textStartY
        + lineSpace * cursor_number
        + (lineSpace / 2)
        - (smallH / 2);
    //int arrowY = textStartY + lineSpace * cursor_number;

    DrawExtendGraph(
        arrowX,
        arrowY,
        arrowX + smallW,
        arrowY + smallH,
        Arrow_image,
        TRUE
    );
}

void TitleScene::Finalize()
{
    DeleteGraph(Title_image);
    DeleteGraph(Box_image);
    DeleteGraph(Arrow_image);
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
    }

    if (pad_input->GetKeyInputState(XINPUT_BUTTON_DPAD_DOWN) == eInputState::ePressed)
    {
        cursor_number++;
        cursor_number %= 3;
    }
}