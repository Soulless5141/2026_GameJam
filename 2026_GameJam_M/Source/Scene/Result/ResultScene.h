#pragma once

#include "../SceneBase.h"

class ResultScene : public SceneBase
{
private:
	int final_score;    // 最終スコア


public:
    ResultScene();
    virtual ~ResultScene();

public:
    virtual void Initialize() override;
    virtual eSceneType Update(const float& delta_second) override;
    virtual void Draw() override;
    virtual void Finalize() override;

public:
    virtual const eSceneType GetNowSceneType() const override
    {
        return eSceneType::eResult;
    }
};