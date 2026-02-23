#pragma once
#include "../SceneBase.h"
#include "../../../Utility/RankingManager/RankingManager.h"

class RankingScene : public SceneBase
{
private:
    RankingManager ranking;  

    int final_score;
    int background_handle;
	int frame_handle;

    int input_handle;
    char player_name[32];
    bool isInputMode;
    bool isRegistered;

    int bgm_handle;     
    int decide_se;      

public:
    RankingScene();
    ~RankingScene();

    void Initialize() override;
    eSceneType Update(const float& delta_second) override;
    void Draw() override;
    void Finalize() override;

    const eSceneType GetNowSceneType() const override
    {
        return eSceneType::eRanking;
    }

    void SetScore(int score) { final_score = score; }
};