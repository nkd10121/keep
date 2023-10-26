#include "Enemy.h"
#include "DxLib.h"

namespace
{
	constexpr int kWidth = 10;
	constexpr int kHeight = 10;

	//画面サイズ
	constexpr int kScreenWidth = 640;
	constexpr int kScreenHeight = 480;
}

Enemy::Enemy():
	m_pos(kScreenWidth / 2, kScreenHeight / 2),
	m_color(0)
{

}

Enemy::~Enemy()
{

}

void Enemy::Init()
{

}

void Enemy::Update()
{
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth * 2, kHeight * 2);

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
}

void Enemy::Draw()
{
	DrawBox(m_pos.x - kWidth,m_pos.y - kHeight, m_pos.x + kWidth, m_pos.y + kHeight,GetColor(255,255,255),true);
}
