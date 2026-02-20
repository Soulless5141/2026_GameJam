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

void FloorBase::OnHitCollision(GameObject* object)
{
	player->velocity.x = 0;
}