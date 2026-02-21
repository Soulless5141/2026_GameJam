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
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() override;
	virtual void Finalize()override;

public:
	virtual const eSceneType GetNowSceneType()const override
	{
		return eSceneType::eHelp;
	}
};


