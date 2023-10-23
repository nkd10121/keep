#pragma once
#include "Vec2.h"

class Player;
class Enemy;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();

	void Update();
	void Draw();

private:
	Player* player;
	Enemy* enemy;
};

