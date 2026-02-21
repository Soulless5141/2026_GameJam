#include "Floor.h"

#include "FloorBase.h"


void Floor::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::Get();
	image = rm->GetImages("Resource/Image/2026_Gamejam_sozai/Chara_right.png", 10, 5, 2, 128, 128)[0];

	// 当たり判定の設定

	collision.box_size.x = 32.0f;
	collision.box_size.x = 8.0f;
	collision.object_type = eObjectType::eFloor;
}

void Floor::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Floor::OnHitCollision(GameObject* hit_object)
{
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		if (landing_flg == false)
		{
			landing_flg = true;
			TimeCountUp();
		}
	}
}

void Floor::TimeCountUp()
{

}
