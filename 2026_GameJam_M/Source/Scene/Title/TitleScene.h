#pragma once

#include "../SceneBase.h"

//タイトル画面クラス

class TitleScene :public SceneBase
{
private:
	int cursor_number;
	int Title_image;
	int Box_image;
	int Arrow_image;
	int cursor_y;
	int BGM;
	int SE1;
	int SE2;

	bool is_result;

	int font_handle;

	int end_img;
	int end_count;
	int end_frame_cnt;

public:
	TitleScene();
	virtual ~TitleScene();

public:
	virtual void Initialize()override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() override;
	virtual void Finalize()override;
	virtual void SelectCursor();

public:
	virtual const eSceneType GetNowSceneType()const override
	{
		return eSceneType::eTitle;
	}
};

