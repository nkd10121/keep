#include "Enemy.h"
#include "DxLib.h"
#include "../Util/Game.h"

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
	m_pos.x = m_pos.x;
	m_pos.y = m_pos.y;
}

void Enemy::Update()
{
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth * 2, kHeight * 2);
}

void Enemy::Draw()
{
	DrawBox(static_cast<int>(m_pos.x - kWidth), static_cast<int>(m_pos.y - kHeight), static_cast<int>(m_pos.x + kWidth), static_cast<int>(m_pos.y + kHeight), m_color, true);
}
