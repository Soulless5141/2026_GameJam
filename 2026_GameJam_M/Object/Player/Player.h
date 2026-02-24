#pragma once

#include "../../Object/GameObject.h"
#include "../../Utility/Vector2D.h"
#include "../../Source/Scene/SceneBase.h"
#include <vector>

class Player : public GameObject
{
public:
	Vector2D velocity;		//移動量
	Vector2D box_size;		//矩形
	float g_velocity;		//重力速度
	float Time;				//タイム
	int jump_up;			//ジャンプ力
	int jump_direction = 0;		//ジャンプ方向
	float charge_Time = 0.0f;
	bool isCharging = false;
	float minJump = 400.0f;//ジャンプ最小
	float maxJump = 700.0f;//ジャンプ最大
	float minMove = 50.0f;
	float maxMove = 150.0f;
	//元のisGround
	bool isGround;

	//リスポーン 追加
	Vector2D respawnPosition;
	bool requestRespawn = false;

private:
	/*bool isGround = false;*/
	//画像
	int left_image;
	int right_image;
	int left_jump_image;
	int right_jump_image;

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
	virtual void OnHitCollision(GameObject* hit_object) override;

	////リスポーン関数　追加
	//void Respawn();
	//void RequestRespawn();
};

