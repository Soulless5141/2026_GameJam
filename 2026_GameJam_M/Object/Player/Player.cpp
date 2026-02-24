#include "Player.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"
#include "../../Source/Input/InputManager.h"
#include"../../Utility/PadInputManager.h"

#include <math.h>
#include <iostream>

#define MAX_CHARGE_TIME (2.0f)
const float SCREEN_WIDTH = 1920.0f;
const float SCREEN_HEIGHT = 1080.0f; // 参考用（下は落下可）

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

    // 画像読み込み
    landing_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_right.png");
    left_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_left_stop.png");
    right_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_right_stop.png");
    left_jump_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_left.png");
    right_jump_image = LoadGraph("Resource/Image/2026_Gamejam_sozai/Chara_sizi.png");

    jump_se_handle = LoadSoundMem("Resource/Image/2026_Gamejam_sozai/BGM SE/ジャンプ音SE.mp3");      
    landing_se_handle = LoadSoundMem("Resource/Image/2026_Gamejam_sozai/BGM SE/着地音SE.mp3");     

    isGround = true;

    // 当たり判定
    collision.box_size.x = 40.0f;
    collision.box_size.y = 64.0f;
    collision.object_type = eObjectType::ePlayer;
    collision.is_blocking = true;
    collision.hit_object_type.push_back(eObjectType::eFloor);
    collision.hit_object_type.push_back(eObjectType::eGoal);

    velocity = 0.0f;
}

void Player::Update(float delta_second)
{
    PadInputManager* pad = PadInputManager::GetInstance();

    // ===== 方向決定 =====
    if (pad->GetKeyInputState(XINPUT_BUTTON_RIGHT_SHOULDER) == eInputState::eHeld)
        jump_direction = 1;
    else if (pad->GetKeyInputState(XINPUT_BUTTON_LEFT_SHOULDER) == eInputState::eHeld)
        jump_direction = -1;

    // ===== チャージ処理 =====
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::eHeld
        && isGround
        && jump_direction != 0)
    {
        charge_Time += delta_second;
        if (charge_Time > MAX_CHARGE_TIME)
            charge_Time = MAX_CHARGE_TIME;
    }

    // ===== ジャンプ処理 =====
    if (pad->GetKeyInputState(XINPUT_BUTTON_A) == eInputState::eReleased
        && isGround
        && jump_direction != 0)
    {
        float powerRate = charge_Time / MAX_CHARGE_TIME;
        powerRate = powerRate * powerRate / 1.25f;

        float jumpPower = minJump + (maxJump - minJump) * powerRate;
        velocity.y = -jumpPower / 1.3f;

        float movePower = minMove + (maxMove - minMove) * powerRate;
        velocity.x = movePower * jump_direction / 0.5f;

        PlaySoundMem(jump_se_handle, DX_PLAYTYPE_BACK);

        charge_Time = 0.0f;

        isGround = false;
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

    // ===== X方向のみ画面端制御 =====
    float halfWidth = collision.box_size.x * 0.5f;
    if (location.x - halfWidth < 0) {
        location.x = halfWidth;
        velocity.x = 0;
    }
    else if (location.x + halfWidth > SCREEN_WIDTH) {
        location.x = SCREEN_WIDTH - halfWidth;
        velocity.x = 0;
    }

    // ===== 画像切り替え =====
    if (!isGround)
    {
        if (jump_direction == 1)
            image = right_jump_image;
        else if (jump_direction == -1)
            image = left_jump_image;
    }
    else
    {
        if (jump_direction == 1)
            image = right_image;
        else if (jump_direction == -1)
            image = left_image;
        else
            image = landing_image;
    }
}

void Player::Draw(const Vector2D& screen_ofset) const
{
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

    PlaySoundMem(landing_se_handle, DX_PLAYTYPE_BACK);

    float floorTop = hit_object->GetLocation().y;
    location.y = floorTop - collision.box_size.y * 0.8f;
}

void Player::Finalize()
{
    DeleteSoundMem(jump_se_handle);     
    DeleteSoundMem(landing_se_handle);
}

Vector2D& Player::GetLocation()
{
    return this->location;
}
