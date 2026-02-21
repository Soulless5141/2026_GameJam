#include "Player.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"
#include "../../Source/Input/InputManager.h"
#include"../../Utility/PadInputManager.h"

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

    image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_right.png");


	//当たり判定の設定
	collision.hit_object_type.push_back(eObjectType::eFloor);
	collision.hit_object_type.push_back(eObjectType::eGoal);

	location = Vector2D(320.0f, 400.0f);
	velocity = 0.0f;
}

void Player::Update(float delta_second)
{
    InputManager* input = InputManager::GetInstance();

    bool isGround = (location.y >= 400.0f);

    // ★ 押した瞬間だけ右ジャンプ
    if (input->GetKeyState(KEY_INPUT_RIGHT) == eInputState::ePressed)
    {
        g_velocity = 0.0f;
        velocity.x = 200.0f;
        velocity.y = -600.0f;
    }
    //★ 押した瞬間だけ左ジャンプ
    if (input->GetKeyState(KEY_INPUT_LEFT) == eInputState::ePressed && isGround)
    {
        g_velocity = 0.0f;
        velocity.x = -200.0;
        velocity.y = -600.0f;
    }

    PadInputManager* pad = PadInputManager::GetInstance();

    if (pad->GetKeyInputState(XINPUT_BUTTON_RIGHT_SHOULDER) == eInputState::ePressed)
    {
        g_velocity = 0.0f;
        velocity.x = 200.0f;
        velocity.y = -600.0f;
    }

    if (pad->GetKeyInputState(XINPUT_BUTTON_LEFT_SHOULDER) == eInputState::ePressed)
    {
        g_velocity = 0.0f;
        velocity.x = -200.0;
        velocity.y = -600.0f;
    }

    // 重力
    g_velocity += D_GRAVITY * delta_second;
    velocity.y += g_velocity * delta_second;

    location += velocity * delta_second;

    if (location.y > 400.0f)
    {
        location.y = 400.0f;
        velocity.y = 0.0f;
        g_velocity = 0.0f;
    }




    // 押している間チャージ
    if (input->GetKeyState(KEY_INPUT_X) == eInputState::ePressed && isGround)
    {
        charge_Time += delta_second;

        if (charge_Time >= 3.0f)
        {
            velocity.y = -900.0f;
            charge_Time = 0.0f;
        }
    }
    else
    {
        // 離した瞬間ジャンプ
        if (charge_Time > 0.0f)
        {
            if (charge_Time < 1.0f)
                velocity.y = -700.0f;
            else if (charge_Time < 2.0f)
                velocity.y = -800.0f;
            else
                velocity.y = -900.0f;

            charge_Time = 0.0f;
        }
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

