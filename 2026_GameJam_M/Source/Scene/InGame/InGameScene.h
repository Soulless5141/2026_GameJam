#pragma once

#include "../SceneBase.h"

class InGameScene :public SceneBase

{
private:
	int time;
	float time_count;


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

private:
	/*/// <summary>
	/// ステージマップ読み込み処理
	/// </summary>
	void LoadStageMapCSV();
	/// <summary>
	/// ステージ生成
	/// </summary>
	void CreateStage();
	/// <summary>
	/// オブジェクト削除
	/// </summary>
	void DeleteStage();*/

	void CountDwon(float delta_second);
};
