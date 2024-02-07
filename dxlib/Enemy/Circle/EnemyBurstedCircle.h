//#pragma once
//#include "EnemyCircleBase.h"
//class EnemyBurstedCircle :	public EnemyCircleBase
//{
//public:
//	EnemyBurstedCircle();
//	~EnemyBurstedCircle();
//
//	void Start(Vec2 pos,Vec2 vec);
//	void Update();
//	void Draw();
//
//private:
//	Vec2 m_vec;
//
//};

#include "../Line/EnemyLineBase.h"
#include "DxLib.h"

class EnemyBurstedCircle : public EnemyLineBase
{
	public:
	EnemyBurstedCircle();
	~EnemyBurstedCircle();

	void Start(Vec2 pos,Vec2 vec);
	void Update();
	void Draw();

private:
	Vec2 m_vec;
	Vec2 m_pos;

};