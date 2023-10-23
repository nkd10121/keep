#include "Player.h"
#include "DxLib.h"

namespace
{
	//移動速度
	constexpr float kSpeed = 5.0f;
	constexpr float kDashSpeed = 12.0f;

	//キャラクターのサイズ
	constexpr int kWidth = 8;
	constexpr int kHeight = 8;

	//画面サイズ
	constexpr int kScreenWidth = 640;
	constexpr int kScreenHeight = 480;

}

Player::Player():
	m_pos(15,15),
	posX(0),
	posY(0),
	speed(5.0f),
	count(0),
	dashFlag(false),
	dashLog(false)
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

	////Wキー
	////if ((pad & PAD_INPUT_8) != 0)
	//if ((pad & PAD_INPUT_UP) != 0)
	//{
	//	//スペースキーを押したときダッシュ
	//	if ((pad & PAD_INPUT_10) != 0)
	//	{
	//		move.y -= kDashSpeed;
	//	}
	//	else
	//	{
	//		move.y -= kSpeed;
	//	}
	//	//m_dir = kDirUp;
	//	isMove = true;
	//}

	////Sキー
	////if ((pad & PAD_INPUT_5) != 0)
	//if ((pad & PAD_INPUT_DOWN) != 0)
	//{

	//	move.y += kSpeed;
	//	//m_dir = kDirDown;
	//	isMove = true;
	//}

	////Aキー
	////if ((pad & PAD_INPUT_4) != 0)
	//if ((pad & PAD_INPUT_LEFT) != 0)
	//{
	//	//m_pos.x -= kSpeed;
	//	move.x -= kSpeed;
	//	//m_dir = kDirLeft;
	//	isMove = true;
	//}

	////Dキー
	////if ((pad & PAD_INPUT_6) != 0)
	//if ((pad & PAD_INPUT_RIGHT) != 0)
	//{
	//	//m_pos.x += kSpeed;
	//	move.x += kSpeed;
	//	//m_dir = kDirRight;
	//	isMove = true;
	//}

	//PADでの操作
	GetJoypadAnalogInput(&posX, &posY, DX_INPUT_KEY_PAD1);
	m_pos.x += speed * (static_cast<float>(posX) / 700);
	m_pos.y += speed * (static_cast<float>(posY) / 700);

	//ダッシュ
	//押している間カウントを増やし続けて
	//押した瞬間だけダッシュし、離してもう一回押すとダッシュするように
	if ((pad & PAD_INPUT_1) != 0)
	{
		count++;
	}
	else
	{
		count = 0;
	}
	//押した瞬間ダッシュ
	if (count == 1 && !dashFlag)
	{
		speed = 20.0f;
		dashFlag = true;
	}
	//スピードを少しづつ元のスピードに
	if (speed >= kSpeed)
	{
		speed--;
		if (speed == kSpeed)
		{
			dashFlag = false;
		}
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




	//画面外に出ないように
	if (m_pos.x + kWidth >= kScreenWidth)
	{
		m_pos.x = 640 - kWidth;
	}
	if (m_pos.x - kWidth <= 0)
	{
		m_pos.x = 0 + kWidth;
	}
	if (m_pos.y - kHeight <= 0)
	{
		m_pos.y = 0 + kHeight;
	}
	if (m_pos.y + kHeight >= kScreenHeight)
	{
		m_pos.y = 480 - kHeight;
	}

	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth * 2, kHeight * 2);

}

void Player::Draw()
{

	DrawBox(m_pos.x - kWidth, m_pos.y - kHeight, m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 255, 0), true);
	//DrawCircle(m_pos.x, m_pos.y, 10, GetColor(255, 255, 255), true);

#ifdef _DEBUG
	DrawFormatString(0,0,GetColor(255,255,255),"X方向の入力 : %d",posX);
	DrawFormatString(0,16,GetColor(255,255,255),"Y方向の入力 : %d",posY);
	DrawFormatString(0,32,GetColor(255,255,255),"Xpos : %f",m_pos.x);
	DrawFormatString(0,48,GetColor(255,255,255),"Ypos : %f",m_pos.y);

	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}
