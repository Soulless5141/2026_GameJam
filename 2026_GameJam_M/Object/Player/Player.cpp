#include "Player.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"
#include "../../Source/Input/InputManager.h"
#include"../../Utility/PadInputManager.h"

#include <math.h>
#include <iostream>

//重力

#define GROUND_Y (400.0f)
#define MAX_CHARGE_TIME (3.0f)



Player::Player() :
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
    bool isGround = (location.y >= GROUND_Y - 0.1f);
    PadInputManager* pad = PadInputManager::GetInstance();

    // ===== 方向決定 =====
    if (pad->GetKeyInputState(XINPUT_BUTTON_RIGHT_SHOULDER) == eInputState::ePressed)
    {
        jump_direction = 1;
    }

    if (pad->GetKeyInputState(XINPUT_BUTTON_LEFT_SHOULDER) == eInputState::ePressed)
    {
        jump_direction = -1;
    }

    // ===== チャージ処理 =====
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::eHeld && isGround)
    {
        charge_Time += delta_second;

        if (charge_Time > MAX_CHARGE_TIME)
            charge_Time = MAX_CHARGE_TIME;
    }

    // ===== 離したらジャンプ =====
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::eReleased && isGround)
    {
        float powerRate = charge_Time / MAX_CHARGE_TIME;

        powerRate = powerRate * powerRate;

        //ジャンプ力の範囲
        float minJump = 400.0f;   // 弱
        float maxJump = 700.0f;  // 強

        
        float jumpPower = minJump + (maxJump - minJump) * powerRate;

        //上方向の速度
        velocity.y = -jumpPower;

        // 横もチャージ比例・横移動の範囲
        float minMove = 200.0f;
        float maxMove = 600.0f;

        float movePower = minMove + (maxMove - minMove) * powerRate;

        velocity.x = movePower * jump_direction;

        charge_Time = 0.0f;
    }

    // ===== 重力（落下少し速く）=====
    if (velocity.y > 0) // 落下中
    {
        velocity.y += D_GRAVITY * 1.3f * delta_second;
    }
    else
    {
        velocity.y += D_GRAVITY * delta_second;
    }

    // ===== 位置更新 =====
    location += velocity * delta_second;

    // ===== 地面判定 =====
    if (location.y > GROUND_Y)
    {
        location.y = GROUND_Y;
        velocity.y = 0.0f;
        velocity.x = 0.0f;  // 着地でピタ止まり
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

Vector2D& Player::GetLocation()
{
    // TODO: return ステートメントをここに挿入します
    return this->location;
}


