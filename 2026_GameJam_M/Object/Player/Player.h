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

	Vector2D velocity;		//移動量
	Vector2D box_size;		//矩形
	float g_velocity;		//重力速度
	float Time;				//タイム
	int jump_up;			//ジャンプ力
	int jump_direction = 0;		//ジャンプ方向
	float charge_Time = 0.0f;
	bool isCharging = false;
public:
	Player();
	~Player();
public:
	virtual void Initialize()override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Update(float delta_second) override;
	void Finalize();

	Vector2D& GetLocation();

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	/*virtual void OnHitCollision(GameObject* hit_object) override;*/

};

