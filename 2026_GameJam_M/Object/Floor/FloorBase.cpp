#include "FloorBase.h"

FloorBase::FloorBase()
{

}

FloorBase::~FloorBase()
{

}

void FloorBase::Initialize()
{

}

void FloorBase::Update(float delta_second)
{

}

void FloorBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void FloorBase::OnHitCollision(GameObject* object)
{
	player->velocity.x = 0;
}