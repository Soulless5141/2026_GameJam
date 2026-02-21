#include "Player.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"
#include "../../Source/Input/InputManager.h"
#include"../../Utility/PadInputManager.h"

#include <math.h>
#include <iostream>

//重力
#define D_GRAVITY (50.0f)
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

    bool isGround = (location.y >= 400.0f);
    PadInputManager* pad = PadInputManager::GetInstance();
   


    if (pad->GetKeyInputState(XINPUT_BUTTON_RIGHT_SHOULDER) == eInputState::ePressed)
    {
        jump_direction = 1;
    }

    if (pad->GetKeyInputState(XINPUT_BUTTON_LEFT_SHOULDER) == eInputState::ePressed)
    {
        jump_direction = -1;
    }

    // 押している間チャージ
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::ePressed)
    {
        charge_Time += delta_second;

        if (charge_Time > charge_Time_max)
        {
            charge_Time = charge_Time_max;
        }
    }
    //離したら飛ぶ
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::eReleased && isGround)
    {
        g_velocity = 0.0f;

        float minJump = -100.0f;   // 最小ジャンプ力
        float maxJump = -300.0f;  // 最大ジャンプ力

        float powerRate = charge_Time / charge_Time_max;  // 0.0～1.0

        float jumpPower = minJump + (maxJump - minJump) * powerRate;

        velocity.y = jumpPower;
        velocity.x = 300.0f * jump_direction;

        charge_Time = 0.0f;
    }

    // 重力
    velocity.y += D_GRAVITY * delta_second;

    // 空中なら横減速
    if (!isGround)
    {
        velocity.x *= 0.90f;
    }

    location += velocity * delta_second;
    location += velocity * delta_second;
    

    if (location.y > 400.0f)
    {
        location.y = 400.0f;
        velocity.y = 0.0f;
        g_velocity = 0.0f;
    }



}
void Player::Draw(const Vector2D& screen_ofset)const
{
    //image(縮小表示)
    int imageW, imageH;
    GetGraphSize(image, &imageW, &imageH);

    int smallW = imageW / 20;
    int smallH = imageH / 20;

    DrawExtendGraph(
        location.x - smallW / 2,
        location.y - smallH / 2,
        location.x + smallW / 2,
        location.y + smallH / 2,
        image,
        TRUE
    );

    /*__super::Draw(screen_ofset);*/
}
void Player::Finalize()
{
}


