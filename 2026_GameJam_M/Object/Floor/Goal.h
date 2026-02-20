#pragma once
#include"FloorBase.h"
class Goal : public FloorBase
{
private:
	bool goal_flg; // ゴールしたか否か

	Goal();
	~Goal()
	{

	}

	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	void TimerStop();

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

};

