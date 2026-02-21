#include "TestScene.h"
#include "../../Input/InputManager.h"
#include"../../../Utility/PadInputManager.h"
#include"../../../Object/Player/Player.h"
#include <DxLib.h>

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
    // SceneBaseの初期化
    __super::Initialize();

    // ★ Player生成（これが正解）
    gm->CreateGameObject<Player>(Vector2D(320.0f, 400.0f));
}

eSceneType TestScene::Update(const float& delta_second)
{
    // ★ これ超重要
    __super::Update(delta_second);

    InputManager* input = InputManager::GetInstance();
    if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed)
    {
        return eSceneType::eTitle;
    }

    PadInputManager* pad = PadInputManager::GetInstance();
    if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
    {
        return eSceneType::eTitle;
    }

    return GetNowSceneType();
}

void TestScene::Draw()
{


    // ★ これ呼ばないとPlayer描画されない
    __super::Draw();

    DrawString(10, 10, "テスト画面", GetColor(255, 255, 255));
}

void TestScene::Finalize()
{
}