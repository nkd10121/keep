#pragma once
#include "EnemyCircleBase.h"

class EnemyCircle : public EnemyCircleBase
{
public:
	EnemyCircle();
	~EnemyCircle();

	virtual void Start(float pos, int radius, bool isSmooth)override;
	virtual void Update()override;
	virtual void Draw()override;

private:
	Vec2 m_dir = {};

	int m_rad;

	bool m_isSmooth;

	float m_angle;
	int m_diagonal;

	float efectCirclePos = 0;
	int effectCircleRad;
};

