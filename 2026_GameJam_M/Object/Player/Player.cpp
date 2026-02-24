#include "Player.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"
#include "../../Source/Input/InputManager.h"
#include"../../Utility/PadInputManager.h"

#include <math.h>
#include <iostream>

//重力

//#define GROUND_Y (650.0f)
#define MAX_CHARGE_TIME (2.0f)



Player::Player() :
    velocity(0.0f),
    box_size(0.0f),
    g_velocity(0.0f),
    isGoal(false)
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
    landing_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_right.png");
    left_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_left_stop.png");
    right_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_right_stop.png");
    left_jump_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_left.png");
    right_jump_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_sizi.png");

    isGround = true;

    //当たり判定の設定
    collision.box_size.x = 40.0f;
    collision.box_size.y = 64.0f;
    collision.object_type = eObjectType::ePlayer;
    collision.is_blocking = true;
    //ここまで追加
    collision.hit_object_type.push_back(eObjectType::eFloor);
    collision.hit_object_type.push_back(eObjectType::eGoal);

    location = Vector2D(600.0f, 400.0f);
    velocity = 0.0f;

    //リスポーン初期位置保存　追加
    respawnPosition = location;
}

void Player::Update(float delta_second)
{
    PadInputManager* pad = PadInputManager::GetInstance();

    // ===== 方向決定（左右キーで更新） =====
    if (pad->GetKeyInputState(XINPUT_BUTTON_RIGHT_SHOULDER) == eInputState::eHeld)
        jump_direction = 1;
    else if (pad->GetKeyInputState(XINPUT_BUTTON_LEFT_SHOULDER) == eInputState::eHeld)
        jump_direction = -1;

    // ===== チャージ処理 =====
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::eHeld
        && isGround
        && jump_direction != 0)   // 方向が決まっている場合のみ溜める
    {
        charge_Time += delta_second;
        if (charge_Time > MAX_CHARGE_TIME)
            charge_Time = MAX_CHARGE_TIME;
    }

    // ===== ジャンプ処理 =====
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::eReleased
        && isGround
        && jump_direction != 0)   // 方向が決まっている場合のみジャンプ
    {
        float powerRate = charge_Time / MAX_CHARGE_TIME;
        powerRate = powerRate * powerRate / 1.25f;

        float jumpPower = minJump + (maxJump - minJump) * powerRate;
        velocity.y = -jumpPower / 1.25f;

        float movePower = minMove + (maxMove - minMove) * powerRate;
        velocity.x = movePower * jump_direction / 1.25f;

        charge_Time = 0.0f;

        isGround = false; // 空中状態に
    }

    // ===== 重力 =====
    float gravityUp = D_GRAVITY * 0.7f;
    float gravityDown = D_GRAVITY * 1.5f;
    velocity.y += (velocity.y < 0 ? gravityUp : gravityDown) * delta_second;

    // 落下速度上限
    float maxFallSpeed = 1000.0f;
    if (velocity.y > maxFallSpeed)
        velocity.y = maxFallSpeed;

    // ===== 位置更新 =====
    location += velocity * delta_second;

    // ===== 衝突判定は OnHitCollision に任せる =====
    collision.pivot = location;

    // ===== 画像切り替え =====
    if (!isGround) // 空中
    {
        if (jump_direction == 1)
            image = right_jump_image;
        else if (jump_direction == -1)
            image = left_jump_image;
    }
    else // 着地
    {
        if (jump_direction == 1)          // 右向き停止
            image = right_image;
        else if (jump_direction == -1)    // 左向き停止
            image = left_image;
        else                              // jump_direction が 0 の場合
            image = landing_image;       // デフォルト右向き
    }
}

void Player::Draw(const Vector2D& screen_ofset)const
{
    //image(縮小表示)
    int imageW, imageH;
    GetGraphSize(image, &imageW, &imageH);

    int smallW = imageW / 40;
    int smallH = imageH / 40;

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

void Player::OnHitCollision(GameObject* hit_object)
{
    if (hit_object->GetCollision().object_type == eObjectType::eGoal)
    {
        isGoal = true;
    }

    if (hit_object->GetCollision().object_type != eObjectType::eFloor)
        return;

    // 落下中だけ着地判定
    if (velocity.y <= 0)
        return;
    isGround = true;
    velocity.y = 0;
    velocity.x = 0;
    jump_direction = 0;

    // Floor の location を「左上」とみなす場合
    float floorTop = hit_object->GetLocation().y;

    // Player の location は「中心」なので、
    // 中心Y = 床の上端 - 自分の高さの半分
    location.y = floorTop - collision.box_size.y * 0.8f;


}
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