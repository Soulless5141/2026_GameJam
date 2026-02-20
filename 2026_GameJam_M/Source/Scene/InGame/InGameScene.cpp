#include "InGameScene.h"
#include "../../Input/InputManager.h"
#include <DxLib.h>
InGameScene::InGameScene()
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	// マップデータ読み込み生成処理
	LoadStageMapCSV();
}

/// <summary>
/// 更新処理
/// </summary>
/// <returns>戻り値は</returns>
eSceneType InGameScene::Update()
{
	InputManager* input = InputManager::GetInstance();
	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed)
	{
		return eSceneType::eResult;
	}
	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	DrawString(10, 10, "インゲーム画面", GetColor(255, 255, 255));
}

void InGameScene::Finalize()
{

}