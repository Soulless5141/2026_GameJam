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
	DrawExtendGraph(0, 0, screenWidth, screenHeight, background_handle, TRUE);
    DrawString(10, 10, "リザルト画面", GetColor(255, 255, 255));

    //中央座標計算
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    //スコア表示（シアン）
    DrawFormatStringToHandle(
        centerX,
        centerY,
        GetColor(0, 255, 255),   // シアン
        font_handle,
        "SCORE : %d",
        final_score
    );

	int frameWidth, frameHeight;
	GetGraphSize(Frame, &frameWidth, &frameHeight);

	int frameX = centerX - frameWidth / 2;
	int frameY = centerY - frameHeight / 2;

	DrawGraph(frameX, frameY, Frame, TRUE);

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