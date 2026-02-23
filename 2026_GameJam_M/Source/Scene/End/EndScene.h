#pragma once

#include "../SceneBase.h"

//エンド画面クラス

class EndScene :public SceneBase
{
private:
	int End_image;
	int EndBGM_handle;

public:
	EndScene();
	virtual ~EndScene();

public:
	virtual void Initialize()override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() override;
	virtual void Finalize()override;

public:
	virtual const eSceneType GetNowSceneType()const override
	{
		return eSceneType::eEnd;
	}
};


