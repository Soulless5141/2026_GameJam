#include "ResultScene.h"
#include "../../Input/InputManager.h"
#include "../../../Utility/PadInputManager.h"
#include <DxLib.h>
ResultScene::ResultScene()
{

}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	final_score = 1500;
	ranking.Load();

    isRegistered = false;

    input_handle = MakeKeyInput(32, TRUE,FALSE, FALSE);
    isInputMode = true;
}

/// <summary>
/// 更新処理
/// </summary>
/// <returns>戻り値は</returns>
eSceneType ResultScene::Update(const float& delta_second)
{
    PadInputManager* pad = PadInputManager::GetInstance();

    // Bボタンで終了
    if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
    {
        return eSceneType::eEnd;
    }

    // Aボタンでインゲームへ戻る
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::ePressed)
    {
        return eSceneType::eInGame;
    }

    // Xボタンでランキング登録
    if (pad->GetKeyInputState(XINPUT_BUTTON_X) == eInputState::ePressed)
    {
        ranking.AddScore("Taro", final_score);  // 仮の名前
        ranking.Save();                         // 保存
        isRegistered = true;                    //一度だけ登録
    }

    if (isInputMode)
    {
        KeyInputString(0, 0, input_handle);

        if (CheckKeyInput(input_handle) == 1) // Enter押された
        {
            GetKeyInputString(player_name, input_handle);
            isInputMode = false;
        }
    }

    return GetNowSceneType();
}


void ResultScene::Draw()
{
    DrawString(10, 10, "リザルト画面", GetColor(255, 255, 255));

    DrawFormatString(10, 50,
        GetColor(255, 255, 0),
        "今回のスコア : %d", final_score);

    DrawString(10, 80, "Xボタンでランキング登録",
        GetColor(0, 255, 255));

    //ランキング表示
    const auto& data = ranking.GetData();

    for (int i = 0; i < data.size(); i++)
    {
        DrawFormatString(200, 150 + i * 30,
            GetColor(255, 255, 255),
            "%d位  %s  %d",
            i + 1,
            data[i].name.c_str(),
            data[i].score);
    }
}

void ResultScene::Finalize()
{
}