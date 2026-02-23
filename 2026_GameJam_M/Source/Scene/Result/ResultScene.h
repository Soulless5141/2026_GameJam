#pragma once

#include "../SceneBase.h"

class ResultScene : public SceneBase
{
private:
	int final_score;    // 最終スコア
	int background_handle; // 背景画像のハンドル
    int bgm_handle;     
    int decide_se;   
	int font_handle;   // フォントのハンドル


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