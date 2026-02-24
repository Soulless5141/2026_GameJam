#include "Goal.h"


void Goal::Initialize()
{
	goal_flg = false;

	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::Get();
	image = rm->GetImages("Resource/Image/2026_Gamejam_sozai/GoalImage.png", 1, 1, 1, 300, 253)[0];

	// 当たり判定の設定

	collision.box_size = 100.0f;
	collision.object_type = eObjectType::eGoal;
}

void Goal::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Goal::TimerStop()
{
	
}

void Goal::OnHitCollision(GameObject* hit_object)
{
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		if (goal_flg == false)
		{
			goal_flg = true;
			// ゴールした時の処理を書く

		}
	}
}
