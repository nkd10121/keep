#include "Enemy.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	constexpr int kWidth = 10;
	constexpr int kHeight = 10;

}

Enemy::Enemy() :
	m_pos(Game::kScreenWidth / 2, Game::kScreenHeight / 2)
{

}

Enemy::~Enemy()
{

}

void Enemy::Init()
{
	m_pos.x = static_cast<int>(m_pos.x);
	m_pos.y = static_cast<int>(m_pos.y);
}

void Enemy::Update()
{
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth * 2, kHeight * 2);
}

void Enemy::Draw()
{
	DrawBox(m_pos.x - kWidth,m_pos.y - kHeight, m_pos.x + kWidth, m_pos.y + kHeight, m_color,true);
}
