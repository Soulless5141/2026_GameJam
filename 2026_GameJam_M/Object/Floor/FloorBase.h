#pragma once
#include "../GameObject.h"
#include "../Player/Player.h"

class FloorBase : public GameObject
{
public:
	class Player* player;

public:
	FloorBase();
	~FloorBase();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void OnHitCollision(GameObject*) override;

};

