#pragma once
#include"FloorBase.h"
class Floor : public FloorBase
{
private:
	bool landing_flg; // 着地したことがあるか否か

	Floor();
	~Floor()
	{

	}

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	void TimeCountUp();  // 制限時間を増やす

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

};

