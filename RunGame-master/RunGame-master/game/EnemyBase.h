#pragma once
#include "Vec2.h"
#include <memory>

class Player;
class EnemyBase
{
public:
	EnemyBase(std::shared_ptr<Player> pPlayer);
	virtual ~EnemyBase() {}

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

protected:
	std::shared_ptr<Player>	m_pPlayer;

	Vec2	m_pos;
	Vec2	m_vec;
};

