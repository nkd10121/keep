#pragma once
#include "Util/Vec2.h"
#include "Util/Col.h"
#include "DrawRotationCirlce.h"

class Goal
{
public:
	Goal();
	~Goal();

	void Start();
	void Update();
	void Draw();

	void DrawQuilateralTriangle(Vec2 centerPos, int sideLength, unsigned int color);

	void Hit();

	Col GetColRect() const { return m_colRect; }

	/// <summary>
	/// ��ʓ��ɑ��݂��邩�̃t���O��Ԃ�
	/// </summary>
	/// <returns>���݂��Ă��邩�t���O</returns>
	bool isExist() const { return m_isExist; }
private:
	int frame;

	int handle = 0;

	Vec2 center;
	Col m_colRect;
	bool m_isExist;

	DrawRotationCirlce inSide;
	DrawRotationCirlce outSide;
};