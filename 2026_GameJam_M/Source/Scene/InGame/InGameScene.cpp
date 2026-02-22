#include "InGameScene.h"
#include "../../Input/InputManager.h"
#include"../../../Utility/PadInputManager.h"
#include "../../../Object/Floor/Floor.h"

#include <DxLib.h>

#define START_TIME (3) // 何秒からスタートかの初期設定

InGameScene::InGameScene() : time(0),time_count(0),ground_stage(NULL)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{

	score = 0;

	// タイマーの初期設定
	time = START_TIME;

	std::vector<int>initi_ground(FLOOR_MAX_Y, ground_stage);
	block = std::vector<std::vector<int>>(FLOOR_MAX_X, initi_ground);

	std::vector<GameObject*>initi_object(FLOOR_MAX_Y, nullptr);
	object = std::vector<std::vector<GameObject*>>(FLOOR_MAX_X, initi_object);

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
	camera->CameraUpdate(player->GetLocation());

	__super::Update(delta_second);

	CountDwon(delta_second);

	// ★時間切れ判定
	if (time < 0)
	{
		return eSceneType::eRanking;
	}

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

void InGameScene::LoadStageMapCSV()
{
	FILE* fp = NULL;
	std::string file_name = "csv";

	ResourceManager* rm = ResourceManager::Get();

	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;

	// ファイル内の文字を確認していく
	while (true)
	{
		// ファイルから1文字抽出する
		int c = fgetc(fp);

		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		// 文字を抽出して格納
		else if (c != ' ' && c != '\n' && c != ',')
		{

			switch (c)
			{
				// 床
			case 'f':
				ground_stage = 'f';
				break;
				// 階段ブロック
			case 'B':
				ground_stage = 'B';
				break;
				// ブロック
			default:
				break;
			}
			// 格納
			block[x][y] = ground_stage;
			x++;
		}

		// 抽出した文字が空白文字なら、生成しないで次の文字を見に行く
		else if (c == ' ')
		{
			ground_stage = NULL;
			x++;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

	}
	// 開いたファイルを閉じる
	fclose(fp);
}

void InGameScene::CreateStage()
{
	GameObjectManager* gm = GameObjectManager::Get();
	for (int x = 0; x < block.size(); x++)
	{
		for (int y = 0; y < block[x].size(); y++)
		{
			if (block[x][y] != NULL && ((float)x * OBJECT_SIZE) < (camera->GetCameraLocation().x + (D_WIN_MAX_X / 1.9)))
			{
				Vector2D genelate_location = Vector2D((float)x * OBJECT_SIZE, (float)y * OBJECT_SIZE);
				switch (block[x][y])
				{
					// 床
				case 'f':
					object[x][y] = gm->CreateGameObject<Floor>(genelate_location);
					break;
				default:
					break;
				}

				block[x][y] = NULL;
			}

		}
	}
}

void InGameScene::DeleteStage()
{
	for (int x = 0; x < object.size(); x++)
	{
		for (int y = 0; y < object[x].size(); y++)
		{
			if (object[x][y] != nullptr && object[x][y]->GetLocation().x < camera->GetCameraLocation().x - (D_WIN_MAX_Y / 1.9))
			{
				gm->DestroyGameObject(object[x][y]);
				object[x][y] = nullptr;
			}
		}
	}
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
