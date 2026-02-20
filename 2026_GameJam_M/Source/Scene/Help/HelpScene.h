#pragma once

#include "../SceneBase.h"

//ƒwƒ‹ƒv‰æ–ÊƒNƒ‰ƒX

class HelpScene :public SceneBase
{
private:

public:
	HelpScene();
	virtual ~HelpScene();

public:
	virtual void Initialize()override;
	virtual eSceneType Update()override;
	virtual void Draw()const override;
	virtual void Finalize()override;

public:
	virtual eSceneType GetNowSceneType()const override
	{
		return eSceneType::eHelp;
	}
};


