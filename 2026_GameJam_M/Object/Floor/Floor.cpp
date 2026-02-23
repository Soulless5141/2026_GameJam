#include "Floor.h"
#include "DxLib.h"

void Floor::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::Get();
	image = rm->GetImages("Resource/Image/2026_Gamejam_sozai/Ekurea2.png", 1, 1, 1, 300, 136)[0];

	collision.box_size.x = 300.0f;
	collision.box_size.y = 136.0f;
	collision.is_blocking = true;
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

void Floor::Update(float delta)
{
	// 床の更新処理を書く
}


void Floor::TimeCountUp()
{

}
