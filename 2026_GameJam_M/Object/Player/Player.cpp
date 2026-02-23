#include "Player.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"
#include "../../Source/Input/InputManager.h"
#include"../../Utility/PadInputManager.h"

#include <math.h>
#include <iostream>

//重力

#define GROUND_Y (400.0f)
#define MAX_CHARGE_TIME (2.0f)



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

    //画像　追加
    image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_right.png");
    left_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_left_stop.png");
    right_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_right_stop.png");
    left_jump_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_left.png");
    right_jump_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_sizi.png");



    //当たり判定の設定
    collision.box_size.x = 32.0f;
    collision.box_size.y = 64.0f;
    collision.object_type = eObjectType::ePlayer;
    //ここまで追加
    collision.hit_object_type.push_back(eObjectType::eFloor);
    collision.hit_object_type.push_back(eObjectType::eGoal);

    location = Vector2D(320.0f, 400.0f);
    velocity = 0.0f;

    //リスポーン初期位置保存　追加
    respawnPosition = location;
}

void Player::Update(float delta_second)
{
    //元のisGround
    bool isGround = (location.y >= GROUND_Y);
    //新　IsGround　追加
    /*isGround = false;*/
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

    // チャージ処理
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::eHeld
        && isGround
        && jump_direction != 0)   // 方向が決まっている場合のみ溜める
    {
        charge_Time += delta_second;
        if (charge_Time > MAX_CHARGE_TIME)
            charge_Time = MAX_CHARGE_TIME;
    }

    // 離したらジャンプ
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::eReleased
        && isGround
        && jump_direction != 0)   // 方向が決まっている場合のみジャンプ
    {
        float powerRate = charge_Time / MAX_CHARGE_TIME;
        powerRate = powerRate * powerRate;

        float jumpPower = minJump + (maxJump - minJump) * powerRate;
        velocity.y = -jumpPower;

        float movePower = minMove + (maxMove - minMove) * powerRate;
        velocity.x = movePower * jump_direction;

        charge_Time = 0.0f;
    }



    // ===== 重力（落下少し速く）=====
    //追加
    float gravityUp = D_GRAVITY * 0.7f;         //上昇中は軽く
    float gravityDown = D_GRAVITY * 1.5f;       //落下は早く
    if (velocity.y < 0) //上昇中
    {
        velocity.y += gravityUp * delta_second;
    }
    else //落下中
    {
        velocity.y += gravityDown * delta_second;
    }

    //落下速度にぢょうげんをつける　追加
    float maxFallSpeed = 1000;
    if (velocity.y > maxFallSpeed)
    {
        velocity.y = maxFallSpeed;
    }

    //元の落下処理
    //if (velocity.y > 0) // 落下中
    //{
    //    velocity.y += D_GRAVITY * 1.3f * delta_second;
    //}
    //else
    //{
    //    velocity.y += D_GRAVITY * delta_second;
    //}

    // ===== 位置更新 =====
    location += velocity * delta_second;

    //  画像切り替え 　追加
    if (location.y < GROUND_Y) // 空中
    {
        if (jump_direction == 1)
            image = right_jump_image;
        else if (jump_direction == -1)
            image = left_jump_image;
    }
    else // 地面
    {
        if (jump_direction == 1)
            image = right_image;
        else if (jump_direction == -1)
            image = left_image;
    }


    // ===== 地面判定 =====
    if (location.y > GROUND_Y)
    {
        location.y = GROUND_Y;
        velocity.y = 0.0f;
        velocity.x = 0.0f;  // 着地でピタ止まり


    }

    collision.pivot = location;
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

//当たり判定処理　追加
//void Player::OnHitCollision(GameObject* hit_object)
//{
//    if (hit_object->GetCollision().object_type == eObjectType::eFloor)
//    {
//        if (velocity.y > 0)//落下中だけ
//        {
//            isGround = true;
//            velocity.y = 0;
//            velocity.x = 0;
//
//            float floorTop = hit_object->GetCollision().pivot.y - hit_object->GetCollision().box_size.y / 2;
//
//            location.y = floorTop - collision.box_size.y / 2;
//        }
//    }
//}
//
////リスポーン　追加
//void Player::Respawn()
//{
//    location = respawnPosition;
//    velocity = Vector2D(0, 0);
//    requestRespawn = false;
//}
//
////フラグだけ耐えtる処理　追加
//void Player::RequestRespawn()
//{
//    requestRespawn = true;
//}





//InGameのリスポーン処理で書くこと
//衝突チェック
//if (IsCheckCollision(player->GetCollision(), floor->GetCollision()))
//{
//    player->OnHitCollision(floor);
//}