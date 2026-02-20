#pragma once

#include "../SceneBase.h"

class InGameScene :public SceneBase

{
private:
	int charge;   // どれぐらい溜めたか
	int time;


public:
	InGameScene();
	virtual ~InGameScene();

public:
	virtual void Initialize()override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType()const override
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
};
