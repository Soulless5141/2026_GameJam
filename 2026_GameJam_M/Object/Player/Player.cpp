#include "Player.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"

#include <math.h>
#include <iostream>

//重力
#define D_GRAVITY (200)
#define jamp_Max_pawa -600.0f
#define MAX_CHARGE_TIME 1.0f 


Player::Player() :
	location(0.0f), 
	velocity(0.0f),
    box_size(0.0f),
    g_velocity(0.0f)
{

}

Player::~Player()
{

}
void Player::Initialize()
{
    ResourceManager* rm = ResourceManager::Get();
	//アニメーション画像の読み込み
    //jump_animation = rm->GetImages("", 1, 1, 1, 32, 32)[0];       //ジャンプアニメーション
    //Left_save_animetion = rm->GetImages("", 1, 1, 1, 32, 32)[0];        //左チャージアニメーション
    //Right_save_animetion = rm->GetImages("", 1, 1, 1, 32, 32)[0];       //右チャージアニメーション
    //Dead_animetion = rm->GetImages("", 1, 1, 1, 32, 32)[0];         //死亡アニメーション
    //Goal_animetion = rm->GetImages("", 1, 1, 1, 32, 32)[0];            //ゴールアニメーション

	//当たり判定の設定
	collision.hit_object_type.push_back(eObjectType::eFloor);
	collision.hit_object_type.push_back(eObjectType::eGoal);

	location = Vector2D(320.0f, 400.0f);
	velocity = 0.0f;
}

void Player::Update(float delta_second)
{
	//ジャンプ処理


        // ===== 地面にいるか判定 =====
        bool isGround = (location.y >= 400.0f);

        // ===== ジャンプ入力（SPACE） =====
        if (CheckHitKey(KEY_INPUT_SPACE) && isGround)
        {
            g_velocity = 0.0f;          // 重力リセット
            velocity.y = -600.0f;       // ジャンプ初速
        }

        // ===== 重力 =====
        g_velocity += D_GRAVITY * delta_second;
        velocity.y += g_velocity * delta_second;

        // ===== 位置更新 =====
        location += velocity * delta_second;

        // ===== 地面処理 =====
        if (location.y > 400.0f)
        {
            location.y = 400.0f;
            velocity.y = 0.0f;
            g_velocity = 0.0f;
        }
    }
void Player::Draw(const Vector2D& screen_ofset)const
{
    Vector2D tl = location - (box_size * 0.5f);
    Vector2D br = tl + box_size;

    //DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), TRUE);
    __super::Draw(screen_ofset);
}
void Player::Finalize()
{
}

void Player::Movement(float param)
{
	velocity.x += param;
}

void Player::Jumpmovement(float param)
{
	velocity.y = -300.0f;
}

