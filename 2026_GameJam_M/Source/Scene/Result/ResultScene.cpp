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

    bgm_handle = LoadSoundMem("Resource/Image/BGM SE/ランキングリザルト画面BGM.mp3");   
    decide_se = LoadSoundMem("Resource/Image/BGM SE/決定SE.mp3");                    
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
    DrawString(10, 10, "リザルト画面", GetColor(255, 255, 255));

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
}