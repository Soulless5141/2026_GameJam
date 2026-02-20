#pragma once

#include "../../Object/GameObject.h"
#include "../../Utility/Vector2D.h"
#include "../../Source/Scene/SceneBase.h"
#include <vector>

class Player : public GameObject
{
public:
	//アニメーション
	std::vector<int> jump_animation;		//ジャンプアニメーション
	std::vector<int> Left_save_animetion;		//チャージアニメーション
	std::vector<int> Right_save_animetion;		//チャージアニメーション
	std::vector<int> Dead_animetion;		//死亡アニメーション
	std::vector<int> Goal_animetion;		//ゴールアニメーション

	Vector2D location;		//位置座標
	Vector2D velocity;		//移動量
	Vector2D box_size;		//矩形
	float g_velocity;		//重力速度
public:
	Player();
	~Player();
public:
	void Initialize();
	void Update(float delta_second);
	virtual void Draw(const Vector2D& screen_ofset) const;
	void Finalize();
public:
	void Movement(float param);
	void Jumpmovement(float param);

};

