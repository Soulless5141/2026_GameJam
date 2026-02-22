#pragma once

#include "../SceneBase.h"
#include "../../../Utility/Camera.h"
#include"../../../Object/Player/Player.h"

#define FLOOR_MAX_X (3)     // 横に何個か
#define FLOOR_MAX_Y (10)    // 縦に何個か

class InGameScene :public SceneBase

{
private:
	class Player* player;
	Camera* camera;
	int ground_stage;
	int time;
	float time_count;
	int score;

	std::vector<std::vector<int>>floor_set;
	std::vector<std::vector<int>>block;
	std::vector<std::vector<GameObject*>>object;

	// 画面サイズを取得
	int screenW, screenH;


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
