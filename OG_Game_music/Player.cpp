#include "Player.h"
#include "DxLib.h"

namespace
{
	//移動速度
	constexpr float kSpeed = 4.0f;
	constexpr float kDashSpeed = 12.0f;

	//キャラクターのサイズ
	constexpr int kWidth = 8;
	constexpr int kHeight = 8;

}

Player::Player():
	m_pos(15,15)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{

	//padの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	bool isMove = false;	//移動しているかどうか
	bool isLogMove = false;

	//Wキー
	if ((pad & PAD_INPUT_8) != 0)
	{
		//スペースキーを押したときダッシュ
		if ((pad & PAD_INPUT_10) != 0)
		{
			move.y -= kDashSpeed;
		}
		else
		{
			move.y -= kSpeed;
		}
		//m_dir = kDirUp;
		isMove = true;
	}

	//Sキー
	if ((pad & PAD_INPUT_5) != 0)
	{

		move.y += kSpeed;
		//m_dir = kDirDown;
		isMove = true;
	}

	//Aキー
	if ((pad & PAD_INPUT_4) != 0)
	{
		//m_pos.x -= kSpeed;
		move.x -= kSpeed;
		//m_dir = kDirLeft;
		isMove = true;
	}

	//Dキー
	if ((pad & PAD_INPUT_6) != 0)
	{
		//m_pos.x += kSpeed;
		move.x += kSpeed;
		//m_dir = kDirRight;
		isMove = true;
	}

	//止まった時、本家みたいに動かしたい
	if (!(isMove) && isLogMove)
	{

	}

	isLogMove = isMove;

	//斜め移動の場合も同じ速さで移動するようにする

	//ベクトルの正規化
	move.normalize();

	//ベクトルの長さをkspeedにする
	move *= kSpeed;

	//座標とベクトルの足し算
	m_pos += move;

}

void Player::Draw()
{
	DrawBox(0, 0, 640, 640, GetColor(8, 4, 8), true);
	DrawBoxAA(m_pos.x - kWidth, m_pos.y - kHeight, m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 255, 0), true);
}
