#pragma once

#include "../SceneBase.h"

//タイトル画面クラス

class TitleScene :public SceneBase
{
private:

public:
	TitleScene();
	virtual ~TitleScene();

public:
	virtual void Initialize()override;
	virtual eSceneType Update()override;
	virtual void Draw()const override;
	virtual void Finalize()override;

public:
	virtual eSceneType GetNowSceneType()const override
	{
		return eSceneType::eTitle;
	}
};

