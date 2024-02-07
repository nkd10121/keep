#pragma once
#include "EnemyCircleBase.h"
class EnemyCircleScaling : public EnemyCircleBase
{
public:
	EnemyCircleScaling();
	~EnemyCircleScaling();

	void Start(Vec2 pos, int rad,int wait,int draw,int speed)override;
	void Update();
	void Draw();
private:
	int m_frame;
	float m_angle;
	Vec2 m_offset;

	Vec2 m_center;
	
	int m_waitFrame;
	int m_drawFrame;

	int m_radius;
	int m_mainCircleRadius;

	int m_radiusSmallSpeed = 0;

	unsigned int m_defaultColor;
	unsigned int m_addColor;
};

