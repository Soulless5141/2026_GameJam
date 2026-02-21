#include "InGameScene.h"
#include "../../Input/InputManager.h"
#include"../../../Utility/PadInputManager.h"

#include <DxLib.h>

#define START_TIME (3) // 何秒からスタートかの初期設定

InGameScene::InGameScene() : time(0),time_count(0)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	// タイマーの初期設定
	time = START_TIME;
	// マップデータ読み込み生成処理
	//LoadStageMapCSV();
	image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Haikei2.png");
	GetScreenState(&screenW, &screenH, nullptr);
	camera = Camera::Get();
	camera->CameraInit();
	player = gm->CreateGameObject<Player>(Vector2D(320.0f, 400.0f));

}

/// <summary>
/// 更新処理
/// </summary>
/// <returns>戻り値は</returns>
eSceneType InGameScene::Update(const float& delta_second)
{
	camera->CameraUpdate(player->GetLocation());		//プレイヤーの座標を基にカメラを更新

	PadInputManager* pad = PadInputManager::GetInstance();
	if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
	{
		return eSceneType::eResult;
	}

	// 親クラスの更新処理を呼び出す
	__super::Update(delta_second);

	CountDwon(delta_second);

	return GetNowSceneType();
}


void InGameScene::Draw() 
{
	DrawString(10, 10, "インゲーム画面", GetColor(255, 255, 255));
	DrawString(10, 100, "時間制限", GetColor(255, 255, 255));
	// 画像を画面いっぱいに引き伸ばして描画
	DrawExtendGraph(0, 0, screenW, screenH, image, TRUE);

	__super::Draw();

	if (time >= 0)
	{
		DrawFormatString(10, 200, GetColor(255, 255, 255), "%d", time);
	}
	else
	{
		DrawFormatString(10, 200, GetColor(255, 255, 255), "TIME UP!");
	}
}

void InGameScene::Finalize()
{
	
}

void InGameScene::CountDwon(float delta_second)
{
	if (time >= 0)
	{
		time_count = time_count + delta_second;
		if (time_count >= 1)
		{
			time_count = 0;
			time--;
		}
	}

}
