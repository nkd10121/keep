#pragma once
#include "EnemyBase.h"
#include <memory>

class Player;
class EnemyNormal : public EnemyBase
{
public:
	EnemyNormal(std::shared_ptr<Player> pPlayer);
	virtual ~EnemyNormal();

	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;

};

