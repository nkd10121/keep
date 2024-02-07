#pragma once
#include "../Util/Vec2.h"
#include "../Util/Col.h"  

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw();

	//敵の当たり判定を取得する
	Col GetColRect() const { return m_colRect; }

	void SetColor(unsigned int color) { m_color = color; }
private:

	Vec2 m_pos;

	Col m_colRect;

	unsigned int m_color;
};