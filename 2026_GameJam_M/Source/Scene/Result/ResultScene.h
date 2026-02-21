#pragma once

#include "../SceneBase.h"
#include "../../../Utility/RankingManager/RankingManager.h"

class ResultScene : public SceneBase
{
private:
    Ranking ranking;
    int final_score;
    bool isRegistered;
    int input_handle;       //名前入力用
    char Player_name[32];   //入力文字保存（32文字）
    bool isInputMode;    //入力中かどうか

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