#pragma once

#include "../SceneBase.h"

//テスト画面クラス

class TestScene : public SceneBase
{
public:
    TestScene();
    virtual ~TestScene();

public:
    virtual void Initialize() override;
    virtual eSceneType Update(const float& delta_second) override;
    virtual void Draw() override;
    virtual void Finalize() override;

    virtual const eSceneType GetNowSceneType() const override
    {
        return eSceneType::eTest;
    }
};
