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

	//“G‚Ì“–‚½‚è”»’è‚ðŽæ“¾‚·‚é
	Col GetColRect() const { return m_colRect; }

	void SetColor(unsigned int color) { m_color = color; }
private:

	Vec2 m_pos;

	Col m_colRect;

	unsigned int m_color;
};