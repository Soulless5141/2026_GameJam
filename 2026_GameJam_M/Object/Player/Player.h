#pragma once

#include "../../Utility/Vector2D.h"

class Player
{
public:
	Vector2D location;		//位置座標
	Vector2D velocity;		//移動量
	Vector2D box_size;		//矩形の大きさ
	float g_velocity;		//重力速度
public:
	Player();
	~Player();
public:
	void Initialize();
	void Update(float delta_second);
	void Draw() const;
	void Finalize();
public:
	void Movement(float param);
	void Jumpmovement(float param);

};

