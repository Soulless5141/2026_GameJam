#pragma once

#include "../SceneBase.h"
#include "../../../Utility/Camera.h"
#include"../../../Object/Player/Player.h"
#include "../../../Object/Floor/Goal.h"

#define FLOOR_MAX_X (40)     // 横に何個か
#define FLOOR_MAX_Y (100)    // 縦に何個か

class InGameScene :public SceneBase

{
private:
	class Player* player;
	Camera* camera;
	int ground_stage;
	int time;
	float time_count;
	int score;
	bool is_goal;

	std::vector<std::vector<int>>floor_set;
	std::vector<std::vector<int>>block;
	std::vector<std::vector<GameObject*>>object;

	// 画面サイズを取得
	int screenW, screenH;

	Goal* goal;
	

public:

	InGameScene();
	virtual ~InGameScene();

public:
	virtual void Initialize()override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() override;
	virtual void Finalize() override;

public:
	virtual const eSceneType GetNowSceneType() const override
	{
		return eSceneType::eInGame;
	}

	virtual int GetScore() const
	{
		return 0;
	}

	/// <summary>
	/// 当たり判定確認処理
	/// </summary>
	/// <param name="target">1つ目のゲームオブジェクト</param>
	/// <param name="partner">2つ目のゲームオブジェクト</param>
	virtual void CheckCollision(GameObject* target, GameObject* partner) override;

private:
	/// <summary>
	/// ステージマップ読み込み処理
	/// </summary>
	void LoadStageMapCSV();
	///// <summary>
	///// ステージ生成
	/// </summary>
	void CreateStage();
	///// <summary>
	/// オブジェクト削除
	/// </summary>
	void DeleteStage();

	void CountDwon(float delta_second);
};
