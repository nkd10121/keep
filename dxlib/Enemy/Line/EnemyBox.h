#pragma once
#include "EnemyLineBase.h"
class EnemyBox : public EnemyLineBase
{
public:
	EnemyBox();
	~EnemyBox();

	void Start(Vec2 pos, int size, int speed, int firstFrame, int secondFrame,bool isPre)override;
	void Update()override;
	void Draw()override;

private:
	Vec2 m_pos{};
	int sizeMax = 0;
	int size = 0;
	int m_speed = 0;
	unsigned int color = 0xff00ff;

	bool m_isMax = false;
	bool m_isDrawPre = true;
};

