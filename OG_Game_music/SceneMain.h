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

	unsigned int  GetMyColor(unsigned int Color) { return Color = color; }

private:
	Player* player;
	Enemy* enemy;

	unsigned int color;
};

