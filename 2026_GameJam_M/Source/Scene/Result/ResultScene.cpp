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

	background_handle = LoadGraph("Resource/Image/2026_Gamejam_sozai/Haikei1.png");
	Frame = LoadGraph("Resource/Image/2026_Gamejam_sozai/TitleFrame.png");
    bgm_handle = LoadSoundMem("Resource/Image/BGM SE/ランキングリザルト画面BGM.mp3");   
    decide_se = LoadSoundMem("Resource/Image/BGM SE/決定SE.mp3");  
    font_handle = CreateFontToHandle("ＭＳ ゴシック", 48, 3);
    PlaySoundMem(bgm_handle, DX_PLAYTYPE_LOOP);                               

}


/// 更新処理
eSceneType ResultScene::Update(const float& delta_second)
{
    PadInputManager* pad = PadInputManager::GetInstance();

    // Bボタンで終了
    if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
    {
        PlaySoundMem(decide_se, DX_PLAYTYPE_BACK);   
        return eSceneType::eEnd;
    }

    // Aボタンでインゲームへ戻る
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::ePressed)
    {
  
        PlaySoundMem(decide_se, DX_PLAYTYPE_BACK);   
        return eSceneType::eInGame;
    }

    // Xボタンでランキング画面へ移動
    if (pad->GetKeyInputState(XINPUT_BUTTON_X) == eInputState::ePressed)
    {
        PlaySoundMem(decide_se, DX_PLAYTYPE_BACK);   
        return eSceneType::eRanking;
    }

    return GetNowSceneType();
}

void ResultScene::Draw()
{
    int screenWidth, screenHeight;
    GetDrawScreenSize(&screenWidth, &screenHeight);

    // 背景
    DrawExtendGraph(0, 0, screenWidth, screenHeight, background_handle, TRUE);

    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    // ★ フレームサイズ取得
    int frameWidth, frameHeight;
    GetGraphSize(Frame, &frameWidth, &frameHeight);

    int frameX = centerX - frameWidth / 2;
    int frameY = centerY - frameHeight / 2;

    // ★ 先にフレーム描画（順番修正）
    DrawGraph(frameX, frameY, Frame, TRUE);

    // ★ 表示文字を作成
    char scoreText[64];
    sprintf_s(scoreText, "SCORE : %d", final_score);

    // ★ 文字サイズ取得
    int textWidth = GetDrawStringWidthToHandle(scoreText, strlen(scoreText), font_handle);
    int textHeight = GetFontSizeToHandle(font_handle);

    // ★ フレーム中央基準で補正
    int drawX = frameX + frameWidth / 2 - textWidth / 2;
    int drawY = frameY + frameHeight / 2 - textHeight / 2;

    // ★ 中央描画
    DrawStringToHandle(
        drawX,
        drawY,
        scoreText,
        GetColor(0, 255, 255),
        font_handle
    );

    DrawFormatString(10, 50,
        GetColor(255, 255, 0),
        "今回のスコア : %d", final_score);

    DrawString(10, 80,
        "Xボタンでランキング登録画面へ",
        GetColor(0, 255, 255));
}
void ResultScene::Finalize()
{
    StopSoundMem(bgm_handle);      
    DeleteSoundMem(bgm_handle);    
    DeleteSoundMem(decide_se);    

	DeleteGraph(background_handle);
}