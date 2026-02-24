#include "RankingScene.h"
#include "../../Input/InputManager.h"
#include "../../../Utility/PadInputManager.h"
#include <DxLib.h>

RankingScene::RankingScene()
{
}

RankingScene::~RankingScene()
{
}

void RankingScene::Initialize()
{
    // ランキング読み込み
    ranking.Load();

    // 背景読み込み
    background_handle = LoadGraph("Resource/Image/2026_Gamejam_sozai/Haikei1.png");
    frame_handle = LoadGraph("Resource/Image/2026_Gamejam_sozai/TitleFrame.png");

    // 名前入力準備
    input_handle = MakeKeyInput(32, TRUE, FALSE, FALSE);
    SetActiveKeyInput(input_handle);
    isInputMode = true;
    isRegistered = false;

    player_name[0] = '\0';

    bgm_handle = LoadSoundMem("Resource/Image/BGM SE/ランキングリザルト画面BGM.mp3");   
    decide_se = LoadSoundMem("Resource/Image/BGM SE/決定SE.mp3");                    
    PlaySoundMem(bgm_handle, DX_PLAYTYPE_LOOP);                               
}



eSceneType RankingScene::Update(const float& delta_second)
{
    SetActiveKeyInput(input_handle);

    PadInputManager* pad = PadInputManager::GetInstance();

    if (pad->GetKeyInputState(XINPUT_BUTTON_Y) == eInputState::ePressed)
    {
        PlaySoundMem(decide_se, DX_PLAYTYPE_BACK);   
        return eSceneType::eTitle;
    }

    // ===== 名前入力中 =====
    if (isInputMode)
    {
        // Enterキーで確定
        if (CheckHitKey(KEY_INPUT_RETURN))
        {
            GetKeyInputString(player_name, input_handle);

            if (strlen(player_name) > 0)
            {
                isInputMode = false;
            }
        }

        return GetNowSceneType();
    }

    // ===== スコア登録（1回だけ）=====
    if (!isRegistered)
    {
        ranking.AddScore(player_name, final_score);
        ranking.Save();
        isRegistered = true;
    }

    // ===== Bボタンでタイトルへ =====
    if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
    {
        PlaySoundMem(decide_se, DX_PLAYTYPE_BACK);   
        return eSceneType::eTitle;
    }

    return GetNowSceneType();
}

void RankingScene::Draw()
{

    int screenW, screenH;
    GetDrawScreenSize(&screenW, &screenH);

    // 背景描画
    DrawExtendGraph(0, 0, screenW, screenH, background_handle, TRUE);

    DrawString(50, 20, "ランキング登録", GetColor(0, 0, 0));
	DrawString(50, 40, "Yボタンでタイトルへ", GetColor(0, 0, 0));
	DrawString(50, 70, "名前を登録したらBボタンでタイトルへ", GetColor(0, 0, 0));

    //入力画面
    if (isInputMode)
    {
        DrawString(50, 90, "名前をキーボードで入力してください (Enterで確定)", GetColor(0, 0, 0));

        // 入力枠（黒背景）
        DrawBox(95, 120, 405, 165, GetColor(0, 0, 0), TRUE);

        // 白枠線
        DrawBox(95, 120, 405, 165, GetColor(255, 255, 255), FALSE);

        // 入力文字（白）
        DrawKeyInputString(105, 130, input_handle);
    }

    int frame_w, frame_h;
    GetGraphSize(frame_handle, &frame_w, &frame_h);

    int frame_x = (screenW - frame_w) / 2;
    int frame_y = (screenH - frame_h) / 2;

    DrawGraph(frame_x, frame_y, frame_handle, TRUE);

    // ★ フレーム内だけ描画
    SetDrawArea(
        frame_x,
        frame_y,
        frame_x + frame_w,
        frame_y + frame_h
		);

    // フレーム内だけ描画させる
    SetDrawArea(
        frame_x,
        frame_y,
        frame_x + frame_w,
        frame_y + frame_h
    );

    const auto& data = ranking.GetData();

    for (int i = 0; i < data.size(); i++)
    {
        char buffer[256];
        sprintf_s(buffer, "%2d位   %-10s   %5d",
            i + 1,
            data[i].name.c_str(),
            data[i].score);

        int str_width = GetDrawStringWidth(buffer, strlen(buffer));

        int text_x = frame_x + (frame_w - str_width) / 2;
        int start_offset_y = 160;   
        int line_height = 35;

        int text_y = frame_y + start_offset_y + i * line_height;

        int neon_yellow = GetColor(255, 255, 80);

        DrawString(text_x, text_y, buffer, neon_yellow);
    }

    // ★ 描画範囲を元に戻す
    SetDrawArea(0, 0, 1280, 720);
}

void RankingScene::Finalize()
{
    StopSoundMem(bgm_handle);      
    DeleteSoundMem(bgm_handle);    
    DeleteSoundMem(decide_se); 


    DeleteGraph(background_handle);  
    DeleteGraph(frame_handle);

    DeleteKeyInput(input_handle);
}