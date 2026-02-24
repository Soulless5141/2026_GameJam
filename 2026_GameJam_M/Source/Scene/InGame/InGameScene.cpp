#include "InGameScene.h"
#include "../../Input/InputManager.h"
#include"../../../Utility/PadInputManager.h"
#include "../../../Object/Floor/Floor.h"
#include "../../../Object/Floor/Goal.h"

#include <DxLib.h>

#define START_TIME (100) // 何秒からスタートかの初期設定

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

	goal = new Goal();
	goal->Initialize();

	//デバック用
	Vector2D pos = player->GetPosition();
	pos.x += 40;

	goal->SetPosition(pos);

	game_objects_list.push_back(goal);

	LoadStageMapCSV();
	CreateStage();

}

/// <summary>
/// 更新処理
/// </summary>
/// <returns>戻り値は</returns>
eSceneType InGameScene::Update(const float& delta_second)
{

	PadInputManager* pad = PadInputManager::GetInstance();
	if (pad->GetKeyInputState(XINPUT_BUTTON_B) == eInputState::ePressed)
	{
		return eSceneType::eResult;
	}

	if(goal&&goal->IsGaol())
	{
		return eSceneType::eEnd;
	}

	// 親クラスの更新処理を呼び出す
	camera->CameraUpdate(player->GetLocation());

	CountDwon(delta_second);

	
	// 親クラスの更新処理を呼び出す
	__super::Update(delta_second);

	//DeleteStage();

	// ★時間切れ判定
	if (time < 0)
	{
		return eSceneType::eRanking;
	}

	return GetNowSceneType();

	//リスポーン処理　追加
	/*player->Update(delta_second);
	
	if (player->IsRespawnRequested())
	{
	    player->Respawn();
	}*/
	//return GetNowSceneType();
}


void InGameScene::Draw() 
{
	DrawString(10, 10, "インゲーム画面", GetColor(255, 255, 255));
	DrawString(10, 100, "時間制限", GetColor(255, 255, 255));
	// 画像を画面いっぱいに引き伸ばして描画
	//DrawExtendGraph(0, 0, screenW, screenH, image, TRUE);

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
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

void InGameScene::LoadStageMapCSV()
{
	FILE* fp = NULL;
	std::string file_name = "Resource/Date_csv/Map2026.csv";

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
			case 'E':
				ground_stage = 'E';
				break;
				// 階段ブロック
			case 'G':
				ground_stage = 'G';
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
		else if (c == ',')
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

		if (goal)             
		{
			delete goal;       
			goal = nullptr;    
		}

	}
	// 開いたファイルを閉じる
	fclose(fp);
}

void InGameScene::CreateStage()
{
	GameObjectManager* gm = GameObjectManager::Get();
	//printfDx("CreateStage called\n");

	for (int x = 0; x < block.size(); x++)
	{
		for (int y = 0; y < block[x].size(); y++)
		{
			if (block[x][y] != NULL && ((float)x * OBJECT_SIZE) < (camera->GetCameraLocation().x + (D_WIN_MAX_X / 1.9)))
			{
				Vector2D genelate_location = Vector2D(((float)x * 200)+250, ((float)y * -130)+750);

				switch (block[x][y])
				{
					// 床
				case 'E':
					object[x][y] = gm->CreateGameObject<Floor>(genelate_location);
					break;
				case 'G':
					object[x][y] = gm->CreateGameObject<Goal>(genelate_location);
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
	/*for (int x = 0; x < object.size(); x++)
	{
		for (int y = 0; y < object[x].size(); y++)
		{
			if (object[x][y] != nullptr && object[x][y]->GetLocation().x < camera->GetCameraLocation().x - (D_WIN_MAX_Y / 1.9))
			{
				gm->DestroyGameObject(object[x][y]);
				object[x][y] = nullptr;
			}
		}
	}*/
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

/// <summary>
/// 当たり判定確認処理
/// </summary>
/// <param name="target">1つ目のゲームオブジェクト</param>
/// <param name="partner">2つ目のゲームオブジェクト</param>
void InGameScene::CheckCollision(GameObject* target, GameObject* partner)
{
	// ヌルポチェック
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// 当たり判定情報を取得
	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	// 当たり判定が有効か確認する
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{
		// カプセル同士の当たり判定
		tc.pivot = target->GetLocation();
		pc.pivot = partner->GetLocation();
		Vector2D distance = target->GetLocation() - partner->GetLocation();
		Vector2D col_size = (tc.box_size + pc.box_size) / 2;
		if (fabsf(distance.x) <= col_size.x && fabsf(distance.y) <= col_size.y)
		{
			partner->OnHitCollision(target);
			target->OnHitCollision(partner);
		}
		//if (IsCheckCollision(tc, pc))
		//{
		//	// 当たっていることを通知する
		//	partner->OnHitCollision(target);
		//	target->OnHitCollision(partner);

		//}
	}
}
