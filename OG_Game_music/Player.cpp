#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "Application.h"

namespace
{
	//移動速度
	constexpr float kBaseSpeed = 3.0f;
	constexpr float kDashSpeed = 16.0f;

	//キャラクターのサイズ
	constexpr int kWidth = 8;
	constexpr int kHeight = 8;
}

Player::Player() :
	m_pos(15, 15),
	m_colPos(0,0),
	m_padStickX(0),
	m_padStickY(0),
	m_speed(kBaseSpeed),
	m_dashCount(0),
	m_isDash(false),
	m_dashLog(false),
	m_knockBackSpeed(0),
	m_damageDrawFrame(0),
	m_playerInvincibleTime(0)
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();

	ScreenSizeW = size.w;
	ScreenSizeH = size.h;
}

Player::~Player()
{

}

void Player::Init()
{

}

void Player::Update(Input& input)
{
	if (m_damageDrawFrame >= 0)
	{
		m_damageDrawFrame--;
	}
	else
	{
		m_damageDrawFrame = 0;
	}

	if (m_playerInvincibleTime >= 0)
	{
		m_playerInvincibleTime--;
	}
	else
	{
		m_playerInvincibleTime = 0;
	}


	//padの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	//padのスティック情報を取得
	GetJoypadAnalogInput(&m_padStickX, &m_padStickY, DX_INPUT_KEY_PAD1);

#ifdef false
	//Wキー
	//if ((pad & PAD_INPUT_8) != 0)
	if (input.IsPushed("UP"))
	{
		move.y = m_padStickY;
		//move.y += m_speed * (m_padStickY * 0.00002);
	}

	//Sキー
	//if ((pad & PAD_INPUT_5) != 0)
	if (input.IsPushed("DOWN"))
	{
		move.y = m_padStickY;
		//move.y += m_speed * (m_padStickY * 0.00002);
	}

	//Aキー
	//if ((pad & PAD_INPUT_4) != 0)
	if (input.IsPushed("LEFT"))
	{
		move.x -= m_speed;
		//move.x += m_speed * (m_padStickX * 0.00002);
	}

	//Dキー
	//if ((pad & PAD_INPUT_6) != 0)
	if (input.IsPushed("RIGHT"))
	{
		move.x += m_speed;
		//move.x += m_speed * (m_padStickX * 0.00002);
	}
#endif

	////PADでの操作
	m_pos.x += m_speed * (static_cast<float>(m_padStickX) / 700) - m_knockBackSpeed;
	m_pos.y += m_speed * (static_cast<float>(m_padStickY) / 700);

	//ノックバックしたとき
	//ノックバックのスピードをだんだん減らす
	if (m_knockBackSpeed != 0)
	{
		m_knockBackSpeed--;
	}

	//斜め移動の場合も同じ速さで移動するようにする
	//ベクトルの正規化
	move.normalize();

	//ベクトルの長さをkspeedにする
	move *= kBaseSpeed;

	//座標とベクトルの足し算
	m_pos += move;

	//画面外に出ないように
	if (m_pos.x + kWidth >= ScreenSizeW)
	{
		m_pos.x = ScreenSizeW - kWidth;
	}
	if (m_pos.x - kWidth <= 0)
	{
		m_pos.x = 0 + kWidth;
	}
	if (m_pos.y - kHeight <= 0)
	{
		m_pos.y = 0 + kHeight;
	}
	if (m_pos.y + kHeight >= ScreenSizeH)
	{
		m_pos.y = ScreenSizeH - kHeight;
	}


	//ダッシュ
	//押している間カウントを増やし続けて
	//押した瞬間だけダッシュし、離してもう一回押すとダッシュするように
	if(input.IsPushed("dash"))
	{
		m_dashCount++;
	}
	else
	{
		m_dashCount = 0;
	}
	//押した瞬間ダッシュ
	if (m_dashCount == 1 && !m_isDash)
	{
		m_speed = kDashSpeed;
		m_isDash = true;
	}
	//スピードを少しずつ元のスピードに
	if (m_speed >= kBaseSpeed)
	{
		m_speed--;
		if (m_speed <= kBaseSpeed)
		{
			m_isDash = false;
		}
	}


	//当たり判定の更新
	//ダッシュしているときかダメージを受けた後の無敵時間の間は当たり判定をなくす
	if (m_isDash  || m_playerInvincibleTime != 0)
	{
		m_colPos = {-30,-30};
	}
	//それ以外の時は当たり判定をつける
	else
	{
		m_colPos = m_pos;
	}

	//当たり判定の設定
	m_colRect.SetCenter(m_colPos.x, m_colPos.y, kWidth * 2, kHeight * 2);
}

void Player::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, GetColor(255, 255, 255), "X方向の入力 : %d", m_padStickX);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Y方向の入力 : %d", m_padStickY);

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "m_speed : %f", m_speed);
	DrawFormatString(0, 32, GetColor(255, 255, 255), "Xpos : %f", m_pos.x);
	DrawFormatString(0, 48, GetColor(255, 255, 255), "Ypos : %f", m_pos.y);

	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif

	//プレイヤーの枠
	DrawBox(m_pos.x - kWidth, m_pos.y - kHeight, m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 255, 0), false);

	//ダメージを受けたとき点滅するように
	if (m_damageDrawFrame % 6 >= 4)
	{
		DrawBox(m_pos.x - kWidth, (m_pos.y - kHeight) + (m_playerInvincibleTime / 11.25), m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 128, 0), true);
		return;
	}

	//プレイヤーの表示
	DrawBox(m_pos.x - kWidth, (m_pos.y - kHeight) + (m_playerInvincibleTime / 11.25), m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 255, 0), true);

}

void Player::HitEnemy()
{
	int count = 180;
	count--;

	//ノックバックスピードを与える
	m_knockBackSpeed = 20;

	m_damageDrawFrame = 180;
	m_playerInvincibleTime = 180;
}
