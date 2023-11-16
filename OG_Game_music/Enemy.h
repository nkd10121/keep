#pragma once
#include "Vec2.h"
#include "Rect.h"  

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw();

	//�G�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

	void SetColor(unsigned int color) { m_color = color; }
private:

	Vec2 m_pos;

	Rect m_colRect;

	unsigned int m_color;
};