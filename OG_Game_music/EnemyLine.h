#pragma once
#include "Vec2.h"
#include "Rect.h"

class EnemyLine
{
public:
	EnemyLine();
	~EnemyLine();

	void Start();
	void Update();
	void Draw();

	//“–‚½‚è”»’è‚ğæ“¾‚·‚é
	Rect GetColRect() const { return colRect; }

	//‘¶İ‚µ‚Ä‚¢‚é‚©
	bool isExist() const { return m_isExist; }

private:
	Vec2 startPos;
	Vec2 endPos;

	Vec2 startColPos;
	Vec2 endColPos;
	
	Rect colRect;

	int frame;

	bool m_isExist;
};

