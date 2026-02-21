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
    Box_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/TitleFrame.png");
    Arrow_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/donut1.png");
    font_handle = CreateFontToHandle(NULL, 40, 3);
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

    DrawExtendGraph(0, 0, screenWidth, screenHeight, Title_image, TRUE);

    int boxW, boxH;
    GetGraphSize(Box_image, &boxW, &boxH);

    int boxX = screenWidth - boxW - 80;
    int boxY = screenHeight / 2 - boxH / 2;

    DrawGraph(boxX, boxY, Box_image, TRUE);

    // 茶色
    int brown = GetColor(139, 69, 19);

    const char* menu[3] = { "START", "HELP", "END" };

    int baseY = boxY + 200;
    int lineSpace = 90;

    // ★ Arrowの基準位置
    int arrowBaseX = boxX + 180;
    int arrowStartY = baseY;

    // 画像サイズ取得（1回だけ）
    int arrowW, arrowH;
    GetGraphSize(Arrow_image, &arrowW, &arrowH);

    int smallW = arrowW / 9;
    int smallH = arrowH / 9;

    for (int i = 0; i < 3; i++)
    {
        int arrowY = arrowStartY + lineSpace * i;

        // ★ 選択中だけArrow表示
        if (i == cursor_number)
        {
            DrawExtendGraph(
                arrowBaseX,
                arrowY,
                arrowBaseX + smallW,
                arrowY + smallH,
                Arrow_image,
                TRUE
            );
        }

        // ★ 文字は常にArrowの右側
        int textX = arrowBaseX + smallW + 30;
        int textY = arrowY + (smallH / 2) - 20;

        DrawStringToHandle(
            textX,
            textY,
            menu[i],
            GetColor(139, 69, 19),
            font_handle
        );
    }
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