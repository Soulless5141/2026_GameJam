#pragma once

#include "../SceneBase.h"

//タイトル画面クラス

class TitleScene :public SceneBase
{
private:
	int cursor_number;
	int Title_image;
	int Box_image;
	int cursor_y;
	int BGM;
	int SE1;
	int SE2;

	bool is_result;

	int end_img;
	int end_count;
	int end_frame_cnt;

public:
	TitleScene();
	virtual ~TitleScene();

public:
	virtual void Initialize()override;
	virtual eSceneType Update()override;
	virtual void Draw()const override;
	virtual void Finalize()override;
	virtual void SelectCursor();

public:
	virtual eSceneType GetNowSceneType()const override
	{
		return eSceneType::eTitle;
	}
};

