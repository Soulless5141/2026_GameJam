#pragma once
#include"FloorBase.h"
class Floor : public FloorBase
{
private:
	bool landing_flg; // 着地したことがあるか否か

public:

	Floor() = default;
	virtual ~Floor()
	{

	}

	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta) override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

};

