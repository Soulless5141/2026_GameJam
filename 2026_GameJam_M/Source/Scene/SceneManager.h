#pragma once

#include "SceneBase.h"

/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager
{
private:
	static SceneManager* instance;
	SceneBase* current_scene;	//現在のシーン情報

private:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* GetInstance();
	static void DeleteInstance();

public:
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw()const;
	//後始末
	void Finalize();

private:
	//シーンの切り替え
	void ChangeScene(eSceneType next_scene_type);

};



