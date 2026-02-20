#pragma once

#include "../SceneBase.h"

//エンド画面クラス

class EndScene :public SceneBase
{
private:

public:
	EndScene();
	virtual ~EndScene();

public:
	virtual void Initialize()override;
	virtual eSceneType Update()override;
	virtual void Draw()const override;
	virtual void Finalize()override;

public:
	virtual eSceneType GetNowSceneType()const override
	{
		return eSceneType::eEnd;
	}
};


