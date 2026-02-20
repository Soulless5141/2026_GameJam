#pragma once
enum class ePlayerState : unsigned char
{
	eIdle,      // 待機中
	eCharge,    // チャージ中
	eJumping,   // 飛んでいる途中
	evoid,      // 落ちて戻ってくる
	eGoal       // ゴールしたとき
};